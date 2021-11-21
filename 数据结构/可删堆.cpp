#include <bits/stdc++.h>
using namespace std;
struct heap  //dynamic heap
{
    priority_queue<int> q1, q2;
    void push(int x) { q1.push(x); }
    void erase(int x) { q2.push(x); }
    int top() {
        while (q2.size() && q1.top() == q2.top())
            q1.pop(), q2.pop();
        return q1.top();
    }
    inline void pop() {
        while (q2.size() && q1.top() == q2.top())
            q1.pop(), q2.pop();
        q1.pop();
    }
    inline int top2() {
        int val = top();
        pop();
        int ret = top();
        push(val);
        return ret;
    }
    inline int size() {
        return q1.size() - q2.size();
    }
};
