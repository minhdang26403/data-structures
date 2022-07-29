#include "hash_table.h"

#include <cassert>
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


int main() {
  Test();

  std::cout << "All test cases passed\n";

  return 0;
}