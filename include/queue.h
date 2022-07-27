#ifndef QUEUE_H_
#define QUEUE_H_

#include "linked_list.h"

namespace ds {
template<typename Type>
class Queue {
public:
  using ValueType = Type;
  using SizeType = std::size_t;
  using Reference = ValueType&;
  using ConstReference = const ValueType&;
public:
  Queue() = default;
  Queue(const Queue& other) = default;
  Queue(Queue&& other) noexcept = default;
  Queue& operator=(const Queue& other) = default;
  Queue& operator=(Queue&& other) = default;
  ~Queue() = default;

  /** @return the current number of elements in the queue */
  SizeType Size() const { return queue_.Size(); }

  /** @return true if the queue is empty; otherwise, false. */
  bool IsEmpty() const { return queue_.Size() == 0; }

  /** @return a reference to the first element in the queue */
  Reference Front() {
    CheckQueue();
    return queue_.Front();
  }

  ConstReference Front() const {
    CheckQueue();
    return queue_.Front();
  }

  /** @return a reference to the first element in the queue */
  Reference Back() {
    CheckQueue();
    return queue_.Back();
  }

  ConstReference Back() const {
    CheckQueue();
    return queue_.Back();
  }

  /**
   * Pushes the given element to the end of the queue
   * @param value the value of the element to push
   */
  void Enqueue(const Type& value) {
    queue_.PushBack(value);
  }

  void Enqueue(Type&& value) {
    queue_.PushBack(std::move(value));
  }

  /** Removes an element from the front of the queue */
  void Dequeue() {
    CheckQueue();
    queue_.PopFront();
  }

private:
  void CheckQueue() {
    if (IsEmpty()) {
      throw std::out_of_range("The queue is empty.");
    }
  }
  LinkedList<Type> queue_;
};
} // namespace ds

#endif // QUEUE_H_