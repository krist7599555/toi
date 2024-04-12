<!-- @codegen_problem begin -->

# TOI12 pipe - ท่อน้ำ

[🏠 รวมเฉลย TOI12](../)

[💎 problem.pdf](./toi12_pipe.pdf)

[🎉 solution.cpp](./toi12_pipe.cpp)

<img width="700" src="https://github.com/krist7599555/toi/assets/19445033/80c80822-7583-4bcd-a705-dae3eacdee85" />
<!-- @codegen_problem end -->

# Solution

Minimum Spanning Tree on **Dense Graph**

ตามโจทย์คือ เชื่อมได้หมดทุก node แปลว่า `Edge = Vertex²`

ถ้าใช้ `priority_queue` ยัด n ครั้งก็ `O(n log n)` กล้ายเป็นใช้เวลา `O(n * n log n)`

แต่ถ้าใช้ dynamic programming จำค่าใน array เลย แล้วหาค่า min จะใช้แค่ `O(n)` รวมใช่เวลา `O(n * n)` จึงเร็วกว่าแล้วผ่าน
