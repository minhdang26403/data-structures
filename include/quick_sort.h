#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_

#include "vector.h"

namespace ds {
/**
 * Find the position of a pivot that splits the list into two 
    parts, one with elements smaller than or equal to the pivot and one
    with elements larger than the pivot.
 * @param list the list of values to partition
 * @param left the left boundary of the list
 * @param right the right boundary of the list
 * @return the index of the pivot
 */
template<typename T>
int partition(Vector<T>& list, int left, int right) {
  int pivot = list[right];
  int i = left - 1;
  for (int j = left; j < right; ++j) {
    if (list[j] <= pivot) {
      std::swap(list[++i], list[j]);
    }
  }
  std::swap(list[i + 1], list[right]);
  return i + 1;
}

/**
 * Sort a list of numbers by selecting a pivot that divides the list into 
    two parts, one with elements less than or equal to the pivot and one
    with elements larger than the pivot. Then, recursively sorting the two parts
    of the list excluding the pivot element since it is already in the correct position.
 * @param list the list of valus to sort
 * @param left the left boundary of the list
 * @param right the right boundary of the list
 */
template<typename T>
void quick_sort(Vector<T>& list, int left, int right) {
  if (left < right) {
    int pivot_idx = partition(list, left, right);
    quick_sort(list, left, pivot_idx - 1);
    quick_sort(list, pivot_idx + 1, right);
  }
}

/**
 * Quicksort wrapper
 * @param list the list of values to sort
 */
template<typename T>
void QuickSort(Vector<T>& list) {
  quick_sort(list, 0, list.Size() - 1);
}
} // namespace ds

#endif // QUICK_SORT_H_