// Binary Search + Greedy
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <functional>
using namespace std;

int input() { int val; std::cin >> val; return val; }

int main(){
	std::cin.sync_with_stdio(0);

  int n = input();
  int q = input();

  std::vector<int> a(n);
  for (int& item : a) item = input();
  std::partial_sum(a.begin(), a.end(), a.begin(), std::plus<int>());
  std::partial_sum(a.rbegin(), a.rend(), a.rbegin(), [](int a, int b){ return std::min(a, b); });

  while (q--) {
    int search = input();
    auto it = std::upper_bound(a.begin(), a.end(), search);
    std::cout << std::distance(a.begin(), it) << "\n";
  }
}