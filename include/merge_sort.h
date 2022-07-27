#ifndef MERGE_SORT_H_
#define MERGE_SORT_H_

#include "vector.h"

namespace ds {
  /**
   * Merge two sorted sublists (called left sublist and right sublist) 
      into a sorted list
   * @param list a list of values
   * @param left the left boundary of the list
   * @param mid the middle of the list (index that splits the list into two parts)
   * @param right the right boundary of the list
   */
template<typename T>
void merge(Vector<T>& list, int left, int mid, int right) {
  Vector<T> left_list;
  for (int i = left; i < mid + 1; ++i) {
    left_list.PushBack(list[i]);
  }
  Vector<T> right_list;
  for (int j = mid + 1; j < right + 1; ++j) {
    right_list.PushBack(list[j]);
  }

  int left_size = mid + 1 - left; int right_size = right - mid;
  int i = 0, j = 0;
  int k = left;
  while (i < left_size && j < right_size) {
    if (left_list[i] < right_list[j]) {
      list[k++] = left_list[i++];
    } else {
      list[k++] = right_list[j++];
    }
  }

  while (i < left_size) {
    list[k++] = left_list[i++];
  }

  while (j < right_size) {
    list[k++] = right_list[j++];
  }

}

/**
 * Sort a list of values by recursively sorting the left half and 
    the right half of the list. After sorting two halves of the list, we
    merge them into a final sorted list
 * @param list a list of values
 * @param left the left boundary of the list
 * @param right the right boundary of the list
 */
template<typename T>
void merge_sort(Vector<T>& list, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    merge_sort(list, left, mid);
    merge_sort(list, mid + 1, right);
    merge(list, left, mid, right);
  }
}

/**
 * Mergesort wrapper
 * @param list the list of values to sort
 */
template<typename T>
void MergeSort(Vector<T>& list) {
  merge_sort(list, 0, list.Size() - 1);
}

} // namespace ds

#endif // MERGE_SORT_H_