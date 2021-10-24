#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
struct Hash {
    //类似奇素数的空间，开最大空间x2
    vector<int> h, v;
    int M;
    Hash() {
        M = 2e6 + 7;
        h = vector<int>(M), v = h;
    }
    int find(int x)  //找地址。若地址没存数字，或关键字为x，返回地址t
    {
        int t = x % M;
        while (h[t] != -1 && h[t] != x)
            if (++t == M)
                t = 0;
        return t;
    }

    void insert(int state, i64 w) {
        int t = find(state);
        if (h[t] == -1)  //空地址
            h[t] = state, v[t] = w;
        else
            v[t] += w;  //已有地址，这里对于已有地址做加值操作
    }
};
