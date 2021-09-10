#include <bits/stdc++.h>
using namespace std;

struct suspended_line {
    vector<vector<int>> a, l, r, up;  //l_{i,j}表示往左延多远，up表示往上延多远。run时l_{i,j}表示i,j到悬线顶的悬线部分左边可以延多远
    int n, m;
    suspended_line(int n, int m, vector<vector<int>> a)  //a[i][j] = 0表示无障碍
        : n(n), m(m), a(a) {
        l = vector<vector<int>>(n, vector<int>(m));
        r = l, up = l;
        /*以下初始化l,r。对于l,r的初始化根据题目而定。以下为求极大子矩阵时的初始化*/
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!a[i][j]) {
                    l[i][j] = r[i][j] = j;
                }
            }
        }
    }

    void run() {  //必然访问了所有极大子矩阵
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                if (!a[i][j] && !a[i][j - 1]) {
                    l[i][j] = l[i][j - 1];
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = m - 2; j >= 0; --j) {
                if (!a[i][j] && !a[i][j + 1]) {
                    r[i][j] = r[i][j + 1];
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!a[i][j]) {
                    up[i][j] = 1;
                    if (i && !a[i - 1][j]) {
                        up[i][j] += up[i - 1][j];
                    }
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i >= 1 && !a[i][j] && !a[i - 1][j]) {
                    l[i][j] = max(l[i][j], l[i - 1][j]);
                    r[i][j] = min(r[i][j], r[i - 1][j]);
                }
                ans = max(ans, 1ll * up[i][j] * (r[i][j] - l[i][j] + 1));  //极大子矩阵的最大面积
            }
        }
    }
};
int main() {
    return 0;
}