/*
@Author: Zitong Zhang
@Date: Oct. 27 2020
@Homework: EECS560 lab9



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
class myDisjointSet
{
public:
    explicit myDisjointSet(int numElements) : s{std::vector<int>(numElements,-1)}
    {}
    int find(int x) const
    {
        if (s[x] < 0)
            return x;
        else
            return find(s[x]);
    }
    int find(int x)
    {
        if (s[x] < 0)
            return x;
        else
            return s[x] = find(s[x]);
    }
    void unionSets(int root1, int root2)
    {
        int m_root1 = find(root1);
        int m_root2 = find(root2);
        if (m_root1 == m_root2)
        {
            return;
        }
        else if (getSetSize(root1) < getSetSize(root2))
        {
            s[m_root2] = s[m_root2] + s[m_root1];
            s[m_root1] = m_root2;
        }
        else
        {
            s[m_root1] = s[m_root1] + s[m_root2];
            s[m_root2] = m_root1;
        }
    }
    void print(int i)
    {
        cout << i << endl;
        if (i != find(i))
            print(s[i]);
    }
    int getNumberElements() const
    {
        return s.size();
    }
    int getSetSize(int i) const
    {
        int Absolute = -s[find(i)];
        return Absolute;
    }

private:
    vector<int> s;
};