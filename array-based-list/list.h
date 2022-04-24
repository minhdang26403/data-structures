// Header file for list.cpp

#ifndef LIST_H
#define LIST_H

#include <cstdlib>
#include <iostream>

using namespace std;

class List
{
public:

  // Default constructor
  List();

  // Copy constructor
  List(const List& src);

  // Destructor
  ~List();

  /* Append a new item to the end of the list 
  Parameters: a string item
  Return values: None */
  void add(string item);

  /* Return the number of items in the list 
  Parameters: None
  Return values: the size of the list */
  int size() const;

  /* Find the index of a value item
  Parameters: a string item
  Return values: index of the item, or -1 if not found */
  int index(string item);

  /* Insert item in position index
  Parameters: a string item and the position index we want to insert 
  Return values: None */
  void insert(int index, string item);

  /* Delete the item in position index
  Parameters: the index of the item we want to remove
  Return values: None */
  void remove(int index);

  /* Return a string representation of the list 
  Parameters: None
  Return values: a string representation of the list */
  string toString() const;

  // Overload indexing operator
  // Also check for index out of range
  string& operator[](int index);

  // Assignment operator to make a deep copy
  List& operator=(const List& src);

  // Concatenation operator
  List& operator+=(const List& src);

private:

  static const int INITIAL_CAPACITY = 10;

  string *data;
  int capacity;
  int count;
  
  /* Make a deep copy list from the source list 
  Parameters: a source list
  Return values: None */
  void deepCopy(const List& src);

  /* Expand the capacity of the current list object 
  Parameters: an integer representing newCapacity 
  Return values: None */
  void expandCapacity(int newCapacity);
};

std::ostream& operator<<(std::ostream& os, List& list);

#endif