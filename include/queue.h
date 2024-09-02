#ifndef QUEUE_H_
#define QUEUE_H_

#include "list.h"

namespace stl {
template<typename T>
class queue {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

 public:
  queue() = default;
  queue(const queue& other) = default;
  queue(queue&& other) noexcept = default;
  queue& operator=(const queue& other) = default;
  queue& operator=(queue&& other) = default;
  ~queue() = default;

  /** @return the current number of elements in the queue */
  size_type size() const { return queue_.size(); }

  /** @return true if the queue is empty; otherwise, false. */
  bool empty() const { return queue_.size() == 0; }

  /** @return a reference to the first element in the queue */
  reference front() {
    check_queue();
    return queue_.front();
  }

  /** @return a constant reference to the first element in the queue */
  const_reference front() const {
    check_queue();
    return queue_.front();
  }

  /** @return a reference to the last element in the queue */
  reference back() {
    check_queue();
    return queue_.back();
  }

  /** @return a constant reference to the last element in the queue */
  const_reference back() const {
    check_queue();
    return queue_.back();
  }

  /**
   * Pushes the given element to the end of the queue. Copy-construct
   * the pushed element.
   * @param value the value of the element to push
   */
  void enqueue(const T& value) { queue_.push_back(value); }

  /**
   * Pushes the given element to the end of the queue. Move-construct
   * the pushed element.
   * @param value the value of the element to push
   */
  void enqueue(T&& value) { queue_.push_back(stl::move(value)); }

  /**
   * Removes an element from the front of the queue
   * @return the element at the front of the queue
   */
  T deque() {
    check_queue();
    T ele = queue_.front();
    queue_.pop_front();
    return ele;
  }

 private:
  void check_queue() {
    if (empty()) {
      throw std::out_of_range("The queue is empty.");
    }
  }

  list<T> queue_;
};
}  // namespace stl

#endif  // QUEUE_H_