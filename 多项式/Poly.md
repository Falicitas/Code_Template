# Poly

## 代码

```cpp
#include <bits/stdc++.h>
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int P = 998244353, g = 3;
std::vector<int> rev, roots{0, 1};

int power(int a, int b) {
    int res = 1;
    for (; b; b >>= 1, a = 1ll * a * a % P)
        if (b & 1)
            res = 1ll * res * a % P;
    return res;
}
void dft(std::vector<int>& a) {  //直接传数组进来。数组需要扩容至2^k
    int n = a.size();
    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; ++i)
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
    }
    for (int i = 0; i < n; ++i)
        if (rev[i] < i)
            std::swap(a[i], a[rev[i]]);
    if (int(roots.size()) < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            int e = power(g, (P - 1) >> (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); ++i) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = 1ll * roots[i] * e % P;
            }
            ++k;
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; ++j) {
                int u = a[i + j];
                int v = 1ll * a[i + j + k] * roots[k + j] % P;
                int x = u + v;
                if (x >= P)
                    x -= P;
                a[i + j] = x;
                x = u - v;
                if (x < 0)
                    x += P;
                a[i + j + k] = x;
            }
        }
    }
}
void idft(std::vector<int>& a) {
    int n = a.size();
    std::reverse(a.begin() + 1, a.end());
    dft(a);
    int inv = power(n, P - 2);
    for (int i = 0; i < n; ++i)
        a[i] = 1ll * a[i] * inv % P;
}
struct Poly {
    std::vector<int> a;
    Poly() {}
    Poly(int a0) {
        if (a0)
            a = {a0};
    }
    Poly(const std::vector<int>& a1)  //保留有效项
        : a(a1) {
        while (!a.empty() && !a.back())
            a.pop_back();
    }
    int size() const {
        return a.size();
    }
    int operator[](int idx) const {
        if (idx < 0 || idx >= size())
            return 0;
        return a[idx];
    }
    Poly mulxk(int k) const {  //返回Poly<<k（右移k位）的结果
        auto b = a;
        b.insert(b.begin(), k, 0);
        return Poly(b);
    }
    Poly modxk(int k) const {  //返回Poly 0~x^{k-1}项的结果。可能第k-1项会非法访问（没开空间）
        k = std::min(k, size());
        return Poly(std::vector<int>(a.begin(), a.begin() + k));
    }
    Poly divxk(int k) const {  //返回Poly 左移k位的结果
        if (size() <= k)
            return Poly();
        return Poly(std::vector<int>(a.begin() + k, a.end()));
    }
    friend Poly operator+(const Poly a, const Poly& b) {  //返回Poly +
        std::vector<int> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); ++i) {
            res[i] = a[i] + b[i];
            if (res[i] >= P)
                res[i] -= P;  //+法一个if解决模域外问题
        }
        return Poly(res);
    }
    friend Poly operator-(const Poly a, const Poly& b) {  //返回Poly -
        std::vector<int> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); ++i) {
            res[i] = a[i] - b[i];
            if (res[i] < 0)
                res[i] += P;
        }
        return Poly(res);
    }
    friend Poly operator*(Poly a, Poly b) {  //返回Poly *
        int sz = 1, tot = a.size() + b.size() - 1;
        while (sz < tot)
            sz *= 2;
        a.a.resize(sz);
        b.a.resize(sz);
        dft(a.a);
        dft(b.a);
        for (int i = 0; i < sz; ++i)
            a.a[i] = 1ll * a[i] * b[i] % P;
        idft(a.a);
        return Poly(a.a);
    }
    Poly& operator+=(Poly b) {  //Poly +=
        return (*this) = (*this) + b;
    }
    Poly& operator-=(Poly b) {  //Poly -=
        return (*this) = (*this) - b;
    }
    Poly& operator*=(Poly b) {  //Poly *=
        return (*this) = (*this) * b;
    }
    Poly deriv() const {  //Poly 微分
        if (a.empty())
            return Poly();
        std::vector<int> res(size() - 1);
        for (int i = 0; i < size() - 1; ++i)
            res[i] = 1ll * (i + 1) * a[i + 1] % P;
        return Poly(res);
    }
    Poly integr() const {  //Poly 积分
        if (a.empty())
            return Poly();
        std::vector<int> res(size() + 1);
        for (int i = 0; i < size(); ++i)
            res[i + 1] = 1ll * a[i] * power(i + 1, P - 2) % P;
        return Poly(res);
    }
    Poly inv(int m) const {  //Poly 求逆
        Poly x(power(a[0], P - 2));
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (2 - modxk(k) * x)).modxk(k);
        }
        return x.modxk(m);
    }
    Poly log(int m) const {  //Poly 取对数
        return (deriv() * inv(m)).integr().modxk(m);
    }
    Poly exp(int m) const {  //Poly 取指数
        Poly x(1);
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (1 - x.log(k) + modxk(k))).modxk(k);
        }
        return x.modxk(m);
    }
    Poly sqrt(int m) const {  //Poly 开方
        Poly x(1);
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (modxk(k) * x.inv(k)).modxk(k)) * ((P + 1) / 2);
        }
        return x.modxk(m);
    }
    Poly mulT(Poly b) const {  //转置
        if (b.size() == 0)
            return Poly();
        int n = b.size();
        std::reverse(b.a.begin(), b.a.end());
        return ((*this) * b).divxk(n - 1);
    }
    std::vector<int> eval(std::vector<int> x) const {  //多点求值
        if (size() == 0)
            return std::vector<int>(x.size(), 0);
        const int n = std::max(int(x.size()), size());
        std::vector<Poly> q(4 * n);
        std::vector<int> ans(x.size());
        x.resize(n);
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                q[p] = std::vector<int>{1, (P - x[l]) % P};
            } else {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        std::function<void(int, int, int, const Poly&)> work = [&](int p, int l, int r, const Poly& num) {
            if (r - l == 1) {
                if (l < int(ans.size()))
                    ans[l] = num[0];
            } else {
                int m = (l + r) / 2;
                work(2 * p, l, m, num.mulT(q[2 * p + 1]).modxk(m - l));
                work(2 * p + 1, m, r, num.mulT(q[2 * p]).modxk(r - m));
            }
        };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
};
```

## 任意模数

```cpp

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

```

