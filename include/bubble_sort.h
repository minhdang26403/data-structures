#ifndef BUBBLE_SORT_H_
#define BUBBLE_SORT_H_

#include <algorithm>

#include "vector.h"

namespace ds {
template<typename T>
void BubbleSort(Vector<T>& list) {
  int n = list.Size();
  for (int i = 0; i < n - 1; ++i) {
    bool swapped = false;
    for (int j = 0; j < n - 1 - i; ++j) {
      if (list[j] > list[j + 1]) {
        std::swap(list[j], list[j + 1]);
        swapped = true;
      }
    }
    if (swapped == false) {
      return;
    }
  }
};
} // namespace ds

#endif // BUBBLE_SORT_H_