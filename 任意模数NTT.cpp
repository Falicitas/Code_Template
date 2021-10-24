
//使用Int数乘法当且仅当IFT时两个多项式点值相乘
//用Int类型多项式f给初始多项式赋值g时使用g[i] = f[i].get()函数，不然会WA。
//包括对原多项式的指数，对数，求逆运算，得到的多项式都需要f[i] = f[i].get()
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int mod;
namespace Math {
int power(ll base, ll n, const int mod) {
    ll res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return (int)res;
}
int inv(int x, const int mod) {
    return power(x, mod - 2, mod);
}
}  // namespace Math

const int mod1 = 998244353, mod2 = 1004535809, mod3 = 469762049, G = 3;
const ll mod_1_2 = 1LL * mod1 * mod2;
const int inv_1 = Math::inv(mod1, mod2),
          inv_2 = Math::inv(mod_1_2 % mod3, mod3);
struct Int {
    int A, B, C;
    Int()
        : A(0), B(0), C(0) {}
    Int(int __num)
        : A(__num), B(__num), C(__num) {}
    Int(int __A, int __B, int __C)
        : A(__A), B(__B), C(__C) {}
    static Int reduce(const Int& x) {
        return Int(x.A + (x.A >> 31 & mod1), x.B + (x.B >> 31 & mod2),
                   x.C + (x.C >> 31 & mod3));
    }
    friend Int operator+(const Int& lhs, const Int& rhs) {
        return reduce(Int(lhs.A + rhs.A - mod1, lhs.B + rhs.B - mod2,
                          lhs.C + rhs.C - mod3));
    }
    friend Int operator-(const Int& lhs, const Int& rhs) {
        return reduce(Int(lhs.A - rhs.A, lhs.B - rhs.B, lhs.C - rhs.C));
    }
    friend Int operator*(const Int& lhs, const Int& rhs) {
        return Int(1LL * lhs.A * rhs.A % mod1, 1LL * lhs.B * rhs.B % mod2,
                   1LL * lhs.C * rhs.C % mod3);
    }
    int get() {
        ll x = 1LL * (B - A + mod2) % mod2 * inv_1 % mod2 * mod1 + A;
        return (1LL * (C - x % mod3 + mod3) % mod3 * inv_2 % mod3 *
                    (mod_1_2 % mod) % mod +
                x) %
               mod;
    }
};

#define maxn 131072

namespace Poly {
#define N (maxn << 1)
int lim, s, rev[N];
Int Wn[N | 1];
void init(int n) {  // init适用于DFT，IDFT，n为运算长度
    s = -1, lim = 1;
    while (lim < n)
        lim <<= 1, ++s;
    for (int i = 1; i < lim; ++i)
        rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
    const Int t(Math::power(G, (mod1 - 1) / lim, mod1),
                Math::power(G, (mod2 - 1) / lim, mod2),
                Math::power(G, (mod3 - 1) / lim, mod3));
    *Wn = Int(1);
    for (Int* i = Wn; i != Wn + lim; ++i)
        *(i + 1) = *i * t;
}
void ntt(vector<Int>& A, int op = 1) {
    for (int i = 1; i < lim; ++i)
        if (i < rev[i])
            swap(A[i], A[rev[i]]);
    for (int mid = 1; mid < lim; mid <<= 1) {
        int t = lim / mid >> 1;
        for (int i = 0; i < lim; i += mid << 1) {
            for (int j = 0; j < mid; ++j) {
                Int W = op == 1 ? Wn[t * j] : Wn[lim - t * j];
                Int X = A[i + j], Y = A[i + j + mid] * W;
                A[i + j] = X + Y, A[i + j + mid] = X - Y;
            }
        }
    }
    if (op == -1) {
        Int ilim(Math::inv(lim, mod1), Math::inv(lim, mod2),
                 Math::inv(lim, mod3));
        for (int i = 0; i < lim; i++)
            A[i] = A[i] * ilim;
    }
}
#undef N
}  // namespace Poly
using Poly::init;
using Poly::ntt;
vector<Int> A, B;

int n, m;
int main() {
    cin >> n >> m >> mod;
    n++, m++;
    A.resize(maxn << 1), B.resize(maxn << 1);
    for (int i = 0, x; i < n; ++i)
        cin >> x, A[i] = x;
    for (int i = 0, x; i < m; ++i)
        cin >> x, B[i] = x;
    Poly::init(n + m);
    Poly::ntt(A), Poly::ntt(B);
    for (int i = 0; i < Poly::lim; ++i)
        A[i] = A[i] * B[i];
    Poly::ntt(A, -1);
    for (int i = 0; i < n + m - 1; ++i)
        cout << A[i].get() << " ";
    cout << "\n";
    return 0;
}
