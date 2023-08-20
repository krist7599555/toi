#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include <vector>

int main() {
  using pii = std::pair<int, int>;
  int n, k;
  std::cin >> n >> k;
  std::priority_queue<
    pii,
    std::vector<pii>,
    std::greater<pii>
  > pq; // [value, index] เรียงค่าน้อยสุดอยู่บน
  
  for (int idx = 1; idx <= n; ++idx) {
    int val;
    std::cin >> val;
    
    while (!pq.empty() && pq.top().second < idx - k /* ถ้าคำตอบที่ดีที่สุดห่างเกิน k แปลว่าใช้ค่านี้ไม่ได้ */) {
      pq.pop();
    }

    int new_val = (pq.empty() ? 0 : pq.top().first) + val;
    pq.emplace(new_val, idx);

    if (idx == n) {
      std::cout << new_val << '\n';
      return 0;
    }  
  }
}
