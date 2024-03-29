#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <algorithm>
#include <functional>
#include <string>
#include <sstream>

#include "linked_list.h"
#include "vector.h"

namespace ds {
template<typename KeyType, typename ValueType>
struct Entry {
  KeyType key_;
  ValueType value_;
  /** Default construct */
  Entry() = default;

  /**
   * Constructs a new Entry object
   * @param key the key of the entry
   * @param value the value of the entry
   */
  Entry(KeyType key, ValueType value) : key_(key), value_(value) {}

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
  HashTable(SizeType capacity, float load_factor) 
    : capacity_(capacity), max_load_factor_(load_factor), table_(new LinkedList<EntryType>[capacity_]) {}

  /** 
   * Copy constructor 
   * @param other the source object to copy from
   */
  HashTable(const HashTable& other) {
    table_ = new LinkedList<EntryType>[other.capacity_];
    size_ = other.size_;
    capacity_ = other.capacity_;
    max_load_factor_ = other.max_load_factor_;
    for (SizeType idx = 0; idx < capacity_; ++idx) {
      for (const auto& entry : other.table_[idx]) {
        table_[idx].PushBack(entry);
      }
    }
  }

  /**
   * Move constructor
   * @param other the source object to move from
   */
  HashTable(HashTable&& other) {
    other.Swap(*this);
  }

  /** Destructor */
  ~HashTable() {
    delete [] table_;
  }

  /** 
   * Copy assignment 
   * @param other the source object to assign from
   * @return a reference to the assigned hash table
   */
  HashTable& operator=(const HashTable& other) {
    HashTable copy(other);
    copy.Swap(*this);
    return *this;
  }

  /**
   * Move assignment
   * @param other the source object to move from
   * @return a reference to the assigned hash table
   */
  HashTable& operator=(HashTable&& other) noexcept {
    other.Swap(*this);
    return *this;
  }
  
  /** @return the number of elements in the hash table */
  SizeType Size() const { return size_; }

  /** @return true if the hash table is empty; otherwise, false */
  bool IsEmpty() const { return Size() == 0; }

  /** Insert a key (with default value) into the hash table.
   * If the key is already exists, modify the value of that key
   * @param key the key to insert
   */
  void Insert(const KeyType& key) {
    Insert(key, ValueType());
  }

  /** Insert a key-value pair into the hash table.
   * If the key is already exists, modify the value of that key
   * @param key the key to insert
   * @param value the value of the key 
   */
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
      index = KeyToIndex(key);
    }
    table_[index].EmplaceFront(key, value);
    ++size_;
  }

  /**
   * Deletes a key from the hash table
   * @param key the key to delete
   */
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

  /**
   * Gets the value of the key
   * Throws exception if the key doesn't exist
   * @param key the key to get its value from
   * @return a reference to the value of that key
   */
  ValueType& Get(const KeyType& key) {
    uint32_t index = KeyToIndex(key);
    for (auto& entry : table_[index]) {
      if (entry.key_ == key) {
        return entry.value_;
      }
    }
    throw std::out_of_range("The key doesn't exist\n");
  }

  ValueType& operator[](const KeyType& key) {
    uint32_t index = KeyToIndex(key);
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
  Vector<KeyType> GetKeys() {
    Vector<KeyType> keys;
    for (SizeType idx = 0; idx < capacity_; ++idx) {
      for (const auto &entry : table_[idx]) {
        keys.PushBack(entry.key_);
      }
    }
    return keys;
  }

  /** Checks if the hash table contains the `key` key
   * @param key the key to check
   * @return true if the key exists; otherwise, false
   */
  bool Contains(const KeyType& key) {
    uint32_t index = KeyToIndex(key);
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
  /**
   * Grows the hash table 
   */
  void GrowTable() {
    SizeType old_capacity = capacity_;
    // Modify capacity first since it used for hashing
    capacity_ *= 2;
    auto new_table = new LinkedList<EntryType>[capacity_];
    for (SizeType idx = 0; idx < old_capacity; ++idx) {
      for (const auto &entry : table_[idx]) {
        uint32_t new_idx = KeyToIndex(entry.key_);
        new_table[new_idx].PushFront(entry);
      }
    }
    delete []table_;
    table_ = new_table;
  }


  /**
   * Swaps the content of two hash tables
   * @param rhs the other hash table to swap with
   */
  void Swap(HashTable& rhs) {
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
  uint32_t KeyToIndex(KeyType key) {
    return std::hash<KeyType>()(key) % capacity_;
  }
  
  // The ratio between the number of elements and the number of bucket slots
  static constexpr float DEFAULT_LOAD_FACTOR = 0.75;
  static constexpr uint32_t DEFAULT_CAPACITY = 8;
  SizeType capacity_{DEFAULT_CAPACITY};
  float max_load_factor_{DEFAULT_LOAD_FACTOR};
  SizeType size_{0};
  LinkedList<EntryType>* table_{};
};

} // namespace ds

#endif // HASH_TABLE_H_