#include "hash_table.h"

#include <cassert>
#include <exception>
#include <iostream>

void Test() {
  ds::HashTable<int, int> hash_table;
  for (int i = 0; i < 10; ++i) {
    hash_table.Insert(i + 1, i + 1);
  }
  std::cout << hash_table.ToString() << '\n';

  hash_table.Delete(2);
  hash_table.Delete(6);
  hash_table.Delete(4);

  assert(hash_table.Contains(1));
  assert(!hash_table.Contains(2));
  hash_table.Insert(5, 10);
  std::cout << hash_table.ToString() << '\n';

}

void Test2() {
  ds::HashTable<int, int> hash_table(4, 0.75);

  for (int i = 0; i < 10; ++i) {
    hash_table.Insert(i + 1, i + 1);
  }

  for (int i = 0; i < 10; ++i) {
    if (i % 2 == 0) {
      hash_table.Delete(i);
    }
  }

  assert(hash_table.Contains(5));
  assert(!hash_table.Contains(8));
  assert(hash_table.Get(7) == 7);
  // Get value from non-exist key returns default value
  try {
    hash_table.Get(4);
  } catch (const std::exception &e) {
    std::cout << "The key doesn't exist\n";
  }

}

int main() {
  // Test();
  Test2();

  std::cout << "All test cases passed\n";

  return 0;
}