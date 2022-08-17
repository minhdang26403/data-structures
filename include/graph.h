#ifndef GRAPH_H_
#define GRAPH_H_

#include <climits>

#include "hash_table.h"
#include "indexed_pq.h"
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
    if (vertex_values_.Contains(value)) {
      std::cerr << "The graph doesn't allow duplicate vertex values\n";
      return nullptr;
    }
    vertex_ptr vertex = new Vertex<Type>(value);
    adj_list_.Insert(vertex);
    vertex_values_.Insert(value, vertex);
    ++vertices_;
    return vertex;
  }

  /**
   * Adds an edge u->v to the graph
   * @param u_value the value of vertex u
   * @param v_value the value of vertex v
   * @return true if add an edge successfully; otherwise, false
   */
  bool AddEdge(const Type& u_value, const Type& v_value, int weight=INT_MIN) {
    return AddEdge(GetVertex(u_value), GetVertex(v_value), weight);
  }

  /**
   * Adds an edge u->v to the graph
   * @param u vertex 
   * @param v vertex
   * @return true if add an edge successfully; otherwise, false
   */
  bool AddEdge(vertex_ptr u, vertex_ptr v, int weight=INT_MIN) {
    if (type_ == GraphType::UNDIRECTED) {
      if (u == v) {
        std::cerr << "An undirected graph doesn't allow self-loops\n";
        return false;
      }
      adj_list_[v].PushBack(u);
      v->weights_.Insert(u, weight);
    }
    adj_list_[u].PushBack(v);
    u->weights_.Insert(v, weight);
    ++edges_;
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
  LinkedList<vertex_ptr> GetNeighbors(vertex_ptr u) {
    return adj_list_[u];
  }

  /** @return the number of vertices in the graph */
  int GetVerticesCount() const { return vertices_; }

  /** @return the number of edges in the graph */
  int GetEdgesCount() const { return edges_; }

  /** @return the type of the graph */
  GraphType GetGraphType() const { return type_; }

  int GetWeight(vertex_ptr u, vertex_ptr v) const { return u->weights_[v]; }
  
  /**
   * Get the vertex with `value` value
   * @param value the value of the vertex
   * @return vertex_ptr a pointer to that vertex
   */
  vertex_ptr GetVertex(const Type& value) { return vertex_values_[value]; }

  /** For debugging */
  void Print() {
    Vector<vertex_ptr> vertices = GetVertices();
    for (int i = vertices.Size() - 1; i > -1; --i) {
      std::cout << vertices[i]->value_ << ": [";
      for (const auto &v : adj_list_[vertices[i]]) {
        std::cout << v->value_ << ", ";
      }
      std::cout << "]\n";
    }
  }

  /**
   * Prints the distance of each vertex from the source vertex `s`
   * @param s a pointer to the source vertex
   */
  void PrintDistance(vertex_ptr s) {
    Vector<vertex_ptr> vertices = GetVertices();
    for (int i = vertices.Size() - 1; i > -1; --i) {
      auto vertex = vertices[i];
      std::cout << "The shortest distance from " << s->value_ << " to " << vertex->value_ << ": " << vertex->distance_ << '\n';
    }
  }


  /** ---------- Algorithms on graph ---------- */

  /**
   * Breadth-First Search algorithms on unweighted graph
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
    LinkedList<vertex_ptr> neighbors;
    while (!queue.IsEmpty()) {
      auto vertex = queue.Dequeue();
      std::cout << vertex->value_ << "->";
      neighbors = GetNeighbors(vertex);
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


  /** Explores the graph using Depth-first search */
  void DFS() {
    Vector<vertex_ptr> vertices = GetVertices();
    int time = 0;

    std::cout << "Vertex\tStart\tFinish\n";
    for (const auto& vertex : vertices) {
      // Initially, all vertices are colored white
      if (vertex->color_ == Color::WHITE) {
        DFSVisit(vertex, time, true);
      }
    }
  }

  /**
   * Performs a topological sort on the directed acyclic graph (DAG)
   * @return a list of vertices in the topological order
   */
  Vector<vertex_ptr> TopologicalSort() {
    // Validation
    if (GetGraphType() == GraphType::UNDIRECTED) {
      std::cerr << "Can't perform topological sort on undirected graph";
      exit(1);
    }

    Vector<vertex_ptr> vertices = GetVertices();
    int v_count = GetVerticesCount();
    Vector<vertex_ptr> ordering(v_count, nullptr);
    int idx = v_count - 1;
    int time = 0;
    bool print_out = true, check_cycle = true;
    for (const auto& vertex : vertices) {
      if (vertex->color_ == Color::WHITE) {
        DFSVisit(vertex, time, ordering, idx, print_out, check_cycle);
      }
    }
    return ordering;
  }

  /**
   * Find the strongly connected components of a graph (Kosaraju's algorithm)
   * Time complexity: O(V + E)
   * @return roots of the depth-first trees in components
   */
  Vector<vertex_ptr> FindStronglyConnectedComponents() {
    if (GetGraphType() == GraphType::UNDIRECTED) {
      std::cerr << "Can't find strongly connected components on undirected graph";
      exit(1);
    }
    // Step 1: Use DFS to compute v.f for each vertex v
    Vector<vertex_ptr> vertices = GetVertices();

    int v_count = GetVerticesCount();
    Vector<vertex_ptr> ordering(v_count, nullptr);
    int idx = v_count - 1;

    int time = 0;
    bool print_out = true;

    for (const auto& vertex : vertices) {
      if (vertex->color_ == Color::WHITE) {
        DFSVisit(vertex, time, ordering, idx, print_out);
      }
    }

    // Step 2: Create the transpose of the graph
    Graph<Type> transpose_graph(GraphType::DIRECTED);
    CreateTransposeGraph(transpose_graph);


    // Step 3: Consider the vertices in order of decreasing finish time
    Vector<vertex_ptr> components;
    time = 0;
    for (const auto &vertex : ordering) {
      auto transpose_vertex = transpose_graph.GetVertex(vertex->value_);
      if (transpose_vertex->color_ == Color::WHITE) {
        transpose_graph.DFSVisit(transpose_vertex, time, false);
        // Push the vertex of the original graph to the result list, not the temporary transpose graph
        components.PushBack(GetVertex(transpose_vertex->value_));
      }
    }
    return components;
  }

  /**
   * Finds the shortest path from the source vertex `s` to every other vertices in the graph
   * Dijkstra's algorithm works on weighted, directed graph will nonnegative edge weights
   * Time complexity: O(VlogV + ElogV)
   * @param s a pointer to the source vertex
   */
  void Dijkstra(vertex_ptr s) {
    if (GetGraphType() == GraphType::UNDIRECTED) {
      std::cerr << "Dijkstra's algorithm: The graph must be directed\n";
      exit(1);
    }

    InitializeSource(s);
    IndexedPriorityQueue<vertex_ptr, int> queue;
    HashTable<vertex_ptr, bool> visited;
    for (const auto &u : GetVertices()) {
      queue.Insert(u, u->distance_);
      visited.Insert(u, false);
    }

    while (!queue.IsEmpty()) {
      auto key_val = queue.Pop();
      vertex_ptr u = key_val.first;
      visited[u] = true;
      for (const auto& v : GetNeighbors(u)) {
        // The visited node already has the shortest path computed correctly.
        // However, this is not true in case of negative edge weights
        if (visited[v]) {
          continue;
        }
        int new_distance = u->distance_ + GetWeight(u, v);
        if (new_distance < v->distance_) {
          v->distance_ = new_distance;
          v->parent_ = u;
          queue.Update(v, v->distance_);
        }
      }
    }
  }

  /**
   * Bellman-Ford algorithm solves the single-source shortest-paths problem in general case 
   * (edge weights can be negative and the graph can have negative cycle)
   * @param s a pointer to the source vertex
   * @return false if the graph contains a negative cycle; otherwise, true
   */
  bool BellmanFord(vertex_ptr s) {
    if (GetGraphType() == GraphType::UNDIRECTED) {
      std::cerr << "Bellman-Ford algorithm: The graph must be directed\n";
      exit(1);
    }

    InitializeSource(s);
    int num_vertices = GetVerticesCount();
    // The algorithm can finish computation earlier than |V| - 1 iterations
    bool relaxed_edge = true;
    for (int i = 1; i < num_vertices - 1 && relaxed_edge; ++i) {
      relaxed_edge = false;
      // Go through total of |E| edges
      for (const auto& vertex : GetVertices()) {
        for (const auto& neighbor : GetNeighbors(vertex)) {
          // Handle integer overflow
          if (vertex->distance_ == INT_MAX) {
            continue;
          }
          int new_distance = vertex->distance_ + GetWeight(vertex, neighbor);
          if (new_distance < neighbor->distance_) {
            neighbor->distance_ = new_distance;
            relaxed_edge = true;
          }
        }
      }
    }

    for (const auto& vertex : GetVertices()) {
      for (const auto& neighbor : GetNeighbors(vertex)) {
        int new_distance = vertex->distance_ + GetWeight(vertex, neighbor);
        if (new_distance < neighbor->distance_) {
          std::cerr << "The graph contains a negative cycle\n";
          return false;
        }
      }
    }
    return true;
  }

 private:
  /**
   * Recursively visits the neighbors of a vertex. Used as subroutine for standard DFS
   * @param vertex the vertex to start searching from
   * @param time the logical time of the procedure
   * @param print whether to print for debugging or not
   */
  void DFSVisit(vertex_ptr vertex, int& time, bool print) {
    ++time;
    vertex->start_ = time;
    vertex->color_ = Color::GRAY;
    LinkedList<vertex_ptr> neighbors = GetNeighbors(vertex);
    for (const auto& neighbor : neighbors) {
      if (neighbor->color_ == Color::WHITE) {
        neighbor->parent_ = vertex;
        DFSVisit(neighbor, time, print);
      }
    }
    ++time;
    vertex->finish_ = time;
    vertex->color_ = Color::BLACK;
    if (print) {
      std::cout << vertex->value_ << '\t' << vertex->start_ << '\t' << vertex->finish_ << '\n';
    }
  }

  /**
   * Recursively visits the neighbors of a vertex. Used as a subroutine for topological sort
   * @param vertex the vertex to start searching from
   * @param time the logical time of the procedure
   * @param ordering the list of vertex in topological order
   * @param idx the idx to store vertex
   * @param print whether to print for debugging or not
   */
  void DFSVisit(vertex_ptr vertex, int& time, Vector<vertex_ptr> &ordering, int &idx, bool print, bool detect_cycle=false) {
    ++time;
    vertex->start_ = time;
    vertex->color_ = Color::GRAY;
    LinkedList<vertex_ptr> neighbors = GetNeighbors(vertex);
    for (const auto& neighbor : neighbors) {
      if (detect_cycle && neighbor->color_ == Color::GRAY) {
        std::cerr << "The graph contains cycle\n";
        return;
      }
      if (neighbor->color_ == Color::WHITE) {
        neighbor->parent_ = vertex;
        DFSVisit(neighbor, time, ordering, idx, print);
      }
    }
    ++time;
    vertex->finish_ = time;
    vertex->color_ = Color::BLACK;
    ordering[idx--] = vertex;
    if (print) {
      std::cout << vertex->value_ << '\t' << vertex->start_ << '\t' << vertex->finish_ << '\n';
    }
  }

  /**
   * Constructs a transpose of from the original graph
   * @param[out] transpose the transpose of the graph
   */
  void CreateTransposeGraph(Graph& transpose) {
    auto vertices = GetVertices();
    for (const auto &vertex : vertices) {
      transpose.AddVertex(vertex->value_);
    }

    for (const auto &vertex : vertices) { 
      auto neighbors = GetNeighbors(vertex);
      for (const auto &neighbor : neighbors) {
        transpose.AddEdge(transpose.GetVertex(neighbor->value_), transpose.GetVertex(vertex->value_));
      }
    }
  }

  void InitializeSource(vertex_ptr s) {
    auto vertices = GetVertices();
    for (const auto& v : vertices) {
      v->distance_ = INT_MAX;
      v->parent_ = nullptr;
    }
    s->distance_ = 0;
  }

  // core data structure representing the graph
  HashTable<vertex_ptr, LinkedList<vertex_ptr>> adj_list_;
  // A map from vertex value to the vertex
  HashTable<Type, vertex_ptr> vertex_values_;
  GraphType type_;
  // number of vertices
  int vertices_{0};
  // number of edges
  int edges_{0};
};


} // namespace ds

#endif // GRAPH_H_