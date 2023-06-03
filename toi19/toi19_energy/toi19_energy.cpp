/*
Matrix Chain Multiplication
*/
#include <iostream>
#include <cstdio>
#include <vector>
using lli = long long;

const int MAXHEIGHT = 10;
const int MAXN = 310;
const int mod = 1e9 + 7;
lli dp[MAXHEIGHT][MAXN][MAXN];

int main() {
  int n, max_height, max_diff;
  std::cin >> n >> max_height >> max_diff;
  
  std::vector<int> qs(n + 1, 0); // quick sum
  for (int i = 1, input; i <= n && std::cin >> input; ++i) {
    qs[i] = qs[i-1] + input;
  }

  for (int l = 1; l <= n; ++l) {
  for (int r = l; r <= n; ++r) {
    dp[0][l][r] = 1;
  }}

  for (int hi = 1; hi < max_height; ++hi) {
  for (int sz = 1; sz <= n; ++sz) {
  for (int l = 1, r = sz; r <= n; ++l, ++r) {
  for (int pivot = l; pivot < r; ++pivot) {
    int qs_lhs = qs[pivot] - qs[l - 1];
    int qs_rhs = qs[r] - qs[pivot];
    if (abs(qs_lhs - qs_rhs) <= max_diff) {
      int ways = dp[hi - 1][l][pivot] * dp[hi - 1][pivot + 1][r] % mod;
      dp[hi][l][r] += ways;
      dp[hi][l][r] %= mod;
  }}}}}

  std::cout << dp[max_height - 1][1][n] << '\n';
}
