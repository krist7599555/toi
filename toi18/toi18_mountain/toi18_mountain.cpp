/**
Dynamic Programming + Binary Search
*/
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <vector>
using namespace std;
#define for_(i,k,n) for (auto i = (k); i != (n); ++i)
typedef long long lli;

const int MAXN = 500;
const lli INF = 1LL << 62;

struct Point {
  lli x;
  lli y;
  static lli distance(const Point& lhs, const Point& rhs) {
    return abs(lhs.x - rhs.x) + abs(lhs.y - rhs.y);
  }
};

int main() {
  // input
  int n, q;
  std::cin >> n >> q;
  std::vector<Point> points(n);
  for (Point& p : points) {
    std::cin >> p.x >> p.y;
  }

  // DP state definition
  lli dp[MAXN][MAXN];
  // dp(node, food) = พลังงานน้อยสุดที่เดินจาก 0 --> node โดยกินอาหาร food ครั้ง
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
  for_(node2, 0, n) {
    if (node != node2) {
      lli new_max_distance = std::max(
        dp[node2][food - 1],                            // 0 --> n2
        Point::distance(points[node], points[node2])    // n2 --> n
      ); 
      dp[node][food] = std::min(dp[node][food], new_max_distance);
  }}}}

  //binary search on dp table
  const lli* foods = dp[n - 1]; // foods[จำนวนจุดที่พัก i] = ระยะทางเดินน้อยสุดที่ต้องการ ที่พักไม่เกิน i ครั้ง
  assert(std::is_sorted(foods, foods + n, std::greater<lli>()));
  lli ans = 0;
  while (q--) {
    lli max_walk;
    std::cin >> max_walk;
    auto it = std::lower_bound(foods, foods + n, max_walk, std::greater<lli>());
    ans += std::distance(foods, it);
  }
  std::cout << ans << std::endl;
}
