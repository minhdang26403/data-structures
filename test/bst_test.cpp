#include "bst.h"

#include <cassert>
#include <iostream>
#include <string>

#include "vector.h"

void TestInsert() {
  std::cout << "----------Test Insert----------\n";
  ds::Vector<int> data = {83,86,77,15,93,35,11,92,49,21};
  ds::BST<int> tree(data);
  assert(tree.GetRoot()->value_ == 83);
  assert(tree.GetRoot()->left_->value_ == 77);
  assert(tree.GetRoot()->right_->value_ == 86);
  assert(tree.Search(93)->left_->value_ == 92);
  assert(tree.Search(92)->parent_->value_ == 93);
  assert(tree.Search(21)->parent_->value_ == 35);
  assert(tree.Search(49)->parent_->value_ == 35);
  assert(tree.Search(15)->left_->value_ == 11);
  assert(tree.Search(15)->right_->value_ == 35);
}

void TestDelete() {
  std::cout << "----------Test Delete----------\n";
  // Initialize the tree by initializer list
  ds::BST<int> tree = {16,65,62,89,91,73,46,66,41,99};
  assert(tree.GetRoot()->value_ == 16);
  tree.Delete(16);
  assert(tree.GetRoot()->value_ == 65);
  assert(tree.Minimum(tree.GetRoot())->value_ == 41);
  assert(tree.Search(73)->left_->value_ == 66);
  assert(tree.Search(73)->parent_->value_ == 89);
  assert(tree.Search(91)->left_ == nullptr);
}

void TestConstructor() {
  std::cout << "----------Test Constructor----------\n";
  ds::BST<int> tree1 = {44,64,29,89,25,36,73,32,63,93};
  ds::BST<int> tree2(tree1);
  assert(tree1.GetRoot() != tree2.GetRoot());
  tree1.Delete(36);
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
  assert(tree3.Search(44) != nullptr);
}

void TestCustomConstructor() {
  ds::BST<std::string> tree1 = {"abc", "esi", "def", "sv", "nvch"};
  assert(tree1.GetRoot() != nullptr);
  assert(tree1.Search("nvch") != nullptr);
  ds::Vector<std::string> data = {"abc", "qwe", "qaz", "kom", "poi"};
  ds::BST<std::string> tree2(data);
  assert(tree2.Search("qaz") != nullptr);
}

void Test5() {
  ds::BST<std::string> tree1 = {"abc", "esi", "def", "sv", "nvch"};
  // Can't do this if the copy constructor is explicit
  ds::BST<std::string> tree2 = tree1;
}

int main() {
  TestInsert();
  TestDelete();
  TestConstructor();
  TestCustomConstructor();

  std::cout << "All test cases passed\n";

  return 0;
}