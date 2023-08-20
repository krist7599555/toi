/*
toi14_technology
ใช้วิธีคิดแบบ topological sort แต่ว่าเริ่มจากจุดไหนก็ได้
ลบ node level 1 และ preriquisit ของมันทั้งหมด ถ้าทำได้ตอบ 1
ลบ node level 2 และ preriquisit ของมันทั้งหมด ถ้าทำได้ตอบ 2
ลบ node level 3 และ preriquisit ของมันทั้งหมด ถ้าทำได้ตอบ 3
...
*/
#include <iostream>
#include <vector>

const int MAXN = 100100;
const int MAXTECH = 10010;
const int FOUND_CYCLE = -1;

std::vector<int> preriquisit[MAXN];
std::vector<int> group_by_tech_level[MAXTECH];
enum { EMPTY, ON_PROGRESS, REMOVED } visits[MAXN] = { EMPTY };

// return จำนวน node ที่ REMOVED หรือ -1 (FOUND_CYCLE) ถ้าเจอ cycle (ทำต่อไม่ได้)
int dfs(int node) {
  if (visits[node] == REMOVED) return 0;
  if (visits[node] == ON_PROGRESS) return FOUND_CYCLE;
  visits[node] = ON_PROGRESS;
  int count = 0;
  for (int parent : preriquisit[node]) {
    int res = dfs(parent);
    if (res == FOUND_CYCLE) return FOUND_CYCLE;
    count += res; 
  }
  visits[node] = REMOVED;
  return count + 1;

}

int main() {
  int n_node, max_tech, time;
  std::cin >> n_node >> max_tech >> time;

  for (int i = 1; i <= n_node; ++i) {
    int tech_level, n_preriquisit;
    std::cin >> tech_level >> n_preriquisit;
    group_by_tech_level[tech_level].push_back(i);
    while (n_preriquisit--) {
      int j;
      std::cin >> j;
      preriquisit[i].push_back(j);
    }  
  }

  int ans = -1;
  std::fill_n(visits, MAXN, EMPTY);
  for (int level = 1; level <= max_tech; ++level) {
    if (group_by_tech_level[level].empty()) continue;
    for (int node : group_by_tech_level[level]) {
      int count = dfs(node);
      if (count != FOUND_CYCLE && count <= time) {
        time -= count;
      } else {
        // รีบจบถ้าเจอ cycle หรือ เวลาในการสร้างไม่พอ
        std::cout << ans << '\n';
        return 0;
      }
    }
    ans = level;
  }
  std::cout << ans << '\n';
  return 0;
}
