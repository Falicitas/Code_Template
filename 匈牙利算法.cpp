#include <bits/stdc++.h>
using namespace std;
struct Hungary {  //点集范围[0,n-1]
    vector<vector<int>> e;
    vector<int> left, link, vis;
    int n;
    Hungary(vector<vector<int>> e_, vector<int> left_)
        : e(e_), left(left_) {
        n = e.size();
        link = vector<int>(n), vis = link;
    }
    int dfs(int u) {
        for (auto v : e[u]) {
            if (vis[v]) {
                continue;
            }  //当前匹配时已经访问过了，再访问会形成环，不是増广路
            vis[v] = 1;
            if (!link[v] || dfs(link[v])) {  //去让之前匹配v的点u'找其他的匹配
                link[v] = u;
                return 1;  //匹配上一条
            }
        }
        return 0;
    }

    vector<int> hungary() {
        int match = 0;
        for (auto u : left) {      //枚举其中一个点集
            vis = vector<int>(n);  //缺省当前另外点集均无访问过
            match += dfs(u);
        }
        return link;
    }
};

int main() {
    vector<vector<int>> e;
    vector<int> left;
    Hungary hg(e, left);
    vector<int> link = hg.hungary();
    return 0;
}