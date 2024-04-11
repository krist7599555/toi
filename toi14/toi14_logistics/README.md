<!-- @codegen_problem begin -->
# TOI14 logistics - โลจิสติกส์ (LOGISTICS)

[🏠 รวมเฉลย TOI14](../)

[💎 problem.pdf](./toi14_logistics.pdf)

[🎉 toi14_logistic.cpp](./toi14_logistic.cpp)

<img width="700" src="https://github.com/krist7599555/toi/assets/19445033/1653294b-0136-47ac-a06d-dbf2b8b48a66" />
<!-- @codegen_problem end -->

Shortest Path หลายมิติ ใช้ Dijkstra's algorithm

```cpp
dp[เมือง][น้ำมัน][ตั๋วพิเศษ] = ค่าใช้จ่ายถูกสุด (price)
```

โดยมีเงื่อนไขการเปลี่ยน State ตามนี้

1. เดินทางโดยใช้น้ำมันในถัง `dp[new_node][fuel - use_fuel][ticket] = price`
1. เติมน้ำมัน 1 หน่วยโดยจ่ายเงิน `dp[node][fuel + 1][ticket] = price + cost[node]`
1. เติมน้ำมันจนเต็ม โดยจ่ายตั๋ว `dp[node][fuel_capacity][0] = dp[node][*][1]`
