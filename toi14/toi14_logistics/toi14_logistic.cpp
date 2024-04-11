/*
Shortest Path หลายมิติ ใช้ Dijkstra's algorithm

dp[เมือง][น้ำมัน][ตั๋วพิเศษ] = ค่าใช้จ่ายถูกสุด (price)

โดยมีเงื่อนไขการเปลี่ยน State ตามนี้

1. เดินทางโดยใช้น้ำมันในถัง `dp[new_node][fuel - use_fuel][ticket] = price`
2. เติมน้ำมัน 1 หน่วยโดยจ่ายเงิน `dp[node][fuel + 1][ticket] = price + cost[node]`
3. เติมน้ำมันจนเต็ม โดยจ่ายตั๋ว `dp[node][fuel_capacity][0] = dp[node][*][1]`
*/

#include <iostream>
#include <tuple>
#include <queue>
#include <algorithm>
#include <cassert>

const int INF = 1e8;
const int MAXN = 101;

int cost[MAXN];
int dp[MAXN][MAXN][2];
std::vector<std::tuple<int,int>> edge[MAXN]; // [node, fuel_use]

int input() { int val; std::cin >> val; return val; }

int main() {
  std::cin.sync_with_stdio(false);
  std::fill_n(dp[0][0], MAXN * MAXN * 2, INF);

  int n = input();
  for (int i = 1; i <= n; ++i) {
    cost[i] = input();
  }
  int city_begin = input();
  int city_end = input();
  int fuel_capacity = input();

  int n_edge = input();
  while (n_edge--) {
    int u = input();
    int v = input();
    int fuel_use = input();
    edge[u].emplace_back(v, fuel_use);
    edge[v].emplace_back(u, fuel_use);
  }

  using Data = std::tuple<int,int,int,int>; // [price, node, fuel, ticket]
  std::priority_queue<
    Data,
    std::vector<Data>,
    std::greater<Data>
  > pq; // [price, node, fuel, ticket]

  auto try_add = [&](int price, int node, int fuel, int ticket) {
    if (price < dp[node][fuel][ticket]) {
      pq.emplace(
        dp[node][fuel][ticket] = price,
        node,
        fuel,
        ticket
      );
    }
  };

  // [price, node, fuel, ticket]
  try_add(0, city_begin, 0, 1);

  while (!pq.empty()) {
    auto [price, node, fuel, ticket] = pq.top(); pq.pop();
    if (price > dp[node][fuel][ticket]) continue;

    // 1. fill tank 1 unit
    if (fuel < fuel_capacity) {
      try_add(price + cost[node], node, fuel + 1, ticket);
    }

    // 2. use special ticket - fill fuel to full without pay
    if (ticket == 1) {
       try_add(price, node, fuel_capacity, 0); 
    }

    // 3. drive on road
    for (auto [node_next, fuel_use] : edge[node]) {
      if (fuel >= fuel_use) {
        try_add(price, node_next, fuel - fuel_use, ticket);       
      }
    }
  }

  // city_end ที่ เติมน้ำมันจนเต็ม และใช้ตั๋วพิเศษแล้ว
  std::cout << dp[city_end][fuel_capacity][0] << std::endl;
}