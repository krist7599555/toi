<!-- @codegen_problem begin -->
# TOI14 blockchain - บล็อกเชน (BLOCKCHAIN)

[🏠 รวมเฉลย TOI14](../)

[💎 problem.pdf](./toi14_blockchain.pdf)

[🎉 solution.cpp](./toi14_blockchain.cpp)

<img width="700" src="https://github.com/krist7599555/toi/assets/19445033/a706c369-2311-4a0b-ab8c-3b2011404482" />
<!-- @codegen_problem end -->

---

ถ้ารู้คุณสมบัติกราฟก็จะตอบได้ว่า

`เปรียบเทียบต้นไม่เหมือนกัน == เปรียบเทียบ edge list`

และถ้ารู้เทคนิคส่ง edge list เข้าไปใน `std::map` เป็น key เพื่อนับได้ก็จะไวขึ้น

โดยให้

```cpp
using Edge = std::tuple<int, int>;
using EdgeList = std::vector<Edge>;
```
