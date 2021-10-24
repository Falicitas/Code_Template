#include <bits/stdc++.h>
using namespace std;
struct QuickGCD {
    int M, T;  //M为gcd对象的值域上界
    vector<vector<int>> pre, fac;
    vector<int> prime, isp;
    int p;
    QuickGCD()
        : M(1e6 + 5), T(1e3 + 5) {
        pre = vector<vector<int>>(T + 5, vector<int>(T + 5));
        prime = vector<int>(M + 5);
        fac = vector<vector<int>>(M + 5, vector<int>(3));
        isp = vector<int>(M + 5);

        fac[1][0] = fac[1][1] = fac[1][2] = 1;
        for (int i = 2; i <= M; i++) {
            if (!isp[i])
                prime[++p] = i;
            for (int j = 1; j <= p && i * prime[j] <= M; j++) {
                int now = i * prime[j];
                isp[now] = true;
                fac[now][0] = fac[i][0] * prime[j];
                fac[now][1] = fac[i][1];
                fac[now][2] = fac[i][2];
                if (fac[now][0] > fac[now][1]) {
                    swap(fac[now][0], fac[now][1]);
                }
                if (fac[now][1] > fac[now][2]) {
                    swap(fac[now][1], fac[now][2]);
                }
                if (i % prime[j] == 0) {
                    break;
                }
            }
        }
        for (int i = 0; i <= T; i++) {
            pre[i][0] = pre[0][i] = i;
        }
        for (int i = 1; i <= T; i++) {
            for (int j = 1; j <= i; j++) {
                pre[i][j] = pre[j][i] = pre[j][i % j];
            }
        }
    }
    int gcd(int a, int b) {
        int ans = 1;
        for (int i = 0; i < 3; i++) {
            int div = (fac[a][i] > T ? (b % fac[a][i] == 0 ? fac[a][i] : 1) : pre[fac[a][i]][b % fac[a][i]]);  //fac[a][i]铁定为素数
            ans *= div;
            b /= div;
        }
        return ans;
    }
};  // namespace Q_GCD
