/*
@Author: Zitong Zhang
@Date: Nov. 21 2020
@Homework: EECS560 lab12



*/

#include <typeinfo>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <exception>
#include <fstream>

using namespace std;

template <typename Comparable>
const Comparable &median3(vector<Comparable> &a, int left, int right, bool reverse)
{
    int center = (left + right) / 2;
    if (reverse == false)
    {

        if (a[center] < a[left])
            std::swap(a[left], a[center]);
        if (a[right] < a[left])
            std::swap(a[left], a[right]);
        if (a[right] < a[center])
            std::swap(a[center], a[right]);

        // Place pivot at position right - 1
        std::swap(a[center], a[right - 1]);
        return a[right - 1];
    }
    else
    {
        if (a[center] > a[left])
            std::swap(a[left], a[center]);
        if (a[right] > a[left])
            std::swap(a[left], a[right]);
        if (a[right] > a[center])
            std::swap(a[center], a[right]);

        // Place pivot at position right - 1
        std::swap(a[center], a[right - 1]);
        return a[right - 1];
    }
}

template <typename Comparable>
void insertionSort(vector<Comparable> &a, int left, int right, bool reverse)
{
    if (reverse == false)
    {
        for (int p = left + 1; p <= right; ++p)
        {
            Comparable tmp = std::move(a[p]);
            int j;

            for (j = p; j > left && tmp < a[j - 1]; --j)
                a[j] = std::move(a[j - 1]);
            a[j] = std::move(tmp);
        }
    }
    else
    {
        for (int p = left + 1; p <= right; ++p)
        {
            Comparable tmp = std::move(a[p]);
            int j;

            for (j = p; j > left && tmp > a[j - 1]; --j)
                a[j] = std::move(a[j - 1]);
            a[j] = std::move(tmp);
        }
    }
}


template <typename Comparable>
void quickSort(vector<Comparable> &a, int left, int right, bool reverse)
{
    if (reverse == false)
    {
        if (left + 10 <= right)
        {
            const Comparable &pivot = median3(a, left, right, reverse);
            cout << pivot << endl;
            // Begin partitioning
            int i = left, j = right - 1;
            for (;;)
            {
                while (a[++i] < pivot)
                {
                }
                while (pivot < a[--j])
                {
                }
                if (i < j)
                    std::swap(a[i], a[j]);
                else
                    break;
            }

            std::swap(a[i], a[right - 1]); // Restore pivot

            quickSort(a, left, i - 1, reverse);  // Sort small elements
            quickSort(a, i + 1, right, reverse); // Sort large elements
        }
        else // Do an insertion sort on the subarray
            insertionSort(a, left, right, reverse);
    }
    else
    {
        if (left + 10 <= right)
        {
            const Comparable &pivot = median3(a, left, right, reverse);
            cout << pivot << endl;
            // Begin partitioning
            int i = left, j = right - 1;
            for (;;)
            {
                while (a[++i] > pivot)
                {
                }
                while (pivot > a[--j])
                {
                }
                if (i < j)
                    std::swap(a[i], a[j]);
                else
                    break;
            }

            std::swap(a[i], a[right - 1]); // Restore pivot

            quickSort(a, left, i - 1, reverse);  // Sort small elements
            quickSort(a, i + 1, right, reverse); // Sort large elements
        }
        else // Do an insertion sort on the subarray
            insertionSort(a, left, right, reverse);
    }
}

template <typename Comparable>
void quickSort(vector<Comparable> &a, bool reverse = false)
{
     quickSort(a, 0, a.size() - 1, reverse);
}