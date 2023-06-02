#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>
#define all(x)  (x).begin(), (x).end()

struct Data {
  int position; // sort key
  int count;
  friend bool operator < (const Data& lhs, const Data& rhs) {
    return lhs.position < rhs.position;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int count_x, count_y, count_question;
  std::cin >> count_x >> count_y >> count_question; 
  std::vector<Data> xs(count_x),  ys(count_y);
  for (auto& vec : { &xs, &ys }) {
    for (auto& it : *vec) std::cin >> it.position;
    for (auto& it : *vec) std::cin >> it.count;
    assert(std::is_sorted(all(*vec)));
    std::for_each(all(*vec), [sum = 0](Data& it) mutable { // quicksum
      sum = (it.count += sum);
    });
  }

  auto binary_search_on_quicksum = [](const auto& vec, int position) {
    auto it = std::upper_bound(all(vec), Data { position, 0 });
    return it == vec.begin() ? 0 : std::prev(it)->count;
  };

  while (count_question--) {
    int n_th, alpha, beta;
    std::cin >> alpha >> beta >> n_th;
    int l = -1e9;
    int r =  1e9;
    while (l < r) {
      int mid_pos = l + (r - l) / 2;
      int acc_x = binary_search_on_quicksum(xs, mid_pos);
      int acc_y = binary_search_on_quicksum(ys, (mid_pos - beta) / alpha);
      if (acc_x + acc_y < n_th) l = mid_pos + 1;
      else r = mid_pos;
    }
    std::cout << l << '\n';
  }
}
