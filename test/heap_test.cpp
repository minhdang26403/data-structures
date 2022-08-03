#include "heap.h"

#include <cassert>
#include <iostream>

#include "vector.h"

int main() {
  ds::Vector<int> data = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
  ds::Heap<int> heap(data);
  assert(heap.Top() == 16);
  heap.Push(17);
  heap.Print();
  assert(heap.Top() == 17);

  std::cout << "All test cases passed\n";

  return 0;
}