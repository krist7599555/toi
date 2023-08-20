#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include <deque>

int main() {
  using pii = std::pair<int, int>;
  int n, k;
  std::cin >> n >> k;
  std::deque<pii> dq; // [value, index] เรียงค่าน้อยสุดอยู่บน
  
  for (int idx = 1; idx <= n; ++idx) {
    int val;
    std::cin >> val;
    
    while (!dq.empty() && dq.front().second < idx - k /* ถ้าคำตอบที่ดีที่สุดห่างเกิน k แปลว่าใช้ค่านี้ไม่ได้ */) {
      dq.pop_front();
    }

    int new_val = (dq.empty() ? 0 : dq.front().first) + val;

    while (!dq.empty() && dq.back().first >= new_val /* ถ้าคำตอบใหม่ ดีกว่าคำตอบก่อนหน้า ก็ลบคำตอบก่อนหน้า */) {
      dq.pop_back();
    }

    dq.emplace_back(new_val, idx);

    if (idx == n) {
      std::cout << new_val << '\n';
      return 0;
    }  
  }
}
