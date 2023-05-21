#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#define for_(i, k, n) for (int i = k; i < n; ++i)
#define all(x) x.begin(), x.end()
using namespace std;
using Vec = std::vector<int>;


Vec longest_increasing_subsequence(const Vec& inp) {
  Vec res;
  Vec dp;
  for (int val : inp) {
    auto it = std::lower_bound(all(dp), val);
    res.push_back(it - dp.begin());    
    if (it != dp.end()) *it = val;
    else dp.push_back(val);
  }
  assert(inp.size() == res.size());
  return res;
}

int main() {
  int n_input, n_question;
  std::cin >> n_input >> n_question;
  Vec inp(n_input);
  for (int& val : inp) {
    std::cin >> val;
  }

  Vec lis_forward = longest_increasing_subsequence(inp);
  std::reverse(all(inp));
  Vec lis_backward = longest_increasing_subsequence(inp);

  while (n_question--) {
    int i;
    std::cin >> i;
    std::cout << std::min(lis_forward[i], lis_backward[n_input-i-1]) << std::endl;
  }
}