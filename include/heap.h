#ifndef HEAP_H_
#define HEAP_H_

#include <algorithm>
#include <functional>
#include <utility>

#include "vector.h"

namespace ds {
// By default, the heap is a max heap
template<typename Type, typename Comparator = std::less<Type>>
class Heap {
 public:
  using SizeType = std::size_t;
  using Reference = typename Vector<Type>::Reference;
  using ConstReference = typename Vector<Type>::ConstReference;
 public:
 /** Default constructor */
  Heap() = default;
  /**
   * Constructs a heap with elements from Vector `data`
   * @param data the list of elements to build the heap
   */
  explicit Heap(const Vector<Type>& data) : Heap(data, Comparator()) {}

  /**
   * Constructs a heap with elements from Vector `data`
   * @param data the list of elements to build the heap
   * @param cmp the comparison function object specifying heap property
   */
  Heap(const Vector<Type>& data, Comparator cmp) : heap_(data), cmp_(cmp) {
    BuildHeap();
  }

  /** Constructs a heap by moving elements from `data` to heap */
  Heap(Vector<Type>&& data, Comparator cmp) : heap_(std::move(data)), cmp_(cmp) {
    BuildHeap();
  }
  Heap(const Heap& other) = default;
  Heap(Heap&& other) noexcept = default;
  Heap& operator=(const Heap& other) = default;
  Heap& operator=(Heap&& other) = default;

  ~Heap() = default;

  /** @return the top element of the heap */
  ConstReference Top() const { return heap_.Front(); }

  /** @return true if the heap is empty; false otherwise */
  bool IsEmpty() const { return heap_.IsEmpty(); }

  /** @return the size of the heap */
  SizeType Size() const { return heap_.Size(); }

  /**
   * Pushes the given element to the heap
   * @param value the value of the element to push
   */
  void Push(const Type& value) {
    heap_.PushBack(value);
    SiftUp(Size() - 1);
  }

  void Push(Type&& value) {
    heap_.PushBack(std::move(value));
    SiftUp(Size() - 1);
  }

  /**
   * Constructs and pushes the element to the heap
   * @param args arguments to construct the element
   */
  template<typename... Args>
  void Emplace(Args&&... args) {
    heap_.EmplaceBack(std::forward<Args>(args)...);
  }

  /**
   * Pops the top element of the heap
   * @return the value of the element
   */
  Type Pop() {
    Type val = heap_[0];
    std::swap(heap_[0], heap_[Size() - 1]);
    heap_.PopBack();
    // Fix the heap invariant from the root
    Heapify(0);
    return val;
  }

 private:
  /** @return the index of the parent of the element at index `i` */
  SizeType GetParent(SizeType i) const { return (i - 1) / 2; }

  /** @return the index of the left child of the element at index `i` */
  SizeType GetLeftChild(SizeType i) const { return 2 * i  + 1; }

  /** @return the index of the right child of the element at index `i` */
  SizeType GetRightChild(SizeType i) const { return 2 * i + 2; }

  /**
   * Sift an element at index `i` up to maintain the heap property
   * @param i the index of the element to sift up
   */
  void SiftUp(SizeType i) {
    while (i > 0 && cmp_(heap_[GetParent(i)], heap_[i])) {
      std::swap(heap_[GetParent(i)], heap_[i]);
      i = GetParent(i);
    }
  }

  /** Builds the heap from unsorted data */
  void BuildHeap() {
    for (int i = (Size() - 1) / 2; i > -1; --i) {
      Heapify(i);
    }
  }

  /**
   * Corrects a single element that violates the heap property
   * @param i the index of the element
   */
  void Heapify(SizeType i) {
    SizeType largest = i;
    SizeType left = GetLeftChild(i);
    SizeType right = GetRightChild(i);
    if (left < Size() && cmp_(heap_[largest], heap_[left])) {
      largest = left;
    }
    if (right < Size() && cmp_(heap_[largest], heap_[right])) {
      largest = right;
    }
    if (largest != i) {
      std::swap(heap_[largest], heap_[i]);
      Heapify(largest);
    }
  }

  // underlying data structure of the heap
  Vector<Type> heap_;
  // comparision function for the heap
  Comparator cmp_;
};

} // namespace ds

#endif // HEAP_H_