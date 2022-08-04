#include "queue.h"

#include <cassert>
#include <iostream>

void Test1() {
  std::cout << "-------Test 1-------\n";
  ds::Queue<int> q;
  q.Enqueue(1);
  q.Enqueue(2);
  q.Enqueue(3);
  assert(q.Size() == 3);
  assert(q.Front() == 1);
  assert(q.Back() == 3);

  q.Dequeue();
  assert(q.Front() == 2);
}

int main() {
  Test1();

  std::cout << "All test cases passed\n";

  return 0;
}