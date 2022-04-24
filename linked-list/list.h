// list.h

#ifndef LIST_H
#define LIST_H

#include <cstdlib>
#include <iostream>

using namespace std;

class Node
{
  public:
 
    string value;
    Node *next;
    Node *prev;
	
    Node();
    Node(string initValue);
    Node(string initValue, Node *initNext);
};

class List
{
  public:
	
    List();                               // default constructor
    List(const List& src);                // copy constructor
    ~List();                              // destructor

    void add(string item);                // append a new item to the end of the list
    int size() const;                     // return the number of items in the list
    int index(string item) const;         // return index of item, or throw ValueError
    void insert(int index, string item);  // insert item at index or throw IndexError
    void remove(int index);               // delete item at index or throw IndexError
    string toString() const;              // return a string representation of the list

    string& operator[](int index);        // indexing operator (may throw IndexError)
    List& operator=(const List& src);     // assignment operator
    List& operator+=(const List& src);    // concatenation operator

    void reverse();                       // reverse the order of the items in the list
	
 private:
 
    Node *head;                           // head of the linked list
    Node *tail;                           // tail of the linked list
    int count;                            // number of items in the list

    void deepCopy(const List& src);       // used by the copy constructor and =
    void deallocate();                    // deallocate the list; used by the destructor and =
    Node* find(int index);                // return a pointer to the node in position index
                                          //    used by insert, remove, and []

    // Recursive functions

    void insert(Node* front, int index, string item);  // called by public insert
    void reverse(Node *front);                         // called by public reverse
};

std::ostream& operator<<(std::ostream& os, const List& list);

class IndexError { };    // exception thrown when an index is out of range
class ValueError { };    // exception thrown when a value is not found

#endif