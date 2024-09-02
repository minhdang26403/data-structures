#include "hash_table.h"

#include <gtest/gtest.h>
#include <exception>
#include <ranges>

using namespace stl;

TEST(HashTableTest, TestBasic1) {
  hash_table<int, int> hash_table;
  for (int i : std::views::iota(1, 11)) {
    hash_table.insert(i, i);
  }
  EXPECT_TRUE(hash_table.size() == 10);

  hash_table.erase(2);
  hash_table.erase(6);
  hash_table.erase(4);

  EXPECT_TRUE(hash_table.contains(1));
  EXPECT_TRUE(!hash_table.contains(2));
  hash_table.insert(5, 10);
  EXPECT_TRUE(hash_table.get(5) == 10);
}

TEST(HashTableTest, TestBasic2) {
  const size_t buckets = 4;
  const double load_factor = 0.75;
  hash_table<int, int> hash_table(buckets, load_factor);

  for (int i : std::views::iota(1, 11)) {
    hash_table.insert(i, i);
  }

  auto even = [](int i) {
    return i % 2 == 0;
  };

  for (int i : std::views::iota(1, 11) | std::views::filter(even)) {
    hash_table.erase(i);
  }

  EXPECT_TRUE(hash_table.contains(5));
  EXPECT_TRUE(!hash_table.contains(8));
  EXPECT_TRUE(hash_table.get(7) == 7);

  try {
    hash_table.get(4);
  } catch (const std::exception& e) {
    EXPECT_TRUE(std::strcmp(e.what(), "The key doesn't exist\n") == 0);
  }
}

TEST(HashTableTest, TestConstructor) {
  const size_t buckets = 4;
  const double load_factor = 0.75;
  hash_table<int, int> hash_table1(buckets, load_factor);

  for (int i : std::views::iota(1, 11)) {
    hash_table1.insert(i, i);
  }

  hash_table<int, int> hash_table2(hash_table1);
  for (int i : std::ranges::iota_view(1, 11)) {
    hash_table2.contains(i);
  }

  hash_table1.erase(1);
  EXPECT_TRUE(hash_table1.size() != hash_table2.size());
  EXPECT_TRUE(!hash_table1.contains(1));
  EXPECT_TRUE(hash_table2.contains(1));
  EXPECT_TRUE(hash_table1.get(2) == hash_table2.get(2));
  hash_table1.insert(2, 20);
  EXPECT_TRUE(hash_table1.get(2) != hash_table2.get(2));

  hash_table<int, int> hash_table3(stl::move(hash_table2));
  EXPECT_TRUE(hash_table2.empty());
}

TEST(HashTableTest, TestAssignment) {
  const size_t buckets = 2;
  const double load_factor = 0.75;
  hash_table<int, int> hash_table1(buckets, load_factor);

  for (int i : std::views::iota(1, 11)) {
    hash_table1.insert(i, i);
  }

  hash_table<int, int> hash_table2;
  hash_table2 = hash_table1;
  for (int i : std::views::iota(1, 11)) {
    EXPECT_TRUE(hash_table2.get(i) == hash_table1.get(i));
  }
  hash_table1.erase(10);
  EXPECT_TRUE(hash_table1.size() != hash_table2.size());
  EXPECT_TRUE(!hash_table1.contains(10));
  EXPECT_TRUE(hash_table2.contains(10));

  hash_table<int, int> hash_table3;
  hash_table3 = stl::move(hash_table2);
  EXPECT_TRUE(!hash_table3.empty());
  EXPECT_TRUE(hash_table2.empty());
}
