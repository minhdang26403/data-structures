#ifndef LINKED_LIST_H
#define LINKED_LIST_H

namespace ds {

template<typename Type>
struct Node {
  Type value_;
  Node *next_;
  Node *prev_;

  Node() = default;
  Node(Type value) : value_(value), next_(nullptr), prev_(nullptr) {}
  Node(Type value, Node *next) : value_(value), next_(next), prev_(nullptr) {}
};

template<typename Type>
class LinkedList {
 public:
  
  /**
   * Default constructor
   */
  LinkedList() = default;

  /**
   * Copy constructor
   * @param src the source object to copy from
   */
  LinkedList(const LinkedList &src) {
    DeepCopy(src);
  }

  /**
   * Destructor
   */
  ~LinkedList() {
    Deallocate();
  }

 private:
  void Deallocate() {
    Node *node_to_delete;
    for (Node *current = head_; current != nullptr; current = current->next_) {
      node_to_delete = current;
      current = current->next_;
      delete node_to_delete;
    }
  }
  void DeepCopy(const LinkedList &src) {
    if (src.head_ == nullptr) {
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      Node *src_node = src.head_;
      head_ = new Node(src_node->value_);
      tail_ = head_;
      src_node = src_node->next;
      for (; src_node != nullptr; src_node = src_node->next_) {
        tail_->next_ = new Node(src_node->value_);
        tail_->next_->prev_ = tail_;
        tail_ = tail_->next_;
      }
    }
    size_ = src.size_;
  }

  Node *head_;
  Node *tail_;
  std::size_t size_;
};

} // namespace ds

#endif 