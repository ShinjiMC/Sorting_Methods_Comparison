#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <algorithm>
#include <functional>
#include <iterator>

template <typename T, typename Compare>
void selectionSort(std::vector<T>& v, Compare compare) {
    if (!v.empty()) {
        for (auto curr = v.begin(); curr != v.end(); ++curr) {
            auto minimum = curr;
            auto forward = curr;
            while (++forward != v.end()) {
                if (compare(*forward, *minimum)) {
                    minimum = forward;
                }
            }
            std::iter_swap(minimum, curr);
        }
    }
}

template <typename T>
void selectionSort(std::vector<T>& v) {
    selectionSort(v, std::less<T>());
}

#endif  // SELECTION_SORT_H
