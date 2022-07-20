#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <cstdio>

namespace ds {
template<typename T>
class Vector {
 public:
 /**
  * Default constructor
  */
  Vector() {
    capacity_ = INITIAL_CAPACITY;
    size_ = 0;
    array_ = new T[capacity_];
  }

  /**
   * Copy constructor
   * @param src the source object to copy from
   */
  Vector(const Vector<T>& src) {
    DeepCopy(src);
  }

  /**
   * Destroys the existing Vector object
   */
  ~Vector() {
    delete []array_;
  }

  /**
   * Adds an element to the end of the vector
   * @param value the value of the element to add
   */
  void push_back(const T& value) {
    insert(size_, value);
  }

  /**
   * Gets the size of the vector
   * @return the current size of the vector
   */
  std::size_t size() const noexcept { return size_; };

  /**
   * Finds the index of an element
   * @param value the value of the element
   * @return the index of the element if exists; otherwise -1
   */
  int index(const T& value) {
    for (int i = 0; i < size_; ++i) {
      if (array_[i] == value) {
        return i;
      }
    }
    return -1;
  }

  /**
   * Inserts an element into the vector at the specified position
   * @param index the position to insert the element
   * @param value the value of the element
   */
  void insert(int index, const T& value) {
    if (index < 0 || index > size_) {
      throw std::out_of_range();
    }
    if (size_ == capacity_) {
      ExpandCapacity();
    }
    for (int i = size_; i > index; --i) {
      array_[i] = array_[i - 1];
    }
    array_[index] = value;
    ++size_;
  }

  /**
   * Removes an element at the specified position
   * @param index the position of the element to be removed
   */
  void remove(int index) {
    if (index < 0 || index > size_) {
      throw std::out_of_range();
    }
    for (int i = index; i < size_; ++i) {
      array_[i] = array_[i + 1];
    }
    --size_;
  }

  /**
   * Returns the element at the specified index
   * @param index the position of the element
   * @return A reference to the element
   */
  T& operator[](int index) {
    return array_[index];
  }

  /**
   * Copy assignment operator 
   * @param src the source object to assign
   * @return a reference to the calling object
   */
  T& operator=(const T& src) {
    if (this != &src) {
      delete []array_;
      DeepCopy(src);
    }
    return *this;
  }

 private:
  static const std::size_t INITIAL_CAPACITY = 10;
  std::size_t capacity_;
  std::size_t size_;
  T* array_;

  /**
   * @brief 
   * 
   */
  void DeepCopy(const Vector<T>& src) {
    capacity_ = src.capacity_;
    size_ = src.size_;
    array_ = new T[capacity_];
    for (int i = 0; i < size_; ++i) {
      array_[i] = src.array_[i];
    }
  }

  /**
   * @brief 
   * 
   */
  void ExpandCapacity() {
    T* old_array = array_;
    capacity_ *= 2;
    array_ = new T[capacity_];
    for (int i = 0; i < size_; ++i) {
      array_[i] = old_array[i];
    }
    delete []old_array;
  }
};

} // namespace ds

#endif