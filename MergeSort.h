#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>

template <typename T>
void merge(std::vector<T>& v, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    std::vector<T> left(n1);
    std::vector<T> right(n2);

    for (int i = 0; i < n1; ++i) {
        left[i] = v[low + i];
    }
    for (int i = 0; i < n2; ++i) {
        right[i] = v[mid + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = low;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            v[k] = left[i];
            ++i;
        } else {
            v[k] = right[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        v[k] = left[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        v[k] = right[j];
        ++j;
        ++k;
    }
}

template <typename T>
void mergeSort(std::vector<T>& v, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(v, low, mid);
        mergeSort(v, mid + 1, high);
        merge(v, low, mid, high);
    }
}

#endif // MERGE_SORT_H
