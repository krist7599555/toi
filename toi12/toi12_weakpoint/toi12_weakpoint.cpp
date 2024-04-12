#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 500005;

std::vector<int> edge[MAXN];
bool visit[MAXN];

int start_node;
int ans_max_sz = 0;
int ans_node;

// return is_cycle ? 0 : size
int dfs(int now, int from) {
  int sz = 0;
  bool is_cycle = false;
  visit[now] = true;
  for (auto nx : edge[now]) {
    if (nx == from) continue;
    if (nx == start_node) is_cycle = true;
    if (visit[nx]) continue;
    int child = dfs(nx,now);
    if (child == 0) is_cycle = true;
    sz += child;
  }
  if (now != start_node) {
    if (sz  > ans_max_sz) { ans_max_sz = sz; ans_node = now;}
    if (sz == ans_max_sz) { ans_max_sz = sz; ans_node = std::min(now,ans_node); }
  }
  return is_cycle ? 0 : sz + 1;
}
int main() {
  std::cin.sync_with_stdio(0);
  int n; std::cin >> n >> start_node;
  for (int i = 0; i < n; ++i){
    int u, v; std::cin >> u >> v;
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(start_node, -1);
  std::cout << ans_node << "\n";
  std::cout << ans_max_sz << "\n";
}