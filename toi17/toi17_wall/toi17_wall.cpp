/**
Search on Table (BFS or DFS)
*/
#include <iostream>
#include <cassert>
#include <string>
#define for_(i, k, n) for (auto i = k; i != n; ++i)

const int MAXN = 1001;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

enum class Cell { EMPTY, HOME, WATER };

struct Table {
  int n_row, n_col;
  Cell dp[MAXN][MAXN];
  
  Table(int _r, int _c): n_row(_r), n_col(_c), dp() {
    std::fill_n(dp[0], MAXN * MAXN, Cell::EMPTY);
  }
  inline bool is_inbound(int i, int j) const {
    return 0 <= i && i < n_row && 0 <= j && j < n_col;
  }
  void dfs(int i, int j, const auto& is_valid, const auto& callback) {
    if (is_inbound(i, j) && is_valid(dp[i][j])) {
      callback(dp[i][j]);
      for (int d = 0; d != 4; ++d) {
        int i2 = i + dx[d];
        int j2 = j + dy[d];
        dfs(i2, j2, is_valid, callback);
  }}}
};

int main() {
  int n_row, n_col;
  std::cin >> n_row >> n_col;
  Table t = Table(n_row, n_col);
  for_(i, 0, n_row) {
    std::string row;
    std::cin >> row;
    assert(row.size() == n_col && row[0] == '.' && row[n_col-1] == '.'); // ขอบซ้ายขวา เป็น .
    for_(j, 0, n_col) {
      assert((i == 0 || i == n_row - 1) ? row[j] == '.' : true); // ขอบบนล่าง เป็น .
      if (row[j] == 'X') {
        t.dp[i][j] = Cell::HOME;
  }}}

  // fill every EMPTY cell with WATER
  assert(t.dp[0][0] == Cell::EMPTY);
  t.dfs(0, 0, 
    [](Cell c) { return c == Cell::EMPTY; },
    [](Cell& c) { c = Cell::WATER; }
  );
  
  // dfs เพื่อหากำแพงทุกกลุ่มบ้าน
  int maximum_wall = 0;
  for_(i, 0, n_row) {
  for_(j, 0, n_col) {
    if (t.dp[i][j] == Cell::HOME) {
      int count_local_wall = 0;
      t.dfs(i, j,
        // check รอบๆ HOME (check valid คือเช็คทุก cell รอบๆอยู่แล้ว)
        [&count_local_wall](Cell c) {
          count_local_wall += c == Cell::WATER ? 1 : 0; // ถ้ารอบ HOME เป็น WATER ให้กั้นกำแพง
          return c == Cell::HOME; // ให้ recursive ไป HOME ที่ติดกัน
        },
        [](Cell& c) { c = Cell::EMPTY; } // ลบ HOME ออกไปเลยถ้าเคยทำแล้ว
      );
      assert(t.dp[i][j] == Cell::EMPTY);
      maximum_wall = std::max(maximum_wall, count_local_wall);
  }}}

  std::cout << maximum_wall << std::endl;
}
