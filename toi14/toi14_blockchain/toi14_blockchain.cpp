// เปรียบเทียบต้นไม่เหมือนกัน == เปรียบเทียบ edge list
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <algorithm>

int input() { int val; std::cin >> val; return val; }

int main() {
  std::cin.sync_with_stdio(0);
  using EdgeList = std::vector<std::tuple<int,int>>;

  auto get_tree_graph = []() -> EdgeList {
    int n = input();
    EdgeList vec;
    for (int i = 1; i < n; ++i){
      int u = input();
      int v = input();
      if (u < v) std::swap(u, v);
      vec.emplace_back(u, v);
    }
    std::sort(vec.begin(), vec.end());
    return vec;
  };

  int t = input();
  int q = input();
  std::map<EdgeList, int> trees;
  while (t--) {
    auto tree = get_tree_graph();
    trees[tree] += 1;
  }
  while (q--) {
    auto tree = get_tree_graph();
    std::cout << trees[tree] << "\n";
  }
}
