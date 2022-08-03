#ifndef HEAP_H_
#define HEAP_H_

#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>

#include "vector.h"

namespace ds {
// By default, the heap is a max heap
template<typename Type, typename Comparator = std::less<Type>>
class Heap {
 public:
  using SizeType = typename Vector<Type>::SizeType;
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

  /** Constructs a heap by moving elements from `data` to heap with default comparator */
  explicit Heap(Vector<Type>&& data) noexcept : Heap(std::move(data), Comparator()) {}

  /**
   * Constructs a heap with elements from Vector `data`
   * @param data the list of elements to build the heap
   * @param cmp the comparison function object specifying heap property
   */
  Heap(const Vector<Type>& data, const Comparator& cmp) : heap_(data), cmp_(cmp) {
    BuildHeap();
  }

  /** Constructs a heap by moving elements from `data` to heap */
  Heap(Vector<Type>&& data, const Comparator& cmp) : heap_(std::move(data)), cmp_(cmp) {
    BuildHeap();
  }

  // Default all special member functions since this class doesn't handle any resource
  /** Copy constructor */
  Heap(const Heap& other) = default;

  /** Move constructor */
  Heap(Heap&& other) noexcept = default;

  /** Copy assignment operator */
  Heap& operator=(const Heap& other) = default;

  /** Move assignment operator */
  Heap& operator=(Heap&& other) = default;

  /** Destructor */
  ~Heap() = default;

  /** @return the top element of the heap. Get garbage values if trying to access an empty heap */
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

  /**
   * Pushes the given element to the heap
   * @param value an rvalue reference to the element
   */
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
    if (IsEmpty()) {
      throw std::out_of_range("The heap is empty\n");
    }
    Type val = heap_[0];
    std::swap(heap_[0], heap_[Size() - 1]);
    heap_.PopBack();
    // Fix the heap invariant from the root
    Heapify(0);
    return val;
  }

  /** For debugging */
  void Print() {
    int size = Size();
    if (size == 0) {
      std::cout << "Empty heap\n";
    } else {
      std::cout << "Heap: ";
      for (int i = 0; i < size - 1; ++i) {
        std::cout << heap_[i] << ", ";
      }
      std::cout << heap_[size - 1] << '\n';
    }
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