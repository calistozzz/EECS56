/*
@Author: Zitong Zhang
@Date: Oct. 21 2020
@Homework: EECS560 lab8



*/

#include <typeinfo>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <exception>

using namespace std;
template <typename Comparable>
class myLeftistHeap
{
public:
    myLeftistHeap()
    {
        root = nullptr;
    }
    myLeftistHeap(const myLeftistHeap &rhs)
    {
        root = clone(rhs.root);
    }
    myLeftistHeap(myLeftistHeap &&rhs)
    {
        root = move(rhs.root);
    }

    ~myLeftistHeap()
    {
        makeEmpty();
    }

    myLeftistHeap &operator=(const myLeftistHeap &rhs)
    {
        if (this != &rhs)
        {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }
    myLeftistHeap &operator=(myLeftistHeap &&rhs)
    {
        root = move(rhs.root);
        return *this;
    }

    bool isEmpty() const
    {
        return (root == nullptr);
    }
    const Comparable &findMin() const
    {
        if (!isEmpty())
            return root->element;
        else
            throw underflow_error("is Empty!");
    }

    void insert(const Comparable &x)
    {
        root = merge(new LeftistNode{x}, root);
    }
    void insert(Comparable &&x)
    {
        root = move(merge(new LeftistNode{x}, root));
    }
    void deleteMin()
    {
        if (isEmpty())
            ;
        // throw underflow_error("is Empty\n");
        else
        {
            LeftistNode *oldRoot = root;
            root = merge(root->left, root->right);
            delete oldRoot;
        }
    }
    void deleteMin(Comparable &minItem)
    {

        minItem = findMin();
        deleteMin();
        // try
        // {
        // minItem = findMin();
        // deleteMin();
        // }
        // catch(exception& e)
        // {
        //     cout << e.what() << '\n';
        // }
    }
    void makeEmpty()
    {
        while (!isEmpty())
            deleteMin();
    }
    void merge(myLeftistHeap &rhs)
    {
        if (this == &rhs) // Avoid aliasing problems
            return;

        root = merge(root, rhs.root);
        rhs.root = nullptr;
    }
    void printInOrder()
    {
        if (!isEmpty())
            printInOrder1(root);
        else
            cout << "the Three is empty!\n";
    }
    void printLevelOrder()
    {
        if (!isEmpty())
        {
            int Maxlevel = getHeight(root);
            for (int i = 0; i <= Maxlevel; i++)
                printLevelOrder1(root, i);
        }

    }

private:
    struct LeftistNode
    {
        Comparable element;
        LeftistNode *left;
        LeftistNode *right;
        int npl;

        LeftistNode(const Comparable &e, LeftistNode *lt = nullptr,
                    LeftistNode *rt = nullptr, int np = 0)
            : element{e}, left{lt}, right{rt}, npl{np} {}

        LeftistNode(Comparable &&e, LeftistNode *lt = nullptr,
                    LeftistNode *rt = nullptr, int np = 0)
            : element{std::move(e)}, left{lt}, right{rt}, npl{np} {}
    };

    LeftistNode *root;

    LeftistNode *merge(LeftistNode *h1, LeftistNode *h2)
    {

        if (h1 == nullptr)
            return h2;
        if (h2 == nullptr)
            return h1;
        if (h1->element < h2->element)
            return merge1(h1, h2);
        else
            return merge1(h2, h1);
    }
    LeftistNode *merge1(LeftistNode *h1, LeftistNode *h2)
    {
        if (h1->left == nullptr) // Single node
            h1->left = h2;       // Other fields in h1 already accurate
        else
        {
            h1->right = merge(h1->right, h2);
            if (h1->left->npl < h1->right->npl)
                swapChildren(h1);
            h1->npl = h1->right->npl + 1;
        }
        return h1;
    }

    void swapChildren(LeftistNode *t)
    {
        LeftistNode *temp = t->left;
        t->left = t->right;
        t->right = temp;
    }
    void reclaimMemory(LeftistNode *t)
    {
        if (t != NULL)
        {
            reclaimMemory(t->left);
            reclaimMemory(t->right);
            delete t;
        }
    }
    LeftistNode *clone(LeftistNode *t) const
    {
        if (t == NULL)
            return NULL;
        else
            return new LeftistNode(t->element, clone(t->left), clone(t->right), t->npl);
    }
    void printInOrder1(LeftistNode *t)
    {
        if (t != NULL)
        {
            printInOrder1(t->left);
            cout << t->element << endl;
            printInOrder1(t->right);
        }
    }
    void printLevelOrder1(LeftistNode *t, int level)
    {
        //cout<<"print levelorder1111 in\n";
        if (t == NULL)
            return;
        if (level == 1)
            cout << t->element << endl;
        else if (level > 1)
        {
            printLevelOrder1(t->left, level - 1);
            printLevelOrder1(t->right, level - 1);
        }

        //cout<<"print levelorder1111 out\n";

    }
    int getHeight(LeftistNode *t)
    {
        if (t == nullptr)
            return 0;
        else
        {
            int leftHeight = getHeight(t->left);
            int rightHeight = getHeight(t->right);

            if (leftHeight > rightHeight)
                return (leftHeight + 1);
            else
                return (rightHeight + 1);
        }
    }
};