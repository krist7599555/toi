/**
segment tree + compress index + sort interval
ปล. จะเอียงแกน 45องศาแล้วทำ fenwick tree ก็ได้
*/
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
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<Interval> inp(n);
  std::vector<int> ans(n);
  std::vector<int> compress;

  for (int idx = 0, l, r; idx != n && std::cin >> l >> r; ++idx) {
    assert(l <= r);
    inp[idx] = Interval { l, r, idx };
    compress.push_back(l);
    compress.push_back(r);
  }

  // compress value 1e9 to unique index
  std::sort(all(compress));
  compress.erase(std::unique(all(compress)), compress.end());
  std::sort(all(inp), [](Interval lhs, Interval rhs) {
    // เรียงตาม r จากน้อยไปมากถ้า r เท่ากัน ให้เรียงตาม -l จะได้ทำจากข้างในเล็กๆออกไปข้างนอกใหญ่ๆ
    return std::tie(lhs.r, rhs.l) < std::tie(rhs.r, lhs.l);
  });

  // optimize segment tree in size of 2**k https://codeforces.com/blog/entry/18051
  int n2 = 1 << int(std::ceil(std::log2(compress.size())));
  std::vector<int> seg(2 * n2, 0);

  for (Interval it : inp) {
    const int l_idx = std::lower_bound(all(compress), it.l) - compress.begin();
    const int r_idx = std::lower_bound(all(compress), it.r) - compress.begin();
    assert(0 <= l_idx && l_idx <= r_idx && r_idx < compress.size());
    // query range=[l, r]
    int max_child = 0;
    for (int l = l_idx + n2, r = r_idx + n2 + 1; l != r; l /= 2, r /= 2) {
      if (l&1) max_child = std::max(max_child, seg[l++]);
      if (r&1) max_child = std::max(max_child, seg[--r]);
    }
    // set answer = max_child + 1 
    ans[it.idx] = max_child + 1;
    // update idx=r = answer
    int idx = l_idx + n2;
    seg[idx] = std::max(seg[idx], max_child + 1);
    for (; idx > 1; idx /= 2) {
      seg[idx / 2] = std::max(seg[idx], seg[idx ^ 1]);
    }
  }

  // print
  std::cout << *std::max_element(all(ans)) << '\n';
  for (int i = 0; i != ans.size(); ++i) {
    std::cout << ans[i] << (i + 1 != n ? ' ' : '\n');
  }
}
