#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>

namespace ds {

template<typename Type>
struct Node {
  Type value_{};
  Node *next_{};
  Node *prev_{};

  Node() = default;
  Node(Type value) : value_(value), next_(nullptr), prev_(nullptr) {}
  Node(Type value, Node *next) : value_(value), next_(next), prev_(nullptr) {}
};

template<typename Type>
class LinkedList {
 public:
  /** Type aliases */
  using ValueType = Type;
  using SizeType = std::size_t;
  using Reference = ValueType&;
  using ConstReference = const ValueType&;
  using Pointer = Node<Type>*;

  /** Implement iterator for Vector class */
  class Iterator {
   public:
    Iterator(Pointer ptr) : m_ptr_(ptr) {}

    Pointer operator->() { return m_ptr_; }

    Reference operator*() { return m_ptr_->value_; }

    Iterator& operator++() {
      m_ptr_ = m_ptr_->next_;
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    Iterator& operator--() {
      m_ptr_ = m_ptr_->prev_;
      return *this;
    }

    Iterator operator--(int) {
      Iterator temp = *this;
      --(*this);
      return *this;
    }

    bool operator==(const Iterator& other) {
      return m_ptr_ == other.m_ptr_;
    }

    bool operator!=(const Iterator& other) {
      return !(*this == other);
    }

   private:
    Pointer m_ptr_;
  };
  
  /**
   * Member functions
   */

  /**
   * Default constructor
   */
  LinkedList() = default;

  /**
   * Constructs the linked list with `count` elements of `value` values
   * @param count the size of the linked list
   * @param value the value to initialize element with 
   */
  explicit LinkedList(SizeType count, const Type& value) : size_(count) {
    auto *current = new Node<Type>(value);
    head_ = current;
    for (SizeType i = 1; i < count; ++i) {
      auto *new_node = new Node<Type>(value);
      current->next_ = new_node;
      new_node->prev_ = current;
      current = current->next_;
    }
    tail_ = current;
  }

  /**
   * Copy constructor
   * @param src the source object to copy from
   */
  LinkedList(const LinkedList& src) {
    DeepCopy(src);
  }

  /**
   * Move constructor
   * @param src the source object to move from
   */
  LinkedList(LinkedList&& src) {
    src.Swap(*this);
  }

  /**
   * Construct a new LinkedList with an initializer list
   * @param init the initializer list
   */
  LinkedList(std::initializer_list<Type> init) : size_(init.size()){
    auto iter = init.begin();
    head_ = new Node<Type>(*iter);
    tail_ = head_;
    ++iter;
    for (; iter != init.end(); ++iter) {
      auto new_node = new Node<Type>(*iter);
      tail_->next_ = new_node;
      new_node->prev_ = tail_;
      tail_ = tail_->next_;
    }
  }

  /**
   * Destructor
   */
  ~LinkedList() {
    Deallocate();
  }

  /**
   * Copy assignment operator 
   * @param src the source object to assign from
   * @return a reference to the calling object
   */
  LinkedList& operator=(const LinkedList& src) {
    LinkedList copy(src);
    copy.Swap(*this);
    return *this;
  }

  /**
   * Move assignment operator
   * @param src the source object to move from
   * @return a reference to the calling object
   */
  LinkedList& operator=(LinkedList&& src) noexcept {
    src.Swap(*this);
    return *this;
  }

  /**
   * Assigns the values of the initializer list to the linked list 
   * @param init the initializer list
   * @return a reference to the calling object
   */
  LinkedList& operator=(std::initializer_list<Type> init) {
    LinkedList copy(init);
    copy.Swap(*this);
    return *this;
  }

  /** Element access */

  /** @return a reference to the first element */
  Reference Front() { return head_->value_; }
  ConstReference Front() const { return head_->value_; }

  /** @return a reference to the last element */
  Reference Back() { return tail_->value_; }
  ConstReference Back() const { return tail_->value_; }

  /** Iterators */
  Iterator begin() noexcept { return Iterator(head_); }
  Iterator end() noexcept { return Iterator((tail_ == nullptr) ? nullptr : tail_->next_); }

  /** Capacity */

  /** @return true if the linked list is empty; false otherwise */
  bool IsEmpty() const noexcept { return size_ == 0; }
  
  /** @return the size of the linked list */
  SizeType Size() const { return size_; }

  /** For debugging */
  std::string ToString() const {
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
  
  /** Erase all elements of the linked list */
  void Clear() noexcept {
    Deallocate();
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
  }

  /**
   * Inserts value before `index`
   * @param index the position before the place the element will be inserted
   * @param value the value of the element
   */
  void Insert(SizeType index, const Type& value) {
    if (index < 0 || index > count) {
      throw IndexError();
    }
    
    auto new_node = Node<Type>(value);
    if (index == 0) {
      new_node->next_ = head_;
      if (head_ != nullptr) {
        head_->prev_ = new_node;
      }
      head_ = new_node;
    } else {
      Node *prev_node = Find(index - 1);
      new_node->next_ = prev_node->next_;
      new_node->prev_ = prev_node;
    }
    if (index == size_) {
      tail_ = new_node;
    } else {
      new_node->next_->prev_ = new_node;
    }
    ++size_;
  }

 private:
  /**
   * Finds the node at the specified index
   * @param index the index of the node needed to find
   * @return pointer to that node
   */
  Pointer Find(SizeType index) {
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
  void Swap(LinkedList& rhs) noexcept {
    using std::swap;
    std::swap(head_, rhs.head_);
    std::swap(tail_, rhs.tail_);
    std::swap(size_, rhs.size_);
  }

  /** Free all allocated nodes */
  void Deallocate() {
    Node<Type> *node_to_delete;
    auto current = head_;
    while (current != nullptr) {
      node_to_delete = current;
      current = current->next_;
      delete node_to_delete;
    }
  }

  /** Creates a deep copy from the source linked list */
  void DeepCopy(const LinkedList &src) {
    if (src.head_ == nullptr) {
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      Node<Type> *src_node = src.head_;
      head_ = new Node<Type>(src_node->value_);
      tail_ = head_;
      src_node = src_node->next_;
      for (; src_node != nullptr; src_node = src_node->next_) {
        tail_->next_ = new Node<Type>(src_node->value_);
        tail_->next_->prev_ = tail_;
        tail_ = tail_->next_;
      }
    }
    size_ = src.size_;
  }

  Node<Type> *head_{};
  Node<Type> *tail_{};
  SizeType size_{};
};

class IndexError { };

} // namespace ds

#endif  // LINKED_LIST_H_