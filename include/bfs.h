#ifndef BFS_H_
#define BFS_H_

#include <climits>

#include "queue.h"
#include "undirected_graph.h"

namespace ds {
template<typename Type>
void BFS(UndirectedGraph<Type>& graph, Vertex<Type> *s) {
  auto vertices = graph.GetVertices();
  for (const auto& vertex : vertices) {
    vertex->color_ = Color::WHITE;
    vertex->distance_ = INT_MAX;
    vertex->parent_ = nullptr;
  }
  s->color_ = Color::GRAY;
  s->distance_ = 0;
  s->parent_ = nullptr;
  Queue<Vertex<Type>*> queue;
  queue.Enqueue(s);
  while (!queue.IsEmpty()) {
    auto u = queue.Dequeue();
    for (auto &v : graph.GetNeighbors(u)) {
      if (v->color_ == Color::WHITE) {
        v->color_ = Color::GRAY;
        v->distance_ = u->distance_ + 1;
        v->parent_ = u;
        queue.Enqueue(v);
      }
    }
    u->color_ = Color::BLACK;
  }
}
} // namespace ds

#endif // BFS_H_