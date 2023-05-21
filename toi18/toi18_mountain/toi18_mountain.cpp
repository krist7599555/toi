/**
Dynamic Programming + Binary Search
*/
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <vector>
#include <map>
#include <climits>
using namespace std;

#define for_(i,k,n) for (auto i = (k); i != (n); ++i)
typedef long long lli;
struct Point { int x; int y; };


lli point_distance(const Point& lhs, const Point& rhs) {
  return abs(lhs.x - rhs.x) + abs(lhs.y - rhs.y);
}

const int MAXN = 500;
const lli INF = LONG_MAX - 1;


int main() {
  int n, q;
  std::cin >> n >> q;
  std::vector<Point> points(n);
  for (Point& p : points) {
    std::cin >> p.x >> p.y;
  }

  lli dp[MAXN][MAXN];
  // dp(node, food) = พลังงานน้อยสุดที่เดินจาก 0 to `node` โดยกินอาหาร food ครั้ง
  // dp(0, 0) = 0     จุดเริ่มต้นไม่ใช้พลังงาน
  // dp(_, 0) = INF   ถ้าไม่มีอาหาร จะไปไหนไม่ได้
  // dp(n, f) = min { n2 in nodes | max(dp(n2, food - 1), distance(n2, n)) } 
  //          = เดินจาก 0 --> n2 --> n   โดย
  //                   0 --> n2         ใช้ค่าจาก dp ที่เคยคำนวนมาก่อนหน้า
  //                         n2 --> n   คำนวนระยะทางใหม่
  //                   รวมค่าโดยสมการ max คือ
  //                      ถ้า 0 --> n2 ใช้พลังงานเยอะ ก็เอา 0 --> n2 เป็นพลังงานสูงสุดที่ต้องใช้
  //                      ถ้า n2 --> n ใช้พลังงานเยอะ ก็เอา n2 --> n เป็นพลังงานสูงสุดที่ต้องใช้
  std::fill_n(dp[0], MAXN * MAXN, INF);
  dp[0][0] = 0;

  for_(food, 1, n) {
  for_(node, 0, n) {
    dp[node][food] = INF;
    for_(node2, 0, n) {
      if (node != node2) {
        dp[node][food] = std::min(
          dp[node][food],
          std::max(dp[node2][food - 1], point_distance(points[node], points[node2]))
        );
  }}}}

  const lli* foods = dp[n - 1]; // foods[จำนวนจุดที่พัก i] = ระยะทางเดินน้อยสุดที่ต้องการ ที่พักไม่เกิน i ครั้ง
  lli ans = 0;
  while (q--) {
    int max_walk;
    std::cin >> max_walk;
    auto it = std::lower_bound(foods, foods + n, max_walk, std::greater<lli>());
    ans += std::distance(foods, it);
  }
  std::cout << ans << std::endl;
}
