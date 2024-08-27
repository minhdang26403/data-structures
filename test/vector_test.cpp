#include "vector.h"

#include <gtest/gtest.h>
#include <string>

using namespace stl;

TEST(VectorTest, TestConstructor) {
  vector<std::string> strs1 = {"abc", "def", "qwe"};
  vector<std::string> strs2(strs1);
  // Check for deep copy
  strs2[2] = "xyz";
  EXPECT_TRUE(strs1[2] != strs2[2]);

  int count = 5;
  int value = 10;
  vector<int> data2(count, value);
  for (int i = 0; i < count; i++) {
    EXPECT_TRUE(data2[i] == value);
  }

  // Move string1 to string3
  vector<std::string> strs3(stl::move(strs1));
  EXPECT_TRUE(strs1.size() == 0);
  EXPECT_TRUE(strs3.size() != 0);
}

TEST(VectorTest, TestAssignment) {
  using std::string;
  vector<string> strs1 = {"abc", "def", "qwe"};
  vector<string> strs2;
  assert(strs2.size() == 0);
  strs2 = strs1;
  strs2[0] = "xyz";
  EXPECT_TRUE(strs1.front() != strs2.front());

  vector<string> strs3;
  strs3 = stl::move(strs2);
  EXPECT_TRUE(strs3.size() != 0);
  EXPECT_TRUE(strs2.size() == 0);

  EXPECT_TRUE(strs3[0] == "xyz");
  EXPECT_TRUE(strs3[1] == "def");
  EXPECT_TRUE(strs3[2] == "qwe");
}

TEST(VectorTest, TestInsert) {
  vector<std::string> data1;
  data1.push_back("abc");
  EXPECT_TRUE(data1.front() == "abc");

  int i = data1.size();
  for (; i < 10; i++) {
    data1.push_back("def");
  }
  assert(data1[i - 1] == "def");

  vector<std::string> data2;
  data2.insert(data2.begin(), "abc");
  EXPECT_TRUE(data2.size() == 1);
  EXPECT_TRUE(data2.front() == "abc");
  data2.insert(data2.begin() + 1, "def");
  data2.insert(data2.begin() + 1, "ghi");
  EXPECT_TRUE(data2[1] == "ghi");
  EXPECT_TRUE(data2[2] == "def");
  data2.insert(data2.end(), "xyz");
  EXPECT_TRUE(data2.size() == 4);
  EXPECT_TRUE(data2[3] == "xyz");
}

TEST(VectorTest, TestRemove) {
  vector<std::string> data;
  data.insert(data.begin(), "abc");
  data.insert(data.begin() + 1, "def");
  data.insert(data.begin() + 1, "ghi");
  data.insert(data.begin(), "xyz");
  data.erase(data.begin());
  EXPECT_TRUE(data.front() == "abc");
  data.erase(data.begin());
  EXPECT_TRUE(data.front() == "ghi");
}

TEST(VectorTest, TestIterator) {
  vector<std::string> data1 = {"ab", "cd", "ef", "gh"};
  int i = 0;
  for (const auto& s : data1) {
    EXPECT_TRUE(s == data1[i]);
    i++;
  }

  vector<int> data2;
  for (int i = 0; i < 10; ++i) {
    data2.push_back(i);
  }
  vector<int> data3;
  for (vector<int>::iterator it = data2.begin(); it != data2.end(); ++it) {
    data3.push_back(*it);
  }

  EXPECT_TRUE(*data3.cbegin() == 0);
}

TEST(VectorTest, TestEmplace) {
  vector<std::pair<int, int>> data1;
  std::pair<int, int> a{1, 2};
  data1.push_back(a);
  data1.emplace_back(3, 4);

  EXPECT_TRUE(data1.front() == a);
  EXPECT_TRUE(data1.back().first == 3);
  EXPECT_TRUE(data1.back().second == 4);
}
