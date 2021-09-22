#include <bits/stdc++.h>
using namespace std;
struct mat {
    vector<vector<int>> c;
    int n, m;
    mat(int a, int b)
        : n(a), m(b) {
        c = vector<vector<int>>(n, vector<int>(m));
    }
    void clear() {
        c = vector<vector<int>>(n, vector<int>(m));
    }
    mat operator*(const mat& temp) {
        mat ans(n, temp.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < temp.m; j++) {
                for (int k = 0; k < m; k++) {
                    ans.c[i][j] += c[i][k] * temp.c[k][j] % MOD;
                    while (ans.c[i][j] >= MOD) {
                        ans.c[i][j] -= MOD;
                    }
                }
            }
        }
        return ans;
    }
    friend mat operator^(mat M, ll n)  //Ҫ�����ţ����ⱻ���ȼ���
    {
        mat ans(M.n, M.n);
        for (int i = 0; i < M.n; i++)
            ans.c[i][i] = 1;
        while (n > 0) {
            if (n & 1)
                ans = ans * M;
            M = M * M;
            n >>= 1;
        }
        return ans;
    }
};
