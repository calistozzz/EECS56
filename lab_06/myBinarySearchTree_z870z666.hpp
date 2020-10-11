/*
@Author: Zitong Zhang
@Date: Oct. 10 2020
@Homework: EECS560 lab6



*/

#include <typeinfo>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;
template <typename Comparable>
class myBinarySearchTree
{
public:
    myBinarySearchTree() : root{nullptr}
    {
    }
    myBinarySearchTree(const myBinarySearchTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }
    myBinarySearchTree(myBinarySearchTree &&rhs) : root{nullptr}
    {
        root = move(rhs.root);
    }
    ~myBinarySearchTree()
    {
        makeEmpty();
    }

    const Comparable &findMin() const
    {
        //cout<<"caole4\n";
        return findMin(root)->element;
        //cout<<"coutle5\n";
    }
    const Comparable &findMax() const
    {
        //cout<<"caole6\n";
        return findMax(root)->element;
    }
    bool contains(const Comparable &x) const
    {
        return contains(x, root);
    }
    bool isEmpty() const
    {
        return (root == nullptr);
    }
    void printTree(ostream &out = cout) const;

    void makeEmpty()
    {
        makeEmpty(root);
    }

    void insert(const Comparable &x)
    {
        insert(x, root);
    }
    void insert(Comparable &&x)
    {
        const Comparable &y = move(x);
        insert(y, root);
    }

    void remove(const Comparable &x)
    {
        remove(x, root);
    }
    void printTreeInorder(ostream &out = cout)
    {
        if (isEmpty())
        {
        }
        else
        {
            printTreeInorder(root, out);
        }
    }

    void printTreePreorder(ostream &out = cout) const
    {
        if (isEmpty())
        {
        }
        else
        {
            printTreePreorder(root, out);
        }
    }

    void printTreePostorder(ostream &out = cout) const
    {
        if (isEmpty())
        {
        }
        else
        {
            printTreePostorder(root, out);
        }
    }

    myBinarySearchTree &operator=(const myBinarySearchTree &rhs)
    {
        if (this != &rhs)
        {
            makeEmpty(root);
            root = clone(rhs.root);
        }
        return *this;
    }
    myBinarySearchTree &operator=(myBinarySearchTree &&rhs)
    {
        root = move(rhs.root);
        return *this;
    }

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{theElement}, left{lt}, right{rt} {}

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
            : element{std::move(theElement)}, left{lt}, right{rt} {}
    };

    BinaryNode *root;

    void insert(const Comparable &x, BinaryNode *&t)
    {
        if (t == nullptr)
            t = new BinaryNode{x, nullptr, nullptr};
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
            ; // Duplicate; do nothing
    }
    void insert(Comparable &&x, BinaryNode *&t)
    {
        if (t == nullptr)
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        else if (x < t->element)
            insert(std::move(x), t->left);
        else if (t->element < x)
            insert(std::move(x), t->right);
        else
            ; // Duplicate; do nothing
    }
    void remove(const Comparable &x, BinaryNode *&t)
    {
        if (t == nullptr)
            return; // Item not found; do nothing
        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) // Two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }
    BinaryNode *findMin(BinaryNode *t) const
    {
        //cout<<"----------------caole1----------------------\n";
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }
    BinaryNode *findMax(BinaryNode *t) const
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    void printTreeInorder(BinaryNode *t, ostream &out) const
    {
        //cout<<"caole1\n";
        if (t != nullptr)
        {
            printTreeInorder(t->left, out);
            out << t->element << endl;
            printTreeInorder(t->right, out);
        }
    }

    void printTreePreorder(BinaryNode *t, ostream &out) const
    {
        //cout<<"caole2\n";

        if (t != nullptr)
        {
            out << t->element << endl;
            printTreePreorder(t->left, out);
            printTreePreorder(t->right, out);
        }
    }

    void printTreePostorder(BinaryNode *t, ostream &out) const
    {
        //cout<<"caole3\n";
        if (t != nullptr)
        {
            printTreePostorder(t->left, out);
            printTreePostorder(t->right, out);
            out << t->element << endl;
        }
    }

    bool contains(const Comparable &x, BinaryNode *t) const
    {

        if (t == nullptr)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true; // Match
    }

    void makeEmpty(BinaryNode *&t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    void printTree(BinaryNode *t, ostream &out) const
    {
        if (t != nullptr)
        {
            printTree(t->left, out);
            out << t->element << endl;
            printTree(t->right, out);
        }
    }
    BinaryNode *clone(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
};