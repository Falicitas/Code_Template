#include <bits/stdc++.h>
using namespace std;

vector<int> prufer_code(vector<vector<int>> e, int n) {  //得到长为n-2的prufer序列
    vector<int> fa(n + 1);
    fa[n] = 0;
    function<void(int)> dfs = [&](int u) {  //保证根不会被当做被删点。间接保证被删的都是除根节点以外的点
        for (auto v : e[u]) {
            if (v == fa[u]) {
                continue;
            }
            fa[v] = u;
            dfs(v);
        }
    };
    dfs(n);
    int ptr = 0;
    vector<int> deg(n + 1);
    for (int i = 1; i <= n; i++) {
        deg[i] = e[i].size();
        if (deg[i] == 1 && ptr == 0) {
            ptr = i;
            //break;//要跑完循环，否则deg[]会错
        }
    }
    vector<int> code(n - 1);
    int leaf = ptr;
    for (int i = 1; i <= n - 2; i++) {
        int nxt = fa[leaf];
        code[i] = nxt;
        if (--deg[nxt] == 1 && nxt < ptr) {
            leaf = nxt;
        } else {
            ptr++;
            while (deg[ptr] != 1)
                ptr++;
            leaf = ptr;
        }
    }
    return code;
}

vector<pair<int, int>> prufer_decode(vector<int> const& code) {
    int n = code.size() + 2;
    vector<int> deg(n + 1, 1);
    deg[0] = 0;
    for (int u : code) {
        deg[u]++;
    }
    int ptr = 1;
    while (deg[ptr] != 1) {
        ptr++;
    }
    int leaf = ptr;
    vector<pair<int, int>> edges;
    for (int v : code) {
        edges.emplace_back(leaf, v);
        if (--deg[v] == 1 && v < ptr) {
            leaf = v;
        } else {
            ptr++;
            while (deg[ptr] != 1)
                ptr++;
            leaf = ptr;
        }
    }
    edges.emplace_back(leaf, n);
    return edges;
}
