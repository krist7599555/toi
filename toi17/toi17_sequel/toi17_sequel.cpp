/**
square root decomposition + quicksum
แต่ด้วย testcase อ่อนเลยทำตรงๆก็ผ่าน
*/
#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;
const int MAXN = 1e5 + 1;
const int MAXSQRTN = 320; // sqrt(1e5) = 316.227766017

int input[MAXN];
int quicksum[MAXSQRTN][MAXN]; // quicksum[step][i] = input[i] + input[i - step] + input[i - step * 2] + input[i - step * 3] + ...

int main() {
  std::cin.sync_with_stdio(false);
  std::cin.tie(0);

  int n, n_question;
  std::cin >> n >> n_question;
  const int sqrt_n = sqrt(n);
  assert(n < MAXN && sqrt_n < MAXSQRTN);

  // quicksum
  // O(n * sqrt(n))
  for (int i=1; i<=n; i++) {
    std::cin >> input[i];
    for (int step = 1; step <= sqrt_n; step++) {
      int prev_step = i - step;
      quicksum[step][i] += input[i] + quicksum[step][std::max(prev_step, 0)];
  }}

  while (n_question--) { // O(q * sqrt(n))
    int l, step, r;
    std::cin >> l >> step >> r;
    if (step <= sqrt_n) { // O(1)
      int n_step_use = (r - l) / step;
      int qs_0_to_r = quicksum[step][l + n_step_use * step]; 
      int qs_0_to_l = quicksum[step][l] - input[l];
      std::cout << (qs_0_to_r - qs_0_to_l) << ' ';
    } else { // O(sqrt(n))
      int sum = 0;
      for (; l <= r; l += step) {
        sum += input[l];
      }
      std::cout << sum << ' ';
    }
  }
}