// list.cpp

#include "list.h"
#include <string>

using namespace std;

List::List() {
    capacity = INITIAL_CAPACITY;
    count = 0;
    data = new string[capacity];
}

List::List(const List&src) {
    deepCopy(src);
}

List::~List() {
    delete []data;
}

void List::add(string item) {
    insert(count, item);
}

int List::size() const {
    return count;
}

int List::index(string item) {
    for (int i = 0; i < count; i++) {
        if (data[i] == item) {
            return i;
        }
    }
    return -1;
}

void List::insert(int index, string item) {
    if (index < 0 || index > count) {
        cerr << "insert: index out of range";
        exit(1);
    }
    if (count == capacity) {
        expandCapacity(capacity * 2);
    }
    for (int i = count; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = item;
    count++;
}

void List::remove(int index) {
    if (count == 0) {
        cerr << "remove: attempted to remove from an empty list";
        exit(1);
    }
    if (index < 0 || index >= count) {
        cerr << "remove: index out of range";
        exit(1);
    }
    count--;
    for (int i = index; i < count; i++) {
        data[i] = data[i + 1];
    }
}

string List::toString() const {
    if (count == 0) return "[]";
    string str = "[\"" + data[0] + "\"";
    for (int i = 1; i < count; i++) {
        str += ", " + ("\"" + data[i] + "\"");
    }
    str += "]";
    return str;
}

string& List::operator[](int index) {
    if (index < 0 || index >= count) {
        cerr << "List index out of range";
        exit(1);
    }
    return data[index];
}

List& List::operator=(const List&src) {
    if (this != &src) {
        delete []data;
        deepCopy(src);
    }
    return *this;
}

List& List::operator+=(const List&src) {
    int oldLength = count;
    int newLength = count + src.count;
    if (newLength >= capacity) {
        expandCapacity(newLength + INITIAL_CAPACITY); // give the list some more space
    }
    count = newLength;
    for (int i = 0; i < src.count; i++) {
        data[oldLength + i] = src.data[i];
    }
    return *this;
}

void List::deepCopy(const List &src) {
    count = src.count;
    capacity = src.capacity;
    data = new string[capacity];
    for (int i = 0; i < count; i++) {
        data[i] = src.data[i];
    }
}

void List::expandCapacity(int newCapacity) {
    string *oldData = data;
    capacity = newCapacity;
    data = new string[capacity];
    for (int i = 0; i < count; i++) {
        data[i] = oldData[i];
    }
    delete []oldData;
}

ostream& operator<<(ostream& os, List& list) {
    return os << list.toString();
}