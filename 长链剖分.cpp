#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int tmp[N], *f[N], *id = tmp, ans[N];  //这里的int取决于f的定义。如果f[][]为double，则所有设为double

struct DepSlipt {
    vector<vector<int>> e;
    vector<int> len, son;
    DepSlipt(vector<vector<int>> e_)
        : e(e_) {
        int n = (int)e.size() - 1;
        len = vector<int>(n + 1), son = len;
        dfs(1, 0);
        f[1] = id;
        id += len[1];  //让出[0,id+len[1])的空间给f[1][0~len[1])使用，或者理解成给节点1代表的一条重链使用
        dp(1, 0);
    }
    void dfs(int u, int fa) {  //不用改
        for (auto v : e[u]) {
            if (v != fa) {
                dfs(v, u);
                if (len[v] > len[son[u]]) {
                    son[u] = v;
                }
            }
        }
        len[u] = len[son[u]] + 1;
    }
    void dp(int u, int fa) {
        f[u][0] = 1;
        if (son[u]) {
            f[son[u]] = f[u] + 1;  //将u的dep=1,2,...作为son[u][0,1,...]计算的空间
            dp(son[u], u);
            ans[u] = ans[son[u]] + 1;  //本题ans记录某个满足条件的深度，所以ans[u]为儿子继承过来的深度+1
        }
        for (auto v : e[u]) {  //v是u的轻儿子
            if (v == fa || v == son[u]) {
                continue;
            }
            f[v] = id;
            id += len[v];  //让出[id,id+len[v])的空间给f[v][0~len[v])使用，或者理解成给节点v代表的一条重链使用
            dp(v, u);
            for (int j = 1; j <= len[v]; ++j) {
                f[u][j] += f[v][j - 1];
                if ((j < ans[u] && f[u][j] >= f[u][ans[u]]) || (j > ans[u] && f[u][j] > f[u][ans[u]])) {  //这里统计答案
                    ans[u] = j;
                }
            }
        }
        //注意，上面只是将轻链的方案与u代表的重链方案合并，并没有统计在u上以u作为一端的<u,v>路径上的方案对答案的贡献。所以搜索结尾要将其统计进去
        if (f[u][ans[u]] == 1) {
            ans[u] = 0;
        }
    }
};
