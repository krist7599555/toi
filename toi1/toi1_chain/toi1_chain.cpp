#include <iostream>
#include <string>

static std::string words[30005];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int word_len;
    int word_count;

    std::cin >> word_len;
    std::cin >> word_count;

    for (int i = 0; i < word_count; i++) {
        std::cin >> words[i];
    }

    for (int i = 0; i + 1 < word_count; i++) {
        int diff_count = 0;

        for (int j = 0; j < word_len; j++) {
            if (words[i][j] != words[i + 1][j]) {
                diff_count++;
                if (diff_count > 2) {
                    std::cout << words[i] << "\n";
                    return 0;
                }
            }
        }
    }

    // ถ้าไม่ขาดเลย
    std::cout << words[word_count - 1] << "\n";
    return 0;
}