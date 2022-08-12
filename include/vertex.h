#ifndef VERTEX_H_
#define VERTEX_H_

#include <functional>

namespace ds {
enum class Color {WHITE, GRAY, BLACK};

template<typename Type>
struct Vertex {
  Type value_{};
  Color color_;
  Vertex *parent_{};
  int distance_{};

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