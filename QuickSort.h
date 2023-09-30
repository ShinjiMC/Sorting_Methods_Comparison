#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>

template<typename T>
int partition(std::vector<T>& v, int low, int high) {
    T pivote = v[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (v[j] < pivote) {
            i++;
            std::swap(v[i], v[j]);
        }
    }
    std::swap(v[i + 1], v[high]);
    return (i + 1);
}

template<typename T>
void quick(std::vector<T>& v, int low, int high) {
    if (low < high) {
        int pi = partition(v, low, high);
        quick(v, low, pi - 1);
        quick(v, pi + 1, high);
    }
}

template<typename T>
void quickSort(std::vector<T>& v) {
    quick(v, 0, v.size() - 1);
}

#endif  // QUICK_SORT_H

