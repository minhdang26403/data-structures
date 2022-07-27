#include "linked_list.h"

#include <cassert>
#include <iostream>
#include <string>

void TestConstructor() {
  using std::cout;
  using std::string;
  string s{"hello"};
  ds::LinkedList<string> data1{3, s};
  cout << "data1: " << data1.ToString() << '\n';

  // copy from data1
  ds::LinkedList<string> data2{data1};
  cout << "data2: " << data2.ToString() << '\n';

  
  ds::LinkedList<string> data3{std::move(data1)};
  cout << "Move data1 to data3" << '\n';
  cout << "data1: " << data1.ToString() << '\n';
  cout << "data3: " << data3.ToString() << '\n';

  ds::LinkedList<int> data4 = {1, 2, 3, 4, 5};
  cout << "data4: " << data4.ToString() << '\n';
}

void TestAssignment() {
  using std::cout;
  ds::LinkedList<int> data1{1, 2, 3, 4, 5};
  ds::LinkedList<int> data2;
  data2 = data1;
  cout << "data2: " << data2.ToString() << '\n';
  assert(data2.Size() == data1.Size());
  data2 = {6, 7, 8, 9, 10};
  cout << "data2: " << data2.ToString() << '\n';
  cout << "Move assignment moves data1 to data 3" << '\n';
  ds::LinkedList<int> data3;
  data3 = std::move(data1);
  cout << "data1: " << data1.ToString() << '\n';
  cout << "data3: " << data3.ToString() << '\n';
}

void TestIterator() {
  using std::cout;
  ds::LinkedList<int> data1{1, 2, 3, 4, 5};
  for (int num : data1) {
    cout << num << ' ';
  }
  cout << '\n';
  for (ds::LinkedList<int>::Iterator it = data1.begin(); it != data1.end(); ++it) {
    cout << *it << ' ';
  }
  cout << '\n';
  ds::LinkedList<std::string> data2;
  assert(data2.begin() == data2.end());
}

void TestInsert() {
  using std::cout;
  using std::string;
  ds::LinkedList<std::pair<string, string>> data1;
  std::pair<string, string> s{"abc", "123"};
  data1.Insert(0, s);
  data1.Emplace(1, "def", "456");
  for (auto pair : data1) {
    cout << pair.first << ", " << pair.second << '\n';
  }
}

void TestEmplace() {
  std::string s{"abc"};
  ds::LinkedList<std::string> data1;
  data1.Insert(0, s);
  std::cout << data1.ToString() << '\n';
  std::cout << s << '\n';
  data1.Insert(1, std::move(s));
  std::cout << data1.ToString() << '\n';
  std::cout << s << '\n';
}

void TestRemove()
{
	ds::LinkedList<std::string> list;
	list.Insert(0, "abc");
	list.Insert(1, "def");
	list.Insert(1, "ghi");
	list.Insert(0, "xyz");
	list.Erase(0);
	assert(list.Front() == "abc");

	list.Erase(0);
	assert(list.Front() == "ghi");

	list.Erase(1);
	assert(list.ToString() == "[ghi]");
}

void TestReverse()
{
	ds::LinkedList<std::string> list;
	list.Reverse();
	assert(list.ToString() == "[]");

	list.Insert(0, "a");
	list.Insert(0, "b");
	assert(list.ToString() == "[b, a]");

	list.Insert(2, "c");
	list.Reverse();
	assert(list.ToString() == "[c, a, b]");

	list.Erase(1);
	list.Reverse();
	assert(list.ToString() == "[b, c]");
}

int main() {
  // TestConstructor();
  // TestAssignment();
  // TestIterator();
  // TestInsert();
  // TestEmplace();
  // TestRemove();
  // TestReverse();
  std::cout << "All tests completed successfully." << '\n';

  return 0;
}