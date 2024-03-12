// TOI6 GEM
// https://programming.in.th/tasks/toi6_gem
// ใช้ 2SAT(2-Satisfiability) และ Optimize ด้วย SCC(StronglyConnectedComponent)
// O(N+M)
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <stack>
#include <vector>

const int UNVISITED = -1;

struct TarjanStronglyConnectedComponent {
    // LEARN FROM HERE https://www.youtube.com/watch?v=wUgWX0nc4NY
    const std::vector<std::vector<int>>& edge;
    int mIdCounter;
    int mSccCount;
    std::vector<int> mIds; // mHight
    std::vector<int> mLow; // mLowIds
    std::stack<int> mStack;
    std::vector<bool> mInStack;

    TarjanStronglyConnectedComponent(const std::vector<std::vector<int>>& _edge):
        edge(_edge),
        mIdCounter(0), mSccCount(0),
        mIds(edge.size(), UNVISITED), mLow(edge.size(), UNVISITED),
        mStack(), mInStack(edge.size(), false)
    {
        for (int i = 0; i < edge.size(); ++i) {
            if (mIds[i] == UNVISITED) {
                dfs(i);
            }
        }
    } 
    bool isSameConnectedComponent(int u, int v) {
        return getGroupId(u) == getGroupId(v);
    }
private:
    int getGroupId(int u) {
        assert(mIds[u] != UNVISITED);
        return mLow[u];
    }
    void dfs(const int at) {
        mStack.push(at);
        mInStack[at] = true;
        mIds[at] = mLow[at] = ++mIdCounter;
        for (int to : edge[at]) {
            if (mIds[to] == UNVISITED) dfs(to);
            assert(mIds[to] != UNVISITED);
            if (mInStack[to]) mLow[at] = std::min(mLow[at], mLow[to]);
        }
        if (mIds[at] == mLow[at]) { // root of current connected component
            mSccCount += 1;
            while (!mStack.empty()) {
                int node = mStack.top();
                mStack.pop();
                mInStack[node] = false;
                mLow[node] = mIds[at];
                if (node == at) break;
            }
        }
    }
};

struct LogicGraph2SAT {
    // https://www.youtube.com/watch?v=Ku-jJ0G4tIc
    const int size;
    std::vector<std::vector<int>> edge;
    LogicGraph2SAT(int _size): size(_size), edge((_size + 1) * 2) {}
    int index(int p) {
        // logic order 0 1 -1 2 -2 3 -3 4 -4
        if (p == 0) throw std::invalid_argument("LogicGraph can not access at logic 0");
        return abs(p) * 2 + (p < 0 ? 1 : 0);
    }

    void addLogicAndThen(int p, int q) {
        this->edge[index(p)].push_back(index(q));
    }
    void addLogicOr(int p, int q) {
        // P or Q === ~P -> Q === ~Q -> P
        this->addLogicAndThen(-p, q);        
        this->addLogicAndThen(-q, p);        
    }
};

inline int input() { int i; scanf("%d", &i); return i;}

int main() {
    for (int q : {1, 2, 3, 4, 5}) {
        int n = input();
        int m = input();
        auto logic = LogicGraph2SAT(m);
        for (; n > 0; n--) {
            // ต้องเลือกอย่างน้อย 1 อัน
            // P or Q
            int p = input();
            int q = input();
            logic.addLogicOr(p, q);
        }
        for (; m > 0; m -= 2) {
            // ไม่สามารถเลือก 2 อันพร้อมกันได้
            // not(P and Q) === not(P) or not(Q)
            int p = input();
            int q = input();
            logic.addLogicOr(-p, -q);
        }

        // https://youtu.be/Ku-jJ0G4tIc?t=399
        // หาว่ามี edge เชื่อมจาก P ไป ~P ไหม ถ้ามีแปลว่าเกิดกรณีที่เป็นไปไม่ได้
        auto tarjan = TarjanStronglyConnectedComponent(logic.edge);
        for (int p = 1; p <= logic.size; ++p) {
            if (tarjan.isSameConnectedComponent(logic.index(p), logic.index(-p))) {
                printf("N");
                goto bye;
            }
        }
        printf("Y");
        bye:;

    }
    printf("\n");
}

/**
4
6
2 3 6 5 3 4 1 2
1 3 2 5 4 6
3
4
1 2 2 3 4 3
1 3 2 4
4
8
1 2 3 4 5 6 7 8
1 3 2 4 5 7 6 8
3
4
1 2 2 3 3 4
2 3 1 4
5
4
1 2 2 3 4 3 1 3 4 2
1 4 2 3
*/

/*
YYYYN
*/