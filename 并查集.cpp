#include <bits/stdc++.h>
using namespace std;
struct Union {
    vector<int> fa, siz;
    Union(int n) {
        fa = vector<int>(n), siz = fa;
        for (int i = 0; i < n; i++) {
            fa[i] = i;
            siz[i] = 1;
        }
    }
    int find(int u) {
        return u == fa[u] ? u : fa[u] = find(fa[u]);
    }
    void Merge(int u, int v) {
        int tu = find(u), tv = find(v);
        if (tu != tv) {
            if (siz[tu] < siz[tv]) {
                swap(tu, tv);
            }
            siz[tu] += siz[tv];
            fa[tv] = tu;
        }
    }
};