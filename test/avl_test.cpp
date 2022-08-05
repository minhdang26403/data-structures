#include "avl.h"

#include <cassert>
#include <iostream>

#include "vector.h"

void Test1() {
  std::cout << "----------Test 1----------\n";
  ds::Vector<int> data = {41, 20, 65, 11, 29, 50, 91, 32, 72, 99};
  ds::AVL<int> tree(data);
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
  ds::AVL<int> tree(data);
  tree.Delete(32);
  assert(tree.GetRoot() == tree.Search(50));
  assert(tree.GetRoot()->left_ == tree.Search(44));
  tree.Delete(50);
  assert(tree.GetRoot() == tree.Search(62));
  assert(tree.GetRoot()->left_ == tree.Search(44));
  assert(tree.GetRoot()->right_ == tree.Search(78));

}

void Test3() {
  std::cout << "----------Test 3----------\n";
  ds::Vector<int> data = {44, 17, 78, 32, 50, 88, 48, 62};
  ds::AVL<int> tree1(data);
  ds::AVL<int> tree2;
  tree2 = tree1; // Test copy assignment
  assert(tree2.GetRoot() == tree2.Search(44));
  tree2.Delete(32);
  assert(tree2.GetRoot() == tree2.Search(50));
  assert(tree2.GetRoot()->left_ == tree2.Search(44));
  tree2.Delete(50);
  assert(tree2.GetRoot() == tree2.Search(62));
  assert(tree2.GetRoot()->left_ == tree2.Search(44));
  assert(tree2.GetRoot()->right_ == tree2.Search(78));

  // Make sure tree1 remains intact
  assert(tree1.GetRoot() == tree1.Search(44));
  assert(tree1.GetRoot()->left_ == tree1.Search(17));
  assert(tree1.GetRoot()->right_ == tree1.Search(78));
  assert(tree1.Search(50)->left_ == tree1.Search(48));
  assert(tree1.Search(50)->right_ == tree1.Search(62));
}

void Test4() {
  std::cout << "----------Test 4----------\n";
  ds::Vector<int> data = {44, 17, 78, 32, 50, 88, 48, 62};
  ds::AVL<int> tree1(data);
  ds::AVL<int> tree2(tree1); // Test copy constructor
  assert(tree2.GetRoot() == tree2.Search(44));
  tree2.Delete(32);
  assert(tree2.GetRoot() == tree2.Search(50));
  assert(tree2.GetRoot()->left_ == tree2.Search(44));
  tree2.Delete(50);
  assert(tree2.GetRoot() == tree2.Search(62));
  assert(tree2.GetRoot()->left_ == tree2.Search(44));
  assert(tree2.GetRoot()->right_ == tree2.Search(78));

  // Make sure tree1 remains intact
  assert(tree1.GetRoot() == tree1.Search(44));
  assert(tree1.GetRoot()->left_ == tree1.Search(17));
  assert(tree1.GetRoot()->right_ == tree1.Search(78));
  assert(tree1.Search(50)->left_ == tree1.Search(48));
  assert(tree1.Search(50)->right_ == tree1.Search(62));
}

void Test5() {
  std::cout << "----------Test 5----------\n";
  ds::Vector<int> data = {41, 20, 65, 11, 29, 50, 91, 32, 72, 99};
  ds::AVL<int> tree1(data);
  ds::AVL<int> tree2(std::move(tree1));
  tree1.Print();
  tree2.Print();
  tree2.Delete(11);
  assert(tree2.GetRoot()->left_ == tree2.Search(29));
  tree2.Delete(50);
  assert(tree2.Search(91)->left_ == tree2.Search(65));
  assert(tree2.GetRoot()->right_ == tree2.Search(91));
  tree2.Delete(99);
  assert(tree2.Search(72)->right_ == tree2.Search(91));
  assert(tree2.Search(72)->left_ == tree2.Search(65));
  assert(tree2.GetRoot()->right_ == tree2.Search(72));
}


int main() {
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();

  std::cout << "All test cases passed\n";

  return 0;
}