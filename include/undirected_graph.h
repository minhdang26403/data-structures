#ifndef UNDIRECTED_GRAPH_H_
#define UNDIRECTED_GRAPH_H_

#include "hash_table.h"
#include "linked_list.h"
#include "vector.h"
#include "vertex.h"

namespace ds {
template<typename Type>
class UndirectedGraph {
 public:
  using vertex_ptr = Vertex<Type>*;
  /** Constructor */
  UndirectedGraph() = default;
  
  /** Disable copy, move constructor and assignment */
  UndirectedGraph(const UndirectedGraph& other) = delete;
  UndirectedGraph& operator=(const UndirectedGraph& other) = delete;
  UndirectedGraph(UndirectedGraph&& other) = delete;
  UndirectedGraph& operator=(UndirectedGraph&& other) = delete;

  /** Destructor */
  ~UndirectedGraph() {
    Vector<vertex_ptr> vertices = adj_list_.GetKeys();
    for (const auto& vertex : vertices) {
      delete vertex;
    }
  }

  /** Add a vertex to the graph */
  vertex_ptr AddVertex(const Type& value) {
    auto vertex = new Vertex<Type>(value);
    adj_list_.Insert(vertex);
    return vertex;
  }

  /**
   * Add an edge {u,v} in the graph
   * @param u vertex 
   * @param v vertex
   */
  void AddEdge(vertex_ptr u, vertex_ptr v) {
    adj_list_[u].PushBack(v);
    adj_list_[v].PushBack(u);
  }

  Vector<vertex_ptr> GetVertices() {
    return adj_list_.GetKeys();
  }

  LinkedList<vertex_ptr>& GetNeighbors(vertex_ptr u) {
    return adj_list_[u];
  }

  void Print() {
    Vector<vertex_ptr> vertices = adj_list_.GetKeys();
    for (const auto &u : vertices) {
      std::cout << u->value_ << ": ";
      for (const auto v : adj_list_[u]) {
        std::cout << v->value_ << "->";
      }
      std::cout << '\n';
    }
  }

 private:
  HashTable<vertex_ptr, LinkedList<vertex_ptr>> adj_list_;
};


} // namespace ds

#endif // UNDIRECTED_GRAPH_H_