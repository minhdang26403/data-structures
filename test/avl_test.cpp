#include "avl.h"

#include <cassert>
#include <iostream>

#include "vector.h"

void Test1() {
  std::cout << "----------Test 1----------\n";
  ds::Vector<int> data = {41, 20, 65, 11, 29, 50, 91, 32, 72, 99};
  ds::AVL<int> tree;
  for (const auto& num : data) {
    tree.Insert(num);
  }
  tree.Delete(11);
  assert(tree.GetRoot()->left_ == tree.Search(29));
  tree.Delete(50);
  assert(tree.Search(91)->left_ == tree.Search(65));
  assert(tree.GetRoot()->right_ == tree.Search(91));
  tree.Delete(99);
  assert(tree.Search(72)->right_ == tree.Search(91));
  assert(tree.Search(72)->left_ == tree.Search(65));
  assert(tree.GetRoot()->right_ == tree.Search(72));
}

void Test2() {
  std::cout << "----------Test 2----------\n";
  ds::Vector<int> data = {44, 17, 78, 32, 50, 88, 48, 62};
  ds::AVL<int> tree;
  for (const auto& num : data) {
    tree.Insert(num);
  }
  tree.Delete(32);
  assert(tree.GetRoot() == tree.Search(50));
  assert(tree.GetRoot()->left_ == tree.Search(44));
  tree.Delete(50);
  assert(tree.GetRoot() == tree.Search(62));
  assert(tree.GetRoot()->left_ == tree.Search(44));
  assert(tree.GetRoot()->right_ == tree.Search(78));
}

int main() {
  Test1();
  Test2();

  std::cout << "All test cases passed\n";

  return 0;
}