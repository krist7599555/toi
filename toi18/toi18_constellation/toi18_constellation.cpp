/**
QuickSum + Combinatoric
*/
#include <iostream>
#include <vector>
#define for_(i, k, n) for (int i = k; i < n; ++i)
using namespace std;
const int MOD = 1e6 + 3;
const int MAXN = 300;
const int OFFSET =  2 * MAXN;
const int MAXN2 = OFFSET + MAXN + OFFSET;

int tr[MAXN2][MAXN2]; // sum 45degree to top-right
int tl[MAXN2][MAXN2]; // sum 45degree to top-left
int pascal[MAXN2][MAXN2];

int main() {
  // static
  // คำนวน n choose k ไว้ก่อนแบบไวๆ
  for_(n, 1, MAXN2) {
    pascal[n][0] = pascal[n][n] = 1;
    for_(k, 1, n) {
      pascal[n][k] = (pascal[n-1][k-1] + pascal[n-1][k]) % MOD;
  }}

  // dynamic
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n_row, n_col, n_require_star;
  std::cin >> n_row >> n_col >> n_require_star;

  // รับ input ไว้ตรงกลางกระดานใหญ่ยัก
  for_(i, 0, n_row) {
    std::string row;
    std::cin >> row;
    for_(j, 0, n_col) {
      char c = row[j];
      tr[i + OFFSET][j + OFFSET] = c == '#' ? 1 : 0;
      tl[i + OFFSET][j + OFFSET] = c == '#' ? 1 : 0;
  }}

  // สร้าง quicksum แนวทะแยง
  for_(i, 1, MAXN2 - 1) {
  for_(j, 1, MAXN2 - 1) {
    tr[i][j] += tr[i-1][j+1];
    tl[i][j] += tl[i-1][j-1];
  }}


  // ทดลองทุกจุดศูนย์กลาง และทุกขนาด คำนวนค่าจาก 4 ด้านรอบๆ
  int acc_ans = 0;
  for_(sz, 1, n_row + n_col + 1) {
  for_(i, OFFSET, OFFSET + n_row) {
  for_(j, OFFSET, OFFSET + n_col) {
    int top_left__star = tr[i][j-sz] - tr[i-sz-1][j+1];
    int top_right_star = tl[i-1][j+sz-1] - tl[i-sz][j];
    int bot_left__star = tl[i+sz-1][j-1] - tl[i][j-sz];
    int bot_right_star = tr[i+sz][j] - tr[i-1][j+sz+1];
    int total_star = top_left__star + bot_right_star + top_right_star + bot_left__star;
    if (total_star >= n_require_star) {
      acc_ans = (acc_ans + pascal[total_star][n_require_star]) % MOD;
    }
  }}}

  std::cout << acc_ans << std::endl;
}