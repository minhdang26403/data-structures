#include "red_black_tree.h"

#include <cassert>
#include <string>

#include "vector.h"

void TestConstructor1() {
  using namespace ds;
  std::cout << "----------Test Constructor 1----------\n";
  Vector<int> data = {41, 20, 65, 11, 29, 50, 91, 32, 72, 99};
  RedBlackTree<int> tree1(data);
  tree1.Print();
  RedBlackTree<std::string> tree2 = {"abc", "def", "ghi", "qwe"};
  tree2.Print();
  RedBlackTree<std::string> tree3(tree2);
  tree3.Print();
  RedBlackTree<int> tree4;
  tree4 = std::move(tree1);
  tree4.Print();
}

void TestConstructor2() {
  std::cout << "----------Test Constructor 2----------\n";
  ds::RedBlackTree<int> tree1 = {44,64,29,89,25,36,73,32,63,93};
  ds::RedBlackTree<int> tree2(tree1);
  assert(tree1.GetRoot() != tree2.GetRoot());
  tree1.Delete(36);
  assert(tree1.Search(36) == tree1.GetNIL());
  assert(tree2.Search(36) != tree2.GetNIL());
  tree2.Insert(30);
  assert(tree2.Search(30) != tree2.GetNIL());
  assert(tree1.Search(30) == tree1.GetNIL());

  ds::RedBlackTree<int> tree3(std::move(tree1));
  tree1.Print();
  tree3.Print();
  assert(tree1.GetRoot() == tree1.GetNIL());
  assert(tree3.GetRoot() != tree3.GetNIL());
  assert(tree3.Search(44) != tree3.GetNIL());

  ds::RedBlackTree<std::string> tree4 = {"abc", "esi", "def", "sv", "nvch"};
  assert(tree4.GetRoot() != tree4.GetNIL());
  assert(tree4.Search("nvch") != tree4.GetNIL());
  ds::Vector<std::string> data = {"abc", "qwe", "qaz", "kom", "poi"};
  ds::RedBlackTree<std::string> tree5(data);
  assert(tree5.Search("qaz") != tree5.GetNIL());
}

void TestInsert() {
  std::cout << "----------Test Insert----------\n";
  using namespace ds;
  ds::RedBlackTree<int> tree1 = {11, 2, 14, 1, 7, 15, 5, 8};
  auto root = tree1.GetRoot();
  assert(root->value_ == 11);
  assert(root->color_ == Color::BLACK);
  assert(tree1.Minimum(root)->value_ == 1);
  assert(tree1.Minimum(root)->color_ == Color::BLACK);
  assert(tree1.Maximum(root)->value_ == 15);
  assert(tree1.Maximum(root)->color_ == Color::RED);
  assert(tree1.Search(8)->color_ == Color::RED);
  assert(tree1.Search(5)->color_ == Color::RED);
  assert(tree1.Search(7)->color_ == Color::BLACK);
  
  tree1.Insert(4);
  root = tree1.GetRoot();
  assert(root->value_ == 7);
  assert(root->color_ == Color::BLACK);
  assert(root->left_ == tree1.Search(2));
  assert(root->right_ == tree1.Search(11));
  assert(tree1.Search(2)->parent_ == root);
  assert(tree1.Search(11)->parent_ == root);
  assert(tree1.Search(11)->left_ == tree1.Search(8));
}

void TestDelete() {
  std::cout << "----------Test Delete----------\n";
  using namespace ds;
  ds::RedBlackTree<int> tree1 = {11, 2, 14, 1, 7, 15, 5, 8};
  tree1.Insert(4);
  tree1.Insert(3);
  auto root = tree1.GetRoot();
  tree1.Delete(1);
  assert(root->left_ == tree1.Search(4));
  assert(root->left_->color_ == Color::RED);
  assert(tree1.Search(4)->left_ == tree1.Search(2));
  assert(tree1.Search(2)->color_ == Color::BLACK);
  assert(tree1.Search(2)->right_ == tree1.Search(3));
  assert(tree1.Predecessor(root)->color_ == Color::BLACK);
  tree1.Delete(7);
  root = tree1.GetRoot();
  assert(root->value_ == 8);
  assert(root->color_ == Color::BLACK);
  assert(root->left_ == tree1.Search(4));
  assert(root->left_->color_ == Color::RED);
}

int main() {
  TestConstructor1();
  TestConstructor2();
  TestInsert();
  TestDelete();

  std::cout << "All test cases passed\n";

  return 0;
}