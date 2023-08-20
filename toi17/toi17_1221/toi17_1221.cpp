/*
toi17_1221
Floyd–Warshall algorithm โดยแทนเส้นเชื่อมเป็นการซื้อของเป็นคู่
*/
#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>
#include <cassert>
#define for_(i, k, n) for (int i = k; i <= n; ++i)
typedef long long lli;
const int MAXN = 505;
const int INF = 1e9;

struct Item {
  int price;
  int piece;
  friend Item operator + (const Item& lhs, const Item& rhs) {
    return Item {
      lhs.price + rhs.price,
      lhs.piece + rhs.piece,
    };
  }
  friend bool operator < (const Item& lhs, const Item& rhs) { // เปรียบเทียบ ราคาถูกก่อน ถ้าราคาเท่าให้เลือกที่ของเยอะ
    return std::tie(lhs.price, rhs.piece) < std::tie(rhs.price, lhs.piece);
  }
};

Item dp[MAXN][MAXN];

int main() {
  int n, n_promotion, n_question;
  std::cin >> n >> n_promotion >> n_question;
  std::fill_n(*dp, MAXN * MAXN, Item { INF, 0 });

  // ราคาซื้อย่างเดียว
  for_(i, 1, n) {
    int price;
    std::cin >> price;
    dp[i][i] = Item { price, 1 };
  }

  // ราคาซื้อคู่
  while (n_promotion--) {
    int a, b, promo_price;
    std::cin >> a >> b >> promo_price;
    assert(a != b);
    dp[a][b] = dp[b][a] = Item { promo_price, 2 };
  }

  // ซื้อแยกชิ้นถูกกว่าซื้อคู่
  for_(i, 1, n) {
  for_(j, 1, n) {
    dp[i][j] = std::min(dp[i][j], dp[i][i] + dp[j][j]);
  }}

  // Floyd–Warshall algorithm
  for_(k, 1, n) {
  for_(i, 1, n) {
  for_(j, 1, n) {
    dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j]);
  }}}

  while (n_question--) {
    int a, b;
    std::cin >> a >> b;
    assert(a != b);
    Item ans = dp[a][b]; 
    std::cout << ans.price << ' ' << ans.piece << '\n';
  }
}
