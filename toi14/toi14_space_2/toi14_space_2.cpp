#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>

const int MAXN = 2010; 

const int VALID = 1 << 0; // valid: B
const int TL = 1 << 1;
const int TR = 1 << 2;
const int BL = 1 << 3;
const int BR = 1 << 4;

int* prv = new int[MAXN];
int* now = new int[MAXN];

char* s1 = new char[MAXN];
char* s2 = new char[MAXN];

int main() {
  int row, col; 
  scanf("%d %d", &col, &row);
  
  int colext = col + 4;
  int ans_triangle = 0;
  int ans_rect = 0;
  int ans_dimond = 0;
  std::fill_n(s1, colext, '0');
  std::fill_n(s2, colext, '0');

  // [a, b] แถว m
  // [c, d] แถว m+1
  // ข้อมูลรูปร่างจะอาศัยนับด้านเอียงเป็นหลัก
  int x = 0;
  char *a, *b, *c, *d; // char
  int *aa, *bb, *cc, *dd; // int
#define _ceq(c1,pointer) (c1 == '*' || c1 == *pointer)
#define cceq(c1,c2,c3,c4) (_ceq(c1, a) && _ceq(c2, b) && _ceq(c3, c) && _ceq(c4, d))
  auto creset = [&](int step = 0) {
    x = step;
    a = &s1[0 + step]; aa = &prv[0 + step];
    b = &s1[1 + step]; bb = &prv[1 + step];
    c = &s2[0 + step]; cc = &now[0 + step];
    d = &s2[1 + step]; dd = &now[1 + step];
  };
  
  auto cinc = [&](){ ++a; ++b; ++c; ++d; ++aa; ++bb; ++cc; ++dd; ++x; };
  auto cdec = [&](){ --a; --b; --c; --d; --aa; --bb; --cc; --dd; --x; };
  for (int i = 0; i <= row; ++i) {
    if (i == row) {
      std::fill_n(s2, col + 2, '0');
    } else {
      scanf("%s", s2 + 1);
      s2[col + 1] = '0';
    }
    std::fill_n(now, col + 2, 0);
    creset(0);
    while (x <= col) {
        if (cceq('0', '1', '1','1')) { *cc |= *dd = *bb | TL | *cc | *dd; } // เอียงบนซ้าย
        if (cceq('1', '0', '1','1')) { *cc |= *dd = *aa | TR | *cc | *dd; } // เอียงบนขวา
        if (cceq('1', '1', '1','0')) { *cc |= *aa | *bb | BR; } // เอียงล่างซ้าย
        if (cceq('1', '1', '0','1')) { *dd |= *aa | *bb | BL; } // เอียงล่างขวา
        if (cceq('*', '*', '1','*')) *cc |= VALID; // ช่องล่างซ้าย เป็นชองเลข 1
        if (cceq('*', '*', '*','1')) *dd |= VALID; // ช่องล่างขวา เป็นชองเลข 1
        cinc();
    }
    for (; x > 0; cdec()) {
      if (cceq('*', '*', '1','1')) {  // ทำย้อนกลับ Sync ข้อมูลซ้ายขวา ในรูปทรงเดียวกัน
        *cc = *dd = *cc | *dd;
      }
    }
    for (; x <= colext; cinc()) {
      // ....01111110.... หาว่าเป็นขอบล่างของรูปทรงหรือยัง
      // ....00000000....
      while (x <= colext && !cceq('0', '1', '*','0')) { cinc(); }  // หาฐานขอบล่างซ้าย
      if (cceq('0', '1', '*','0')) { // เจอฐานขอบล่างซ้าย
        cinc(); // ขยับไปกลางฐาน
        while (x <= colext && cceq('1', '1', '0', '0')) { // ขยับไปเรื่อยๆจนจบขอบฐาน
            cinc();
        }
        
        if (cceq('1', '0', '0', '*')) { // จบที่ฐานขอบล่างขวาไหม
          if (*aa == VALID) ans_rect += 1; // ไม่มีด้านลาดเอียง = สี่เหลี่ยม
          else if (*aa == (VALID | TL | TR | BL | BR)) ans_dimond += 1; // ทุกด้านเอียง = ข้าวหลามตัด
          else ans_triangle += 1; // มีเอียงอย่างน้อย 1 ด้าน = สามเหลี่ยม
        }
      }
    }

    std::fill_n(prv, col + 2, 0);
    std::fill_n(s1, col + 2, '0');
    std::swap(now, prv);
    std::swap(s2, s1);
  }
  printf("%d %d %d\n", ans_rect, ans_dimond, ans_triangle);
}

