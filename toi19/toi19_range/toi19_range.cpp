#include <algorithm>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <cassert>
#define all(x) (x).begin(), (x).end()

struct Interval {
  int l, r, idx;
};

int main() {
  int n;
  std::cin >> n;
  std::vector<Interval> inp(n);
  std::vector<int> ans(n);
  for (int i = 0; i != n; ++i) {
    std::cin >> inp[i].l >> inp[i].r;
    inp[i].idx = i;
  }
  std::sort(all(inp), [](Interval lhs,  Interval rhs) {
    // sort by r
    return std::make_tuple(lhs.r, -lhs.l) < std::make_tuple(rhs.r, -rhs.l);
  });
  std::vector<int> lis; // longest increasing subsequence
  for (Interval& intv : inp) {
    int val = intv.l;
    auto it = std::upper_bound(all(lis), val, std::greater<int>());
    if (it == lis.end()) {
      lis.push_back(val);
      ans[intv.idx] = lis.size();
    } else {
      *it = val;
      ans[intv.idx] = std::distance(lis.begin(), it) + 1;
    }

    // ลองปริ้นได้
    // std::cerr << "idx=[" << intv.l  << "," << intv.r  << "]; lis = ";
    // for (int v : lis) std::cerr << v << ' ';
    // std::cerr << '\n';
  }

  // print
  std::cout << lis.size() << '\n';
  for (int i = 0; i != ans.size(); ++i) {
    std::cout << ans[i] << (i + 1 != n ? ' ' : '\n');
  }
}