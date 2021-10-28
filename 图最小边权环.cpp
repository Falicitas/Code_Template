#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
struct MinRing  //n^3
{
    int n;
    vector<vector<i64>> G, dis;  // 原图的邻接矩阵
    MinRing(vector<vector<i64>> G_)
        : G(G_) {
        n = (int)G.size() - 1;
    }
    int floyd() {
        dis = G;
        i64 ans = inf;
        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i < k; ++i)
                for (int j = 1; j < i; ++j)
                    ans = min(ans, dis[i][j] + G[i][k] + G[k][j]);  // 更新答案
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    dis[i][j] = std::min(
                        dis[i][j], dis[i][k] + dis[k][j]);  // 正常的 floyd 更新最短路矩阵
        }
        return ans;
    }
};
