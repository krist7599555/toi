<!-- @codegen_problem begin -->

# TOI18 mountain - แอ่วม่อน (Mountain)

[🏠 รวมเฉลย TOI18](../)

[💎 problem.pdf](./toi18_mountain.pdf)

[🎉 solution.cpp](./toi18_mountain.cpp)

<img width="700" src="https://github.com/krist7599555/toi/assets/19445033/2caed7c8-5601-4969-9dea-a54da40ceb11" />
<!-- @codegen_problem end -->

Dynamic Programming + Binary Search

ใช้นิยามต่อกราฟแบบทั้วไปก่อน

```cpp
walk(from=a, to=c) = bestof b { walk(a, b) --> walk(b, c) }
```

ในที่นี้ค่าของเราคือจำนวนอาหารที่ต้องใช้ operation `-->` เลยเป็นค่า `max`

```cpp
dp(node, food) = พลังงานน้อยสุดที่เดินจาก 0 --> node โดยกินอาหาร food ครั้ง
dp(0, 0) = 0     // จุดเริ่มต้นไม่ใช้พลังงาน
dp(_, 0) = INF   // ถ้าไม่มีอาหาร จะไปไหนไม่ได้
dp(n, f) = min { n2 in nodes | max(dp(n2, food - 1), distance(n2, n)) }
         = เดินจาก 0 --> n2 --> n   โดย
                  0 --> n2         ใช้ค่าจาก dp ที่เคยคำนวนมาก่อนหน้า
                        n2 --> n   คำนวนระยะทางใหม่
                  รวมค่าโดยสมการ max คือ
                     ถ้า 0 --> n2 ใช้พลังงานเยอะ ก็เอา 0 --> n2 เป็นพลังงานสูงสุดที่ต้องใช้
                     ถ้า n2 --> n ใช้พลังงานเยอะ ก็เอา n2 --> n เป็นพลังงานสูงสุดที่ต้องใช้
```

หลังจากนั้นก็ binary search บนค่า `dp(n, 0..)` ว่าไปถึงจุด `n` ต้องใช้อาหารน้อยสุดเท่าไหร่
