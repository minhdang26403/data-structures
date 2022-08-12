#include "bfs.h"

void Test() {
  using namespace ds;
  UndirectedGraph<int> graph;
  Vertex<int>* v1 = graph.AddVertex(1);
  Vertex<int>* v2 = graph.AddVertex(2);
  Vertex<int>* v3 = graph.AddVertex(3);
  Vertex<int>* v4 = graph.AddVertex(4);
  Vertex<int>* v5 = graph.AddVertex(5);
  graph.AddEdge(v1, v5);
  graph.AddEdge(v1, v2);
  graph.AddEdge(v2, v3);
  graph.AddEdge(v2, v4);
  graph.AddEdge(v2, v5);
  graph.AddEdge(v3, v4);
  graph.AddEdge(v4, v5);

  graph.Print();

  BFS<int>(graph, v1);
}

int main() {
  Test();

  return 0;
}