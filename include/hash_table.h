#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <algorithm>
#include <functional>
#include <sstream>
#include <string>

#include "list.h"
#include "vector.h"

namespace stl {
template<typename K, typename V>
struct Entry {
  K key_;
  V value_;
  /** Default construct */
  Entry() = default;

  /**
   * Constructs a new Entry object
   * @param key the key of the entry
   * @param value the value of the entry
   */
  Entry(K key, V value) : key_(key), value_(value) {}

  /**
   * @param rhs the Entry to compare with
   * @return true if two entries have the same key; otherwise, false
   */
  bool operator==(const Entry& rhs) const { return key_ == rhs.key_; }

  /**
   * @param rhs the Entry to compare with
   * @return true if two entries have different keys; otherwise, false
   */
  bool operator!=(const Entry& rhs) const { return !(*this == rhs); }
};

template<typename K, typename V>
class hash_table {
 public:
  using size_type = std::size_t;
  using entry_type = Entry<K, V>;

 public:
  /** Default constructor */
  hash_table() : hash_table(DEFAULT_CAPACITY, DEFAULT_LOAD_FACTOR) {}

  /** Constructs a hash table with `capacity` buckets 
   * @param capacity the number of buckets of the hash table
   */
  hash_table(size_type capacity) : hash_table(capacity, DEFAULT_LOAD_FACTOR) {}

  /**
   * Construct a new hash table object
   * @param capacity the number of buckets of the hash table
   * @param load_factor the average number of elements per bucket
   */
  hash_table(size_type capacity, double load_factor)
      : capacity_(capacity),
        max_load_factor_(load_factor),
        table_(new list<entry_type>[capacity_]) {}

  /** 
   * Copy constructor 
   * @param other the source hash table to copy from
   */
  hash_table(const hash_table& other) {
    table_ = new list<entry_type>[other.capacity_];
    size_ = other.size_;
    capacity_ = other.capacity_;
    max_load_factor_ = other.max_load_factor_;
    for (size_type idx = 0; idx < capacity_; ++idx) {
      for (const auto& entry : other.table_[idx]) {
        table_[idx].push_back(entry);
      }
    }
  }

  /**
   * Move constructor
   * @param other the source object to move from
   */
  hash_table(hash_table&& other) { other.swap(*this); }

  /** Destructor */
  ~hash_table() { delete[] table_; }

  /** 
   * Copy assignment 
   * @param other the source object to assign from
   * @return a reference to the assigned hash table
   */
  hash_table& operator=(const hash_table& other) {
    hash_table copy(other);
    copy.swap(*this);
    return *this;
  }

  /**
   * Move assignment
   * @param other the source object to move from
   * @return a reference to the assigned hash table
   */
  hash_table& operator=(hash_table&& other) noexcept {
    other.swap(*this);
    return *this;
  }

  /** @return the number of elements in the hash table */
  size_type size() const { return size_; }

  /** @return true if the hash table is empty; otherwise, false */
  bool empty() const { return size() == 0; }

  /** Insert a key (with default value) into the hash table.
   * If the key is already exists, modify the value of that key
   * @param key the key to insert
   */
  void insert(const K& key) { insert(key, V()); }

  /** Insert a key-value pair into the hash table.
   * If the key is already exists, modify the value of that key
   * @param key the key to insert
   * @param value the value of the key 
   */
  void insert(const K& key, const V& value) {
    uint32_t index = key_to_index(key);
    for (auto& entry : table_[index]) {
      if (entry.key_ == key) {
        entry.value_ = value;
        return;
      }
    }
    if (size_ > max_load_factor_ * capacity_) {
      grow_table();
      index = key_to_index(key);
    }
    table_[index].emplace_front(key, value);
    ++size_;
  }

  /**
   * Deletes a key from the hash table
   * @param key the key to delete
   */
  void erase(const K& key) {
    uint32_t index = key_to_index(key);
    for (auto& entry : table_[index]) {
      if (entry.key_ == key) {
        table_[index].erase(entry);
        --size_;
        break;
      }
    }
  }

  /**
   * Gets the value of the key
   * Throws exception if the key doesn't exist
   * @param key the key to get its value from
   * @return a reference to the value of that key
   */
  V& get(const K& key) {
    uint32_t index = key_to_index(key);
    for (auto& entry : table_[index]) {
      if (entry.key_ == key) {
        return entry.value_;
      }
    }
    throw std::out_of_range("The key doesn't exist\n");
  }

  V& operator[](const K& key) {
    uint32_t index = key_to_index(key);
    for (auto& entry : table_[index]) {
      if (entry.key_ == key) {
        return entry.value_;
      }
    }
    throw std::out_of_range("The key doesn't exist\n");
  }

  /**
   * Retrieves all the keys from the hash table
   * @return a list of keys in the hash table
   */
  vector<K> get_keys() {
    vector<K> keys;
    for (size_type idx = 0; idx < capacity_; ++idx) {
      for (const auto& entry : table_[idx]) {
        keys.push_back(entry.key_);
      }
    }
    return keys;
  }

  /** Checks if the hash table contains the `key` key
   * @param key the key to check
   * @return true if the key exists; otherwise, false
   */
  bool contains(const K& key) {
    uint32_t index = key_to_index(key);
    for (const auto& entry : table_[index]) {
      if (entry.key_ == key) {
        return true;
      }
    }
    return false;
  }

  /**
   * Converts the content of hash table to string
   * @return the hash table as string (i.e. [{key1, val1}, {key2, val2},...])
   */
  std::string to_string() {
    if (size() == 0) {
      return "[]";
    }
    std::stringstream ss;
    ss << "[";
    for (size_type idx = 0; idx < capacity_; ++idx) {
      for (const auto& entry : table_[idx]) {
        ss << '{' << entry.key_ << ',' << entry.value_ << "}, ";
      }
    }
    std::string res = ss.str();
    res = res.substr(0, res.size() - 2) + "]";
    return res;
  }

 private:
  /**
   * Grows the hash table 
   */
  void grow_table() {
    size_type old_capacity = capacity_;
    // Modify capacity first since it used for hashing
    capacity_ *= 2;
    auto new_table = new list<entry_type>[capacity_];
    for (size_type idx = 0; idx < old_capacity; ++idx) {
      for (const auto& entry : table_[idx]) {
        uint32_t new_idx = key_to_index(entry.key_);
        new_table[new_idx].push_front(entry);
      }
    }
    delete[] table_;
    table_ = new_table;
  }

  /**
   * Swaps the content of two hash tables
   * @param rhs the other hash table to swap with
   */
  void swap(hash_table& rhs) {
    using std::swap;
    swap(capacity_, rhs.capacity_);
    swap(max_load_factor_, rhs.max_load_factor_);
    swap(size_, rhs.size_);
    swap(table_, rhs.table_);
  }

  /**
   * Converts the key into index to the bucket
   * @param key the key to convert
   * @return the index (bucket number)
   */
  uint32_t key_to_index(K key) { return std::hash<K>()(key) % capacity_; }

  // The ratio between the number of elements and the number of bucket slots
  static constexpr double DEFAULT_LOAD_FACTOR = 0.75;
  static constexpr uint32_t DEFAULT_CAPACITY = 8;

  size_type capacity_{DEFAULT_CAPACITY};
  double max_load_factor_{DEFAULT_LOAD_FACTOR};
  size_type size_{0};
  list<entry_type>* table_{};
};

}  // namespace stl

#endif  // HASH_TABLE_H_