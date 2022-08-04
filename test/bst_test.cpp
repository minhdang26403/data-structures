#include "bst.h"

#include <cassert>
#include <iostream>
#include <string>

#include "vector.h"

void TestInsert() {
  std::cout << "----------Test Insert----------\n";
  ds::BST<int> tree;
  for (int i = 0; i < 10; ++i) {
    tree.Insert(i + 1);
  }
  assert(tree.Search(2) != nullptr);
  assert(tree.Search(16) == nullptr);
  assert(tree.Minimum(tree.GetRoot())->value_ == 1);
}

void TestDelete() {
  std::cout << "----------Test Delete----------\n";
  ds::BST<long> tree;
  for (int i = 0; i < 15; ++i) {
    tree.Insert(rand() % 100);
  }
  tree.Print();
  assert(tree.Minimum(tree.GetRoot())->value_ == 15);
  assert(tree.Search(90) != nullptr);
  tree.Delete(62);
  tree.Print();
}

void TestConstructor() {
  std::cout << "----------Test Constructor----------\n";
  ds::BST<int> tree1;
  for (int i = 0; i < 10; ++i) {
    tree1.Insert(rand() % 100);
  }
  std::cout << "Tree 1: ";
  tree1.Print();
  ds::BST<int> tree2(tree1);
  std::cout << "Tree 2: ";
  tree2.Print();
  assert(tree1.GetRoot() != tree2.GetRoot());
  tree1.Delete(36);
  std::cout << "Tree 1: ";
  tree1.Print();
  std::cout << "Tree 2: ";
  tree2.Print();
  assert(tree1.Search(36) == nullptr);
  assert(tree2.Search(36) != nullptr);
  tree2.Insert(30);
  assert(tree2.Search(30) != nullptr);
  assert(tree1.Search(30) == nullptr);

  ds::BST<int> tree3(std::move(tree1));
  tree1.Print();
  tree3.Print();
  assert(tree1.GetRoot() == nullptr);
  assert(tree3.GetRoot() != nullptr);
  assert(tree3.Search(11) != nullptr);
}

void TestCustomConstructor() {
  ds::BST<std::string> tree1 = {"abc", "esi", "def", "sv", "nvch"};
  assert(tree1.GetRoot() != nullptr);
  tree1.Print();
  assert(tree1.Search("nvch") != nullptr);
  ds::Vector<std::string> data = {"abc", "qwe", "qaz", "kom", "poi"};
  ds::BST<std::string> tree2(data);
  assert(tree2.Search("qaz") != nullptr);
  tree2.Print();
}

int main() {
  TestInsert();
  TestDelete();
  TestConstructor();
  TestCustomConstructor();

  std::cout << "All test cases passed\n";

  return 0;
}