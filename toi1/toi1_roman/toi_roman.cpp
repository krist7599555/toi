#include <cstdio>
#include <algorithm>
#include <string>

#define for_(i, s, t) for (int i = (s); i < (t); ++i)

// ตารางเลขโรมันของแต่ละหลัก
const char* ones[] = { "", "i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix" };
const char* tens[] = { "", "x", "xx", "xxx", "xl", "l", "lx", "lxx", "lxxx", "xc" };
const char* hundreds[] = { "", "c", "cc", "ccc" };

int main() {
    int d;
    std::scanf("%d", &d);

    // ตัวนับจำนวนสัญลักษณ์ i v x l c ตามลำดับ
    int ans[5] = {0};

    // วนทุกหน้า ตั้งแต่ 1 ถึง d
    for_(page, 1, d + 1) {
        int h = page / 100 % 10;
        int t = page / 10  % 10;
        int o = page / 1   % 10;

        // นับตัวอักษร
        for (auto s : { ones[o], tens[t], hundreds[h] }) {
          for (const char* c = s; *c != '\0'; ++c) {
                   if (*c == 'i') ans[0]++;
              else if (*c == 'v') ans[1]++;
              else if (*c == 'x') ans[2]++;
              else if (*c == 'l') ans[3]++;
              else if (*c == 'c') ans[4]++;
          }
        }
    }

    // แสดงผล
    std::printf("%d %d %d %d %d\n", ans[0], ans[1], ans[2], ans[3], ans[4]);
}