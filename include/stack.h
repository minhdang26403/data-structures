#ifndef STACK_H_
#define STACK_H_

#include <stdexcept>

#include "vector.h"

namespace ds {
template<typename Type>
class Stack {
public:
  using ValueType = Type;
  using SizeType = std::size_t;
  using Reference = ValueType&;
  using ConstReference = const ValueType&;
public:
  Stack() = default;
  Stack(const Stack& other) = default;
  Stack(Stack&& other) noexcept = default;
  Stack& operator=(const Stack& other) = default;
  Stack& operator=(Stack&& other) noexcept = default;
  ~Stack() = default;

  /** @return a reference to the element at the top of the stack */
  Reference Top() {
    CheckStack();
    return data_.Back();
  }
  ConstReference Top() const {
    CheckStack();
    return data_.Back();
  }

  /** @return true if the stack is empty; otherwise, false */
  bool IsEmpty() {
    return data_.Size() == 0;
  }

  /** @return the size of the stack */
  SizeType Size() const {
    return data_.Size();
  }

  /**
   * Pushes the given element to the top of the stack 
   * @param value the value of the element to push
   */
  void Push(const Type& value) {
    data_.PushBack(value);
  }

  void Push(Type&& value) {
    data_.PushBack(std::move(value));
  }

  /**
   * Pushes a new element on top of the stack and constructs the element in-place
   * @param args arguments to forward to the constructor of the element
   */
  template<typename... Args>
  void Emplace(Args&&... args) {
    data_.EmplaceBack(std::forward<Args>(args)...);
  }

  /** Removes the top element from the stack */
  void Pop() {
    CheckStack();
    data_.PopBack();
  }

  /** @return true if two stacks are the same; otherwise, false */
  bool operator==(const Stack& rhs) {
    return data_ == rhs.data_;
  }
private:
  void CheckStack() {
    if (IsEmpty()) {
      throw std::out_of_range("The stack is empty.");
    }
  }
  Vector<Type> data_;
};
} // namespace ds

#endif // STACK_H_