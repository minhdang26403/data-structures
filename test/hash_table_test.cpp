#include "hash_table.h"

#include <cassert>
#include <exception>
#include <iostream>

void Test1() {
  std::cout << "-------Test 1-------\n";
  ds::HashTable<int, int> hash_table;
  for (int i = 0; i < 10; ++i) {
    hash_table.Insert(i + 1, i + 1);
  }
  std::cout << "Hash table: " << hash_table.ToString() << '\n';

  hash_table.Delete(2);
  hash_table.Delete(6);
  hash_table.Delete(4);

  assert(hash_table.Contains(1));
  assert(!hash_table.Contains(2));
  hash_table.Insert(5, 10);
  std::cout << "Hash table: " << hash_table.ToString() << '\n';

}

void Test2() {
  std::cout << "-------Test 2-------\n";
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
    std::cout << e.what();
  }

}

void Test3() {
  std::cout << "-------Test 3-------\n";
  ds::HashTable<int, int> hash_table1(4, 0.75);

  for (int i = 0; i < 10; ++i) {
    hash_table1.Insert(i + 1, i + 1);
  }


  ds::HashTable<int, int> hash_table2(hash_table1);
  std::cout << "Hash table 1: " << hash_table1.ToString() << '\n';
  std::cout << "Hash table 2: " << hash_table2.ToString() << '\n';

  hash_table1.Delete(1);
  assert(hash_table1.Size() != hash_table2.Size());
  assert(!hash_table1.Contains(1));
  assert(hash_table2.Contains(1));
  std::cout << "Hash table 1: " << hash_table1.ToString() << '\n';
  std::cout << "Hash table 2: " << hash_table2.ToString() << '\n';

  assert(hash_table1.Get(2) == hash_table2.Get(2));
  hash_table1.Insert(2, 20);
  assert(hash_table1.Get(2) != hash_table2.Get(2));
  
  // Can't use hash table 2 any more
  ds::HashTable<int, int> hash_table3(std::move(hash_table2));
  std::cout << "Hash table 2: " << hash_table2.ToString() << '\n';
  std::cout << "Hash table 3: " << hash_table3.ToString() << '\n';
}

void Test4() {
  std::cout << "-------Test 4-------\n";
  ds::HashTable<int, int> hash_table1(2, 0.75);

  for (int i = 0; i < 10; ++i) {
    hash_table1.Insert(i + 1, i + 1);
  }

  ds::HashTable<int, int> hash_table2;
  hash_table2 = hash_table1;
  std::cout << "Hash table 1: " << hash_table1.ToString() << '\n';
  std::cout << "Hash table 2: " << hash_table2.ToString() << '\n';
  assert(hash_table1.Get(1) == hash_table1.Get(1));
  hash_table1.Delete(10);
  assert(hash_table1.Size() != hash_table2.Size());
  assert(!hash_table1.Contains(10));
  assert(hash_table2.Contains(10));

  ds::HashTable<int, int> hash_table3;
  hash_table3 = std::move(hash_table2);
  std::cout << "Hash table 2: " << hash_table2.ToString() << '\n';
  std::cout << "Hash table 3: " << hash_table3.ToString() << '\n';
}

int main() {
  // Test1();
  // Test2();
  // Test3();
  // Test4();

  std::cout << "All test cases passed\n";

  return 0;
}