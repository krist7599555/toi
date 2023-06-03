/*
Dijkstra on bitset (bitmask)
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

const int MAXPOISON = 19;
const int MAXPOISONEXP = 1 << MAXPOISON;
const int INF = 1e9;

struct Edge {
  int node;
  int weight;
  friend bool operator > (Edge lhs, Edge rhs) {
    return lhs.weight > rhs.weight;
  }
};

int distance[MAXPOISONEXP];
std::vector<Edge> edge[MAXPOISONEXP];

int main() {
  int n_input, n_poison;
  std::cin >> n_input >> n_poison;
  assert(n_poison <= MAXPOISON);

  std::vector<int*> answer;
  for (int i = 0, weight; i < n_input; ++i) {
    std::cin >> weight;
    int s_bit = 0;
    int t_bit = 0;
    for (int k_bit = 1, poison; k_bit < (1 << n_poison); k_bit <<= 1) {
      std::cin >> poison;
      switch (poison) {
        case -1: { s_bit |= k_bit; break; }
        case  1: { t_bit |= k_bit; break; }
      }
    }
    edge[s_bit].push_back(Edge { t_bit, weight });
    answer.push_back(&distance[s_bit]);
  }

  std::fill_n(distance, MAXPOISONEXP, INF);
  std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
  pq.push(Edge { 0, distance[0] = 0 });

  while (!pq.empty()) {
    const int bit = pq.top().node; pq.pop();
    // eat apple
    for (Edge nx : edge[bit]) {
      int new_dist = distance[bit] + nx.weight; 
      if (new_dist < distance[nx.node]) {
        pq.push(Edge { nx.node, distance[nx.node] = new_dist });
    }}

    // apply to subset (ถ้าแก้พิษ 01110110 ได้ก็ย้่่อมแก้ทุก subset ของ 01110110 ได้)
    for (int k_bit = 1, poison; k_bit < (1 << n_poison); k_bit <<= 1) {
     if (bit & k_bit) {
      int subset_bit = bit ^ k_bit;
      assert((subset_bit & bit) == subset_bit);
      if (distance[bit] < distance[subset_bit]) {
        pq.push(Edge { subset_bit, distance[subset_bit] = distance[bit] });
    }}}
  }

  const int ans = std::accumulate(answer.begin(), answer.end(), 0, [](int acc, int* dist) {
    return std::max(acc, *dist == INF ? 0 : *dist);
  });

  std::cout << ans << '\n';
}