<!-- @codegen_problem begin -->

# TOI18 sausage - ไส้อั่วทิพย์ (Sai-ua)

[🏠 รวมเฉลย TOI18](../)

[💎 problem.pdf](./toi18_sausage.pdf)

[🎉 solution.cpp](./toi18_sausage.cpp)

<img width="700" src="https://github.com/krist7599555/toi/assets/19445033/38b4d87c-0304-4d26-90a0-9ddb8706e481" />
<!-- @codegen_problem end -->

Dynamic Programmin 2 ขั้น

- ขั้น 1 ช่วงดีสุดที่ไม่ตัด `O(n^2)`
- ขั้น 2 ลองตัดหลายๆช่วง `O(n)`

```cpp
int dp_saiua[MAXN][MAXN]; // dp_saiua[L, R)
//  = ใส่อั่วมากสุดที่ทำได้ในช่วง [L..R) = magic(L, R-1) + max(dp_saiua[L+1..R), dp_saiua[L..R-1)) โดยไม่ตัดเลย

int dp_multisaiua[MAXN]; // dp_multisaiua[size]
// = ใส่อั่วที่ดีสุดในช่วง [0..size) โดยแบ่งกี่ช่วงก้ได้แต่ต้องดีสุด
//   หาโดยทดลองตัวใส่อั่วหลายๆท่อนในช่วง [0..size)


for (int sz = 1; sz <= n; ++sz) {
for (int l = 0, r = sz; r <= n; ++l, ++r) {
  //         {_____dp_saiua[l, r)____}
  // = max > [l]{__dp_saiua[l+1, r)__}
  //       > {__dp_saiua[l, r-1)__}[r]
  // + magic
  int magic = abs(inp[l] - inp[r-1]);
  dp_saiua[l, r] = magic + std::max(dp_saiua[l+1, r], dp_saiua[l, r-1]);
}}

for (int sz = 1; sz <= n; ++sz) {
for (int cut = 0; cut < sz; ++cut) {
  // {_______dp_multisaiua[sz]________}
  // {__dp_multisaiua[cut]__}[dp_saiua]
  //                        ^
  //                       cut
  dp_multisaiua[sz] = std::max(
    dp_multisaiua[sz], // ตัดแบบเดิม
    dp_multisaiua[cut] + dp_saiua[cut][sz] // ลองตัดที่ cut
  );
}}
```
