// Authors: Dang and Ava
// list.cpp
// This is a doubly linked list implementation of a List class.

#include <sstream>
#include "list.h"

Node::Node()
{
   value = "";
   next = NULL;
   prev = NULL;
}

Node::Node(string initValue)
{
   value = initValue;
   next = NULL;
   prev = NULL;
}

Node::Node(string initValue, Node *initNext)
{
   value = initValue;
   next = initNext;
   prev = NULL;
}

List::List()
{
	head = NULL;
	tail = NULL;
	count = 0;
}

List::List(const List& src)
{
	deepCopy(src);
}

List::~List()
{
	deallocate();
}

void List::add(string item)
{
	Node *newNode = new Node(item);
	
	if (head != NULL)  // list is not empty
	{
		tail->next = newNode;
		newNode->prev = tail;
	}
	else
	{
		head = newNode;
	}
	
	tail = newNode;
	count++;
}

int List::size() const
{
    return count;
}

int List::index(string item) const
{
    Node *current = head;
    int counter = 0;
    
    while ((current != NULL) && (current->value != item))
    {
        counter++;
        current = current->next;
    }
    if (current == NULL)
        //throw ValueError();
		return -1;
    else
        return counter;
}

// void List::insert(int index, string item)
// {
// 	if ((index < 0) || (index > count))
// 		throw IndexError();
	
// 	Node *newNode = new Node(item);
// 	if (index == 0)
// 	{
// 	    newNode->next = head;
// 		// if (head != NULL)
// 		// 	head->prev = newNode;
// 		head = newNode;
// 	}
// 	else
// 	{
// 	    Node *prevNode = find(index - 1);
// 	    newNode->next = prevNode->next;
// 		newNode->prev = prevNode;
// 		prevNode->next = newNode;
// 		// if (newNode->next != NULL)
// 		// 	newNode->next->prev = newNode;
// 	}
	
// 	if (index == count)
// 		tail = newNode;
// 	else
// 		newNode->next->prev = newNode;

// 	count++;
// }

void List::remove(int index)
{
	if ((index < 0) || (index >= count))
		throw IndexError();
		
	Node *nodeToDelete;
	
	if (index == 0)
	{
		nodeToDelete = head;
		head = head->next;
		if (head == NULL)  // equivalently, if (count == 1)
		    tail = NULL;
	}
	else
	{
		Node *prevNode = find(index - 1);
		nodeToDelete = prevNode->next;
		prevNode->next = prevNode->next->next;
		if (index == count - 1) {
			tail = prevNode;
		} else {
			prevNode->next->prev = prevNode;
		}
	}
	delete nodeToDelete;
	count--;
}

string List::toString() const
{
    if (head == NULL)
        return "[]";
    
    std::stringstream ss;
    ss << "[";
    
	Node *current = head;
	while (current->next != NULL)  // get all but the last item
	{
		ss << current->value << ", ";
		current = current->next;
	}
	ss << current->value << "]";  // last item followed by closing bracket
	
	return ss.str();
}

string& List::operator[](int index)
{
	if ((index < 0) || (index >= count))
		throw IndexError();
		
	Node *node = find(index);
	return node->value;
}

List& List::operator=(const List& src)
{
    if (this != &src)
    {
	    deallocate();
	    deepCopy(src);
	}
	
	return *this;
}

List& List::operator+=(const List& src)
{
    Node *current = src.head;
    while (current != NULL)
    {
        add(current->value);
        current = current->next;
    }
    
    return *this;
}

void List::deepCopy(const List& src)
{
    if (src.head == NULL)
    {
        head = NULL;
	    tail = NULL;
    }
    else
    {
	    Node *srcNode = src.head;
		head = new Node(srcNode->value);
		
		tail = head;
		srcNode = srcNode->next;
	    while (srcNode != NULL)
	    {
		    tail->next = new Node(srcNode->value);
			tail->next->prev = tail;
		    tail = tail->next;
			srcNode = srcNode->next;
	    }
	}
	count = src.count;
}

void List::deallocate()
{
	Node *nodeToDelete;
	Node *current = head;
	
	while (current != NULL)
	{
		nodeToDelete = current;
		current = current->next;
		delete nodeToDelete;
	}
}

// private method used by insert, [], remove
Node* List::find(int index)
{
	if ((index < 0) || (index >= count))
		throw IndexError();

	Node *current = head;
	for (int i = 0; i < index; i++)
		current = current->next;

	return current;
}

std::ostream& operator<<(std::ostream& os, const List& list)
{
	os << list.toString();
	return os;
}


// recursive insert
void List::insert(Node* front, int index, string item)
{
    if (index == 0) {
		Node *newNode = new Node(item);
		newNode->next = head;
		if (head != NULL) {
			head->prev = newNode;
		} else {
			tail = newNode;
		}
		head = newNode;
		count++;
	} else if (index == 1) {
		Node *newNode = new Node(item);
		newNode->next = front->next;
		newNode->prev = front;
		front->next = newNode;
		if (newNode->next != NULL) {
			newNode->next->prev = newNode;
		} else {
			tail = newNode;
		}
		count++;
	} else {
		insert(front->next, index - 1, item);
	}
}

// version of insert that calls the private recursive insert
void List::insert(int index, string item)
{
	if ((index < 0) || (index > count))
		throw IndexError();
		
	insert(head, index, item);
}

// recursive reverse
void List::reverse(Node *front)
{
	if (front == NULL || front->next == NULL) {
		if (front != NULL) 
			front->prev = NULL;
		return;
	}
	reverse(front->next);
	front->next->next = front;
	front->prev = front->next;
	front->next = NULL;
	return;
}

void List::reverse()
{
	reverse(head);
	Node *cur = head;
	head = tail;
	tail = cur;
}

