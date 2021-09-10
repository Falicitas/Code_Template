#include <bits/stdc++.h>
using namespace std;
//保证f[0] = 1,求g^2(x) = f(x),_g = g^-1
void PolySqrt(int deg, vector<int>& f, vector<int>& g) {
    if (deg == 1) {
        g[0] = 1;
        return;
    }
    PolySqrt((deg + 1) >> 1, f, g);
    int lim = 1;
    while (lim < (deg << 1))
        lim <<= 1;
    vector<int> h(lim), _g(lim);
    REP(i, 0, deg - 1)
    h[i] = f[i];
    PolyInv(deg, g, _g);
    ntt(g, lim, 1), ntt(h, lim, 1), ntt(_g, lim, 1);
    REP(i, 0, lim - 1)
    g[i] = 1LL * inv[2] * (1LL * g[i] + 1LL * _g[i] * h[i] % mod) % mod;
    ntt(g, lim, -1);
    REP(i, deg, lim - 1)
    g[i] = 0;
}

//不保证f[0] = 1，但保证f[0]是在模mod的二次剩余
namespace Twice_Remainder  //用于解决f[0] != 1的情况
{
int mod = 998244353;
ll I_2;  // 虚数单位的平方
struct complex {
    ll real, i;
    complex(ll real = 0, ll i = 0)
        : real(real), i(i) {}
};
bool operator==(complex x, complex y) {
    return x.real == y.real && x.i == y.i;
}
complex operator*(complex x, complex y) {
    return complex((x.real * y.real + I_2 * x.i % mod * y.i) % mod, (x.i * y.real + x.real * y.i) % mod);
}
complex qp(complex x, int k) {
    complex res = 1;
    while (k) {
        if (k & 1)
            res = res * x;
        x = x * x;
        k >>= 1;
    }
    return res;
}
bool check_if_residue(int x) {
    return qp(x, (mod - 1) >> 1) == 1;
}  //判断常数项是否有解
int solve(int b) {
    int x0, x1;
    ll a = rand() % mod;
    while (!a || check_if_residue((a * a + mod - b) % mod))
        a = rand() % mod;
    I_2 = (a * a + mod - b) % mod;
    x0 = int(qp(complex(a, 1), (mod + 1) >> 1).real), x1 = mod - x0;
    return min(x0, x1);
}
}  // namespace Twice_Remainder

void PolySqrt(int deg, vector<int>& f, vector<int>& g) {
    if (deg == 1) {
        g[0] = Twice_Remainder::solve(f[0]);
        return;
    }
    PolySqrt((deg + 1) >> 1, f, g);
    int lim = 1;
    while (lim < (deg << 1))
        lim <<= 1;
    vector<int> h(lim), _g(lim);
    REP(i, 0, deg - 1)
    h[i] = f[i];
    PolyInv(deg, g, _g);
    ntt(g, lim, 1), ntt(h, lim, 1), ntt(_g, lim, 1);
    REP(i, 0, lim - 1)
    g[i] = 1LL * inv[2] * (1LL * g[i] + 1LL * _g[i] * h[i] % mod) % mod;
    ntt(g, lim, -1);
    REP(i, deg, lim - 1)
    g[i] = 0;
}
