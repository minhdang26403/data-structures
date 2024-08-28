#include "list.h"

#include <gtest/gtest.h>
#include <string>

using namespace stl;

TEST(ListTest, TestConstructor) {
  using std::cout;
  using std::string;
  string s{"hello"};
  list<string> data1{3, s};
  for (const auto& data : data1) {
    EXPECT_TRUE(data == s);
  }

  // copy from data1
  list<string> data2{data1};
  for (const auto& data : data2) {
    EXPECT_TRUE(data == s);
  }

  list<string> data3{std::move(data1)};
  EXPECT_TRUE(data1.empty());
  for (const auto& data : data3) {
    EXPECT_TRUE(data == s);
  }

  list<int> data4 = {1, 2, 3, 4, 5};
  int val = 1;
  for (const auto data : data4) {
    EXPECT_TRUE(data == val);
    val++;
  }
}

TEST(ListTest, TestAssignment) {
  list<int> data1{1, 2, 3, 4, 5};
  list<int> data2;
  data2 = data1;
  auto it1 = data1.begin();
  for (const auto data : data2) {
    EXPECT_TRUE(data == *it1);
    it1++;
  }

  EXPECT_TRUE(data2.size() == data1.size());

  data2 = {6, 7, 8, 9, 10};
  list<int> data3;
  data3 = std::move(data1);
  auto it2 = data2.begin();
  for (const auto data : data3) {
    EXPECT_TRUE(data + 5 == *it2);
    it2++;
  }
}

TEST(ListTest, TestIterator) {
  list<int> data1 {1, 2, 3, 4, 5};
  auto it = data1.begin();
  for (const auto data : data1) {
    EXPECT_TRUE(data == *it);
    it++;
  }

  list<std::string> data2;
  EXPECT_TRUE(data2.begin() == data2.end());
}

TEST(ListTest, TestInsert) {
  using std::string;
  list<std::pair<string, string>> data1;
  std::pair<string, string> s{"abc", "123"};
  data1.insert(0, s);
  data1.emplace(1, "def", "456");
  EXPECT_TRUE(data1.front() == s);
  std::pair<string, string> p{"def", "456"};
  EXPECT_TRUE(data1.back() == p);
}

TEST(ListTest, TestEmplace) {
  std::string s{"abc"};
  list<std::string> data1;
  data1.insert(0, s);
  EXPECT_TRUE(data1.front() == s);
  data1.insert(1, stl::move(s));
  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(data1.back() == "abc");
}

TEST(ListTest, TestErase) {
  list<std::string> list;
  list.insert(0, "abc");
  list.insert(1, "def");
  list.insert(1, "ghi");
  list.insert(0, "xyz");
  list.erase("xyz");
  EXPECT_TRUE(list.front() == "abc");

  list.erase("abc");
  EXPECT_TRUE(list.front() == "ghi");

  list.erase("def");
  EXPECT_TRUE(list.to_string() == "[ghi]");
  list.erase("ghi");
  EXPECT_TRUE(list.size() == 0);
}

TEST(ListTest, TestReverse) {
  list<std::string> list;
  list.reverse();
  EXPECT_TRUE(list.to_string() == "[]");

  list.insert(0, "a");
  list.insert(0, "b");
  EXPECT_TRUE(list.to_string() == "[b, a]");

  list.insert(2, "c");
  list.reverse();
  EXPECT_TRUE(list.to_string() == "[c, a, b]");

  list.erase(1);
  list.reverse();
  EXPECT_TRUE(list.to_string() == "[b, c]");
}
