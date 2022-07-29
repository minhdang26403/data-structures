#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <functional>
#include <string>
#include <sstream>

#include "linked_list.h"

namespace ds {
template<typename KeyType, typename ValueType>
struct Entry {
  KeyType key_;
  ValueType value_;
  Entry() = default;
  Entry(KeyType key, ValueType value) : key_(key), value_(value) {}
  bool operator==(const Entry& rhs) const { return key_ == rhs.key_; }
  bool operator!=(const Entry& rhs) const { return !(*this == rhs); }
};

template<typename KeyType, typename ValueType>
class HashTable {
 public:
  using SizeType = std::size_t;
  using EntryType = Entry<KeyType, ValueType>;
 public:
  /** Default constructor */
  HashTable() : HashTable(DEFAULT_CAPACITY, DEFAULT_LOAD_FACTOR) {}

  /** Constructs a hash table with `capacity` buckets 
   * @param capacity the number of buckets of the hash table
   */
  HashTable(SizeType capacity) : HashTable(capacity, DEFAULT_LOAD_FACTOR) {}

  /**
   * Construct a new Hash Table object
   * @param capacity the number of buckets of the hash table
   * @param load_factor the average number of elements per bucket (used for growing/shrinking table)
   */
  HashTable(SizeType capacity, float load_factor) : capacity_(capacity), max_load_factor_(load_factor), table_(new LinkedList<EntryType>[capacity_]) {}

  ~HashTable() {
    delete [] table_;
  }

  HashTable(const HashTable& other) = delete;
  HashTable& operator=(const HashTable& other) = delete;
  
  /** @return the number of elements in the hash table */
  SizeType Size() const { return size_; }

  /** @return true if the hash table is empty; otherwise, false */
  bool IsEmpty() const { return Size() == 0; }

  void Insert(const KeyType& key, const ValueType& value) {
    uint32_t index = KeyToIndex(key);
    for (auto& entry : table_[index]) {
      if (entry.key_ == key) {
        entry.value_ = value;
        return;
      }
    }
    if (size_ > max_load_factor_*capacity_) {
      GrowTable();
    }
    table_[index].EmplaceFront(key, value);
    ++size_;
  }

  void Delete(const KeyType& key) {
    uint32_t index = KeyToIndex(key);
    for (auto &entry : table_[index]) {
      if (entry.key_ == key) {
        table_[index].Erase(entry);
        --size_;
        break;
      }
    }
  }

  ValueType& Get(const KeyType& key) {
    uint32_t index = KeyToIndex(key);
    for (const auto& entry : table_[index]) {
      if (entry.key_ == key) {
        return entry.value_;
      }
    }
    return ValueType();
  }

  bool Contains(const KeyType& key) {
    uint32_t index = KeyToIndex(key);
    for (const auto& entry : table_[index]) {
      if (entry.key_ == key) {
        return true;
      }
    }
    return false;
  }

  std::string ToString() {
    if (Size() == 0) {
      return "[]";
    }
    std::stringstream ss;
    ss << "[";
    for (SizeType idx = 0; idx < capacity_; ++idx) {
      for (const auto &entry : table_[idx]) {
        ss << '{' << entry.key_ << ',' << entry.value_ << "}, ";
      }
    }
    std::string res = ss.str();
    res = res.substr(0, res.size() - 2) + "]";
    return res;
  }

 private:
  void GrowTable() {
    auto new_table = new LinkedList<EntryType>[capacity_*2];
    for (SizeType idx = 0; idx < capacity_; ++idx) {
      for (const auto &entry : table_[idx]) {
        uint32_t new_idx = KeyToIndex(entry.key_);
        new_table[new_idx].PushFront(entry);
      }
    }
    capacity_ *= 2;
    delete []table_;
    table_ = new_table;
  }
  uint32_t KeyToIndex(KeyType key) {
    return std::hash<KeyType>()(key) % capacity_;
  }
  // The ratio between the number of elements and the number of bucket slots
  static constexpr float DEFAULT_LOAD_FACTOR = 0.75;
  static constexpr uint32_t DEFAULT_CAPACITY = 8;
  SizeType capacity_;
  float max_load_factor_;
  SizeType size_{0};
  LinkedList<EntryType>* table_;
};

} // namespace ds

#endif // HASH_TABLE_H_