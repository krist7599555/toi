<!-- @codegen_problem begin -->
# TOI12 weakpoint - กำจัดจุดอ่อน

[🏠 รวมเฉลย TOI12](../)

[💎 problem.pdf](./toi12_weakpoint.pdf)

[🎉 solution.cpp](./toi12_weakpoint.cpp)

<img width="700" src="https://github.com/krist7599555/toi/assets/19445033/80c80822-7583-4bcd-a705-dae3eacdee85" />
<!-- @codegen_problem end -->

## Solution

- Detech Cycle ให้ได้ โดยใช้วิธี DFS
- DFS อีกครั้งจากจุดรอบๆ Cycle เพื่อหาขนาดของ sub tree
- ทดลองตัดกราฟโดย
  - ถ้าจุดข้อมูลสำคัญอยู่ในวงกลม
    - ให้ลองตัดลูกๆข้างล่าง
    - ให้ลองตัดจุดอื่นๆรอบ Cycle
  - ถ้าจุดข้อมูลสำคัญอยู่เป็นกิ่ง
    - ให้ลองตัดลูกๆข้างล่าง
    - ให้ลองตัดจุดข้างบน

ในที่นี้ผมใช้เทคนิคแบบ Kahn’s algorithm for Topological Sorting คือการนับ degree ของเส้นเชื่อม โดยอนุมานได้เลยว่า จุดไหนมีเส้นเชื่อม == 1 จะต้องเป็น leaf แน่นอน แล้วก็วนทำไปเรื่อยๆในการกำจัด leaf พร้อมกับได้ขนาดของต้นไม้มาด้วยเลย ทำให้โคดสั้นลงไปอีก
