#ifndef INDEXED_PQ_H_
#define INDEXED_PQ_H_
/**
 * Indexed Priority Queue implementation
 * It is a variant of regular priority queue which suppors quick updates 
 * and deletions of key-value pairs.
 */

#include <functional> // comparision function
#include <iostream>
#include <stdexcept>
#include <utility> // pair

#include "hash_table.h"
#include "vector.h"

namespace ds {
/** 
 * By default, the Index Priority Queue in a min queue 
 * The Priority Queue uses key as an identifer and value for determining the priority in the queue
 */
template<typename KeyType, typename ValueType, typename Comparator = std::greater<ValueType>>
class IndexedPriorityQueue {
 public:
  using KeyValue = std::pair<KeyType, ValueType>;
  using SizeType = typename Vector<KeyValue>::SizeType;
  using Reference = typename Vector<KeyValue>::Reference;
  using ConstReference = typename Vector<KeyValue>::ConstReference;
 public:
  /** Default constructor */
  IndexedPriorityQueue() = default;

  IndexedPriorityQueue(const Comparator& cmp) : cmp_(cmp) {}

  // Default all special member functions since this class doesn't handle any resource
  /** Copy constructor */
  IndexedPriorityQueue(const IndexedPriorityQueue& other) = default;

  /** Move constructor */
  IndexedPriorityQueue(IndexedPriorityQueue&& other) noexcept = default;

  /** Copy assignment operator */
  IndexedPriorityQueue& operator=(const IndexedPriorityQueue& other) = default;

  /** Move assignment operator */
  IndexedPriorityQueue& operator=(IndexedPriorityQueue&& other) = default;

  /** Destructor */
  ~IndexedPriorityQueue() = default;

  /** @return true if the priority queue is empty; false otherwise */
  bool IsEmpty() const { return values_.IsEmpty(); }

  /** @return the size of the priority queue */
  SizeType Size() const { return values_.Size(); }

  /** @return the top element of the priority queue. 
   * Throws an exception if trying to access an empty queue 
   */
  ConstReference Top() const {
    if (IsEmpty()) {
      throw std::out_of_range("The indexed priority queue is empty\n");
    }
    return values_.Front(); 
  }

  /**
   * Pushes the given key-value pair to the priority queue
   * @param key the key to push
   * @param value the value corresponds to the key
   */
  void Insert(const KeyType& key, const ValueType& value) {
    KeyValue kv {key, value};
    SizeType idx = Size();
    key_idx_.Insert(key, idx);
    values_.PushBack(kv);
    SiftUp(idx);
  }

  /**
   * Pops the top element of the priority queue
   * @return the value of the element
   */
  KeyValue Pop() {
    if (IsEmpty()) {
      throw std::out_of_range("The priority queue is empty\n");
    }
    KeyValue kv = values_[0];
    KeyValue &last_kv = values_[Size() - 1];

    // Change key_idx map of last kv before deleting 
    key_idx_[last_kv.first] = 0;
    key_idx_.Delete(kv.first); 

    std::swap(values_[0], last_kv);
    values_.PopBack();
    // Corrects the prioriy queue invariant from the root down to leaves
    SiftDown(0);
    return kv;
  }

  /**
   * Updates the value of a key to `value` 
   * @param key the key to update
   * @param value the value to update to
   */
  void Update(const KeyType& key, const ValueType& value) {
    if (!key_idx_.Contains(key)) {
      throw std::out_of_range("The key doesn't exist\n");
    }
    SizeType idx = key_idx_[key];
    values_[idx].second = value;

    // Compare with child node
    SiftDown(idx);
    // Compare with parent node
    SiftUp(idx);
  }

  // No notion of decrease key or increase key in a generic priority queue
  void DecreaseKey(const KeyType& key, const ValueType& value) = delete;
  void IncreaseKey(const KeyType& key, const ValueType& value) = delete;

  /** Prints the current priority queue */
  void PrintPriorityQueue() {
    IndexedPriorityQueue<KeyType, ValueType> copy(*this);
    KeyValue kv;
    std::cout << "Priority Queue: ";
    while (!copy.IsEmpty()) {
      kv = copy.Pop();
      std::cout << "(" << kv.first << ", " << kv.second << ") ";
    }
    std::cout << '\n';
  }

  /** Prints the key-index map */
  void PrintIndexMap() {
    std::cout << "Index Map: " <<key_idx_.ToString() << '\n';
  }

 private:
  /** @return the index of the parent of the element at index `i` */
  SizeType GetParent(SizeType i) const { return (i - 1) / 2; }

  /** @return the index of the left child of the element at index `i` */
  SizeType GetLeftChild(SizeType i) const { return 2 * i  + 1; }

  /** @return the index of the right child of the element at index `i` */
  SizeType GetRightChild(SizeType i) const { return 2 * i + 2; }

  /**
   * Sift an element at index `i` up to maintain the priority queue property
   * @param i the index of the element to sift up
   */
  void SiftUp(SizeType i) {
    while (i > 0 && cmp_(values_[GetParent(i)].second, values_[i].second)) {
      // Update the index map
      Swap(GetParent(i), i);
      i = GetParent(i);
    }
  }

  void SiftDown(SizeType i) {
    SizeType largest = i;
    SizeType left = GetLeftChild(i);
    SizeType right = GetRightChild(i);
    if (left < Size() && cmp_(values_[largest].second, values_[left].second)) {
      largest = left;
    }
    if (right < Size() && cmp_(values_[largest].second, values_[right].second)) {
      largest = right;
    }
    if (largest != i) {
      Swap(largest, i);
      SiftDown(largest);
    }
  }

  /**
   * Swaps the elements at index `i` and `j` and updates the index map accordingly
   * @param i the index of the element to swap
   * @param j the index of the element to swap
   */
  void Swap(SizeType i, SizeType j) {
    std::swap(values_[i], values_[j]);
    key_idx_[values_[i].first] = i;
    key_idx_[values_[j].first] = j;
  }

  // underlying data structure of the priority queue
  Vector<KeyValue> values_;
  // A map from keys to the indices of keys' corresponding values
  HashTable<KeyType, SizeType> key_idx_;
  // Comparision function for the queue
  Comparator cmp_;
};

} // namespace ds

#endif // INDEXED_PQ_H_