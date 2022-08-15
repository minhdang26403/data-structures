#include "dfs.h"
#include "graph.h"

void Test1() {
  std::cout << "----------DFS on Directed Graph Test----------\n";
  ds::Graph<int> graph(ds::GraphType::DIRECTED);
  auto v1 = graph.AddVertex(1);
  auto v2 = graph.AddVertex(2);
  auto v3 = graph.AddVertex(3);
  auto v4 = graph.AddVertex(4);
  auto v5 = graph.AddVertex(5);
  auto v6 = graph.AddVertex(6);
  graph.AddEdge(v1, v2);
  graph.AddEdge(v1, v4);
  graph.AddEdge(v2, v5);
  graph.AddEdge(v3, v5);
  graph.AddEdge(v3, v6);
  graph.AddEdge(v4, v2);
  graph.AddEdge(v5, v4);
  graph.AddEdge(v6, v6);

  ds::DFS(graph);
}

int main() {
  Test1();

  return 0;
}