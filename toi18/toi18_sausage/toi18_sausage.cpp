#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <numeric>
#define for_(i, k, n) for (int i = k; i < n; ++i)
#define all(x) x.begin(), x.end()
using namespace std;

const int MAXN = 5005;
int dp_saiua[MAXN][MAXN]; // dp_saiua[L, R) = ใส่อั่วมากสุดที่ทำได้ในช่วง [L..R) = magic(L, R-1) + max(dp_saiua[L+1..R), dp_saiua[L..R-1)) โดยไม่ตัดเลย
int dp_multisaiua[MAXN]; // dp_multisaiua[size] = ทดลองตัวใส่อั่วหลายๆท่อนในช่วง [0..size)

int main() {
  std::cin.sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::vector<int> inp(n);
  for (int& val : inp) {
    std::cin >> val;
  }

  for (int sz = 1; sz <= n; ++sz) {
  for (int l = 0, r = sz; r <= n; ++l, ++r) {
    //         {_____dp_saiua[l, r)____}
    // = max > [l]{__dp_saiua[l+1, r)__}
    //       > {__dp_saiua[l, r-1)__}[r]
    // + magic
    int magic = abs(inp[l] - inp[r-1]);
    dp_saiua[l][r] = magic + std::max(dp_saiua[l+1][r], dp_saiua[l][r-1]); 
  }}
  
  for (int sz = 1; sz <= n; ++sz) {
  for (int cut = 0; cut < sz; ++cut) {
    // {_______dp_multisaiua[sz]________}
    // {__dp_multisaiua[cut]__}[dp_saiua]
    //                        ^
    //                       cut
    dp_multisaiua[sz] = std::max(dp_multisaiua[sz], dp_multisaiua[cut] + dp_saiua[cut][sz]);
  }}
  
  std::cout << dp_multisaiua[n] + std::accumulate(inp.begin(), inp.end(), 0) << std::endl;
}
