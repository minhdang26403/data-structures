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

void TestDijkstra() {
  std::cout << "----------Dijkstra's algorithm Test----------\n";
  ds::Vector<char> vertices = {'s', 't', 'x', 'y', 'z'};
  ds::Graph<char> graph(ds::GraphType::DIRECTED);
  for (const auto& v : vertices) {
    graph.AddVertex(v);
  }
  ds::Vertex<char>* source = graph.GetVertex('s');
  graph.AddEdge('s', 't', 10);
  graph.AddEdge('s', 'y', 5);
  graph.AddEdge('t', 'x', 1);
  graph.AddEdge('t', 'y', 2);
  graph.AddEdge('x', 'z', 4);
  graph.AddEdge('y', 't', 3);
  graph.AddEdge('y', 'x', 9);
  graph.AddEdge('y', 'z', 2);
  graph.AddEdge('z', 's', 7);
  graph.AddEdge('z', 'x', 6);
  graph.Dijkstra(source);
  assert(graph.GetVertex('s')->distance_ == 0);
  assert(graph.GetVertex('t')->distance_ == 8);
  assert(graph.GetVertex('x')->distance_ == 9);
  assert(graph.GetVertex('y')->distance_ == 5);
  assert(graph.GetVertex('z')->distance_ == 7);
  graph.PrintDistance(source);
}

void TestBellmanFord1() {
  std::cout << "----------Bellman-Ford algorithm without negative cycles Test----------\n";
  ds::Graph<char> graph(ds::GraphType::DIRECTED);
  auto s = graph.AddVertex('s');
  auto t = graph.AddVertex('t');
  auto x = graph.AddVertex('x');
  auto y = graph.AddVertex('y');
  auto z = graph.AddVertex('z');
  graph.AddEdge(s, t, 6);
  graph.AddEdge(s, y, 7);
  graph.AddEdge(t, x, 5);
  graph.AddEdge(t, y, 8);
  graph.AddEdge(t, z, -4);
  graph.AddEdge(x, t, -2);
  graph.AddEdge(y, x, -3);
  graph.AddEdge(y, z, 9);
  graph.AddEdge(z, s, 2);
  graph.AddEdge(z, x, 7);
  graph.BellmanFord(s);
  graph.PrintDistance(s);
}

void TestBellmanFord2() {
  std::cout << "----------Bellman-Ford algorithm with negative cycles Test----------\n";
  ds::Graph<char> graph(ds::GraphType::DIRECTED);
  auto s = graph.AddVertex('s');
  auto t = graph.AddVertex('t');
  auto x = graph.AddVertex('x');
  auto y = graph.AddVertex('y');
  auto z = graph.AddVertex('z');
  graph.AddEdge(s, t, 6);
  graph.AddEdge(s, y, 7);
  graph.AddEdge(t, x, 5);
  graph.AddEdge(t, y, 8);
  graph.AddEdge(t, z, -4);
  graph.AddEdge(x, t, -6);
  graph.AddEdge(y, x, -3);
  graph.AddEdge(y, z, 9);
  graph.AddEdge(z, s, 2);
  graph.AddEdge(z, x, 7);
  graph.BellmanFord(s);
  graph.PrintDistance(s);
}

int main() {
  // TestGraph1();
  // TestGraph2();
  // TestBFS();
  // TestDFS();
  // TestTopologicalSort();
  // TestSCC();
  // TestDijkstra();
  // TestBellmanFord1();
  TestBellmanFord2();
  
  return 0;
}