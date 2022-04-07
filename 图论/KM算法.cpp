#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
struct KM {  //求最小完美匹配的板子。求最大完美匹配，将边权矩阵取负即可。对于边数=O(n^2)，快过费用流
    const i64 inf = 0x3f3f3f3f3f3f3f3f;
    vector<vector<i64>> w;
    int n, m;
    KM(int n_, int m_, vector<vector<i64>> w_)
        : n(n_), m(max(m_, n_)), w(w_) {
    }  //w[i][j]指左点集i与右点集j的权值。左点集大小为n，右点集大小为m
    i64 km() {
        std::vector<i64> u(n + 1), v(m + 1), p(m + 1), way(m + 1);
        for (int i = 1; i <= n; i++) {
            p[0] = i;
            i64 j0 = 0;
            std::vector<i64> minv(m + 1, inf);
            std::vector<char> used(m + 1, false);
            do {
                used[j0] = true;
                i64 i0 = p[j0], delta = inf, j1;
                for (int j = 1; j <= m; ++j) {
                    if (!used[j]) {
                        i64 cur = w[i0][j] - u[i0] - v[j];
                        if (cur < minv[j]) {
                            minv[j] = cur, way[j] = j0;
                        }
                        if (minv[j] < delta) {
                            delta = minv[j], j1 = j;
                        }
                    }
                }
                for (int j = 0; j <= m; ++j) {
                    if (used[j]) {
                        u[p[j]] += delta, v[j] -= delta;
                    } else {
                        minv[j] -= delta;
                    }
                }
                j0 = j1;
            } while (p[j0] != 0);
            do {
                i64 j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }
        i64 res = 0;
        for (int i = 1; i <= m; i++) {
            res += w[p[i]][i];
        }
        return res;
    }
};