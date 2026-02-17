#include <cstdio>
#include <algorithm>

#define for_(i, s, t) for (int i = (s); i < (t); ++i)

char fabric[50000][71] = {'\0'}; // +1 เผื่อ '\0'

int main() {
    int n, mxn = 0;
    std::scanf("%d", &n);

    // เตรียมผ้าทุกแถวเป็น 'o'
    for_(i, 0, n) {
        std::fill_n(fabric[i], 70, 'o');
    }

    // อ่านข้อมูลลายผ้า
    for_(i, 0, n) {
        int row, col, len;
        std::scanf("%d %d %d", &row, &col, &len);
        mxn = std::max(mxn, row);

        // แปลงเป็น base 0
        row -= 1;
        col -= 1;

        // วาดลายผ้า โดยไม่ให้เกิน 70 คอลัมน์
        std::fill(
            fabric[row] + std::min(col, 70), // 20% of testcase
            fabric[row] + std::min(col + len, 70),
            'x'
        );
    }

    // แสดงผล
    for_(i, 0, mxn) {
        std::puts(fabric[i]);
    }

}