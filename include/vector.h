#ifndef VECTOR_H_
#define VECTOR_H_

#include <algorithm>
#include <memory>
#include <stdexcept>

#include "type_traits.h"
#include "utility.h"

/*============================================================
=============================Vector===========================
==============================================================*/

namespace stl {

template <typename T, typename Allocator = std::allocator<T>>
class vector {
 public:
  /*====================Member types====================*/
  using value_type = T;
  using allocator_type = Allocator;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer =
      typename std::allocator_traits<Allocator>::const_pointer;
  using iterator = pointer;
  using const_iterator = const_pointer;

  /*====================Member functions====================*/

  /**
   * Default constructor
   * Constructs an empty container with a default-constructed allocator
   */
  vector() noexcept(noexcept(Allocator()))
      : data_(std::allocator_traits<Allocator>::allocate(get_allocator(),
                                                         INITIAL_CAPACITY)),
        capacity_(INITIAL_CAPACITY) {}

  /**
   * Constructs an empty container with the given allocator `alloc`
   * @param alloc custom allocator
   */
  explicit vector(const Allocator& alloc) noexcept : allocator_(alloc) {}

  /**
   * Constructs the container with `count` copies of elements with value `value`
   * @param count number of elements to initialize with
   * @param value value of these elements
   * @param alloc custom allocator
   */
  vector(size_type count, const T& value, const Allocator& alloc = Allocator())
      : allocator_(alloc) {
    assign(count, value);
  }

  /**
   * Constructs the container with `count` default-inserted instances of T. No
   * copies are made
   * @param count number of elements to initialize with
   * @param alloc custom allocator
   */
  explicit vector(size_type count,
                  const Allocator& alloc = Allocator())
      : data_(new T[count]()),  // use new with parenthesis to value-initialize
                                // elements
        size_(count),
        capacity_(count),
        allocator_(alloc) {}

  /**
   * Constructs the container with the contents of the range [first, last)
   * Requires `enable_if_t` for overload resolution
   * @param first iterator to the first element of the range
   * @param last iterator to one place beyond the last element
   */

  template <typename InputIt,
            typename = stl::enable_if_t<stl::is_pointer_v<InputIt>>>
  vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
      : allocator_(alloc) {
    assign(first, last);
  }

  /**
   * Copy constructor. Constructs the container with the contents of `other`
   * @param other source object to copy from
   */
  vector(const vector& other) : vector(other, other.get_allocator()) {}

  /**
   * Copy constructor. Constructs the container with the contents of `other`,
   * but using `alloc` as the allocator
   * @param other source object to copy from
   * @param alloc custom allocator
   */
  vector(const vector& other, const Allocator& alloc)
      : data_(std::allocator_traits<Allocator>::allocate(get_allocator(),
                                                         other.capacity())),
        size_(other.size()),
        capacity_(other.capacity()),
        allocator_(alloc) {
    copy_data(data(), other.data(), size());
  }

  /**
   * Move constructor
   * @param other source object to move from
   */
  vector(vector&& other) noexcept { other.swap(*this); }

  /**
   * Constructs the container with the contents of the initializer list `init`
   * @param init initializer list
   * @param alloc custom allocator
   */
  vector(std::initializer_list<value_type> init,
         const Allocator& alloc = Allocator())
      : allocator_(alloc) {
    assign(init);
  }

  /**
   * Destructor
   */
  ~vector() {
    std::allocator_traits<Allocator>::deallocate(get_allocator(), data(),
                                                 capacity());
  }

  /**
   * Copy assignment operator. Replaces the contents with the those of `other`
   * @param other source object to copy-assign from
   * @return reference to this vector object
   */
  vector& operator=(const vector& other) {
    vector copy(other);
    copy.swap(*this);
    return *this;
  }

  /**
   * Move assignment operator. Replaces the contents with those of `other` using
   * move semantics
   * @param other source object to move from
   * @return reference to this vector object
   */
  vector& operator=(vector&& other) noexcept {
    other.swap(*this);
    other.size_ = 0;
    return *this;
  }

  /**
   * Replaces the contents with those of initializer list `ilist`
   * @param ilist source initialize list
   * @return reference to this vector object
   */
  vector& operator=(std::initializer_list<T> ilist) {
    assign(ilist);
    return *this;
  }

  /**
   * Replaces the contents with `count` copies of `value`
   * @param count new size of the container
   * @param value value to initialize elements of the container with
   */
  void assign(size_type count, const T& value) {
    assign_impl(count, [&](size_type i) {
      while (i < count) {
        data_[i++] = value;
      }
    });
  }

  /**
   * Replaces the contents with copies of those in the range [first, last)
   * @param first iterator to the first element of the range
   * @param last iterator to one place beyond the last element of the range
   */
  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    assign_impl(last - first, [&](size_type i) {
      for (auto it = first; it != last; it++) {
        data_[i++] = *it;
      }
    });
  }

  /**
   * Replaces the contents with the elements from `ilist`
   * @param ilist initializer list to copy contents from
   */
  void assign(std::initializer_list<T> ilist) {
    assign_impl(ilist.size(), [&](size_type i) {
      for (const auto& ele : ilist) {
        data_[i++] = ele;
      }
    });
  }

  /**
   * Returns the allocator associated with the container
   * @return the associated allocator
   */
  constexpr allocator_type get_allocator() const noexcept { return allocator_; }

  /*==========Element access==========*/

  /**
   * Returns a reference to the element at position `pos` with bound checking
   * @param pos position of the element to return
   * @return reference to the requested element
   */
  reference at(size_type pos) {
    if (pos < 0 || pos >= size()) {
      throw std::out_of_range("invalid index");
    }
    return data_[pos];
  }
  const_reference at(size_type pos) const {
    if (pos < 0 || pos >= size()) {
      throw std::out_of_range("invalid index");
    }
    return data_[pos];
  }

  /**
   * Returns a reference to the element at position `pos`
   * @param pos position of the element to return
   * @return reference to the requested element
   */
  reference operator[](size_type pos) { return data_[pos]; }
  const_reference operator[](size_type pos) const { return data_[pos]; }

  /**
   * Returns a reference to the first element in the container
   * Calling `front` on an empty container causes undefined behavior
   * @return reference to the requested element
   */
  reference front() { return data_[0]; }
  const_reference front() const { return data_[0]; }

  /**
   * Returns a reference to the last element in the container
   * Calling `back` on an empty container causes undefined behavior
   * @return reference to the requested element
   */
  reference back() { return data_[size() - 1]; }
  const_reference back() const { return data_[size() - 1]; }

  /**
   * Returns a pointer to the underlying array
   * @return pointer to the underlying element storage
   */
  pointer data() noexcept { return data_; }
  const_pointer data() const noexcept { return data_; }

  /*==========Iterators==========*/

  /**
   * Returns an iterator to the first element of the vector
   * @return iterator to the first element
   */
  iterator begin() noexcept { return static_cast<iterator>(data()); }
  const_iterator begin() const noexcept {
    return static_cast<const_iterator>(data());
  }
  const_iterator cbegin() const noexcept { return begin(); }

  /**
   * Returns an iterator to the element following the last element of the
   * vector. This element acts as a placeholder; attempting to access it results
   * in undefined behavior.
   * @return iterator to the element following the last element of the vector
   */
  iterator end() noexcept { return static_cast<iterator>(data() + size()); }
  const_iterator end() const noexcept {
    return static_cast<const_iterator>(data() + size());
  }
  const_iterator cend() const noexcept { return end(); }

  /*==========Capacity==========*/
  /**
   * Checks whether the container has no elements
   * @return true if the container is empty, false otherwise
   */
  bool empty() const noexcept { return size() == 0; }

  /**
   * Returns the number of elements in the container
   * @return the number of elements in the container
   */
  size_type size() const noexcept { return size_; }

  /**
   * Increases the capacity of the vector to a value greater than or equal to
   * `new_cap`. If `new_cap` is greater than the current capacity, new storage
   * is allocated, otherwise the function does nothing.
   * Iterators and references to elements of the container are invalidated
   * if reallocation takes place.
   * @param new_cap new capacity of the vector
   */
  void reserve(size_type new_cap) {
    if (capacity() < new_cap) {
      expand_capacity(std::max(new_cap, capacity() * 2));
    }
  }

  /**
   * Returns the capacity of the vector (the total number of elements that
   * the vector can hold without requiring reallocation)
   * @return capacity of the vector
   */
  constexpr size_type capacity() const noexcept { return capacity_; }

  /*==========Modifiers==========*/
  /**
   * Erases all elements from the container
   * Invalidates any references, pointers, or iterators referring to contained
   * elements (including past-the-end iterators)
   */
  void clear() noexcept { size_ = 0; }

  /**
   * Inserts `value` at `pos`
   * @param pos position to insert value
   * @param value value to insert
   * @return iterator to the inserted `value`
   */
  iterator insert(const_iterator pos, const T& value) {
    return insert_impl(pos, 1, [&](size_type idx) { data_[idx] = value; });
  }

  iterator insert(const_iterator pos, T&& value) {
    return insert_impl(pos, 1, [&](size_type idx) {
      // must use `stl::move` here instead of `move` even though we are in
      // namespace stl due to argument-dependent lookup (ADL)
      data_[idx] = stl::move(value);
    });
  }

  /**
   * Inserts `count` copies of `value` at `pos`
   * @param pos position to insert value
   * @param count number of values to insert
   * @param value value to insert
   * @return iterator to the first inserted element, or `pos` if `count == 0`
   */
  iterator insert(const_iterator pos, size_type count, const T& value) {
    return insert_impl(pos, count, [&](size_type idx) {
      for (size_type i = 0; i < count; i++) {
        data_[idx + i] = value;
      }
    });
  }

  /**
   * Inserts elements from the range [first, last) at `pos`
   * @param pos position to insert value
   * @param first the first element of the range
   * @param last the element following the last element of the range
   * @return iterator to the first inserted element, or `pos` if `first == last`
   */
  template <typename InputIt,
            typename = stl::enable_if_t<stl::is_pointer_v<InputIt>>>
  iterator insert(const_iterator pos, InputIt first, InputIt last) {
    return insert_impl(pos, last - first, [&](size_type idx) {
      for (auto it = first; it != last; it++) {
        data_[idx++] = *it;
      }
    });
  }

  /**
   * Inserts elements from the initializer list `ilist` at `pos`
   * @param pos position to insert value
   * @param ilist initializer list to insert values from
   * @return iterator to the first inserted element, or `pos` if `ilist` is
   * empty
   */
  iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
    return insert_impl(pos, ilist.size(), [&](size_type idx) {
      for (const auto& ele : ilist) {
        data_[idx++] = ele;
      }
    });
  }

  /**
   * Insert an element at `pos` using in-place construction
   * @param pos position to insert the new element
   * @param args arguments to construct the element from
   * @return iterator to the inserted element
   */
  template <typename... Args>
  iterator emplace(const_iterator pos, Args&&... args) {
    size_type idx = pos - begin();
    prep_for_insertion(idx, 1);
    iterator iter = &data_[idx];
    std::allocator_traits<Allocator>::construct(get_allocator(), iter,
                                                stl::forward<Args>(args)...);
    size_++;
    return iter;
  }

  /**
   * Removes the element at `pos`
   * @param pos position of the element to remove
   * @return iterator following the last removed element
   */
  stl::enable_if_t<stl::is_move_assignable_v<T>, iterator> erase(
      const_iterator pos) {
    size_--;
    if (pos == end()) {
      return end();
    }

    size_type idx = pos - begin();
    for (size_type i = idx; i < size(); i++) {
      data_[i] = stl::move(data_[i + 1]);
    }
    return static_cast<iterator>(data_ + idx);
  }

  /**
   * Appends the given `value` to the end of the container. The new element is
   * initialized of a copy of `value`. Iterators and references to elements are
   * invalidated if reallocation takes place
   * @param value value of the element to append
   */
  void push_back(const T& value) { insert(end(), value); }

  /**
   * Appends the given `value` to the end of the container. `value` is moved to
   * the new element. Iterators and references to elements are invalidated if
   * reallocation takes place
   * @param value value of the element to append
   */
  void push_back(T&& value) { insert(end(), stl::move(value)); }

  /**
   * Appends a new element to the end of the container using in-place
   * construction. Iterators and references to elements are invalidated if
   * reallocation takes place
   * @param args arguments to construct the new element
   * @return reference to the inserted element
   */
  template <typename... Args>
  reference emplace_back(Args&&... args) {
    auto it = emplace(end(), stl::forward<Args>(args)...);
    return data_[it - begin()];
  }

  /**
   * Removes the last element from the container. Calling this function on an
   * empty container causes undefined behavior.
   */
  void pop_back() { size_--; }

  /**
   * Resizes the container to contain `count` elements
   * @param count the new size of the container
   */
  void resize(size_type count) { resize_impl(count, value_type()); }

  void resize(size_type count, const value_type& value) {
    resize_impl(count, value);
  }

 private:
  constexpr allocator_type& get_allocator() noexcept { return allocator_; }

  void swap(vector& rhs) noexcept {
    using std::swap;
    swap(data_, rhs.data_);
    swap(size_, rhs.size_);
    swap(capacity_, rhs.capacity_);
  }

  void copy_data(T* dst, const T* src, size_type sz) {
    for (size_type i = 0; i < sz; i++) {
      dst[i] = src[i];
    }
  }

  void move_data(T* dst, T* src, size_type sz) {
    for (size_type i = 0; i < sz; i++) {
      dst[i] = stl::move(src[i]);
    }
  }

  void realloc(size_type sz) {
    T* new_data =
        std::allocator_traits<Allocator>::allocate(get_allocator(), sz);
    std::allocator_traits<Allocator>::deallocate(get_allocator(), data(),
                                                 capacity());
    data_ = new_data;
    capacity_ = sz;
  }

  void expand_capacity(size_type new_cap) {
    T* new_data =
        std::allocator_traits<Allocator>::allocate(get_allocator(), new_cap);
    if constexpr (stl::is_nothrow_move_assignable_v<T>) {
      move_data(new_data, data(), size());
    } else {
      copy_data(new_data, data(), size());
    }
    std::allocator_traits<Allocator>::deallocate(get_allocator(), data(),
                                                 capacity());
    data_ = new_data;
    capacity_ = new_cap;
  }

  // make room for inserting `count` elements at index `idx`
  void prep_for_insertion(size_type idx, size_type count) {
    if (size() + count > capacity()) {
      expand_capacity(std::max(size() + count, capacity() * 2));
    }

    for (size_type i = size() + count - 1; i > idx + count - 1; i--) {
      data_[i] = data_[i - count];
    }
  }

  template <typename AssignFunc>
  void assign_impl(size_type count, AssignFunc&& assign_func) {
    if (capacity() < count) {
      realloc(count);
    }
    assign_func(0);
    size_ = count;
  }

  template <typename InsertFunc>
  iterator insert_impl(const_iterator pos, size_type count,
                       InsertFunc&& insert_func) {
    // must calculate idx first; otherwise, `pos` iterator
    // may be invalidated due to reallocation
    size_type idx = pos - begin();
    if (count == 0) {
      return static_cast<iterator>(data_ + idx);
    }
    // prep_for_insertion can invalidate iterator
    prep_for_insertion(idx, count);
    insert_func(idx);
    size_ += count;
    return static_cast<iterator>(data_ + idx);
  }

  void resize_impl(size_type count, const value_type& value) {
    if (size() >= count) {
      size_ = count;
      return;
    }

    if (count > capacity()) {
      expand_capacity(std::max(count, capacity() * 2));
    }
    for (size_type i = 0; i < count - size(); i++) {
      data_[size() + i] = value;
    }
    size_ = count;
  }

  static constexpr size_t INITIAL_CAPACITY = 4;

  T* data_{};
  size_t size_{};
  size_t capacity_{};
  Allocator allocator_{};
};

};  // namespace stl

#endif  // VECTOR_H_