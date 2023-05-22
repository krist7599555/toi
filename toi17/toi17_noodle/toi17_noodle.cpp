/**
BinarySearch + K-th Largest Element using Priority Queue
https://www.geeksforgeeks.org/k-th-smallest-element-in-an-unsorted-array-using-priority-queue/
*/
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long lli;

// ให้ว่า sum (max k-th ตัวในกลุ่ม) >= minimum_sum_noodle_pershop จะแบ่งได้กี่กลุ่ม
int maximum_noodleshop(const std::vector<int>& noodles, 
                       const lli minimum_sum_noodle_pershop,
                       const int noodle_count_pershop) {
  int count_shop = 0;
  lli pq_sum = 0; // ผลรวมของทุกตัวใน pq
  std::priority_queue<lli, std::vector<lli>, std::greater<lli>> pq;
  
  for (int val : noodles) {
    if (pq.size() < noodle_count_pershop) { // < k ตัว ให้ใส่เพิ่ม
      pq_sum += val;
      pq.push(val);
    } else if (val > pq.top()) { // = k ตัว ถ้าค่าดีกว่าเดิม ให้สลับกับตัวน้อยสุด
      assert(pq.size() == noodle_count_pershop);
      pq_sum -= pq.top();
      pq.pop();
      pq_sum += val;
      pq.push(val);
    }

    // เช็คว่า sum (max k-th ตัวในกลุ่ม) >= minimum_sum_noodle_pershop หรือยัง จะได้แบ่ง shop
    if (pq.size() == noodle_count_pershop && pq_sum >= minimum_sum_noodle_pershop) {
      count_shop += 1;
      pq_sum = 0;
      pq = {}; // pq.clear()
    }
  }
  return count_shop;
} // end maximum_noodleshop

int main() {
  // input
  int n_input, n_shop, noodle_count_pershop;
  std::cin >> n_input >> n_shop >> noodle_count_pershop;
  std::vector<int> input(n_input);
  for (int& val : input) {
    std::cin >> val;
  }

  // binary search `minimum_sum_noodle_pershop` 
  lli l = 0;
  lli r = std::accumulate(all(input), 0LL) / n_shop;
  while (l < r) {
    lli m = (l + r) / 2; // minimum_sum_noodle_pershop 
    if (maximum_noodleshop(input, m, noodle_count_pershop) >= n_shop) {
      l = m + 1;
    } else {
      r = m;
  }}

  std::cout << l - 1 << std::endl;
}