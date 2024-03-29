#ifndef VERTEX_H_
#define VERTEX_H_

#include "hashtable.h"
#include <functional>

namespace ds {
enum class Color {WHITE, GRAY, BLACK};

template<typename Type>
struct Vertex {
  Type value_{};
  Color color_{Color::WHITE};
  Vertex *parent_ {nullptr};
  int distance_{};
  int start_{};
  int finish_{};
  // weights of path to each adjacent vertex
  HashTable<Vertex<Type>*, int> weights_;

  /** Default constructor */
  Vertex() = default;

  /**
   * Constructs a new vertex with value `value`
   * @param value the value of the vertex
   */
  Vertex(Type value) : value_(value) {}

  /** @return true if two vertex have the same value; otherwise, false */
  bool operator==(const Vertex& rhs) const { return value_ == rhs.value_; }

  /** @return true if two vertex have different values; otherwise, false */
  bool operator!=(const Vertex& rhs) const { return !(*this == rhs); }
};

} // namespace ds

namespace std {
template<typename Type>
struct hash<ds::Vertex<Type>> {
  std::size_t operator()(const ds::Vertex<Type> &vertex) {
    return std::hash<Type>()(vertex.value_);
  }
};
} // namespace std

#endif // VERTEX_H_