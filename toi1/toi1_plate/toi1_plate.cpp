#include <cstdio>
#include <queue>
#include <algorithm>
#include <cassert>

#define for_(i, s, t) for (int i = (s); i < (t); ++i)

int student_class[10001] = {};          // student_id -> class_id
std::queue<int> class_queue[11];   // คิวนักเรียนของแต่ละชั้น
std::queue<int> plate_queue;       // คิวลำดับชั้นเรียน

int main() {
    int nc, ns;
    std::scanf("%d %d", &nc, &ns);

    // อ่านข้อมูลนักเรียนทั้งหมด
    for_(i, 0, ns) {
        int c, s;
        std::scanf("%d %d", &c, &s);
        assert(student_class[s] == 0);
        student_class[s] = c; // แปลงเป็น base 0
    }

    char cmd;
    while (std::scanf(" %c", &cmd) == 1) {
    
        switch (cmd) {
            case 'E': {
                int id;
                std::scanf("%d", &id);
                int cls = student_class[id];

                // ถ้าชั้นนี้ยังไม่มีในแถว ให้เพิ่มเข้า plate_queue
                if (class_queue[cls].empty()) {
                    plate_queue.push(cls);
                }

                class_queue[cls].push(id);
                break;
            }

            case 'D': {
                if (plate_queue.empty()) {
                    std::puts("0");
                } else {
                    int cls = plate_queue.front();
                    int stu = class_queue[cls].front();
                    class_queue[cls].pop();

                    std::printf("%d\n", stu);

                    // ถ้าชั้นนี้ไม่มีนักเรียนแล้ว เอาออกจาก plate_queue
                    if (class_queue[cls].empty()) {
                        plate_queue.pop();
                    }
                }
                break;
            }

            case 'X':
                std::puts("0");
                break;
        }
    }

    return 0;
}