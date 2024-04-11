// Closest Pair of Points (Divide and Conquer) 
// https://www.youtube.com/watch?v=6u_hWxbOc7E
// https://chimengchi.medium.com/closest-pair-easy-explanation-872e78e16b17
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <functional>
#include <tuple>
#include <cmath>
using namespace std;

struct Point { double x; double y; };
auto cmp_x = [](auto lhs, auto rhs) { return lhs.x < rhs.x; };
auto cmp_y = [](auto lhs, auto rhs) { return lhs.y < rhs.y; };

template<typename T = int>
T input() { T val; std::cin >> val; return val; }

double dis(Point lhs, Point rhs) {
    auto [x1, y1] = lhs;
    auto [x2, y2] = rhs;
    return std::hypotf(x1 - x2, y1 - y2);
}

const int MAXIMUM_COMPAREPOINT_IN_CLOSETPAIR_STRIP = 6;
template<typename It>
double closest_pair(It s, It t) { // [s, t) = iterator
    int len = std::distance(s, t);
    if (len <= 1) return 1e10;
    if (len == 2) return dis(*s, *std::next(s));
    if (len == 3) return std::min({
        dis(*s, *std::next(s)),
        dis(*s, *std::next(s, 2)),
        dis(*std::next(s), *std::next(s, 2)),
    });

    auto mid = std::next(s, len / 2);
    double closet_ans = std::min(
      closest_pair(s, mid),
      closest_pair(std::next(mid), t)
    );

    std::vector<Point> strip;
    std::copy_if(s, t, std::back_inserter(strip), [&](Point p) {
        return std::abs(p.x - mid->x) <= closet_ans;
    });
    std::sort(strip.begin(), strip.end(), cmp_y);
    for (auto it = strip.begin(); it != strip.end(); ++it) {
        int lim = MAXIMUM_COMPAREPOINT_IN_CLOSETPAIR_STRIP;
        for (auto nx = std::next(it); nx != strip.end() && lim > 0; ++nx, --lim) {
            closet_ans = std::min(closet_ans, dis(*it, *nx));
        }
    }
    return closet_ans;
}

int main(){
  std::cin.sync_with_stdio(false);
  int question = input();
  while (question--){
    int n = input();
    int r = input();
    int d = input();
    std::vector<Point> vec(n);
    for (auto& p : vec) {
      p.x = input();
      p.y = input();
    }
    std::sort(vec.begin(), vec.end(), cmp_x);
    double closet_distance = closest_pair(vec.begin(), vec.end());
    bool is_valid = closet_distance >= (d + 2 * r);
    std::cout << (is_valid ? "Y" : "N") << '\n';
  }
}