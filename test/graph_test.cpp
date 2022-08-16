#include "graph.h"

#include <cassert>

void TestGraph1() {
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
}

void TestGraph2() {
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
}

void TestBFS() {
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

  graph.BFS(v1);
}

void TestDFS() {
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

  graph.DFS();
}

void TestTopologicalSort() {
  std::cout << "----------Topological sort Test----------\n";
  ds::Graph<int> graph(ds::GraphType::DIRECTED);
  auto v1 = graph.AddVertex(1);
  auto v2 = graph.AddVertex(2);
  auto v3 = graph.AddVertex(3);
  auto v4 = graph.AddVertex(4);
  auto v5 = graph.AddVertex(5);
  auto v6 = graph.AddVertex(6);
  graph.AddEdge(v1, v2);
  graph.AddEdge(v1, v4);
  graph.AddEdge(v3, v5);
  graph.AddEdge(v3, v6);
  graph.AddEdge(v5, v4);

  auto ordering = graph.TopologicalSort();
  for (const auto v : ordering) {
    std::cout << v->value_ << ' ';
  }
  std::cout << '\n';
}


void TestSCC() {
  std::cout << "----------Strongly Connected Components Test----------\n";
  ds::Graph<char> graph(ds::GraphType::DIRECTED);
  auto va = graph.AddVertex('a');
  auto vb = graph.AddVertex('b');
  auto vc = graph.AddVertex('c');
  auto vd = graph.AddVertex('d');
  auto ve = graph.AddVertex('e');
  auto vf = graph.AddVertex('f');
  auto vg = graph.AddVertex('g');
  auto vh = graph.AddVertex('h');
  graph.AddEdge(va, vb);
  graph.AddEdge(vb, vc);
  graph.AddEdge(vb, ve);
  graph.AddEdge(vb, vf);
  graph.AddEdge(vc, vd);
  graph.AddEdge(vc, vg);
  graph.AddEdge(vd, vc);
  graph.AddEdge(vd, vh);
  graph.AddEdge(ve, va);
  graph.AddEdge(ve, vf);
  graph.AddEdge(vf, vg);
  graph.AddEdge(vg, vf);
  graph.AddEdge(vg, vh);

  auto components = graph.FindStronglyConnectedComponents();
  for (const auto &root : components) {
    std::cout << root->value_ << ' ';
  }
  std::cout << '\n';

}

int main() {
  TestGraph1();
  TestGraph2();
  TestBFS();
  TestDFS();
  TestTopologicalSort();
  TestSCC();

  return 0;
}