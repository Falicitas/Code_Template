#include <bits/stdc++.h>
using namespace std;
//st_n = \sum_{i=1}^{k} st_{n-i}a_i
namespace Recurrence  //初始读入a[1~k],st[0~k-1]
{
vector<int> g(maxn << 1), gT(maxn << 1), _gT(maxn << 1);
void PolyModulo(int n, int m, vector<int>& f, vector<int>& R)  //只关心取模后的多项式//2k+1,k+1
{
    int lim = 1, deg = 2 * n - m + 10;
    while (lim < (deg))
        lim <<= 1;
    vector<int> fT(lim), Q(lim);
    REP(i, 0, n - 1)
    fT[i] = f[n - 1 - i];
    ntt(fT, lim, 1);
    REP(i, 0, lim - 1)
    fT[i] = 1LL * fT[i] * _gT[i] % mod;
    ntt(fT, lim, -1);
    REP(i, 0, n - m)
    Q[i] = fT[i];
    reverse(Q.begin(), Q.begin() + n - m + 1);
    lim = 1, deg = n + 10;
    while (lim < (deg))
        lim <<= 1;
    f.resize(lim);  //g1.resize(lim);
    Q.resize(lim), R.resize(lim);
    ntt(f, lim, 1), ntt(Q, lim, 1);  //ntt(g,lim,1)
    REP(i, 0, lim - 1)
    R[i] = (1LL * f[i] + mod - 1LL * g[i] * Q[i] % mod) % mod;
    ntt(R, lim, -1);
}
void get_g(int n, int m) {
    int lim = 1, deg = 2 * n - m + 10;
    while (lim < (deg))
        lim <<= 1;
    REP(i, 0, m - 1)
    gT[i] = g[m - 1 - i];
    REP(i, n - m + 1, lim - 1)
    gT[i] = 0;
    PolyInv(n - m + 1, gT, _gT);
    ntt(_gT, lim, 1);
    lim = 1, deg = n + 10;
    while (lim < (deg))
        lim <<= 1;
    ntt(g, lim, 1);
}
vector<int> f(maxn << 1);
void mul(int k) {
    int lim = 1;
    while (lim < (2 * k + 1))
        lim <<= 1;
    ntt(f, lim, 1);
    REP(i, 0, lim - 1)
    f[i] = 1LL * f[i] * f[i] % mod;
    ntt(f, lim, -1);
    vector<int> R;
    PolyModulo(2 * k + 1, k + 1, f, R);
    REP(i, 0, k - 1)
    f[i] = R[i];
    REP(i, k, lim - 1)
    f[i] = 0;
}
void add(int k) {
    _REP(i, k, 1)
    f[i] = f[i - 1];
    f[0] = 0;
}

int a[maxn], st[maxn];  //递推系数，初始值，长度均为k

int work(int n, int k) {
    if (n == 0)
        return st[0];  //0值要特判
    REP(i, 0, (maxn << 1) - 1)
    f[i] = g[i] = gT[i] = _gT[i] = 0;
    REP(i, 1, k)
    g[k - i] = a[i],
          g[k - i] = (g[k - i] % mod + mod) % mod;
    g[k] = mod - 1;
    get_g(2 * k + 1, k + 1);
    f[1] = 1;
    int cur = 1, lg = log2(n), ok = 0;
    _REP(i, lg - 1, 0) {
        if (k <= (cur << 1))
            ok = 1;
        if (!ok)
            f[cur << 1] = f[cur], f[cur] = 0, cur <<= 1;
        else
            mul(k);
        if (n & (1 << i)) {
            if (!ok)
                f[cur + 1] = f[cur], f[cur] = 0, cur += 1;
            else
                add(k);
        }
    }
    vector<int> R;
    PolyModulo(2 * k + 1, k + 1, f, R);
    REP(i, 0, k - 1)
    f[i] = R[i];
    int ans = 0;
    REP(i, 0, k - 1)
    (ans += 1LL * f[i] * st[i] % mod) %= mod;
    return (ans + mod) % mod;
}
}  // namespace Recurrence
