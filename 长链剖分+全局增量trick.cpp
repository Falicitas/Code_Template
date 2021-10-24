#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

using i64 = long long;
const int N = 1e6 + 5;
i64 tmp[N], *f[N], *id = tmp, ans = 1e18;
int m;

/*
这题中要统计经过m个点的路径<u,v>的点权最小值
O(1)继承儿子的信息时，若是给儿子的信息每个都加上u的点权a[u]复杂度会炸
这里用一个全局增量的tag[u]，表示u到所在重链最底端的增量总和，此时 令子树u到儿子长为d的路径上点权和的最小值 为f[u][d] + tag[u]（代码实现则有点小细节比如f[u][d]+tag[u]是路径经过d+1个点的最小值）
让f[u][0] -= a[u]；此时容易得到u所在重链上的v都满足长为d路径上<u,v>的点权和为f[u][d]+tag[u]
那么轻链的如何并到f[u]上，使f[u]的定义不改变？
容易知道f[v][d]+tag[v]+a[u]是长为d+1的<u,v'>的路径最小值，其中v'是子树v距离v为d的一个儿子。
那么只要令f[u][d + 1] = min(f[u][d + 1], f[v][d] + tag[v] + a[u] - tag[u]);
假设更新了f[u][d+1]，那么加上tag[u]即为u往轻链v走的路径权值和了
也就做到了O(1)继承，保证了长链剖分的复杂度
*/

struct DepSlipt {
    vector<vector<int>> e;
    vector<int> len, son;
    vector<i64> a, tag;

    DepSlipt(vector<vector<int>> e_, vector<i64> a_)
        : e(e_),a(a_) {
        int n = (int)e.size() - 1;
        len = vector<int>(n + 1), son = len;
        a = vector<i64>(n + 1);
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
        tag[u] = a[u];
        f[u][0] = 0;
        if (son[u]) {
            f[son[u]] = f[u] + 1, dp(son[u], u), tag[u] += tag[son[u]], f[u][0] -= tag[son[u]];
        }
        for (auto v : e[u]) {
            if (v == fa || v == son[u]) {
                continue;
            }
            f[v] = id;
            id += len[v];
            dp(v, u);
            for (int j = 0; j < len[v] && j < m; ++j) {
                if (m - j - 1 < len[u]) {
                    ans = min(ans, f[v][j] + tag[v] + f[u][m - j - 1] + tag[u]);
                }
            }
            for (int j = 0; j < len[v] && j < m; ++j)
                f[u][j + 1] = min(f[u][j + 1], f[v][j] + tag[v] + a[u] - tag[u]);
        }
        //注意，上面只是将轻链的方案与u代表的重链方案合并，并没有统计在u上以u作为一端的<u,v>路径上的方案对答案的贡献。所以搜索结尾要将其统计进去
        if (m < len[u]) {
            ans = min(ans, f[u][m] + tag[u]);
        }
    }
};

int main() {
    return 0;
}