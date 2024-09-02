#include "queue.h"

#include <gtest/gtest.h>

TEST(QueueTest, BasicTest) {
  stl::queue<int> q;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  EXPECT_TRUE(q.size() == 3);
  EXPECT_TRUE(q.front() == 1);
  EXPECT_TRUE(q.back() == 3);

  q.deque();
  EXPECT_TRUE(q.front() == 2);
}
