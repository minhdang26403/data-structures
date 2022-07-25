#ifndef VECTOR_H_
#define VECTOR_H_

#include <algorithm>
#include <stdexcept>
#include <cstdlib>

#include "./config.h"

namespace ds {
template<typename Type>
class Vector {
 public:
  /** Type aliases */
  using ValueType = Type;
  using Reference = ValueType&;
  using ConstReference = const ValueType&;
  using Pointer = Type*;
  using SizeType = std::size_t;
  
  /** Implement iterator for Vector class */
  class Iterator {
   public:
    Iterator(Pointer ptr) : m_ptr_(ptr) {}

    Pointer operator->() { return m_ptr_; }

    Reference operator*() { return *m_ptr_; }

    Iterator& operator++() {
      ++m_ptr_;
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    Iterator& operator--() {
      --m_ptr_;
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
  * Default constructor
  */
  Vector() : array_{new Type[INITIAL_CAPACITY]} {}

  /**
   * Construct a new Vector object of `count` elements with `value` values
   * @param count the size of the vector
   * @param value the value to initialize elements with
   */
  explicit Vector(SizeType count, const Type& value) 
    : array_{new Type[count]}, capacity_{count}, size_{count} 
  {
    for (SizeType i = 0; i < size_; ++i) {
      array_[i] = value;
    }
  }

  /**
   * Construct a new Vector object of `count` elements
   * @param count the size of the vector
   */
  explicit Vector(SizeType count) : array_{new Type[count]}, capacity_{count}, size_{count} {}

  /**
   * Copy constructor
   * @param src the source object to copy from
   */
  explicit Vector(const Vector& src) 
    : array_{new Type[src.capacity_]}, capacity_(src.capacity_), size_(src.size_) 
  {
    std::copy(src.array_, src.array_ + size_, array_);
  }

  /**
   * Move constructor
   * @param src the temporary (rvalue) source object to move from
   */
  Vector(Vector&& src) noexcept : array_{nullptr}, capacity_{0}, size_{0} {
    src.Swap(*this);
  }

  /**
   * Construct a new Vector object with an initializer list
   * @param init the initializer list
   */
  Vector(std::initializer_list<Type> init) 
    : array_{new Type[init.size()]}, capacity_{init.size()}, size_{init.size()}
  { 
    int i = 0;
    for (auto it = init.begin(); it != init.end(); ++it) {
      array_[i++] = *it;
    }
  }

  /**
   * Destroys the existing Vector object
   */
  ~Vector() {
    delete []array_;
  }

  /**
   * Copy assignment operator 
   * @param src the source object to assign from
   * @return a reference to the calling object
   */
  Vector& operator=(const Vector& src) {
    Vector temp(src);
    temp.Swap(*this);
    return *this;
  }

  /**
   * Move assignment operator
   * @param src the source object to move from
   * @return a reference to the calling object
   */
  Vector& operator=(Vector&& src) noexcept {
    src.Swap(*this);
    return *this;
  }

  /** Access methods */

  /**
   * Returns a reference to the element at the specified index
   * @param index the position of the element
   * @return a reference to the element
   */
  Reference At(SizeType index) {
    ValidateIndex(index);
    return array_[index];
  }

  /**
   * Returns a const reference to the element at the specified index
   * @param index the position of the element
   * @return a const reference to the element
   */
  ConstReference At(SizeType index) const {
    ValidateIndex(index);
    return array_[index];
  }

  /** Index operator without bound checking */
  Reference operator[](SizeType index) {
    return array_[index];
  }

  /** Index operator for const Vector object */
  ConstReference operator[](SizeType index) const {
    return array_[index];
  }

  /** Iterators */
  Iterator begin() noexcept { return Iterator(array_); }
  Iterator end() noexcept { return Iterator(array_ + size_); }

  /**
   * Checks whether the vector is empty
   * @return true if the vector is empty; false otherwise
   */
  bool IsEmpty() const noexcept { return size_ == 0; }

  /**
   * Gets the size of the vector
   * @return the current size of the vector
   */
  SizeType Size()  const noexcept { return size_; }

  /**
   * Increase the capacity of the vector
   * Does nothing if the current capacity is larger than or equal to the new capacity
   * @param new_capacity the new capacity of the vector
   */
  void Reserve(SizeType new_capacity) {
    if (new_capacity > capacity_) {
      Type *old_array = array_;
      array_ = new Type[new_capacity];
      capacity_ = new_capacity;
      std::copy(old_array, old_array + size_, array_);
    }
  }

  /** Modifiers */

  /**
   * Inserts an element into the vector at the specified position
   * @param index the position to insert the element
   * @param value the value of the element
   */
  void Insert(SizeType index, const Type& value) {
    PrepareForInsertion(index);
    array_[index] = value;
    ++size_;
  }

  /** Overload of insert method supporting move semantics */
  void Insert(SizeType index, Type&& value) {
    PrepareForInsertion(index);
    array_[index] = std::move(value);
    ++size_;
  }

  /**
   * Adds an element to the end of the vector
   * @param value the value of the element to add
   */
  void PushBack(const Type& value) {
    Insert(size_, value);
  }

  /** Overload of push back method supporting move semantics */
  void PushBack(Type&& value) {
    Insert(size_, std::move(value));
  }

  // template<typename... Args>
  // Iterator Emplace(ConstIterator pos, Args&&... args);

  // template<typename... Args>
  // Reference EmplaceBack(Args&&... args);

  /**
   * Removes the last element of the vector
   */
  void PopBack() {
    Remove(size_ - 1);
  }

  /**
   * Removes an element at the specified position
   * @param index the position of the element to be removed
   */
  void Remove(SizeType index) {
    ValidateIndex(index);
    for (SizeType i = index; i < size_; ++i) {
      array_[i] = array_[i + 1];
    }
    --size_;
  }

 private:
  /**
   * Checks for index boundary, reallocates the array (if needed), and shifts elements
   */
  void PrepareForInsertion(SizeType index) {
    if (index < 0 || index > size_) {
      throw std::out_of_range("Index out of range");
    }
    if (size_ == capacity_) {
      ExpandCapacity();
    }
    for (SizeType i = size_; i > index; --i) {
      array_[i] = array_[i - 1];
    }
  }


  /**
   * Validate the index of an element
   * @param index the position of the element
   */
  void ValidateIndex(SizeType index) {
    if (index < 0 || index >= size_) {
      throw std::out_of_range("Index out of range");
    }
  }

  /**
   * Swap the content of two Vector objects
   * @param rhs the other Vector object
   */
  void Swap(Vector& rhs) noexcept {
    using std::swap;
    swap(array_, rhs.array_);
    swap(capacity_, rhs.capacity_);
    swap(size_, rhs.size_);
  }

  /**
   * Expands the capacity of the vector
   */
  void ExpandCapacity() {
    Type* old_array = array_;
    capacity_ *= 2;
    array_ = new Type[capacity_];
    std::copy(old_array, old_array + size_, array_);
    delete []old_array;
  }

  /** The array holding elemets */
  Type* array_{};
  /** The maximum capacity of the array */
  SizeType capacity_{INITIAL_CAPACITY};
  /** The current size of the array */
  SizeType size_{};
};

} // namespace ds

#endif  // VECTOR_H_