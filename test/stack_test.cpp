#include "stack.h"

#include <cassert>
#include <iostream>

void Test1() {
  ds::Stack<int> data;
  data.Push(2);
  data.Push(6);
  data.Push(4);
  assert(data.Size() == 3);
  assert(data.Top() == 4);
  data.Pop();
  assert(data.Size() == 2);
  assert(data.Top() == 6);
}

int main() {
  Test1();

  std::cout << "All test cases passed\n";

  return 0;
}