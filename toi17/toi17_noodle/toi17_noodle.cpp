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
using namespace std;
typedef long long lli;


int maximum_noodleshop(const std::vector<int>& noodles, 
                       lli minimum_sum_noodle_pershop,
                       int noodle_count_pershop) {
  int shop = 0;
  lli pq_sum = 0;
  std::priority_queue<lli, std::vector<lli>, std::greater<lli>> pq;
  
  for (int noodle : noodles) {
    if (pq.size() < noodle_count_pershop) {
      pq_sum += noodle;
      pq.push(noodle);
    } else if (noodle > pq.top()) {
      assert(pq.size() == noodle_count_pershop);
      pq_sum -= pq.top();
      pq.pop();
      pq_sum += noodle;
      pq.push(noodle);
    }

    if (pq.size() == noodle_count_pershop && pq_sum >= minimum_sum_noodle_pershop) {
      shop += 1;
      pq_sum = 0;
      pq = {};
    }
  }
  return shop;
}
int main() {
  int n_input, n_shop, noodle_count_pershop;
  std::cin >> n_input >> n_shop >> noodle_count_pershop;
  std::vector<int> input(n_input);
  for (int& val : input) {
    std::cin >> val;
  }

  lli l = 0;
  lli r = std::accumulate(input.begin(), input.end(), 0LL);
  while (l < r) {
    lli m = (l + r) / 2;
    if (maximum_noodleshop(input, m, noodle_count_pershop) >= n_shop) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  std::cout << l - 1 << std::endl;
}