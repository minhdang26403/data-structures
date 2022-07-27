#include "bubble_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "selection_sort.h"

#include <string>

#include "util.h"
#include "vector.h"

void TestBubbleSort() {
  using std::cout;
  ds::Vector<int> data;
  for (int i = 0; i < MAX_ELEMENTS; ++i) {
    data.PushBack(rand() % 100);
  }
  cout << "Bubble sort test: ...\n";
  cout << "The initial list: ";
  cout << data << '\n';
  ds::BubbleSort<int>(data);
  cout << "The list after being sorted: ";
  cout << data << '\n';
}

void TestSelectionSort() {
  using std::cout;
  ds::Vector<int> data;
  for (int i = 0; i < MAX_ELEMENTS; ++i) {
    data.PushBack(rand() % 200);
  }
  cout << "Selection sort test: ...\n";
  cout << "The initial list: ";
  cout << data << '\n';
  ds::SelectionSort<int>(data);
  cout << "The list after being sorted: ";
  cout << data << '\n';
}

void TestMergeSort() {
  using std::cout;
  ds::Vector<int> data;
  for (int i = 0; i < MAX_ELEMENTS; ++i) {
    data.PushBack(rand() % 50);
  }
  cout << "Merge sort test: ...\n";
  cout << "The initial list: ";
  cout << data << '\n';
  ds::MergeSort<int>(data);
  cout << "The list after being sorted: ";
  cout << data << '\n';
}

void TestQuickSort() {
  using std::cout;
  ds::Vector<int> data;
  for (int i = 0; i < MAX_ELEMENTS; ++i) {
    data.PushBack(rand() % 100);
  }
  cout << "Quicksort test: ...\n";
  cout << "The initial list: ";
  cout << data << '\n';
  ds::QuickSort<int>(data);
  cout << "The list after being sorted: ";
  cout << data << '\n';
}

int main() {
  // TestBubbleSort();
  // TestSelectionSort();
  // TestMergeSort();
  TestQuickSort();

  std::cout << "All test cases passed\n";
}