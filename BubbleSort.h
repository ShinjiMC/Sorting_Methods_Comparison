#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <vector>

template <typename T>
void bubbleSort(std::vector<T>& v, int n) {
    if (n == 1)
        return;
    for (int i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) {
            std::swap(v[i], v[i + 1]);
        }
    }
    bubbleSort(v, n - 1);
}

template <typename T>
void bubbleSort(std::vector<T>& v) {
    int n = v.size();
    bubbleSort(v, n);
}

#endif // BUBBLESORT_H
