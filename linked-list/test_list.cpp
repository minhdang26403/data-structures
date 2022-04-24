// Authors: Dang and Ava
// test_list.cpp

#include "list.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

void testDefaultConstructor()
{
	List list;
	assert(list.size() == 0);
	assert(list.toString() == "[]");
}

void testCopyConstructor()
{
	List list1;
	list1.add("hello");
	list1.add("world");
	List list2(list1);
	assert(list2.size() == list1.size());
	assert(list2.toString() == list1.toString());
	assert(list2[0] == list1[0]);
	assert(list2[1] == list1[1]);

	list1.add("abc");
	assert(list1.size() > list2.size());
	assert(list1.toString() != list2.toString());
}

void testAdd()
{
	List list;
	list.add("abc");
	assert(list[0] == "abc");

	int i = list.size();
	for (; i < 10; i++) {
		list.add("def");
	}
	assert(list[i - 1] == "def");
}

void testSize()
{
	List list;
	assert(list.size() == 0);

	list.add("qwe");
	list.insert(0, "xyz");
	assert(list.size() == 2);

	list.remove(0);
	assert(list.size() == 1);

	list.remove(0);
	assert(list.size() == 0);
}

void testIndex()
{
	List list;
	assert(list.index("hello") == -1);

	list.add("hello");
	list.add("world");
	list.add("c++");
	assert(list.index("hello") == 0);
	assert(list.index("c++") == 2);
	assert(list.index("xyz") == -1);

	list.remove(1);
	assert(list.index("world") == -1);
}

void testInsert()
{
	List list;
	list.insert(0, "abc");
	assert(list.size() == 1);
	assert(list.toString() == "[abc]");
	assert(list[0] == "abc");

	list.insert(1, "def");
	list.insert(1, "ghi");
	assert(list[1] == "ghi");
	assert(list[2] == "def");

	list.insert(3, "xyz");
	assert(list[3] == "xyz");
	assert(list.toString() == "[abc, ghi, def, xyz]");

	list.reverse();
	assert(list.toString() == "[xyz, def, ghi, abc]");

	list.insert(0, "k");
	list.insert(5, "j");
	list.insert(2, "h");
	assert(list.toString() == "[k, xyz, h, def, ghi, abc, j]");
}

void testRemove()
{
	List list;
	list.insert(0, "abc");
	list.insert(1, "def");
	list.insert(1, "ghi");
	list.insert(0, "xyz");
	list.remove(0);
	assert(list[0] == "abc");

	list.remove(0);
	assert(list[0] == "ghi");

	list.remove(1);
	assert(list.toString() == "[ghi]");
}

void testIndexing()
{
	List list;
	list.insert(0, "abc");
	list.insert(1, "def");
	list.insert(1, "xyz");
	assert(list[2] == "def");

	list.remove(1);
	assert(list[1] == "def");

	list.insert(0, "qwe"); // qwe, abc, def
	list.insert(3, "xyz"); // qwe, abc, def, xyz
	list.insert(1, "ghi"); // qwe, ghi, abc, def, xyz
	list.reverse();
	assert(list[0] == "xyz");
	assert(list[4] == "qwe");
	assert(list[2] == "abc");
}

void testAssignment()
{
	List list1;
	List list2;
	list1.add("abc");
	list2 = list1;
	list1[0] = "def";
	assert(list1[0] != list2[0]);
	list1.insert(1, "ghi");
	assert(list1.size() > list2.size());
}

void testConcat()
{
	List list1, list2;
	for (int i = 0; i < 15; i++) {
		list1.add(to_string(i));
	}

	for (int i = 15; i < 30; i++) {
		list2.add(to_string(i));
	}
	int oldLength = list1.size();
	list1 += list2;
	assert(list1.size() == oldLength + list2.size());
	for (int i = 0; i < 30; i++) {
		assert(list1[i] == to_string(i));
	}
}

void testReverse()
{
	List list;
	list.reverse();
	assert(list.toString() == "[]");

	list.insert(0, "a");
	list.insert(0, "b");
	assert(list.toString() == "[b, a]");

	list.insert(2, "c");
	list.reverse();
	assert(list.toString() == "[c, a, b]");

	list.remove(1);
	list.reverse();
	assert(list.toString() == "[b, c]");
}

int main()
{
	testDefaultConstructor();
	testCopyConstructor();
	testAdd();
	testSize();
	testIndex();
	testInsert();
	testRemove();
	testIndexing();
	testAssignment();
	testConcat();
	testReverse();

	cout << "All tests completed successfully." << endl;
	
	return 0;
}