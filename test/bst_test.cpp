#include "bst.h"

#include <cassert>
#include <iostream>

void TestInsert() {
  ds::BST<int> tree;
  for (int i = 0; i < 10; ++i) {
    tree.Insert(i + 1);
  }
  assert(tree.Search(2) != nullptr);
  assert(tree.Search(16) == nullptr);
  assert(tree.Minimum(tree.GetRoot())->value_ == 1);


}

int main() {
  TestInsert();

  std::cout << "All test cases passed\n";

  return 0;
}