#ifndef TOPOLOGICAL_SORT_H_
#define TOPOLOGICAL_SORT_H_

#include "graph.h"

namespace ds {

#define vertex_ptr Vertex<Type>*

/**
 * Performs a topological sort on the directed acyclic graph (DAG)
 * @param graph the graph to do topological sort
 * @return a list of vertices in the topological order
 */
template<typename Type>
Vector<vertex_ptr> TopologicalSort(Graph<Type>& graph) {
  // Validation
  if (graph.GetType() == GraphType::UNDIRECTED) {
    std::cerr << "Can't perform topological sort on undirected graph";
  }
  Vector<vertex_ptr> vertices = graph.GetVertices();
  for (const auto& vertex : vertices) {
    vertex->color_ = Color::WHITE;
  }

  int v_count = graph.GetVerticesCount();
  Vector<vertex_ptr> ordering(v_count);
  int idx = v_count - 1;
  for (const auto& vertex : vertices) {
    if (vertex->color_ == Color::WHITE) {
      DFSVisit(graph, vertex, ordering, idx);
    }
  }
  return ordering;
}

/**
 * Recursively visits the neighbors of a vertex
 * @param vertex the vertex to start searching from
 * @param time the logical time of the procedure
 */
template<typename Type>
void DFSVisit(Graph<Type>& graph, vertex_ptr vertex, Vector<vertex_ptr> &ordering, int &idx) {
  vertex->color_ = Color::GRAY;
  LinkedList<vertex_ptr> neighbors = graph.GetNeighbors(vertex);
  for (const auto& neighbor : neighbors) {
    if (neighbor->color_ == Color::WHITE) {
      neighbor->parent_ = vertex;
      DFSVisit(graph, neighbor, ordering, idx);
    }
  }
  vertex->color_ = Color::BLACK;
  ordering[idx--] = vertex;
}

} // namespace ds

#endif // TOPOLOGICAL_SORT_H_