#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct heap  // dynamic heap
{
    priority_queue<T> q1, q2;
    void push(T x) { q1.push(x); }
    void erase(T x) { q2.push(x); }
    T top() {
        while (q2.size() && q1.top() == q2.top())
            q1.pop(), q2.pop();
        return q1.top();
    }
    inline void pop() {
        while (q2.size() && q1.top() == q2.top())
            q1.pop(), q2.pop();
        q1.pop();
    }
    inline T top2() {
        T val = top();
        pop();
        T ret = top();
        push(val);
        return ret;
    }
    inline int size() {
        return q1.size() - q2.size();
    }
};
