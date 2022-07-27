#include "vector.h"

#include <cassert>
#include <iostream>
#include <string>

template<typename Type>
std::ostream& operator<<(std::ostream& s, const ds::Vector<Type>& v) {
    s.put('[');
    char comma[3] = {'\0', ' ', '\0'};
    for (uint32_t i = 0; i < v.Size(); ++i) {
        s << comma << v[i];
        comma[0] = ',';
    }
    return s << ']';
}

void TestConstructor() {
  ds::Vector<std::string> strs1 = {"abc", "def", "qwe"};
  std::cout << strs1 << '\n';
  ds::Vector<std::string> strs2(strs1);
  std::cout << strs2 << '\n';
  // Check for deep copy
  strs2[2] = "xyz";
  assert(strs1[2] != strs2[2]);

  ds::Vector<int> data2(5, 10);
  std::cout << data2 << '\n';

  // Move string1 to string3
  ds::Vector<std::string> strs3(std::move(strs1));
  std::cout << strs3 << '\n';
  std::cout << strs1 << '\n';

  assert(strs1.Size() == 0);

  std::cout << "Constructor test passed" << '\n';
}

void TestAssignment() {
  using std::string;
  ds::Vector<string> strs1 = {"abc", "def", "qwe"};
  ds::Vector<string> strs2;
  assert(strs2.Size() == 0);
  strs2 = strs1;
  std::cout << strs1 << '\n';
  std::cout << strs2 << '\n';
  strs2[0] = "xyz";
  assert(strs1[0] != strs2[0]);

  ds::Vector<string> strs3;
  strs3 = std::move(strs2);
  std::cout << strs3 << '\n';
  std::cout << strs2 << '\n';

  std::cout << "Assignment test passed" << '\n';
}

void TestInsert() { 
  ds::Vector<std::string> data1;
	data1.PushBack("abc");
	assert(data1[0] == "abc");

	// test expandCapacity()
	int i = data1.Size();
	for (; i < 10; i++) {
		data1.PushBack("def");
	}
	assert(data1[i - 1] == "def");

	ds::Vector<std::string> data2;
	data2.Insert(0, "abc");
	assert(data2.Size() == 1);
	assert(data2[0] == "abc");
	data2.Insert(1, "def");
	data2.Insert(1, "ghi");
	assert(data2[1] == "ghi");
	assert(data2[2] == "def");
	data2.Insert(3, "xyz");
	assert(data2[3] == "xyz");

  std::cout << "Insert test passed" << '\n';
}

void TestRemove() {
	ds::Vector<std::string> data;
	data.Insert(0, "abc");
	data.Insert(1, "def");
	data.Insert(1, "ghi");
	data.Insert(0, "xyz");
	data.Remove(0);
	assert(data[0] == "abc");
	data.Remove(0);
	assert(data[0] == "ghi");

  std::cout << "Remove test passed" << '\n';
}

void TestIterator() {
  ds::Vector<std::string> data1 = {"ab", "cd", "ef", "gh"};
  for (std::string s : data1) {
    std::cout << s << '\n';
  }
  ds::Vector<int> data2;
  for (int i = 0; i < 10; ++i) {
    data2.PushBack(i);
  }
  std::cout << data2 << '\n';
  ds::Vector<int> data3;
  for (ds::Vector<int>::Iterator it = data2.begin(); it != data2.end(); ++it) {
    data3.PushBack(*it);
  }
  std::cout << data3 << '\n';

  std::cout << *data1.cbegin() << '\n';
}

void TestEmplace() {
  ds::Vector<std::pair<int, int>> data1;
  std::pair<int, int> a {1, 2};
  data1.PushBack(a);
  data1.EmplaceBack(3, 4);
  for (auto pair : data1) {
    std::cout << pair.first << ", " << pair.second << '\n';
  }
}

int main()
{ 
  // TestConstructor();
  // TestAssignment();
	// TestInsert();
	// TestRemove();
  // TestIterator();
  // TestEmplace();
  using std::cout;
	
  ds::Vector<std::string> data1;
  std::string s{"abc"};
  data1.PushBack(s);
  cout << data1 << '\n';
  cout << s << '\n';

	cout << "All tests completed successfully." << '\n';
	
	return 0;
}