#include "heap.h"

#include <cassert>
#include <iostream>

#include "vector.h"

void Test1() {
  std::cout << "-------Test 1-------\n";
  ds::Vector<int> data = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
  ds::Heap<int> heap(data);
  heap.Print();
  assert(heap.Top() == 16);
  heap.Push(17);
  heap.Print();
  assert(heap.Top() == 17);
}

void Test2() {
  std::cout << "-------Test 2-------\n";
  ds::Heap<int> heap;
  for (int i = 0; i < 11; ++i) {
    heap.Push(i);
  }
  heap.Print();
  assert(heap.Top() == 10);
  assert(heap.Pop() == 10);
  assert(heap.Top() == 9);
  heap.Push(20);
  assert(heap.Top() == 20);
  heap.Print();
  for (int i = 0; i < 5; ++i) {
    heap.Pop();
  }
  assert(heap.Top() == 5);
  heap.Print();
}

void Test3() {
  std::cout << "-------Test 3-------\n";
  ds::Vector<int> data = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
  ds::Heap<int, std::greater<int>> heap(std::move(data));
  heap.Print();
  assert(heap.Top() == 1);
  heap.Push(-1);
  heap.Print();
  assert(heap.Top() == -1);
  assert(heap.Pop() == -1);
  heap.Print();
  assert(heap.Pop() == 1);
  heap.Print();
  assert(heap.Pop() == 2);
  heap.Print();
  assert(heap.Top() == 3);
}

void Test4() {
  std::cout << "-------Test 4-------\n";
  ds::Heap<int> heap;
  heap.Print();
  std::cout << heap.Top() << '\n';
  try {
    heap.Pop();
  } catch (const std::exception& e) {
    std::cout << e.what();
  }
  for (int i = 0; i < 10; ++i) {
    heap.Push(rand() % 100);
  }
  heap.Print();
}

int main() {
  Test1();
  Test2();
  Test3();
  Test4();

  std::cout << "All test cases passed\n";

  return 0;
}