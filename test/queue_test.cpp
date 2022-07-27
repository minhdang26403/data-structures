#include "queue.h"

#include <cassert>
#include <iostream>

int main() {
  ds::Queue<int> q;
  q.Enqueue(1);
  q.Enqueue(2);
  q.Enqueue(3);
  assert(q.Size() == 3);
  assert(q.Front() == 1);
  assert(q.Back() == 3);

  q.Dequeue();
  assert(q.Front() == 2);

  std::cout << "All test cases passed\n";

  return 0;
}