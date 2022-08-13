#ifndef GRAPH_H_
#define GRAPH_H_

#include <climits>

#include "hash_table.h"
#include "linked_list.h"
#include "queue.h"
#include "vector.h"
#include "vertex.h"

namespace ds {

enum class GraphType {UNDIRECTED, DIRECTED};

template<typename Type>
class Graph {
 public:
  using vertex_ptr = Vertex<Type>*;
  /** Constructor */
  Graph(GraphType type) : type_(type) {};
  
  /** Disable copy, move constructor and assignment */
  Graph(const Graph& other) = delete;
  Graph& operator=(const Graph& other) = delete;
  Graph(Graph&& other) = delete;
  Graph& operator=(Graph&& other) = delete;

  /** Destructor */
  ~Graph() {
    Vector<vertex_ptr> vertices = adj_list_.GetKeys();
    for (const auto& vertex : vertices) {
      delete vertex;
    }
  }

  /** 
   * Add a vertex to the graph
   * Assume that graphs doesn't have vertices with the same value
   * @param value the value of that vertex
   * @return a pointer to the vertex
   */
  vertex_ptr AddVertex(const Type& value) {
    auto vertex = new Vertex<Type>(value);
    adj_list_.Insert(vertex);
    return vertex;
  }

  /**
   * Adds an edge u->v to the graph
   * @param u vertex 
   * @param v vertex
   * @return true if add an edge successfully; otherwise, false
   */
  bool AddEdge(vertex_ptr u, vertex_ptr v) {
    if (type_ == GraphType::UNDIRECTED) {
      if (u == v) {
        std::cout << "An undirected graph doesn't allow self-loops\n";
        return false;
      }
      adj_list_[v].PushBack(u);
    }
    adj_list_[u].PushBack(v);
    return true;
  }

  /** @return a list of pointers to vertices of the graph */
  Vector<vertex_ptr> GetVertices() {
    return adj_list_.GetKeys();
  }

  /**
   * Retrieves neighbor nodes of a vertex
   * @param u the vertex to get its neighbors
   * @return a list of neighbor vertices
   */
  LinkedList<vertex_ptr>& GetNeighbors(vertex_ptr u) {
    return adj_list_[u];
  }

  /** For debugging */
  void Print() {
    Vector<vertex_ptr> vertices = adj_list_.GetKeys();
    for (int i = vertices.Size() - 1; i > -1; --i) {
      std::cout << vertices[i]->value_ << ": ";
      for (const auto v : adj_list_[vertices[i]]) {
        std::cout << v->value_ << "->";
      }
      std::cout << '\n';
    }
  }

  /** ---------- Algorithms on graph ---------- */

  /**
   * Breadth-First Search algorithms on graph
   * @param s the starting vertex to search from
   */
  void BFS(vertex_ptr s) {
    auto vertices = GetVertices();
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
    while (!queue.IsEmpty()) {
      auto u = queue.Dequeue();
      for (const auto &v : GetNeighbors(u)) {
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

  void DFS() {
    Vector<vertex_ptr> vertices = GetVertices();
    for (const auto& vertex : vertices) {
      vertex->color_ = Color::WHITE;
      vertex->parent_ = nullptr;
    }

    for (const auto& vertex : GetVertices()) {
      if (vertex->color_ == Color::WHITE) {
        DFSVisit(vertex);
      }
    }
  }

  void DFSVist(vertex_ptr vertex) {
    vertex->color_ = Color::GRAY;
    for (const auto& v : GetNeighbors(vertex)) {
      if (v->color_ == Color::WHITE) {
        v->parent_ = vertex;
        DFSVisit(vertex);
      }
    }
    vertex->color_ = Color::BLACK;
  }



 private:
  HashTable<vertex_ptr, LinkedList<vertex_ptr>> adj_list_;
  GraphType type_;
};


} // namespace ds

#endif // GRAPH_H_