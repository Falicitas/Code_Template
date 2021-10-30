# 单位根反演 & Bluestein’s Algorithm

## 单位根反演

单位根反演的式子为：$[n \mid k]=\frac{1}{n} \sum_{i=0}^{n-1}\left(\omega_{n}^{k}\right)^{i}$

分类讨论，易证。

当计数题中等式含有整除形式，且题目取模的模数 p 的 $n|\varphi(p)$​​​​​ 时，便能去考虑将整除用单位根反演，利用各种组合数学将式子化简。

## 循环卷积 & DFT|IDFT

**循环卷积** 的式子定义： $c_{r}=\sum_{p, q}[(p+q) \bmod n=r] a_{p} b_{q}$​，其中$a_i,b_i,i\in[0,n-1]$​处均有定义。

求法：单位根反演展开：$[(p+q)\bmod n = r] = [n \mid (p + q - r)] = \frac{1}{n}\sum\limits_{i=0}^{n-1}(w_n^{p+q-r})^i$

放回式子里，有 $c_r = \frac{1}{n}\sum\limits_{k=0}^{n-1}w_n^{-rk}\sum\limits_{p=0}^{n-1}a_pw_n^{pk}\sum\limits_{q=0}^{n-1}b_qw_n^{qk}$​。发现后面两个式子很独立，令 $A_k = \sum\limits_{p=0}^{n-1}a_pw_n^{pk},B_k = \sum\limits_{q=0}^{n-1}b_qw_n^{qk}$ ​​以便于观察。

根据 **DFT** 的定义，$A_k$​ ​​​​是关于多项式 $f(x) = \sum a_ix^i$​​​​​ 的点值形式 $f(w_n^k)$​​​，$B_k$​​​ 同理（设其多项式为 $g(x)$​​​）。故后面两项为以长度为 $n$​​ ​的 $\mathrm{DFT}(f(x))*\mathrm{DFT}(g(x))$​​​​​​ （逐项累乘）。

类似的，对于 $c_k$ ​来说，右边的式子明显为 **IDFT** 的定义，即为 $\mathrm{IDFT}(\mathrm{DFT}(f(x))*\mathrm{DFT}(g(x)))(n)$​。故证得：

**DFT** 为关于多项式的长度为 $n$ ​的循环卷积， **IDFT** 则为关于多项式的长度为 $n$ ​的循环逆卷积。在复数域，单位根为 $w_n^1 = \cos\frac{2\pi}{n} + i\sin\frac{2\pi}{n}$​；在模域下，单位根为 $g^{\frac{p-1}{n}}$​，$g$ ​是关于模数 $ p$ ​的原根。

> 故通常的 FFT 会在一个多项式后面补零，以避免循环卷积的影响（因为 $\bmod 2^k$​（ $2^k$ ​为卷积的长度）压根没影响正常的多项式运算）。

对于长度 $n = 2^k$ ​来说，自然可以直接对 f,g 进行 DFT/IDFT。而对于任意的多项式长度 $n$​，有两种解法：递归法，Bluestein's Algorithm。

### 循环卷积的性质

对长度为 $n$ ​的多项式 $f(x)$ ​乘 $x$​，相当于对 $f(x)$​ ​向右循环平移一位。

## 递归法

考虑普通的 FFT/NTT，DFT 求出奇偶项系数表示的子多项式对应的 **点值** ，利用 $A(x) = A_1(x^2) + xA_2(x^2)$ ​求出多项式 $A$ ​的点值；IDFT则带入共轭单位根，运算结束后除运算长度 $n$​​​。

该式可以递归的本质是此时多项式的运算长度 $lim = 2^k$​，第若干层的子多项式的运算长度均为 2 的倍数，所以可以递归到 1​。

于是乎就可以提出递归法的 FFT/NTT 的做法：将多项式长度 n 按质因子分解，每次选一个质因子 P，将多项式分为 P 份（当$P=2$​时自然就分成两份，即奇偶两式）。

拿$P=3$举例，分成三式多项式，

$A_0(x) = a_0 + a_3x + a_6x^2 + \dots + a_{n-3}x^{\frac{n}{3}}$

$A_1(x) = a_1 + a_4x + a_5x^2 + \dots + a_{n-2}x^{\frac{n}{3}}$

$A_2(x) = a_2 + a_5x + a_7x^2 + \dots + a_{n-1}x^{\frac{n}{3}}$，

则$A(x) = A_0(x^3) + xA_1(x^3) + x^2A_2(x^3)$

递归求得$A_0,A_1,A_2$​的点值，有多项式 $A$ ​的点值为 $A(w_n^j) = \sum\limits_{i=0}^{P-1}w_n^{ij}A_i(w_{\frac{n}{P}}^{j\bmod \frac{n}{p}})$​，这里的 $n$ ​为当前递归的运算长度。可以预处理出初始多项式长度 $n'$ ​的单位根，有 $w^{q}_n = w_{n'}^{\frac{qn'}{n}}$​，加快运算速度。

瓶颈在于最大的质因子 $P_m$​，复杂度为 $O(P_mnlog_{P_m}n)$​​​。

约束较多：需要循环节 $\varphi(x) = n$ 且 x 有原根（比如性能优化的 x=n+1 且 n+1 为素数）；最大值因子要小。

### 代码（取自「性能优化」）

```cpp
//code sourced from kinesis
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

i64 power(i64 base, i64 n, i64 mod) {
    i64 res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return res;
}

int generator(int p) {
    {
        if (p != 2 && p != 4) {
            if (p % 2 == 0) {
                p /= 2;
            }  //此时只有p^e才能有原根
            for (int i = 2; i * i <= p; i++) {
                if (p % i == 0) {
                    while (p % i == 0) {
                        p /= i;
                    }
                    if (i == 2 || p != 1) {
                        return -1;
                    }
                    break;
                }
            }
        }
    }  //能过这个无名函数，说明p必有原根
    int phi = p;
    {
        int tmp = p;
        for (int i = 2; i * i <= tmp; ++i) {
            if (tmp % i == 0) {
                phi = phi / i * (i - 1);
                while (tmp % i == 0) {
                    tmp /= i;
                }
            }
        }
        if (tmp > 1) {
            phi = phi / tmp * (tmp - 1);
        }
    }  // O(\sqrt{p}) 得到 p 的 phi 值
    vector<int> fact;
    {
        int n = phi;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                fact.push_back(i);
                while (n % i == 0) {
                    n /= i;
                }
            }
        }
        if (n > 1) {
            fact.push_back(n);
        }
    }  //得到 phi 的素因子
    for (int g = 1; g <= p; ++g) {
        if (__gcd(g, p) != 1) {
            continue;
        }  //原根与模数互质
        bool ok = true;
        for (int factor : fact) {
            if (power(g, phi / factor, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) {
            return g;
        }
    }
    assert(0);
    return -1;
}

vector<int> fac;

void get_fac(int n) {
    if (n % 2 == 0)
        fac.push_back(2);
    if (n % 3 == 0)
        fac.push_back(3);
    if (n % 5 == 0)
        fac.push_back(5);
    if (n % 7 == 0)
        fac.push_back(7);
}

const int maxn = 5e5 + 5;
int n;

namespace NTT  //递归版的IDFT到外面记得除n
{
int buf[maxn];
int w[maxn], g;
void init() {
    g = generator(n + 1);  //循环节phi(x) = n，那么x = n+1 <==> n+1是质数
    w[0] = 1;
    for (int i = 1; i < n; i++) {
        w[i] = 1LL * w[i - 1] * g % (n + 1);
    }
    get_fac(n);
}
void ntt(int* x, int lim, int opt) {
    if (lim == 1) {
        return;
    }
    int P;
    for (int i = 0; i < fac.size(); i++) {
        if (lim % fac[i] == 0) {
            P = fac[i];
        }
    }
    for (int i = 0; i < lim / P; i++) {
        for (int j = 0; j < P; j++) {
            buf[i + lim / P * j] = x[P * i + j];
        }
    }
    for (int i = 0; i < lim; i++) {
        x[i] = buf[i];
    }
    for (int i = 0; i < P; i++) {
        ntt(x + i * lim / P, lim / P, opt);
    }
    for (int j = 0; j < lim; j++) {  //由这可判定复杂度为O(P_m n\log n),P_m n是最大的质因子
        buf[j] = 0;
        for (int i = 0; i < P; i++) {
            int upd = (opt == -1 ? ((n - 1LL * i * j * n / lim % n) % n) : (1LL * i * j * n / lim % n)), wi = w[upd];
            buf[j] = (buf[j] + 1LL * wi * x[i * lim / P + (j % (lim / P))] % (n + 1)) % (n + 1);
        }
    }
    for (int j = 0; j < lim; j++) {
        x[j] = buf[j];
    }
}
}  // namespace NTT
using NTT::ntt;

int a[maxn], b[maxn];

int main() {  //求f*g^C关于n的循环卷积，此题 n 分解成若干不超过 10 的素因子的乘积
    int C;
    cin >> n >> C;
    NTT::init();
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    ntt(a, n, 1), ntt(b, n, 1);
    for (int i = 0; i < n; i++) {
        a[i] = 1LL * a[i] * power(b[i], C, n + 1) % (n + 1);
    }
    ntt(a, n, -1);  //IDFT后尚未除n
    {
        int nInv = power(n, n - 1, n + 1);
        for (int i = 0; i < n; i++) {
            int ci = 1LL * a[i] * nInv % (n + 1);
            cout << ci << " ";
        }
        cout << "\n";
    }
    return ~~(0 - 0);
}
```

## Bluestein's Algorithm

采用的 **核心策略** 为 $ij = \left(\begin{array}{c}i+j \\ 2\end{array}\right)-\left(\begin{array}{l}i \\ 2\end{array}\right)-\left(\begin{array}{l}j \\ 2\end{array}\right)$​

**DFT**：

$y_{k}=\sum\limits_{i=0}^{n-1} a_{i} \omega_{n}^{k i}$

出现了指数 $ki$​，用策略变换一下有：$\omega_{n}^{-\dbinom{k}{2}} \sum\limits_{i=0}^{n-1} a_{i} \omega_{n}^{\dbinom{k+i}{2}} \omega_{n}^{-\dbinom{i}{2}}$​​ 是个卷积式，可以用 ntt 解决。

具体的，令 $f(x) = \sum\limits_{i=0}^{n-1}a_iw_n^{-\dbinom{i}{2}},f' = rev(f),g(x) = w_n^{\dbinom{i}{2}}$​​，运算长度为 $lim \geq 3n$​​。

`IDFT`：

$c_{k}=\frac{1}{n} \sum\limits_{i=0}^{n-1} a_{i} \omega_{n}^{-k i}$

$ = \frac{1}{n} \omega_{n}^{\dbinom{k}{2}} \sum\limits_{i=0}^{n-1} a_{i} \omega_{n}^{\dbinom{i}{2}} \omega_{n}^{-\dbinom{k+i}{2}}$

同样也是卷积式。

具体的，令$f(x) = \sum\limits_{i=0}^{n-1}a_iw_n^{\dbinom{i}{2}},f' = rev(f),g(x) = w_n^{-\dbinom{i}{2}}$，运算长度为$lim \geq 3n$。

复杂度上界为 3 个完整的 FFT/NTT 即 9 个 **DFT/IDFT** ，由于求 $a,b$​​ ​点值的结构相似，可优化几个 **DFT/IDFT** ，常数仍很大就是了。

### 代码（选自「Bluestein's Algorithm裸题，求 f/g 的循环卷积」）

```cpp
//code sourced from kinesis
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

const int maxn = 1 << 17;
const double PI = acos(-1.0);

namespace FFT {
struct Complex {
    double x, y;
    Complex(double _x = 0.0, double _y = 0.0) { x = _x, y = _y; }
    Complex operator-(const Complex& b) const { return Complex(x - b.x, y - b.y); }
    Complex operator+(const Complex& b) const { return Complex(x + b.x, y + b.y); }
    Complex operator*(const Complex& b) const { return Complex(x * b.x - y * b.y, x * b.y + y * b.x); }
    Complex operator/(const Complex& b) const { return Complex((x * b.x + y * b.y) / (b.x * b.x + b.y * b.y), (y * b.x - x * b.y) / (b.x * b.x + b.y * b.y)); }
};
int rev[maxn << 2];
void change(Complex* x, int len) {
    int bit = 0;
    while ((1 << bit) < len)
        bit++;
    for (int i = 0; i < len; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        if (i < rev[i])
            swap(x[i], x[rev[i]]);
    }
}

}  // namespace FFT
//using FFT::fft;
using FFT::Complex;

void fft(Complex* a, int N, int f) {
    int i, j, t, k;
    for (i = 1, j = 0; i < N - 1; i++) {
        for (t = N; j ^= (t >>= 1), ~j & t;)
            ;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    for (i = 1; i < N; i <<= 1) {
        Complex wn(cos(PI / i), f * sin(PI / i));
        t = i << 1;
        for (j = 0; j < N; j += t) {
            Complex w(1, 0);
            for (k = 0; k < i; k++, w = w * wn) {
                Complex x(a[j + k]), y(w * a[j + i + k]);
                a[j + k] = x + y;
                a[j + i + k] = x - y;
            }
        }
    }
    if (f == -1) {
        for (i = 0; i < N; i++) {
            a[i] = a[i] / N;
        }
    }
}

Complex w[maxn];

void init(int n) {
    for (int i = 0; i < n; i++) {
        w[i] = Complex(cos(2 * PI * i / n), sin(2 * PI * i / n));
    }
}

void bluestein(Complex* x, int n, int opt)  //opt=1时是bluestein的DFT，-1是bluestein的IDFT
{
    static Complex f[maxn << 2], g[maxn << 2];
    int lim = 1;
    while (lim < (3 * n))
        lim <<= 1;
    for (int i = 0; i < lim; i++) {
        f[i] = g[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        f[i] = x[i] * (opt == 1 ? w[(n - 1LL * i * (i - 1) / 2 % n) % n] : w[1LL * i * (i - 1) / 2 % n]);
    }
    reverse(f, f + n);
    for (int i = 0; i < 2 * n; i++) {
        g[i] = (opt == -1 ? w[(n - 1LL * i * (i - 1) / 2 % n) % n] : w[1LL * i * (i - 1) / 2 % n]);
    }
    fft(g, lim, 1), fft(f, lim, 1);
    for (int i = 0; i < lim; i++) {
        f[i] = f[i] * g[i];
    }
    fft(f, lim, -1);
    for (int i = 0; i < n; i++) {
        x[i] = (opt == 1 ? w[(n - 1LL * i * (i - 1) / 2 % n) % n] : w[1LL * i * (i - 1) / 2 % n]) * f[n - 1 + i];
    }
    if (opt == -1) {
        for (int i = 0; i < n; i++) {
            x[i] = x[i] / n;
        }
    }
}

Complex c[maxn], b[maxn], a[maxn];

int main() {  //实现长度为n的c/b的循环卷积
    int n;
    cin >> n;
    init(n);  //记得使用bluestein前调用init(n)
    for (int i = 0; i < n; i++) {
        cin >> b[i].x;
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i].x;
    }
    bluestein(b, n, 1), bluestein(c, n, 1);
    for (int i = 0; i < n; i++) {
        a[i] = c[i] / b[i];
    }
    bluestein(a, n, -1);
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(5) << a[i].x << "\n";
    }
    return ~~(0 - 0);
}
```



## 一些题目

### P5293 [HNOI2019]白兔之舞

先考虑 $n = 1$ ​的情况，很明显 $x = y = 1$​。

令 $W = w[1][1]$​。题目要求走 $i$​ 步模 $k$ ​等于 $t$ ​的方案数，而走 $i$ ​步可考虑组合意义：从 $[1,L]$ ​挑 $i$ ​个点走，则一共有方案数 $\dbinom{L}{i}W^i$ ​种方案数。$i\bmod k = t$​，则枚举 $i$​，$ans_t = \sum\limits_{i=0}^{L}[k \mid (i-t)] \dbinom{L}{i}W^i$​​​。见到互质，套路往单位根反演思路走，有

$ans_t = \sum\limits_{i=0}^L \dbinom{L}{i}W^i \frac{1}{k}\sum\limits_{j=0}^{k-1}(w_k^{i-t})^j$

$ = \frac{1}{k} \sum\limits_{i=0}^L\dbinom{L}{i} W^i\sum\limits_{j=0}^{k-1}w_k^{ij}w_k^{-tj}$。考虑变换遍历顺序，有

$ = \frac{1}{k}\sum\limits_{j=0}^{k-1}w_k^{-tj}\sum\limits_{i=0}^{L}w_k^{ij}W^i\dbinom{L}{i}$。眼尖一点可以发现后面是二项式的形式，有

$ = \frac{1}{k}\sum\limits_{j=0}^{k-1}w_k^{-tj}(w_k^jW + 1)^L$​​。后面的式子仅跟 $j$​ ​有关，可以预处理出来，记作 $c_j$​​。利用 bluestein’s algorithm 的策略，变换$-tj = \dbinom{t}{2} + \dbinom{j}{2} - \dbinom{t+j}{2}$​​​，原式有

$=\frac{1}{k} \sum\limits_{j=0}^{k-1} \omega_{k}^{\left(\begin{array}{c}t \\ 2\end{array}\right)+\left(\begin{array}{c}j \\ 2\end{array}\right)-\left(\begin{array}{c}t+j \\ 2\end{array}\right)} c_{j}$

$=\frac{1}{k} \omega_{k}^{\left(\begin{array}{l}t \\ 2\end{array}\right)} \sum\limits_{j=0}^{k-1} \omega_{k}^{\left(\begin{array}{l}j \\ 2\end{array}\right)-\left(\begin{array}{c}t+j \\ 2\end{array}\right)}{c}_{j}$

$=\frac{1}{k} \omega_{k}^{\left(\begin{array}{l}t \\ 2\end{array}\right)} \sum\limits_{j=0}^{k-1} \omega_{k}^{\left(\begin{array}{l}j \\ 2\end{array}\right)}{c}_{j} \omega_{k}^{-\left(\begin{array}{c}t+j \\ 2\end{array}\right)}$

令 $f(x) = \sum\limits_{i=0}^{k-1} \omega_{k}^{\left(\begin{array}{l}i \\ 2\end{array}\right)}{c}_{i},f'(x) = rev (f(x))(k),g(x) = \sum\limits_{i=0}^{2k-1}\omega_{k}^{-\left(\begin{array}{c}i \\ 2\end{array}\right)}$​

则原式有 $ans_t = \frac{1}{k} \omega_{k}^{\left(\begin{array}{l}t \\ 2\end{array}\right)} (f'(x)*g(x)(k-1+t))$​

不为正常模数，MTT 一下即可。

当 $n=3$​​​​​ 时，实际上只需要将 $M$​ ​​​​换成给定的 $w[][]$​​​​​ 矩阵即可（基于三个点分别对下三个点均有对应 $w[][]$​​​​​​ ​​的贡献），运算元换成矩阵的形式。（实际只取矩阵的第 y 列，于是不需要改 ntt 的结构，将矩阵第 y 列的值赋给 c[] 即可）

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int maxn = 131072;
int mod;
namespace Math {
int qp(i64 base, i64 n, const int mod) {
    i64 res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return (int)res;
}
int inv(int x, const int mod) {
    return qp(x, mod - 2, mod);
}
}  // namespace Math

const int mod1 = 998244353, mod2 = 1004535809, mod3 = 469762049, G = 3;
const i64 mod_1_2 = 1LL * mod1 * mod2;
const int inv_1 = Math::inv(mod1, mod2), inv_2 = Math::inv(mod_1_2 % mod3, mod3);
struct Int {
    int A, B, C;
    Int()
        : A(0), B(0), C(0) {}
    Int(int __num)
        : A(__num), B(__num), C(__num) {}
    Int(int __A, int __B, int __C)
        : A(__A), B(__B), C(__C) {}
    static Int reduce(const Int& x) {
        return Int(x.A + (x.A >> 31 & mod1), x.B + (x.B >> 31 & mod2), x.C + (x.C >> 31 & mod3));
    }
    friend Int operator+(const Int& lhs, const Int& rhs) {
        return reduce(Int(lhs.A + rhs.A - mod1, lhs.B + rhs.B - mod2, lhs.C + rhs.C - mod3));
    }
    friend Int operator-(const Int& lhs, const Int& rhs) {
        return reduce(Int(lhs.A - rhs.A, lhs.B - rhs.B, lhs.C - rhs.C));
    }
    friend Int operator*(const Int& lhs, const Int& rhs) {
        return Int(1LL * lhs.A * rhs.A % mod1, 1LL * lhs.B * rhs.B % mod2, 1LL * lhs.C * rhs.C % mod3);
    }
    int get() {
        i64 x = 1LL * (B - A + mod2) % mod2 * inv_1 % mod2 * mod1 + A;
        return (1LL * (C - x % mod3 + mod3) % mod3 * inv_2 % mod3 * (mod_1_2 % mod) % mod + x) % mod;
    }
};

#define maxn 131072

namespace Poly {
#define N (maxn << 1)
int lim, s, rev[N];
Int Wn[N | 1];
void init(int n) {  //init适用于DFT，IDFT，n为运算长度
    s = -1, lim = 1;
    while (lim < n)
        lim <<= 1, ++s;
    for (int i = 1; i < lim; ++i)
        rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
    const Int t(Math::qp(G, (mod1 - 1) / lim, mod1), Math::qp(G, (mod2 - 1) / lim, mod2), Math::qp(G, (mod3 - 1) / lim, mod3));
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
        Int ilim(Math::inv(lim, mod1), Math::inv(lim, mod2), Math::inv(lim, mod3));
        for (int i = 0; i < lim; i++)
            A[i] = A[i] * ilim;
    }
}
#undef N
}  // namespace Poly
using Poly::init;
using Poly::ntt;

i64 power(i64 base, i64 n, int P = mod) {
    base %= P;
    i64 res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= P;
        (base *= base) %= P;
        n >>= 1;
    }
    return res;
}

const int maxk = 65536;
int w_k[maxk], c[maxk], w[3][3];

struct mat {
    i64 c[3][3];
    int m, n;
    mat() {
        memset(c, 0, sizeof(c));
        m = n = 3;
    }
    mat(int a, int b)
        : m(a), n(b) {
        memset(c, 0, sizeof(c));
    }
    void clear() {
        memset(c, 0, sizeof(c));
    }
    mat operator+(const mat& temp) {
        mat ans(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ans.c[i][j] = (c[i][j] + temp.c[i][j]) % mod;
            }
        }
        return ans;
    }
    mat operator*(const int v) {
        mat ans(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ans.c[i][j] = 1LL * c[i][j] * v % mod;
            }
        }
        return ans;
    }
    mat operator*(const mat& temp) {
        mat ans(m, temp.n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < temp.n; j++) {
                for (int k = 0; k < n; k++) {
                    ans.c[i][j] += c[i][k] * temp.c[k][j] % mod;  //能不取模 尽量不取模
                    //这里maxn=2 故不会超过ll 视具体情况 改变取模情况
                    if (ans.c[i][j] >= mod)
                        ans.c[i][j] %= mod;
                }
            }
        }
        return ans;
    }
    friend mat operator^(mat M, i64 n) {
        mat ans(M.m, M.m);
        for (int i = 0; i < M.m; i++)
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

namespace get_G  //求一般的原根、、多一步求phi的过程
{
int generator(int p) {
    if (p < 2)
        return -1;
    int phi = p, tmp = p;
    for (int i = 2; i * i <= tmp; ++i) {
        if (tmp % i == 0) {
            phi = phi / i * (i - 1);
            while (tmp % i == 0)
                tmp /= i;
        }
    }
    if (tmp > 1)
        phi = phi / tmp * (tmp - 1);
    int n = phi;
    vector<int> fact;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        fact.push_back(n);
    for (int res = 1; res <= p; ++res) {
        if (__gcd(res, p) != 1)
            continue;
        bool ok = true;
        for (int factor : fact) {
            if (power(res, phi / factor, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok)
            return res;
    }
    return -1;
}
}  // namespace get_G

vector<Int> f(maxn << 1), g(maxn << 1);

int main() {
    int n, k, L, x, y, p;
    cin >> n >> k >> L >> x >> y >> p;
    mod = p;
    mat W(n, n), I(n, n), beg(1, n);
    beg.c[0][x - 1] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> W.c[i][j];
            I.c[i][j] = (i == j ? 1 : 0);
        }
    }
    int g_w = power(get_G::generator(p), (p - 1) / k);  //(g_w)^k = 1;
    w_k[0] = 1;
    for (int i = 1; i < k; i++) {
        w_k[i] = 1LL * w_k[i - 1] * g_w % p;
    }
    for (int i = 0; i < k; i++) {
        mat tmp = beg * ((W * w_k[i] + I) ^ L);
        c[i] = tmp.c[0][y - 1];
    }
    for (int i = 0; i < k; i++) {
        f[i] = 1LL * w_k[1LL * i * (i - 1) / 2 % k] * c[i] % mod;
    }
    reverse(f.begin(), f.begin() + k);
    for (int i = 0; i < 2 * k; i++) {
        g[i] = w_k[(k - (1LL * i * (i - 1) / 2) % k) % k];
    }
    init(3 * k);
    ntt(f), ntt(g);
    for (int i = 0; i < Poly::lim - 1; i++) {
        f[i] = f[i] * g[i];
    }
    ntt(f, -1);
    int kInv = power(k, p - 2);
    for (int t = 0; t < k; t++) {
        cout << 1LL * kInv * w_k[1LL * t * (t - 1) / 2 % k] % p * f[k - 1 + t].get() % p << "\n";
    }
    return 0;
}

```

### CF901E Cyclic Cipher

题目大意：给定长为 $n$​​ ​的序列 $b,c$​​​，以及式子 $c_{k}=\sum_{i=0}^{n-1}\left(b_{(i-k) \bmod n}-a_{i}\right)^{2}$​​​，求出序列 $a$​​​。

拆式子，有 $c_k = \sum\limits_{i=0}^{n-1} (b_i^2 + a_i^2) - 2\sum\limits_{i=0}^{n-1}b_{(i-k)\bmod i}a_i$​​

由于对于任意的 $c_k,k\in[0,n-1]$​，都有定值 $\sum\limits_{i=0}^{n-1}(b_i^2 + a_i^2)$​，考虑差分后再将其还原。

有 $\Delta c_k = c_k - c_{k-1} = 2\sum\limits_{i=0}^{n-1}b_{i-k+1}a_i - 2\sum\limits_{i=0}^{n-1}b_{i-k}a_i$ 。（该题考虑合并 b 而非 a，原因在后记会提及。）

$\Delta c_k = -2b_{n-k}(a_0 - a_{n-1}) - 2\sum\limits_{i=1}^{n-1}b_{i-k}(a_i - a_{i-1})$​​。记 $\Delta a_i = a_i - a_{i-1},\Delta a_0 = a_0 - a_{n-1}$​​，合并两项有：

$\Delta c_k = -2\sum\limits_{i=0}b_{i-k}\Delta a_{i}$​，此时处理 $b_i' = -2*b_{-i}$​，有 $\Delta c_k = \sum\limits_{i=0}b'_{-i+k}\Delta a_{i}$​。

考虑已经求得了 $\Delta a_i$ ​

假设 $a_0$ 是确定的数，则可通过 $a_k = a_0 + \sum\limits_{i=1}^k \Delta a_i$ 来求得。根据一开始给的方程，$c_0 = \sum\limits_{i=0}^{n-1}(b_i - a_i)^2$，有$na_0^2 + 2\sum\limits_{i=0}^{n-1}(s_i-b_i)a_0 + \sum\limits_{i=0}^{n-1}(s_i - b_i)^2 - c_0 = 0,s_k = \sum\limits_{i=1}^{k}\Delta a_i$，可知 $a_0$ 至多两个解。由于要求的序列 $a$ 是 **整数列** ，故 $a_0$ 也需为整数。

后记（有兴趣再看）：关于为什么拿 $b_i$ 作合并而不是 $a_i$，以及题目的循环线性无关如何保证 $g(w_n^i)$ 不为$0$：

首先题目给的条件是，不存在非全零的$x_i$，使得下面的方程组成立：

$\left\{\begin{array}{}x_{0} b_{0} +x_{1} b_{n-1}+\cdots+x_{n-1} b_{1}=0 \\ x_{0} b_{1}  +x_{1} b_{0}+\cdots+x_{n-1} b_{2}=0 \\ \vdots & \\ x_{0} b_{n-1}+x_{1} b_{n-2}+\cdots+x_{n-1} b_{0}  =0\end{array}\right.$

换言之，仅有$x_i = 0,i\in[0,n-1]$时才有唯一解，即有唯一零解，根据 **克拉默法则** 有系数矩阵行列式$|A|$不为0：

$A = \left[\begin{array}{cccc}b_{0} & b_{n-1} & \cdots & b_{1} \\ b_{1} & b_{0} & \cdots & b_{2} \\ \vdots & \vdots & \ddots & \vdots \\ b_{n-1} & b_{n-2} & \cdots & b_{0}\end{array}\right]$

该矩阵比较特殊，每一行由上一行向右平移一位得来，称其为 **循环矩阵（circulant matrix）**。

令 $g2(x) = b_0 + \sum\limits_{i=1}b_{n-i}x^i$，

与 **范德蒙矩阵**$V = \left[\begin{array}{cccc}1 & 1 & \cdots & 1 \\ \epsilon_{0}^{1} & \epsilon_{1}^{1} & \cdots & \epsilon_{n-1}^{1} \\ \vdots & \vdots & \ddots & \vdots \\ \epsilon_{0}^{n-1} & \epsilon_{1}^{n-1} & \cdots & \epsilon_{n-1}^{n-1}\end{array}\right]$，其中$\epsilon_i = w_n^i$

发现$A V=\left[\begin{array}{cccc}g_{2}\left(\epsilon_{0}\right) & g_{2}\left(\epsilon_{1}\right) & \cdots & g_{2}\left(\epsilon_{n-1}\right) \\ \epsilon_{0}^{1} g_{2}\left(\epsilon_{0}\right) & \epsilon_{1}^{1} g_{2}\left(\epsilon_{1}\right) & \cdots & \epsilon_{n-1}^{1} g_{2}\left(\epsilon_{n-1}\right) \\ \vdots & \vdots & \ddots & \vdots \\ \epsilon_{0}^{n-1} g_{2}\left(\epsilon_{0}\right) & \epsilon_{1}^{n-1} g_{2}\left(\epsilon_{1}\right) & \cdots & \epsilon_{n-1}^{n-1} g_{2}\left(\epsilon_{n-1}\right)\end{array}\right] = \left[\begin{array}{cccc}1 & 1 & \cdots & 1 \\ \epsilon_{0}^{1} & \epsilon_{1}^{1} & \cdots & \epsilon_{n-1}^{1} \\ \vdots & \vdots & \ddots & \vdots \\ \epsilon_{0}^{n-1} & \epsilon_{1}^{n-1} & \cdots & \epsilon_{n-1}^{n-1}\end{array}\right]       \left[\begin{array}{cccc}g_2(\epsilon_0) & 0 & \cdots & 0 \\ 0 & g_2(\epsilon_{1}) & \cdots & 0 \\ \vdots & \vdots & \ddots & \vdots \\ 0 & 0 & \cdots & g_2(\epsilon_{n-1})\end{array}\right]$

易知 $|AV| = |V|\prod\limits_{i=0}^{n-1}g_2(\epsilon_{i})$

对于范德蒙矩阵，$|V| = \prod\limits_{0\leq j<i\leq n-1}(\epsilon_i - \epsilon_j),j<i$时$(\epsilon_i - \epsilon_j)\neq 0$，故$|AV| = |A||V| = |V|\prod\limits_{i=0}^{n-1}g_2(\epsilon_{i})$，故$|A| = \prod\limits_{i=0}^{n-1}g_2(w_n^i)$。由于$|A|\neq 0$，故$\prod\limits_{i=0}^{n-1}g_2(w_n^i) \neq 0 \Rightarrow \forall i,g_2(w_n^i)\neq 0$。由于$g(x) = g_2(x) *(-2x)$，而单位根不为0，所以$g(w_n^i)\neq 0$。而如果合并$a_i$，$g(x) = \sum\limits_{i=0} \Delta b_ix^i$就可能没这样的结论。

### CF1270I Xor on Figures

有一个 $2^{k} \times 2^{k}$ 的矩阵 $A$, 行列从 0 开始标号，有两个长度为 $t$ 的序列 $x, y$ 。

你需要通过若干次操作使得整个矩阵 $A$ 全为 0 。

一次操作需要三个参数 $(p, q, w)$, 会给所有 $A\left[\left(x_{i}+p\right) \bmod 2^{k}\right]\left[\left(y_{i}+q\right) \bmod 2^{k}\right]$ 异或上 $w_{\text {。 }}$ 求最小的操作次数。

$k \leq 9, t \leq 99$ 且 $t$ 为奇数。

首先考虑一维的情况，对于长度为 $2^k$ 的序列 $a_i$ 的生成函数为 $A$，有若干的点 $x_i$ 构成的序列（记生成函数为 $f(x)$），每次对$x_{i+d\bmod 2^k}$的点异或一个值$w$，使$A$全为零。以下的乘法运算都是 **异或循环卷积** 。比如一维的$[x^k]f(x) = \bigotimes_{i=0}^{k}g_ih_{k-i}$。

先按位思考，对于某一位$bit_t$：要使得$A$为零，即$f(x)$与其向右平移的选中的若干多项式$x^if(x)$的加法等于$A$。有$A_t = 2^t\sum\limits_{i=0}^{2^k-1}f(x)x^is_i$，$s_i$为向右平移$i$位的多项式选不选（即非零即一）。令$g(x) = s_ix^i$，有$g(x)f(x)2^t = A_t$。

很明显要求的就是$g(x)$啦，由于$A$的位与位是加法的关系，即有$g(x)f(x) = A,f_{x[i],y[i]}=1$。扩展至二维为$f_{x,y}g_{x,y} = A$.定义二维的 **异或循环卷积** 为$[x^0y^0](a\times b) = \bigotimes_{i=0}^{2^{k}-1} \bigotimes_{j=0}^{2^{k}-1} a[i][j] \times b\left[(x-i) \bmod 2^{k}\right]\left[(y-j) \bmod 2^{k}\right]$

 现在的难题是如何求$f_{i,j}$在异或循环卷积下的逆元。

首先，多项式的逆元的定义为$f_{x,y}f^{-1}_{x,y} = 1$；

其次，考虑$f^2$，仅有$(2x_i\bmod 2^k,2y_i\bmod 2^k)$的点上才有值，由于$(x_i+x_j,y_i+y_j)$的点会被贡献两次。而$f^{2^k}$有$[x^iy^j]f^{2^k} = [i=0,j=0]$。故$f^{2^k-1} = f^{-1} = \prod\limits_{i=0}^{k-1}f^i$。

所以原式等于$g(x) = A\prod\limits_{i=0}^{k-1}f^i$，由于每个$f_i$至多有$t$个点有值，所以总复杂度为$O(tk4^k)$。

![img](https://espresso.codeforces.com/e509ee7e142bbe29200b770d93afb3c552aeabc2.png)
