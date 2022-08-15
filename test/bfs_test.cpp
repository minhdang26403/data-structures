#include "bfs.h"
#include "graph.h"

void Test1() {
  std::cout << "----------BFS on Undirected Graph Test----------\n";
  ds::Graph<int> graph(ds::GraphType::UNDIRECTED);
  auto v1 = graph.AddVertex(1);
  auto v2 = graph.AddVertex(2);
  auto v3 = graph.AddVertex(3);
  auto v4 = graph.AddVertex(4);
  auto v5 = graph.AddVertex(5);
  graph.AddEdge(v1, v5);
  graph.AddEdge(v1, v2);
  graph.AddEdge(v2, v3);
  graph.AddEdge(v2, v4);
  graph.AddEdge(v2, v5);
  graph.AddEdge(v3, v4);
  graph.AddEdge(v4, v5);

  ds::BFS(graph, v1);
}

int main() {
  Test1();

  return 0;
}