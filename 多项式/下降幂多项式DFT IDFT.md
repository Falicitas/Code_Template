# 下降幂多项式DFT IDFT

现有多项式 $F(x)=\sum_{i=0}^{n-1} a_{i} x^{\underline{i}}$，求该多项式的DFT / IDFT。

首先考虑多项式 $x^{\underline{n}}$ 的点值的 EGF：

$ = \sum\limits_{i=0}^{\infty}\frac{i^{\underline{n}}}{i!}x^i = \sum\limits_{i=0}^{\infty}\frac{x^i}{(i-n)!} = x^n\sum\limits_{i=0}^{\infty}\frac{x^i}{i!} = x^ne^x$

设 $G(x)$​ 为 $F(x)$ ​的一系列点值的多项式。构造 $F(x)$​ 的点值的 EGF，有

$\sum\limits_{i=0}^{\infty}\frac{F(i)}{i!}x^i = \sum\limits_{i=0}^{\infty}\frac{1}{i!}x^i\sum\limits_{j=0}^{n-1}f_ji^{\underline{j}}$。调换遍历顺序，有

$ = \sum\limits_{j=0}^{n-1}f_j\sum\limits_{i=0}^{\infty}\frac{1}{(i-j)!}x^i = \sum\limits_{j=0}^{n-1}f_jx^j\sum\limits_{i=0}^{\infty}\frac{1}{i!}x^i = e^x\sum\limits_{j=0}^{n-1}f_jx^j$

将 $F(x)$​ ​看做普通多项式，$G(x)$​​ 为点值的 EGF，则有 $e^xF(x) = G(x)$​​，点值运算完后（记得点值 EGF 转 OGF），直接 $G(x)e^{-x} = F(x)$​​​。

## 下降幂的一些性质

### 下降幂二项式

下降幂二项式 $(a+b)^{\underline{n}} = \sum\limits_{i=0}^n \dbinom{n}{i}a^{\underline{i}}b^{\underline{n-i}}$​

被迫学会证明。

二项式展开下降幂：

$\sum_{i=0}^{n}\left(\begin{array}{c}n \\ i\end{array}\right)\left(\begin{array}{c}a \\ i\end{array}\right)\left(\begin{array}{c}b \\ n-i\end{array}\right) i !(n-i) !$​，合并 $\dbinom{n}{i}i!(n-i)!$​，有

$=n ! \sum_{i=0}^{n}\left(\begin{array}{c}a \\ i\end{array}\right)\left(\begin{array}{c}b \\ n-i\end{array}\right)$，后面两个写成生成函数，闭形式为$(1+x)^a,(1+x)^b$，所以有下式（类比「欧拉数」里的下界为定值）

$=n !\left(\begin{array}{c}a+b \\ n\end{array}\right)=(a+b)^{\underline{n}}$

### 计算平移点值

对于多项式 $f(x) = \sum\limits_{i=0}^{n}a_ix^{\underline{i}}$​​，现要计算平移 $m$ ​​位的点值

$f(m),f(m+1),\dots,f(m+n)$​​​

先列出等价多项式

$f(x+c) = \sum\limits_{i=0}^{n}a_i(x+c)^{\underline{i}}$，二项式展开，

$ = \sum\limits_{i=0}^{n}a_i\sum\limits_{j=0}^{i}\dbinom{i}{j}x^{\underline{j}}c^{\underline{i-j}}$

$ = \sum\limits_{i=0}^{n}i!a_i\sum\limits_{j=0}^{i}\frac{x^{\underline{j}}}{j!}\frac{c^{\underline{i-j}}}{(i-j)!}$。变换遍历顺序，

$ = \sum\limits_{j=0}^n\frac{x^{\underline{j}}}{j!}\sum\limits_{i=j}^{n}i!a_i\frac{c^{\underline{i-j}}}{(i-j)!}$。后面的式子是卷积的形式，令$g_i = (n-i)!a_{n-i},h_i = \frac{c^{\underline{i}}}{i!}$，有

$ = \sum\limits_{j=0}^n \frac{x^{\underline{j}}}{j!}((g*h)(n-j))$，再做多一次卷积变成**点值**即可。

这里要注意，上界为 $n$​​，上界改成 $n-1$​​​，对应函数要做修改。

```cpp
//code sourced from kinesis
#include <bits/stdc++.h>
using namespace std;

#define _REP(i, a, b) for (int i = (a); i >= (int)(b); --i)
#define REP(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define UREP(i, u) for (int i = p[(u)]; i + 1; i = edge[i].next)
//iterator: for(int u:x),x is container
#define x(p) (p).first
#define y(p) (p).second
#define pii pair<int, int>
#define mp(x, y) make_pair((x), (y))
#define sign(x) (fabs(x) < eps ? 0 : ((x) > 0 ? 1 : -1))
#define ll long long
#define L7 __int128  //1<<7 bit
#define ull unsigned long long
const int inf = 0x3f3f3f3f;
const ll inff = 0x3f3f3f3f3f3f3f3f;
const int mod = 998244353;
const double eps = 1e-9;
#define ri1(x) scanf("%d", &(x))
#define ri2(x, y) scanf("%d%d", &(x), &(y))
#define ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
//#define Debug
#ifdef Debug
#endif  // Debug
mt19937 rnd(228);

const int maxn = 262144;

namespace NTT  //优化过的ntt，使用时记得初始化
{
const int p = 998244353, g = 3;
int w[maxn << 2], inv[maxn << 2], r[maxn << 2], last;
int mod(int x) {
    return x >= p ? x - p : x;
}
ll qp(ll base, ll n) {
    base %= p;
    ll res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= p;
        (base *= base) %= p;
        n >>= 1;
    }
    return res;
}

void init() {
    int lim = maxn << 1;  //最长数组的两倍
    inv[1] = 1;
    for (int i = 2; i <= lim; i++)
        inv[i] = mod(p - 1ll * (p / i) * inv[p % i] % p);
    for (int i = 1; i < lim; i <<= 1) {
        int wn = qp(g, (p - 1) / (i << 1));
        for (int j = 0, ww = 1; j < i; j++, ww = 1ll * ww * wn % p)
            w[i + j] = ww;
    }
}

void ntt(vector<int>& f, int n, int op) {
    if (last != n) {
        for (int i = 1; i < n; i++)
            r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
        last = n;
    }
    for (int i = 1; i < n; i++)
        if (i < r[i])
            swap(f[i], f[r[i]]);
    for (int i = 1; i < n; i <<= 1)
        for (int j = 0; j < n; j += i << 1)
            for (int k = 0; k < i; k++) {
                int x = f[j + k], y = 1ll * f[i + j + k] * w[i + k] % p;
                f[j + k] = mod(x + y);
                f[i + j + k] = mod(x - y + p);
            }
    if (op == -1) {
        reverse(&f[1], &f[n]);
        for (int i = 0; i < n; i++)
            f[i] = 1ll * f[i] * inv[n] % p;
    }
}
}  // namespace NTT
using NTT::ntt;

namespace Comb {
ll Finv[maxn + 10], fac[maxn + 10], inv[maxn + 10];
ll qp(ll base, ll n) {
    ll res = 1;
    base %= mod;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return res;
}
void init()  //n<N
{
    int n = maxn;
    inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        inv[i] = ((mod - mod / i) * inv[mod % i]) % mod;
    fac[0] = Finv[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod, Finv[i] = Finv[i - 1] * inv[i] % mod;
}
}  // namespace Comb
using Comb::fac;
using Comb::Finv;

vector<int> f(maxn << 1), g(maxn << 1), h(maxn << 1), g1(maxn << 1), g2(maxn << 1);

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);  //cf needn't delete this
#endif                              // ONLINE_JUDGE
    NTT::init();
    Comb::init();
    int n, m, _n, op = 1;
    ri2(n, m);
    n++, m++;
    REP(i, 0, n - 1)
    ri1(f[i]);
    REP(i, 0, m - 1)
    ri1(g[i]);
    _n = n, n = max(n, m);
    REP(i, 0, 2 * n - 1)
    g1[i] = Finv[i],
    g2[i] = (op * Finv[i] + mod) % mod, op = -op;  //g1到2n-1由于是要取到f,g的2n-1的点值
    int lim = 1;
    while (lim < (n << 2))
        lim <<= 1;
    ntt(g1, lim, 1), ntt(f, lim, 1), ntt(g, lim, 1);
    REP(i, 0, lim - 1)
    f[i] = 1LL * f[i] * g1[i] % mod,
    g[i] = 1LL * g[i] * g1[i] % mod;
    ntt(f, lim, -1), ntt(g, lim, -1);
    REP(i, 0, 2 * n - 1)
    h[i] = 1LL * f[i] * fac[i] % mod * g[i] % mod;  //h还是EGF，所以只乘一个fac[i]
    ntt(h, lim, 1), ntt(g2, lim, 1);
    REP(i, 0, lim - 1)
    h[i] = 1LL * h[i] * g2[i] % mod;
    ntt(h, lim, -1);
    REP(i, 0, _n + m - 2)
    printf("%d%c", h[i], i == _n + m - 2 ? '\n' : ' ');
    return 0;
}

```

## 一些习题

### P5667 拉格朗日插值2

用下降幂来做的方法：

点值转系数多项式直接EGF乘$e^{-x}$，加上上述步骤，共三次NTT。

