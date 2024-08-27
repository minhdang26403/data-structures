#include "stack.h"
#include <gtest/gtest.h>

TEST(StackTest, BasicTest) {
  stl::stack<int> data;
  data.push(2);
  data.push(6);
  data.push(4);
  EXPECT_TRUE(data.size() == 3);
  EXPECT_TRUE(data.top() == 4);
  data.pop();
  EXPECT_TRUE(data.size() == 2);
  EXPECT_TRUE(data.top() == 6);
}
