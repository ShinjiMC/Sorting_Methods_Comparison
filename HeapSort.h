#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <vector>

template <typename T>
void heapify(std::vector<T> &v, int n, int i) {
    int n2 = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && v[l] > v[n2])
        n2 = l;
    if (r < n && v[r] > v[n2])
        n2 = r;
    if (n2 != i) {
        std::swap(v[i], v[n2]);
        heapify(v, n, n2);
    }
}

template <typename T>
void heapsort(std::vector<T> &v) {
    int n = v.size();

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(v, n, i);
    // Extract element from heap one by one
    for (int i = n - 1; i >= 0; --i) {
        std::swap(v[0], v[i]);
        heapify(v, i, 0);
    }
}

#endif  // HEAP_SORT_H

