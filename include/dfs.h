#ifndef DFS_H_
#define DFS_H_

#include "graph.h"

namespace ds {
/** Explores the graph using Depth-first search 
  * @param graph the graph to explore
  */
template<typename Type>
void DFS(Graph<Type> &graph) {
  Vector<Vertex<Type>*> vertices = graph.GetVertices();
  for (const auto& vertex : vertices) {
    vertex->color_ = Color::WHITE;
    vertex->parent_ = nullptr;
  }
  int time = 0;
  std::cout << "Vertex\tStart\tFinish\n";
  for (const auto& vertex : vertices) {
    if (vertex->color_ == Color::WHITE) {
      DFSVisit(graph, vertex, time);
    }
  }
}

/**
 * Recursively visits the neighbors of a vertex
 * @param vertex the vertex to start searching from
 * @param time the logical time of the procedure
 */
template<typename Type>
void DFSVisit(Graph<Type> &graph, Vertex<Type>* vertex, int& time) {
  ++time;
  vertex->start_ = time;
  vertex->color_ = Color::GRAY;
  auto neighbors = graph.GetNeighbors(vertex);
  for (const auto& neighbor : neighbors) {
    if (neighbor->color_ == Color::WHITE) {
      neighbor->parent_ = vertex;
      DFSVisit(graph, neighbor, time);
    }
  }
  ++time;
  vertex->finish_ = time;
  vertex->color_ = Color::BLACK;
  std::cout << vertex->value_ << '\t' << vertex->start_ << '\t' << vertex->finish_ << '\n';
}

} // namespace ds

#endif // DFS_H_