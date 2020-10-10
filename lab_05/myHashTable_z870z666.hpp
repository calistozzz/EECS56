#include "myDlList_z870z666.hpp"
#include <typeinfo>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

template <typename HashedObj>
class myHashTable
{
public:
    explicit myHashTable(int size = 101)
    {
        currentSize = 0;
        theLists.resize(101);
        // theLists = nullptr;
    }

    bool contains(const HashedObj &x)
    {
        auto &whichList = theLists[myhash(x)];
        return find(begin(whichList), end(whichList), x) != end(whichList);
    }

    void makeEmpty()
    {
        for (auto &thisList : theLists)
            thisList.clear();
    }

    bool insert(const HashedObj &x)
    {
        auto &whichList = theLists[myhash(x)];
        if (find(begin(whichList), end(whichList), x) != end(whichList))
            return false;
        whichList.push_back(x);

        // Rehash; see Section 5.5
        if (++currentSize > theLists.size())
            rehash();

        return true;
    }

    bool insert(HashedObj &&x)
    {
        const auto &y = move(x);
        auto &whichList = theLists[myhash(x)];
        if (find(begin(whichList), end(whichList), x) != end(whichList))
            return false;
        whichList.push_back(y);

        // Rehash; see Section 5.5
        if (++currentSize > theLists.size())
            rehash();

        return true;
    }

    int nextPrime(int n)
    {
        int zero_time =0;
        bool check = false;
        int thenextPrime = n;
       if(n ==1 || n == 0){
           return 2;
       }
        while (!check){
            thenextPrime++;
            // cout<<thenextPrime<<endl;
            for(int i = 2; i< thenextPrime-1 ;i++){
                if(thenextPrime % i ==0){
                    zero_time++;
                    //cout<<zero_time<<endl;
                }
            }
            if(zero_time ==0){
                return thenextPrime;
                check = true;
            }
            zero_time =0;
        }
    }

    typename myDlList<HashedObj>::iterator getiteratorbegin(int index)
    {
        return theLists[index].begin();
    }

    typename myDlList<HashedObj>::iterator getiteratorend(int index)
    {
        return theLists[index].end();
    }

    int hashsize()
    {
        return theLists.size();
    }
    typename myDlList<HashedObj>::iterator find(typename myDlList<HashedObj>::iterator from, typename myDlList<HashedObj>::iterator to, const HashedObj &x)
    {
        for (auto &a = from; a != to; a++)//(auto x: list)()
            {
                if (a.getItem() == x)
                    return a;
            }
    }

    bool remove(const HashedObj &x)
    {
        auto &whichList = theLists[myhash(x)];
        auto itr = find(begin(whichList), end(whichList), x);

        if (itr == end(whichList))
            return false;

        whichList.erase(itr);
        --currentSize;
        return true;
    }

private:
    vector<myDlList<HashedObj>> theLists; // The array of Lists
    int currentSize;

    void rehash()
    {
        vector<myDlList<HashedObj>> oldLists = theLists;

        // Create new double-sized, empty table
        theLists.resize(nextPrime(2 * theLists.size()));
        for (auto &thisList : theLists)
            thisList.clear();

        // Copy table over
        currentSize = 0;
        for (auto &thisList : oldLists)
            for (auto &x : thisList)
                insert(std::move(x));
    }

    size_t myhash(const HashedObj &x) const
    {
        static hash<HashedObj> hf;
        return hf(x) % theLists.size();
    }

    template <typename hashitem>
    class hash
    {
    public:
        size_t operator()(const std::string &key)
        {
            size_t hashVal = 0;
            for (char ch : key)
                hashVal = 37 * hashVal + ch;
            return hashVal;
        }
        size_t operator()(const int &key)
        {
            size_t hashVal = 0;
            hashVal = 37 * hashVal + key;
            return hashVal;
        }
    };
};