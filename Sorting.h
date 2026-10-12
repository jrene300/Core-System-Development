#ifndef SORTING_H
#define SORTING_H

#include <vector>
using namespace std;

template <typename T, typename Before>
void mergeRanges(vector<T>& a, vector<T>& tmp, int lo, int mid, int hi, Before before)
{
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi)
    {
        if (before(a[j], a[i])) tmp[k++] = a[j++];
        else                    tmp[k++] = a[i++];
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= hi)  tmp[k++] = a[j++];
    for (k = lo; k <= hi; k++) a[k] = tmp[k];
}

template <typename T, typename Before>
void mergeSortRange(vector<T>& a, vector<T>& tmp, int lo, int hi, Before before)
{
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    mergeSortRange(a, tmp, lo, mid, before);
    mergeSortRange(a, tmp, mid + 1, hi, before);
    mergeRanges(a, tmp, lo, mid, hi, before);
}

template <typename T, typename Before>
void mergeSortBy(vector<T>& data, Before before)
{
    if (data.size() < 2) return;
    vector<T> tmp(data);
    mergeSortRange(data, tmp, 0, (int)data.size() - 1, before);
}

#endif