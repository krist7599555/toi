#include <iostream>

static bool is_nugget[101];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    // mark all possible nugget numbers up to 100
    for (int a = 0; a * 6 <= 100; a++) {
        for (int b = 0; b * 9 <= 100; b++) {
            for (int c = 0; c * 20 <= 100; c++) {
                int sum = a * 6 + b * 9 + c * 20;
                if (sum <= 100 && sum > 0) {
                    is_nugget[sum] = true;
                }
            }
        }
    }

    bool found = false;
    for (int i = 1; i <= n; i++) {
        if (is_nugget[i]) {
            std::cout << i << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "no\n";
    }

    return 0;
}