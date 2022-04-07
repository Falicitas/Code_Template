#include <bits/stdc++.h>
using namespace std;
struct Gauss {
    const double eps = 1e-7;
    vector<vector<double>> a;
    int n;
    Gauss(int n_)
        : n(n_) {
        a = vector<vector<double>>(n + 2, vector<double>(n + 2));
    }
    vector<double>& operator[](int j) {
        return a[j];
    }
    int gauss() {
        int now = 1, to;
        double t;
        for (int i = 1; i <= n; i++) {
            for (to = now; to <= n; to++) {
                if (fabs(a[to][i]) > eps) {
                    break;
                }
            }
            if (to > n) {
                continue;
            }
            if (to != now) {
                swap(a[to], a[now]);
            }
            t = a[now][i];
            for (int j = 1; j <= n + 1; j++) {
                a[now][j] /= t;
            }
            for (int j = 1; j <= n; j++) {
                if (j != now) {
                    t = a[j][i];
                    for (int k = 1; k <= n + 1; k++) {
                        a[j][k] -= t * a[now][k];
                    }
                }
            }
            now++;
        }
        for (int i = now; i <= n; i++)
            if (fabs(a[i][n + 1]) > eps)
                return 0;             //无解
        return now == n + 1 ? 1 : 2;  // 1唯一解；2无穷多解
    }
};

int main() {
    Gauss gs(10);
    gs[1][2] = 3;
    return 0;
}