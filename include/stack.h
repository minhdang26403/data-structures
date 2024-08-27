#ifndef STACK_H_
#define STACK_H_

#include "vector.h"

namespace stl {
template<typename T>
class stack {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

 public:
  stack() = default;
  stack(const stack& other) = default;
  stack(stack&& other) noexcept = default;
  stack& operator=(const stack& other) = default;
  stack& operator=(stack&& other) noexcept = default;
  ~stack() = default;

  /**
   * @brief undefined behavior if called on an empty stack
   * @return a reference to the element at the top of the stack
   */
  reference top() { return data_.back(); }

  const_reference top() const { return data_.back(); }

  /** @return true if the stack is empty; otherwise, false */
  bool empty() { return data_.size() == 0; }

  /** @return the size of the stack */
  size_type size() const { return data_.size(); }

  /**
   * Pushes the given element to the top of the stack 
   * @param value the value of the element to push
   */
  void push(const T& value) { data_.push_back(value); }

  void push(T&& value) { data_.push_back(stl::move(value)); }

  /**
   * Pushes a new element on top of the stack and constructs the element in-place
   * @param args arguments to forward to the constructor of the element
   */
  template<typename... Args>
  void emplace(Args&&... args) {
    data_.emplace_back(stl::forward<Args>(args)...);
  }

  /**
   * Removes the top element from the stack. Calls pop on an empty stack 
   * results in undefined behavior
   */
  void pop() { data_.pop_back(); }

  /** @return true if two stacks are the same; otherwise, false */
  bool operator==(const stack& rhs) { return data_ == rhs.data_; }

 private:
  vector<T> data_;
};
}  // namespace stl

#endif  // STACK_H_