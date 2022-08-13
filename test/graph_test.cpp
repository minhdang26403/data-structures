#include "graph.h"

#include <iostream>

void Test1() {
  std::cout << "----------Undirected Graph Test----------\n";
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
  graph.Print();

  std::cout << "----------BFS on Undirected Graph Test----------\n";
  graph.BFS(v1);
}

void Test2() {
  std::cout << "----------Directed Graph Test----------\n";
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
  graph.Print();
  
  std::cout << "----------BFS on Directed Graph Test----------\n";
  graph.BFS(v3);
  std::cout << v2->distance_ << '\n';
}

int main() {
  Test1();
  Test2();

  return 0;
}