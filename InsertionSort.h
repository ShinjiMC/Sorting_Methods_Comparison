#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <vector>

template <typename T>
void InsertionSort(std::vector<T>& v) {
    for (int i = 1; i < v.size(); ++i) {
        T cur_value = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > cur_value) {
            v[j + 1] = v[j];
            j -= 1;
        }

        v[j + 1] = cur_value;
    }
}

#endif // INSERTION_SORT_H
