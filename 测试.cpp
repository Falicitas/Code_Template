#include <bits/stdc++.h>
using namespace std;

int main() {
    auto cmp = [&](int x, int y) {
        return x > y;
    };
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    for (int i = 0; i < 10; i++) {
        pq.push(i);
    }
    while (pq.size()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    return 0;
}