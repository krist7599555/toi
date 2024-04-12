#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>
#include <tuple>

const int MAXN = 500010;
const int INVALID = -1;
struct Node {
  int size;
  int parent;
  Node(int sz = 1, int pa = INVALID): size(sz), parent(pa) {}
  bool is_cycle() { return parent == INVALID; }
  bool is_leaf() { return parent != INVALID; }
};
std::vector<int> edge[MAXN];
Node graph[MAXN]; // leaf point to parent, else INVALID
int edge_count[MAXN] = {}; // for topo sort

int main() {
  std::cin.sync_with_stdio(0);

  int n, main_node;
  std::cin >> n >> main_node;
  for (int i = 0; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    edge[u].push_back(v);
    edge[v].push_back(u);
    edge_count[u] += 1;
    edge_count[v] += 1;
  }
  std::fill_n(graph + 1, n, Node(1, INVALID));
  std::queue<int> leafs;
  for (int i = 1; i <= n; ++i) { // หา leaf node
    if (edge_count[i] == 1) {
      leafs.push(i);
    }
  }
  while (not leafs.empty()) { // ทำการลบ leaf ไปเรื่อยๆพร้อม update ค่าของ parent
    int node = leafs.front(); leafs.pop();
    assert(edge_count[node] == 1);
    for (int nx : edge[node]) {
      edge_count[nx] -= 1;
      if (graph[nx].parent == node) continue; // skip parent
      graph[nx].size += graph[node].size;
      graph[node].parent = nx;
      if (edge_count[nx] == 1) {
        leafs.push(nx);
      }
    }
    // std::cerr << "leaf(" << node << "), size = " << graph[node].size << '\n';
    assert(graph[node].is_leaf());
  }
  for (int i = 1; i <= n; ++i) { // node ที่เหลือทั้งหมดจะอยู่ใน cycle
    if (graph[i].is_cycle()) {
      // std::cerr << "cycle(" << i << "), size = " << graph[i].size << '\n';
      assert(edge_count[i] == 2);
    }
    else if (graph[i].is_leaf()) {
      assert(
        graph[graph[i].parent].is_cycle()
          ? edge_count[i] == 1
          : edge_count[i] == 0
      );
    }
  }

  std::vector<std::tuple<int,int>> ans; // [impact_count, -node]
  if (graph[main_node].is_leaf()) {
    // cut around self
    for (int nx : edge[main_node]) {
      if (graph[nx].is_leaf() and graph[nx].parent == main_node) {
        // cut child
        ans.emplace_back(graph[nx].size, -nx);
      } else {
        // cut parent
        ans.emplace_back(n - graph[main_node].size, -nx);
      }
    }
  } else if (graph[main_node].is_cycle()) {
    // cut around self
    for (int nx : edge[main_node]) {
      if (graph[nx].is_leaf() and graph[nx].parent == main_node) {
        // cut child
        ans.emplace_back(graph[nx].size, -nx);
      }
    }
    // cut big tree around cycle
    for (int i = 1; i <= n; ++i) {
      if (i != main_node and graph[i].is_cycle()) {
        ans.emplace_back(graph[i].size, -i);
      }
    }
  }

  auto [impact_count, neg_node] = *std::max_element(ans.begin(), ans.end());
  std::cout << -neg_node << '\n';
  std::cout << impact_count - 1 << '\n';
}