#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <array>
using namespace std;
const int MAXN = 15009;
const int INF = 1e9;

struct Point { int x; int y; };
inline int point_distance(const Point& lhs, const Point& rhs) {
  return std::abs(lhs.x - rhs.x) + std::abs(lhs.y - rhs.y);
}

// TestCase 17 Will Timeout if using std::vector<bool> in main
bool visit[MAXN];
int dist[MAXN];

int main() {
  std::cin.sync_with_stdio(0);
  std::cin.tie(0);
  
  int n, k; std::cin >> n >> k;
  std::vector<Point> point(n);
  for (auto& p : point) std::cin >> p.x >> p.y;
  
  std::fill_n(visit, n, false);
  std::fill_n(dist, n, INF);
  std::vector<int> mst;
  
  for (int node = 0; mst.size() != n - 1;) {
    std::tuple<int, int> local_min = { INF, -1 }; // [distance, node]
    visit[node] = true;
    for (int nx = 0; nx < n; nx++) {
      if (visit[nx]) continue;
      int cost = point_distance(point[node], point[nx]);
      local_min = std::min(local_min, {
        dist[nx] = std::min(dist[nx], cost),
        nx
      });
    }
    auto [min_cost, ans_node] = local_min;
    mst.push_back(min_cost);
    node = ans_node;
    assert(node != -1);
  }
  std::sort(mst.begin(), mst.end()); // Tip! Optimize Use Below nth_element without fully sort
  // std::nth_element(mst.begin(), mst.begin() + n - k, mst.end()); // Sadly TestCase 17 Run Slower on this
  int ans = std::accumulate(mst.begin(), mst.begin() + n - k, 0);
  std::cout << ans << '\n';
}