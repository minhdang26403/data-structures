#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "utility.h"

namespace stl {

class IndexError {};

template<typename T>
struct Node {
  T value_{};
  Node* next_{};
  Node* prev_{};

  Node() = default;

  Node(const T& value, Node* next = nullptr, Node* prev = nullptr)
      : value_(value), next_(next), prev_(prev) {}

  Node(T&& value, Node* next = nullptr, Node* prev = nullptr)
      : value_(stl::move(value)), next_(next), prev_(prev) {}
};

template<typename T>
class list {
 public:
  /** type aliases */
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = Node<T>*;

  /** Implement iterator for `list` class */
  class iterator {
   public:
    iterator(pointer ptr) : m_ptr_(ptr) {}

    pointer operator->() { return m_ptr_; }

    reference operator*() { return m_ptr_->value_; }

    iterator& operator++() {
      m_ptr_ = m_ptr_->next_;
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator& operator--() {
      m_ptr_ = m_ptr_->prev_;
      return *this;
    }

    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return *this;
    }

    bool operator==(const iterator& other) { return m_ptr_ == other.m_ptr_; }

    bool operator!=(const iterator& other) { return !(*this == other); }

   private:
    pointer m_ptr_;
  };

  /**
   * Member functions
   */

  /**
   * Default constructor
   */
  list() = default;

  /**
   * Constructs the linked list with `count` elements of `value` values
   * @param count the size of the linked list
   * @param value the value to initialize element with 
   */
  list(size_type count, const T& value) : size_(count) {
    head_ = new Node<T>(value);
    tail_ = head_;
    for (size_type i = 1; i < count; ++i) {
      auto* new_node = new Node<T>(value);
      tail_->next_ = new_node;
      new_node->prev_ = tail_;
      tail_ = tail_->next_;
    }
  }

  /**
   * Copy constructor
   * @param src the source object to copy from
   */
  list(const list& src) { deep_copy(src); }

  /**
   * Move constructor
   * @param src the source object to stl::move from
   */
  list(list&& src) { src.swap(*this); }

  /**
   * Construct a new list with an initializer list
   * @param init the initializer list
   */
  list(std::initializer_list<T> init) : size_(init.size()) {
    auto iter = init.begin();
    head_ = new Node<T>(*iter);
    tail_ = head_;
    ++iter;
    for (; iter != init.end(); ++iter) {
      auto new_node = new Node<T>(*iter);
      tail_->next_ = new_node;
      new_node->prev_ = tail_;
      tail_ = tail_->next_;
    }
  }

  /**
   * Destructor
   */
  ~list() { deallocate(); }

  /**
   * Copy assignment operator 
   * @param src the source object to assign from
   * @return a reference to the calling object
   */
  list& operator=(const list& src) {
    list copy(src);
    copy.swap(*this);
    return *this;
  }

  /**
   * Move assignment operator
   * @param src the source object to stl::move from
   * @return a reference to the calling object
   */
  list& operator=(list&& src) noexcept {
    src.swap(*this);
    return *this;
  }

  /**
   * Assigns the values of the initializer list to the linked list 
   * @param init the initializer list
   * @return a reference to the calling object
   */
  list& operator=(std::initializer_list<T> init) {
    list copy(init);
    copy.swap(*this);
    return *this;
  }

  /** Element access */

  /** @return a reference to the first element */
  reference front() { return head_->value_; }

  const_reference front() const { return head_->value_; }

  /** @return a reference to the last element */
  reference back() { return tail_->value_; }

  const_reference back() const { return tail_->value_; }

  /** Iterators */
  iterator begin() noexcept { return iterator(head_); }

  iterator end() noexcept {
    return iterator((tail_ == nullptr) ? nullptr : tail_->next_);
  }

  /** Capacity */

  /** @return true if the linked list is empty; false otherwise */
  bool empty() const noexcept { return size_ == 0; }

  /** @return the size of the linked list */
  size_type size() const { return size_; }

  /** For debugging */
  std::string to_string() const {
    if (head_ == nullptr) {
      return "[]";
    }
    std::stringstream ss;
    ss << "[";
    auto current = head_;
    while (current->next_ != nullptr) {
      ss << current->value_ << ", ";
      current = current->next_;
    }
    ss << current->value_ << "]";
    return ss.str();
  }

  /** Modifiers */

  /** erase all elements of the linked list */
  void clear() noexcept {
    deallocate();
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
  }

  /**
   * Inserts value before `index`
   * @param index the position before the place the element will be inserted
   * @param value the value of the element
   */
  void insert(size_type index, const T& value) { emplace(index, value); }

  /** Overload method taking rvalue reference */
  void insert(size_type index, T&& value) {
    emplace(index, stl::move(value));
  }

  /**
   * Constructs and inserts an element into the position `index`
   * @param index the position to insert
   * @param args the arguments to construct the element
   */
  template<typename... Args>
  void emplace(size_type index, Args&&... args) {
    if (index < 0 || index > size_) {
      throw IndexError();
    }

    auto new_node =
        new Node<T>(stl::move(T(forward<Args>(args)...)));
    if (index == 0) {
      new_node->next_ = head_;
      if (head_ != nullptr) {
        head_->prev_ = new_node;
      }
      head_ = new_node;
    } else {
      pointer prev_node = find(index - 1);
      new_node->next_ = prev_node->next_;
      new_node->prev_ = prev_node;
      prev_node->next_ = new_node;
    }
    if (index == size_) {
      tail_ = new_node;
    } else {
      new_node->next_->prev_ = new_node;
    }
    ++size_;
  }

  /**
   * Erases the element at `index` position from the linked list
   * @param index the position to delete
   */
  void erase(size_type index) {
    if (index < 0 || index >= size_) {
      throw IndexError();
    }

    pointer node_to_delete;
    if (index == 0) {
      node_to_delete = head_;
      head_ = head_->next_;
      if (head_ == nullptr) {
        tail_ = nullptr;
      }
    } else {
      pointer prev_node = find(index - 1);
      node_to_delete = prev_node->next_;
      prev_node->next_ = prev_node->next_->next_;
      if (index == size_ - 1) {
        tail_ = prev_node;
      } else {
        prev_node->next_->prev_ = prev_node;
      }
    }
    delete node_to_delete;
    --size_;
  }

  /**
   * Erases the element with `value` value
   * @param value the value of the element to erase
   */
  void erase(const T& value) {
    pointer prev = nullptr;
    pointer node_to_delete = head_;
    while (node_to_delete != nullptr && node_to_delete->value_ != value) {
      prev = node_to_delete;
      node_to_delete = node_to_delete->next_;
    }
    if (prev == nullptr) {
      head_ = head_->next_;
      if (head_ == nullptr) {
        tail_ = nullptr;
      }
    } else {
      prev->next_ = node_to_delete->next_;
      if (prev->next_ != nullptr) {
        prev->next_->prev_ = prev;
      } else {
        tail_ = prev;
      }
    }
    delete node_to_delete;
    --size_;
  }

  /** Appends the given element value to the end of the linked list 
   * @param value the value of the element to append
   */
  void push_back(const T& value) { emplace(size_, value); }

  void push_back(T&& value) { emplace(size_, stl::move(value)); }

  /** Prepends the given element value to the beginning of the linked list 
   * @param value the value of the element to prepend
   */
  void push_front(const T& value) { emplace(0, value); }

  void push_front(T&& value) { emplace(0, stl::move(value)); }

  /**
   * Constructs and pushes an element to the end of the linked list
   * @param args the arguments to constructs the element
   * @return the value of the element
   */
  template<typename... Args>
  reference emplace_back(Args&&... args) {
    emplace(size_, forward<Args>(args)...);
    return back();
  }

  /**
   * Constructs and pushes an element to the beginning of the linked list
   * @param args the arguments to constructs the element
   * @return the value of the element
   */
  template<typename... Args>
  reference emplace_front(Args&&... args) {
    emplace(0, forward<Args>(args)...);
    return front();
  }

  /** Removes the last element of the linked list */
  void pop_back() { erase(size_ - 1); }

  /** Removes the first element of the linked list */
  void pop_front() { erase(static_cast<size_type>(0)); }

  void reverse() noexcept {
    pointer cur = head_;
    while (cur != nullptr) {
      pointer temp = cur->next_;
      cur->next_ = cur->prev_;
      cur->prev_ = temp;
      cur = temp;
    }
    std::swap(head_, tail_);
  }

 private:
  /**
   * Finds the node at the specified index
   * @param index the index of the node needed to find
   * @return pointer to that node
   */
  pointer find(size_type index) {
    if (index < 0 || index >= size_) {
      throw IndexError();
    }

    auto current = head_;
    for (uint32_t i = 0; i < index; ++i) {
      current = current->next_;
    }
    return current;
  }

  /**
   * Swaps the content of two linked list objects
   * @param rhs the other linked list
   */
  void swap(list& rhs) noexcept {
    using std::swap;
    swap(head_, rhs.head_);
    swap(tail_, rhs.tail_);
    swap(size_, rhs.size_);
  }

  /** Free all allocated nodes */
  void deallocate() {
    Node<T>* node_to_delete;
    auto current = head_;
    while (current != nullptr) {
      node_to_delete = current;
      current = current->next_;
      delete node_to_delete;
    }
  }

  /** Creates a deep copy from the source linked list */
  void deep_copy(const list& src) {
    if (src.head_ == nullptr) {
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      Node<T>* src_node = src.head_;
      head_ = new Node<T>(src_node->value_);
      tail_ = head_;
      src_node = src_node->next_;
      for (; src_node != nullptr; src_node = src_node->next_) {
        tail_->next_ = new Node<T>(src_node->value_);
        tail_->next_->prev_ = tail_;
        tail_ = tail_->next_;
      }
    }
    size_ = src.size_;
  }

  // Always initialize pointers by default if the constructor doesn't specify
  Node<T>* head_{};
  Node<T>* tail_{};
  size_type size_{};
};

}  // namespace stl

#endif  // LINKED_LIST_H_