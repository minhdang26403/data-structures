#ifndef BFS_H_
#define BFS_H_

#include "graph.h"
#include "queue.h"

namespace ds {
/**
 * Breadth-First Search algorithms on unweighted graph
 * @param graph the graph to search
 * @param s the starting vertex to search from
 */
template<typename Type>
void BFS(Graph<Type>& graph, Vertex<Type>* s) {
  using vertex_ptr = Vertex<Type>*;
  auto vertices = graph.GetVertices();
  for (const auto& vertex : vertices) {
    vertex->color_ = Color::WHITE;
    vertex->distance_ = INT_MAX;
    vertex->parent_ = nullptr;
  }
  s->color_ = Color::GRAY;
  s->distance_ = 0;
  s->parent_ = nullptr;
  Queue<vertex_ptr> queue;
  queue.Enqueue(s);
  LinkedList<vertex_ptr> neighbors;
  while (!queue.IsEmpty()) {
    auto vertex = queue.Dequeue();
    std::cout << vertex->value_ << "->";
    neighbors = graph.GetNeighbors(vertex);
    for (const auto &neighbor : neighbors) {
      if (neighbor->color_ == Color::WHITE) {
        neighbor->color_ = Color::GRAY;
        neighbor->distance_ = vertex->distance_ + 1;
        neighbor->parent_ = vertex;
        queue.Enqueue(neighbor);
      }
    }
    vertex->color_ = Color::BLACK;
  }
  std::cout << "x\n";
}

} // namespace ds

#endif // BFS_H_