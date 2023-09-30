#ifndef SHELL_SORT_H
#define SHELL_SORT_H

#include <vector>

template <typename T>
void shellSort(std::vector<T>& v) {
    size_t j;
    for (size_t sp = v.size() / 2; sp > 0; sp /= 2) {
        for (size_t i = sp; i < v.size(); i++) {
            T t = v[i];
            for (j = i; j >= sp && t < v[j - sp]; j -= sp) {
                v[j] = v[j - sp];
            }
            v[j] = t;
        }
    }
}

#endif  // SHELL_SORT_H
