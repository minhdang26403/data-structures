#include "indexed_pq.h"

#include <cassert>

void TestConstructor() {
  std::cout << "----------Constructor Test----------\n";
  ds::IndexedPriorityQueue<int, int> pq;
  assert(pq.IsEmpty());
  assert(pq.Size() == 0);
  pq.Insert(1, 2);
  assert(!pq.IsEmpty());
  assert(pq.Size() == 1);
  auto ele = pq.Pop();
  assert(ele.first == 1);
  assert(ele.second == 2);
  assert(pq.IsEmpty());
}

void TestInsertPop() {
  std::cout << "----------Insert Test----------\n";
  ds::IndexedPriorityQueue<int, int> pq;
  assert(pq.IsEmpty());
  pq.Insert(2, 1);
  pq.Insert(3, 7);
  pq.Insert(1, 0);
  pq.Insert(4, 5);
  assert(pq.Size() == 4);

  pq.PrintPriorityQueue();
  pq.PrintIndexMap();
  assert(pq.Size() == 4);

  pq.Update(3, 2);
  pq.PrintPriorityQueue();
  pq.PrintIndexMap();

  auto top_ele = pq.Top();
  assert(top_ele.first == 1);
  assert(top_ele.second == 0);
  pq.Pop();
  top_ele = pq.Top();
  assert(top_ele.first == 2);
  assert(top_ele.second == 1);
  pq.PrintPriorityQueue();

  pq.Pop();
  pq.Pop();
  assert(pq.Top().first == 4);
  assert(pq.Top().second == 5);
}



int main() {
  TestConstructor();
  TestInsertPop();

  return 0;
}