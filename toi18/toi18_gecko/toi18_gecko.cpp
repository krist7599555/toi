/**
ShortestPath (Dijkstra's algorithm) + Backtrack of DFS
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <stack>
#define for_(i, k, n) for (int i = k; i < n; ++i)
#define all(x) x.begin(), x.end()
using namespace std;
template<typename T>
using Vec = std::vector<T>;
const int INFINITY = 2e9;

struct Bridge {
  int from;
  int to;
  int weight;
  friend bool operator > (const Bridge& lhs, const Bridge& rhs) {
    return lhs.weight > rhs.weight;
  }
};
struct Ceil {
  int min_distance = INFINITY; // mutable
  Vec<Bridge> bridges;
};

int main() {
  // input
  int n_ceil, n_bridge, n_end_position, begin_position;
  std::cin >> n_ceil >> n_bridge >> n_end_position >> begin_position;
  assert(n_ceil <= 20000 && n_bridge <= 2000000 && begin_position < n_ceil);
  Vec<int> end_positions(n_end_position); // use in answer section
  for (int& pos : end_positions) {
    std::cin >> pos;
    assert(pos < n_ceil);
  }
  Vec<Ceil> ceil(n_ceil); // use in DP section
  while (n_bridge-- > 0) {
    int u, v, weight;
    std::cin >> u >> v >> weight;
    assert(u < v && v < n_ceil);
    ceil[u].bridges.push_back(Bridge { u, v, weight });
    ceil[v].bridges.push_back(Bridge { v, u, weight });
  }

  // shortest path with backtrack used bridge
  std::priority_queue<Bridge, Vec<Bridge>, std::greater<Bridge>> pq;
  std::stack<Bridge> backtrack; // use for print output only
  pq.push(Bridge { -1, begin_position, ceil[begin_position].min_distance = 0 });
  while (!pq.empty()) {
    Bridge curr = pq.top(); pq.pop();
    if (ceil[curr.to].min_distance != curr.weight) continue; // better value is updated. so skip

    backtrack.push(curr); // 1 node จะทำ 1 ครั้ง เพราะเป็น dijktra

    for (const Bridge nx : ceil[curr.to].bridges) {
      if (curr.weight + nx.weight < ceil[nx.to].min_distance) {
        pq.push(Bridge { 
          nx.from,
          nx.to,
          ceil[nx.to].min_distance = curr.weight + nx.weight
        });
  }}}

  // answer
  for (int pos : end_positions) {
    std::cout << ceil[pos].min_distance << ' ';
    assert(ceil[pos].min_distance < INFINITY);
  }
  std::cout << std::endl;
  std::cout << backtrack.size() - 1 << std::endl; // exclude root node
  while (backtrack.size() > 1) {
    Bridge b = backtrack.top(); backtrack.pop();
    std::cout << std::min(b.from, b.to) 
       << ' ' << std::max(b.from, b.to) << std::endl;
  }
}