/**
Quicksum + Binarysearch
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#define all(x) x.begin(), x.end()
using namespace std;

int main() {
  ios::sync_with_stdio(false);  // require ไม่้งั้นติด T
  std::cin.tie(0); // require ไม่้งั้นติด T

  // เงินเริ่มต้นไม่เกี่ยวข้องกับคะแนนรางวัล ต่อให้ได้คะแนนรางวัลเยอะเงินก็ไม่เพิ่ม มีแค่ลด
  // เพราะงั้น หาว่าด้วยเงินเท่านี้ ใช้จ่ายแล้วไปได้ไกลสุดแค่ไหน
  // เอาช่วงนั้นมาคำนวนหารางวัลทั้งหมดในช่วง
  int n, n_tourist;
  std::cin >> n >> n_tourist;
  std::vector<int> qs_reward(n + 1, 0); // qs = quick sum
  std::vector<int> qs_cost(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    int game_score_or_cost;
    std::cin >> game_score_or_cost;
    qs_reward[i] += qs_reward[i-1] + std::max(0, game_score_or_cost);
    qs_cost[i] += qs_cost[i-1] + std::max(0, -game_score_or_cost);
  }

  assert(qs_reward[0] == 0 && std::is_sorted(all(qs_reward)));
  assert(qs_cost[0] == 0 && std::is_sorted(all(qs_cost)));

  while (n_tourist--) {
    int cost_begin_idx, begin_money;
    std::cin >> cost_begin_idx >> begin_money;
    int cost_end_idx = std::lower_bound(all(qs_cost), qs_cost[cost_begin_idx] + begin_money) - qs_cost.begin();
    int reward_between_begin_end = qs_reward[cost_end_idx - 1] - qs_reward[cost_begin_idx];
    std::cout << reward_between_begin_end << '\n'; // ถ้าใช้ std::endl จะติด T
  }
}
