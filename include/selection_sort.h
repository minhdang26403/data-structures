#ifndef SELECTION_SORT_H_
#define SELECTION_SORT_H_

/** 
 * Sort a list of numbers by going through each position and
    find the correct number to insert into that position.
    Starting at index 0, we find the smallest element from index 0 
    to the end of the list, then swap that element with the element 
    at index 0. We continue the same process for index 1, 2,...
 * @param list a list of integers 
 */

#include <algorithm>

#include "vector.h"
namespace ds {
template<typename T>
void SelectionSort(Vector<T>& list) {
  int n = list.Size();
  for (int i = 0; i < n; ++i) {
    int pos = i;
    for (int j = i + 1; j < n; ++j) {
      if (list[j] < list[pos]) {
        pos = j;
      }
    }
    std::swap(list[i], list[pos]);
  }
};
} // namespace ds

#endif // SELECTION_SORT_H_