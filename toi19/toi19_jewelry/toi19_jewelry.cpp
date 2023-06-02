#include <iostream>
#include <utility>
#include <cassert>
using namespace std;
using lli = long long;
const int MAXN = 1e6 + 10;

int main() {
  int n;
  char str[MAXN];
  scanf("%d %s", &n, str + 1);
 
  lli ans = 0;
  lli sum = 0;
  int memo[MAXN];
  std::fill_n(memo, MAXN, 0);
  
  for (int l = 1; l <= n;) {
    switch (str[l]) {
      case 'F': {
        ans += sum;
        l += 1;
        break;
      }
      case 'T': {
        const int r = [&str, n, r = l]() mutable {
          while (r < n && str[r + 1] == 'T') r++;
          return r;
        }();
        for (int it = l, kadane = 1, new_memo = r; it <= r; it++, kadane++, new_memo--) {
          assert(l <= it && it <= r);
          assert(memo[kadane] < new_memo);
          sum += it - std::exchange(memo[kadane], new_memo);
          ans += sum;
        }
        l = r + 1;
        break;
      }
  }}
  printf("%lld\n", ans);
}