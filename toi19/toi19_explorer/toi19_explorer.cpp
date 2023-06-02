#include <iostream>
#include <stack>
#include <cassert>
#include <queue>
#include <algorithm>

const int mod = 1e9 + 7;
typedef long long lli;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> child_count(n + 1, 0);
  std::vector<lli> ways(n + 1, 1); // ways[node] = factorial(child[node].size()) * product { ways[child] }
  std::vector<int> dfs;
  
  for (int t = 2 * n - 1; t > 0; t--) {
    int node;
    std::cin >> node;

    if (dfs.size() >= 2 && *std::prev(dfs.end(), 2) == node) {
      int child = dfs.back();
      dfs.pop_back(); 
      lli curr_way = ++child_count[node] * ways[child] % mod;
      ways[node] = ways[node] * curr_way % mod;  
    } else {
      dfs.push_back(node);
    }
  }

  std::cout << ways[dfs.front()] << '\n';
}