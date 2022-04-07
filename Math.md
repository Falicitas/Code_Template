[toc]

# 杜教筛

## 应用

$O(n^{3 / 4}) / O(n^{2 / 3})$ 求出 **积性函数的前缀和**。

## 引理

记 $S(n) = \sum\limits_{i=1}^n f(i)$

有 $\sum\limits_{i=1}^{n}\sum\limits_{d|i}g(d)f(\frac{i}{d}) = \sum\limits_{i=1}^ng(i)S(\left\lfloor\frac{n}{i}\right\rfloor)$ （下面证明简化 $\left\lfloor\frac{n}{i}\right\rfloor = \frac{n}{i}$ ）

证明：

更换遍历方式， $i,j$ 代替 $d,\frac{i}{d}$ ，有 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{\frac{n}{i}}g(i)f(j) = \sum\limits_{i=1}^{n}g(i)*S(\frac{n}{i})$

证毕。

## 杜教筛

$\sum\limits_{i=1}^{n}\sum\limits_{d|i}g(d)f(\frac{i}{d}) = \sum\limits_{i=1}^ng(i)S(\left\lfloor\frac{n}{i}\right\rfloor)$

$\Rightarrow g(1)S(n) = \sum\limits_{i=1}^n(g * f)(i) - \sum\limits_{i=2}^{n}g(i)S(\left\lfloor\frac{n}{i}\right\rfloor)$

若能快速求出 $\sum\limits_{i=1}^n(g * f)(i)$ ，则能达到 $O(n^{\frac{3}{4}})$ 将求出前缀和。预处理能达到 $O(n^\frac{2}{3})$​ 。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

namespace linear_table {
int S[10000007];
}

namespace Du_table  //g函数既要好与f卷，其前缀和也要好求，不需要预处理的那种
{
using linear_table::S;  //在线性筛里的前缀和

map<i64, i64> S_map;

i64 dirichlet(i64 n) {  //dirichlet(n)为sum{i=1~n}(f*g)(i)的值
    return 1;
}

i64 gSum(i64 n) {  //g(i)为g的前缀和
    return 1;
}

i64 cal(i64 n) {
    if (n < 10000007) {
        return S[n];
    }
    if (S_map.count(n)) {
        return S_map[n];
    }
    i64 res = dirichlet(n);
    for (i64 i = 2, j; (n / i); i = j + 1) {
        j = n / (n / i);
        res -= (gSum(j) - gSum(i - 1)) * cal(n / i);
    }
    return S_map[n] = res;
}
}  // namespace Du_table

```



### 复杂度证明

由于对于 $\frac{n}{i},i\in[1,n]$ 来说， $\frac{n}{i},i\in[1,\sqrt{n}]$ 不重叠的散落在 $[\sqrt{n},n]$ 中， $\frac{n}{i},i\in[\sqrt{n},n]$ 密集排布在 $[1,\sqrt{n}]$ 上。对于每个 $\frac{n}{i}$ 仅需访问一次，故设求 $S(n)$ 的复杂度为 $T(n)$ ，有 $T(n) = O(\sqrt{n} + \sum\limits_{i=1}^{\sqrt{n}}(T(i) + T(\frac{n}{i}))$

往下展开一项， $T(n) = O(\sqrt{n}) + \sum\limits_{i=1}^{\sqrt{n}}(O(\sqrt{i})+... + O(\sqrt{\frac{n}{i}})+...)$ ，除去高阶小量，有 $T(n) = O(\sqrt{n}) + \sum\limits_{i=1}^{\sqrt{n}}(O(\sqrt{i}) + O(\sqrt{\frac{n}{i}}))$

由基本不等式，  $O(\sqrt{i}) + O(\sqrt{\frac{n}{i}}) >= 2n^\frac{1}{4},\sum\limits_{i=1}^{\sqrt{n}} 2n^{1 / 4} = O(n^{\frac{3}{4}})$

预处理至少大于 $O(\sqrt{n})$ 。假设预处理了 $k$ 项，原式有 $T(n) = O(\sqrt{n}) + \sum\limits_{i=1}^{\frac{n}{k}}O(\sqrt{\frac{n}{i}})$ 。用积分拟合级数， $\int_{i=1}^{\frac{n}{k}}\sqrt{\frac{n}{i}}dx = \frac{n}{\sqrt{k}}$

当预处理 $k = n^\frac{2}{3}$ 能达到较优复杂度 $T(n) = O(n^{\frac{2}{3}})$

**应当经常复习** 。此复杂度证明的覆盖面 **不仅在于** 杜教筛。

例子：对于预处理前 $n ^ {2 / 3}$ 的某函数值，该函数值单点求值的复杂度为 $\sqrt{n}$ ，问求剩余的 $n / i$ 的值的复杂度。

由于前 $n ^ {2 / 3}$ 的值求出来了，即要求 $n / i \geq n^{2 / 3}$ ，即 $i \leq n ^ {1 / 3}$ 的所有值。复杂度为 $\sum\limits_{i = 1} ^{n^{1 / 3}} \sqrt{n / i} = n ^ {2 / 3}$ 。 

# 二次剩余

已经写过了模板，但还不太想了解原理- -仅适用于奇素数。

> 当剩余为0，有唯一解0；
>
> 当无解时没有解；
>
> 否则定有两个解，其在模奇素数$p$下互为相反数。

注意，0不属于二次剩余、、在取模下较小的数为正，较大的数为负。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

namespace Twice_Remainder  //先判断剩余是否为0，为0则有唯一解0。然后判断是否有解；有解的话就一定有两个解，套solve
{
int mod;
i64 I_2;  // 虚数单位的平方
struct complex {
    i64 real, i;
    complex(i64 real = 0, i64 i = 0)
        : real(real), i(i) {}
};
inline bool operator==(complex x, complex y) {
    return x.real == y.real && x.i == y.i;
}
inline complex operator*(complex x, complex y) {
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
void solve(int b, int p, int& x0, int& x1) {
    mod = p;
    i64 a = rand() % mod;
    while (!a || check_if_residue((a * a + mod - b) % mod))
        a = rand() % mod;
    I_2 = (a * a + mod - b) % mod;
    x0 = int(qp(complex(a, 1), (mod + 1) >> 1).real), x1 = mod - x0;
}
}  // namespace Twice_Remainder

```

# 二项式反演

~~现在我也不知道他是用来干什么的。既然是反演，那就是一个函数的定义式，等价于另一个函数的定义式、、总之先学着吧。~~

是用于关于至少必包含$k$个元素的$f(k)$函数与恰好包含$k$个元素的$g(k)$函数的相互转化。只需知道其中一个函数，就能反演得到另一个函数。

## 二维遍历倒置的原理

遍历的时候倒置的原理就是，i和j的遍历构成了一张表，反过来遍历时仍然是遍历这张表。倒置的目的是把后面复杂函数的复数组合拆分，将遍历中与$i$或与$j$无关的项提前。遵守不重不漏原则。

## 形式0

在容斥定理中，假设每个事件都是等同性质$A$，记$f(i)$为i个事件取交的方案数，$g(i)$为i个事件补取交的方案数。

通过容斥定理可以得到：

$\begin{array}{l}
f(n)=\sum_{i=0}^{n}(-1)^{i}\left(\begin{array}{c}
n \\
i
\end{array}\right) g(i) \\
g(n)=\sum_{i=0}^{n}(-1)^{i}\left(\begin{array}{c}
n \\
i
\end{array}\right) f(i)
\end{array}$

故此时就有了形式0，即一个等价式：

$f(n)=\sum_{i=0}^{n}(-1)^{i}\left(\begin{array}{l}
n \\
i
\end{array}\right) g(i) \Leftrightarrow g(n)=\sum_{i=0}^{n}(-1)^{i}\left(\begin{array}{l}
n \\
i
\end{array}\right) f(i)$

## 形式1

$f(n)=\sum_{i=0}^{n}\left(\begin{array}{l}
n \\
i
\end{array}\right) g(i) \Leftrightarrow g(n)=\sum_{i=0}^{n}(-1)^{n-i}\left(\begin{array}{l}
n \\
i
\end{array}\right) f(i)$

证明1：

构造函数$h(x) = (-1)^xg(x)$,放入形式0中有:$f(n)=\sum_{i=0}^{n}\left(\begin{array}{l}
n \\
i
\end{array}\right) h(i) \Leftrightarrow \frac{h(n)}{(-1)^n}=\sum_{i=0}^{n}(-1)^{i}\left(\begin{array}{l}
n \\
i
\end{array}\right) f(i)$

整理后就是形式1。

证明2:

假设成立，将形式1的等价式右式带入左式中，得
$\begin{aligned}
f(n) &=\sum_{i=0}^{n}\left(\begin{array}{c}
n \\
i
\end{array}\right) \sum_{j=0}^{i}(-1)^{i-j}\left(\begin{array}{c}
i \\
j
\end{array}\right) f(j) \\
&=\sum_{i=0}^{n} \sum_{j=0}^{i}(-1)^{i-j}\left(\begin{array}{c}
n \\
i
\end{array}\right)\left(\begin{array}{c}
i \\
j
\end{array}\right) f(j)
\end{aligned}$

将遍历的两个顺序调换，得以将后面的函数前置：

$f(n)=\sum_{j=0}^{n} f(j) \sum_{i=j}^{n}(-1)^{i-j}\left(\begin{array}{l}
n \\
i
\end{array}\right)\left(\begin{array}{l}
i \\
j
\end{array}\right)$

后面的组合数乘积没有现有的化简方案，用下面的式子尝试变形，将其中一项前置：

$C_n^iC_i^j=C_n^jC_{n-j}^{i-j}$

证明的话将组合数按定义展开是恒等式。形象一点，就是n个无色块涂上i个绿色块、i个绿色块上涂j个红色块，等价于先涂j个红色块，再涂i-j个绿色块。

回到原问题，前置，换元、变换上下限：

$\begin{aligned}
f(n) &=\sum_{j=0}^{n}\left(\begin{array}{c}
n \\
j
\end{array}\right) f(j) \sum_{i=j}^{n}\left(\begin{array}{c}
n-j \\
i-j
\end{array}\right)(-1)^{i-j} \\
&=\sum_{j=0}^{n}\left(\begin{array}{c}
n \\
j
\end{array}\right) f(j) \sum_{t=0}^{n-j}\left(\begin{array}{c}
n-j \\
t
\end{array}\right)(-1)^{t} 1^{n-j-t} \\
&=\sum_{j=0}^{n}\left(\begin{array}{c}
n \\
j
\end{array}\right) f(j)(1-1)^{n-j}
\end{aligned}$

当$n\ !=j$时，$(1-1)^{n-j}=0$
当$n=j$时，由于$0^0$不存在，回到展开前：$C^0_0(-1)^0=1$，得$f(n)=f(n)$。等价式成立。

注：由于证明二并未用到 i 从 0 开始这一性质，因此更通用的公式为：
$
f(n)=\sum_{i=m}^{n}\left(\begin{array}{l}
n \\
i
\end{array}\right) g(i) \Leftrightarrow g(n)=\sum_{i=m}^{n}(-1)^{n-i}\left(\begin{array}{l}
n \\
i
\end{array}\right) f(i)
$

## 形式2

$f(n)=\sum_{i=n}^{m}\left(\begin{array}{c}
i \\
n
\end{array}\right) g(i) \Leftrightarrow g(n)=\sum_{i=n}^{m}(-1)^{i-n}\left(\begin{array}{c}
i \\
n
\end{array}\right) f(i)$

注意形式1和形式2正负的指数不同。。形式1中$n$是上界，形式2中$n$是下界。

证明：

$\begin{aligned}
f(n) &=\sum_{i=n}^{m}\left(\begin{array}{c}
i \\
n
\end{array}\right) \sum_{j=i}^{m}(-1)^{j-i}\left(\begin{array}{c}
j \\
i
\end{array}\right) f(j) \\
&=\sum_{i=n}^{m} \sum_{j=i}^{m}(-1)^{j-i}\left(\begin{array}{c}
i \\
n
\end{array}\right)\left(\begin{array}{c}
j \\
i
\end{array}\right) f(j) \\
&=\sum_{j=n}^{m} f(j) \sum_{i=n}^{j}(-1)^{j-i}\left(\begin{array}{c}
i \\
n
\end{array}\right)\left(\begin{array}{c}
j \\
i
\end{array}\right) \\
&=\sum_{j=n}^{m}\left(\begin{array}{c}
j \\
n
\end{array}\right) f(j) \sum_{i=n}^{j}\left(\begin{array}{c}
j-n \\
j-i
\end{array}\right)(-1)^{j-i} \\
&=\sum_{j=n}^{m}\left(\begin{array}{c}
j \\
n
\end{array}\right) f(j) \sum_{t=0}^{j-n}\left(\begin{array}{c}
j-n \\
t
\end{array}\right)(-1)^{t} 1^{j-n-t} \\
&=\sum_{j=n}^{m}\left(\begin{array}{c}
j \\
n
\end{array}\right) f(j)(1-1)^{j-n} \\
&=\sum_{j=n}^{m}\left(\begin{array}{c}
j \\
n
\end{array}\right) f(j)[j=n] \\
&=\left(\begin{array}{c}
n \\
n
\end{array}\right) f(n) \\
&=f(n)
\end{aligned}$

## 组合意义

将$f(n)$定义为钦定选n个物品(至多or至少)的方案，根据形式1 or 形式2反演得到的$g(n)$就是恰好选$n$个的方案、、

## 总结

说到底，$f$与$g$皆是抽象出来的函数，上述两个形式，四个方程，在整数领域中皆可行。对于$f\ or\ g$的解释只是建立起了与组合数学的桥梁。

> * 如果计算出来的$f(x)$代表至少选$x$个，则$f(x)=\sum_{i=x}^{n}\left(\begin{array}{c}
>   i \\
>   x
>   \end{array}\right) g(i)$，得到的$g(x)$就是恰好选$x$的个数。对应形式2的反演。
> * 如果计算出来的$f(x)$代表至多选$x$个，则$f(x)=\sum_{i=m}^{x}\left(\begin{array}{l}
>   n \\
>   i
>   \end{array}\right) g(i)$，得到的$g(x)$就是恰好选$x$的个数。对应形式1的反演。

## 例题1 [bzoj2839]集合计数

题意：一个有 $n$ 个元素的集合有 $2^{n}$ 个不同子集 (包含空集) ，现在要在这 $2^{n}$ 个集合中取出至少一个集合，使得它们的交集的元素个 求取法的方案数模 $10^{9}+7,1 \leq n \leq 10^{6}, 0 \leq k \leq n$

设$f(k)$为子集交至少有$k$个元素的情况。易得出$f(k)=C_n^k(2^{2^{n-k}}-1),-1$表示至少有1个子集存在。

形式2，$f(k)=\sum_{i=k}^{n}\left(\begin{array}{l}
i \\
k
\end{array}\right) g(i)$

反演得$g(k)=\sum_{i=k}^{n}(-1)^{i-k}\left(\begin{array}{l}
i \\
k
\end{array}\right) f(i)=\sum_{i=k}^{n}(-1)^{i-k}\left(\begin{array}{l}
i \\
k
\end{array}\right)\left(\begin{array}{l}
n \\
i
\end{array}\right)\left(2^{2^{n-i}}-1\right)$

其中$2^{2^{i}} = 2^{2^{i-1}} * 2^{2^{i-1}},O(n)$预处理一下。

## 例题2 [bzoj3622]已经没有什么好害怕的了

题意
给出两个长度均为 $n$ 的序列 $A$ 和 $B,$ 保证这 $2 n$ 个数互不相同。现要将 $A$ 序列中的数与 $B$ 序列中的数两两配对, $A>B$ 的对数比 $A<B$ 的对数"恰好多 $k$ "的配对方案数模 $10^{9}+9$

构建$dp(i,j)$，表示前$i$个$a_i$与$b_i$配对$j$对$a_i>b_i$的方案数。
当前$i$不配对，$dp(i,j)=dp(i-1,j)$
配对，则$dp(i,j)=dp(i-1,j-1)*(cnt[i]-(j-1)),cnt[i]$为$a_i$大于$b[i]$的个数。

故方程为$dp(i,j)=dp(i-1,j)+dp(i-1,j-1)*(cnt[i]-(j-1))$,初始$dp(i,0)=1$

在n中选好i个(即$dp[n][i]$)，其余自由配对，那就是至少选$i$对a>b的方案数$f(i)=dp[n][i]*(n-i)!$。二项式反演就得到答案。

# 高斯消元

```cpp
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
        return now == n + 1 ? 1 : 2;  //1唯一解；2无穷多解
    }
};

int main() {
    Gauss gs(10);
    gs[1][2] = 3;
    return 0;
}
```

# 基于值域的快速gcd

基于值域预处理的gcd、、复杂度在$O(3)\sim O(1)$左右、、

## 引理1

任何数n均可被分解成三个因子$\{a,b,c\},a\leq b\leq c,$且$c$要不$\leq \sqrt{n}$ ,要不是素数$p$、、

证明：当$c > \sqrt{n}$且$c$是合数，将$c$分解成$\{d,e\},d\leq e$,由于$c> \sqrt{n},ab = \frac{n}{c} \leq \sqrt{n} $,则$n$的三个因子可以表示成：$\{ab,d,e\}$

倘若$e>\sqrt{n}$，且是合数则继续分解，直到对应的第三项$\leq \sqrt{n}$或者不能再分解（此时为素数）

## 引理2

任何数$n$可以由最小质因子$p_0$与$\frac{n}{p_0}$的三个升序因子$\{a,b,c\}$的组合$\{ap_0,b,c\}$所构成，且$ap_0\leq \sqrt{n}\ or\ ap$是素数。

证明：当$n$是质数时显然成立：$[n=p_0]+[\{1,1,1\}] = \{1,1,p_0\}$,对应的$ap_0$为素数、、

当$n$为合数，最小素因子必满足$p_0 \leq \sqrt{n}$。给$n$的最小素因子限定上界$p_0\leq n^{\frac{1}{4}}$,带入$a\leq{\frac{n}{p_0}}^{\frac{1}{3}}$，解得$ap_0\leq n^{\frac{1}{2}}$、、若$p_0 > n^{\frac{1}{4}}$，对$\frac{n}{p_0}$进行讨论：

当$\frac{n}{p_0}$是质数时，三个因子必是$\{1,1,\frac{n}{p}\},$此时$a = 1,ap \leq \sqrt{n}$；

当$\frac{n}{p_0}$的形式为$p_1^2\ or\ p_1*p_2,p_0\leq p_1,p_0\leq p_2,$三个因子为$\{1,p_1,p_1\}\ or\ \{1,p_1,p_2\},a = 1,ap_0\leq \sqrt{n}$；

否则，$\frac{n}{p_0}$三个因子$\{a,b,c\}$必均$\geq p_0$，由于$n = p_0 * a * b * c > n$，此时便不存在$p_0>n^{\frac{1}{4}}$，即不存在当$p_0>n^{\frac{1}{4}}$时，存在$\frac{n}{p_0} = a*b*c$使$n = p_0 * a * b *c$成立的等式。

综上，$p_0\leq n^{\frac{1}{4}}\ or\ p_0>n^{\frac{1}{4}}$都是存在的，但$ap\leq \sqrt{n}\ or\ ap $是素数均成立。证明**分解**的必要性在于$ap$不是素数则必然是合数，若$ap>\sqrt{n}$，则由**分解**递推得来的三个因子不符合定理1，即希望由递推得到的就是正好满足引理1而不需额外操作。

```cpp
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

```

# 矩阵快速幂

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int P = 1000000007;
using i64 = long long;
// assume -P <= x < 2P
int norm(int x) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}
template <class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0)
        : x(norm(x)) {}
    int val() const { return x; }
    Z operator-() const { return Z(norm(P - x)); }
    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z& operator*=(const Z& rhs) {
        x = i64(x) * rhs.x % P;
        return *this;
    }
    Z& operator+=(const Z& rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z& operator-=(const Z& rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z& operator/=(const Z& rhs) { return *this *= rhs.inv(); }
    friend Z operator*(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
};
struct mat {
    int n, m;
    vector<vector<Z>> c;
    mat(int a, int b)
        : n(a), m(b) {
        c = vector<vector<Z>>(n, vector<Z>(m));
    }
    void clear() {
        c = vector<vector<Z>>(n, vector<Z>(m));
    }
    vector<Z>& operator[](int x) {
        return c[x];
    };
    mat
    operator*(mat temp) {
        mat ans(n, temp.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < temp.m; j++) {
                for (int k = 0; k < m; k++) {
                    ans.c[i][j] += c[i][k] * temp.c[k][j];
                }
            }
        }
        return ans;
    }
    friend mat operator^(mat M, i64 n) {
        mat ans(M.n, M.n);
        for (int i = 0; i < M.n; i++) {
            ans.c[i][i] = 1;
        }
        while (n > 0) {
            if (n & 1) {
                ans = ans * M;
            }
            M = M * M;
            n >>= 1;
        }
        return ans;
    }
};
```

## 一些习题

### [NOI2013]矩阵游戏

给定：

$F[1][1]=1$
$F[i, j]=a \times F[i][j-1]+b(j \neq 1)$
$F[i, 1]=c \times F[i-1][m]+d(i \neq 1)$

求$n,m$。

这个式子可以求通项。本质是递推转通项式。需要特判。



# 卡特兰数

具体的先不细写。。

## 递推式及通项

$H_n = \sum\limits_{i=0}^{n-1}H_{n-i-1}H_{i}$

$H_n = \frac{2n!}{n!(n+1)!}$

## 开头若干项

有时打表容易注意到这样的数列：

$1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440$

这即是卡特兰数 $H_n = \frac{2n!}{n!(n+1)!}$ ​的开头若干项。

### P1641 [SCOI2010]生成字符串

卡特兰数问题可以转化成折线问题：将非法的线段按y=-1对称后，可以视为从点(0,-2)点出发沿任意路径到原本终点。故该题答案为$\dbinom{n}{n+m} - \dbinom{n+1}{n+m}$。

### P2155 [SDOI2008]沙拉公主的困惑

。。写题解时又忘记怎么写了。

答案为$\sum\limits_{i=1}^{N!}[\operatorname{gcd}(i,M!)=1]$。这里注意N>M，所以$M!|N!$。

考虑到$[1,M!],[M!+1,2M!],\dots,[(\frac{N!}{M!}-1)*M!+1,N!]$每个区间的i的答案都是一样的，仅算一个。

于是有答案$ans = \frac{N!}{M!} * \varphi(M!) = \frac{N!}{M!} M! \prod\limits_{p|M!}\frac{p-1}{p} = N!\prod\limits_{p|M!}\frac{p-1}{p}$，后者可以线性筛筛出。

有些细节，具体看[小粉兔的题解](https://www.luogu.com.cn/problem/solution/P2155)。

# 康托/逆康托展开（Cantor expansion）

将排列与自然数建立双射关系。

## 康托展开

定义长度为$n$的排列集中$1,2,\dots,n$编号为0。此时对于排列$P_1,P_2,\dots,P_n$的编号为$a_1 (n-1)! + a_2(n-2)!\dots a_n(0)!$，其中$a_i$为 **现存可取数中比$P_i$小的数的个数** 。

> 比如$4,2,3,1$：
>
> 1. 当前可取数为{1,2,3,4}。比4小的有3个，则编号$+3*(4-1)! = 18$。去掉4。
> 2. 当前可取数为{1,2,3}。比2小的有1个，则编号$+1*2! = 2$。去掉2。
> 3. 当前可取数为{1,3}。比3小的有1个，则编号$+1*1! = 1$。去掉3。
> 4. 当前可取数为{1}。比1小的有0个，则编号$+0*0! = 0$。故当前排列编号为21。
>
> 通俗来说就是在可取的数集里存在比当前的数小的数，则让该数处在该位，后面任意排列都比当前排列的字典序小。按位统计即可。

由于每次都是统计比自己数小的存在的数，故用BIT优化就能达到$O(n\log n)$。

## 逆康托展开

很简单，逆着来就行了。

把数顺序扔进平衡树里。比如当前确定第i个数，将编号除$(n-i)!$，商+1（记作第j大）则为当前该确定的数，余数则用来确定后面的数。每次确定完后，要从平衡树里删掉第j大的数。复杂度$O(n\log n)$。

# 扩展欧拉定理 & 原根

## 扩展欧拉定理（用于降幂）

$$
a^{c} \equiv\left\{\begin{array}{ll}
a^{c \% \varphi(p)}, & \operatorname{gcd}(a, p)=1 \\
a^{c}, & \operatorname{gcd}(a, p) \neq 1, c<\varphi(p) \quad(\bmod p) \\
a^{c \% \varphi(p)+\varphi(p)}, & \operatorname{gcd}(a, p) \neq 1, c \geq \varphi(p)
\end{array}\right.
$$

## 代码（高精度）

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct BigInt {  // a = 0时size = 0
    vector<int> a;
    BigInt() { a = {}; }
    BigInt(int a0) {
        a = vector<int>();
        while (a0) {
            a.emplace_back(a0 % 10);
            a0 /= 10;
        }
    }
    BigInt(const std::string& s0) {
        int n = s0.length();
        a = vector<int>(n);
        for (int i = n - 1; i >= 0; i--) {
            a[n - i - 1] = s0[i] - '0';
        }
        while (!a.empty() && !a.back())
            a.pop_back();
    }
    BigInt(const std::vector<int>& a1) : a(a1) {
        while (!a.empty() && !a.back())
            a.pop_back();
    }
    int size() const { return a.size(); }
    int operator[](int idx) const {
        if (idx < 0 || idx >= size())
            return 0;
        return a[idx];
    }
    i64 get() {  //前提是BigInt在i64范围内
        i64 num = 0;
        for (int i = (int)a.size() - 1; i >= 0; i--) {
            num = num * 10 + a[i];
        }
        return num;
    }
    friend BigInt operator/(const BigInt& x, int y)  //低精除，返回商
    {
        assert(y != 0);
        i64 r = 0;
        vector<int> b(x.size());
        for (int i = (int)x.a.size() - 1; i >= 0; i--) {
            r = r * 10 + x[i];
            if (r >= y) {
                b[i] = r / y;
                r %= y;
            } else {
                b[i] = 0;
            }
        }
        return BigInt(b);
    }
    friend i64 operator%(const BigInt& x, int y)  //低精除，返回余数
    {
        assert(y != 0);
        i64 r = 0;
        for (int i = (int)x.a.size() - 1; i >= 0; i--) {
            r = r * 10 + x[i];
            if (r >= y) {
                r %= y;
            }
        }
        return r;
    }
    friend bool operator<(const BigInt& x,
                          const BigInt& y)  // x>y:1 x==y:0 x<y:-1
    {
        if (x.size() != y.size()) {
            return x.size() < y.size();
        }
        for (int i = (int)x.size() - 1; i >= 0; i--) {
            if (x[i] != y[i]) {
                return x[i] < y[i];
            }
        }
        return 0;
    }
};  // namespace BigInt

i64 power(i64 base, i64 n, int P) {
    i64 res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= P;
        (base *= base) %= P;
        n >>= 1;
    }
    return res;
}

i64 ExEuler(BigInt base, BigInt n, i64 P) {  //只适用于i32的P，除非power上光速幂
    i64 phi;
    {
        phi = P;
        i64 N = P;
        for (i64 i = 2; i * i <= N; i++)
            if (N % i == 0) {
                phi = phi / i * (i - 1);
                while (N % i == 0)
                    N /= i;
            }
        if (N > 1)
            phi = phi / N * (N - 1);
    }
    i64 Base = base % P, N;  //只要取模的余数，不改变被除数
    BigInt Phi(phi);
    if (n < Phi) {
        N = n % phi;
    } else {
        N = n % phi + phi;
    }
    return power(Base, N, P);
}

int main() {//a^b \bmod P
    string a, b;
    int P;
    cin >> a >> P >> b;
    cout << Ex(a, b, P) << "\n";
    return 0;
}
```

### 原根的个数

若存在一个原根 $g$，根据 $a^l\equiv 1(\%p)$ 的理论，跟 $g$ 同阶的个数有 $\varphi(l = p-1)$。由于非质数也存在原根，一般情况则是：存在原根 $g$，那么所有原根就是$\{g^s|s\in[1,\varphi(m)],(s,\varphi(m))=1\}$

### 求一个原根

$(g, m)=1$，设 $p_{1}, p_{2}, \cdots, p_{k}$ 是 $\varphi(m)$ 的所有不同的素因数，则 $g$ 是 $m$ 的原根，当且仅当对任意 $1 \leq i \leq k$，都有 $g^{\frac{\varphi(m)}{p_{i}}} \not \equiv 1(\bmod m)$。

王元于 1959 年证明了若 $m$ 有原根，其最小原根是不多于 $m^{0.25}$ 级别的。此处略去证明。这保证了我们暴力找一个数的最小原根，复杂度是可以接受的。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int mod = 1e9 + 7;

ll power(ll a, int b, int p = mod) {
    ll res = 1;
    for (; b; b /= 2, a *= a, a %= p) {
        if (b % 2) {
            res *= a;
            res %= p;
        }
    }
    return res;
}

/*
首先，一个正整数 n 有原根的充要条件是 n=2,4,p^e,2p^e，其中，p奇素数，e为正整数。
当保证有原根时，对于原根g，满足对于所有phi的素因子{p_i}，都有g^{\frac{phi}{p_i}}!=
1(\mod p) 所以从小到大枚举g，就得出g是多少。常见的原根都很小
*/

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

int main() {
    int T;
    int P;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &P);
        int g = generator(P);
        printf("%d\n", g);
    }
    return 0;
}
```

## 一些习题

### P4139 上帝与集合的正确用法

大概长这样：

对于任意 $b \geq \varphi(p)$，有：
$$
a^{b} \equiv a^{b \bmod \varphi(p)+\varphi(p)}(\bmod p)
$$
当 $b<\varphi(p)$ 时有 $a^{b} \equiv a^{b \bmod \varphi(p)}(\bmod p)$

其中 $a, p$ 可以不互质。

有了这个式子，题目中的 $2^{2^{2^{2}}} \bmod p$ 就很好求了，照着上面的式子递归至 mod p = 1 就行。这里要注意应用条件：这里的指数 $b=2^{2^{2^{2}}}$ 是满足 $b \geq \varphi(p)$ 的， 于是可以直接用第一个式子。

### P4549 【模板】裴蜀定理

裴蜀定理即 $ax+by=c$ 的 <x,y> 解。

### CF1184A3 Heidi Learns Hashing (Hard)

给定一个哈希运算，对于串 $w$ 的运算结果为 $H_{p}(w)=\sum\limits_{i=0}^{|w|-1} w_{i} r^{i} \bmod p$ 。给定长为 $n$ 的两个串 $s_1,s_2$，求一对 $<r,p>$ 满足 $H_p(s_1) = H_p(s_2)$。$p\geq m$。

考虑串对应字符做差，原问题等价于求一组 $<r,p>$ 使等式 $\sum\limits_{i=0}^{n-1}(a_i - b_i)r^i \equiv 0(\bmod p)$，这里记 $c_i = (a_i - b_i)$。先考虑一个非常暴力但正确的思路：枚举大于等于下界 $m$ 的质数 $p$，然后枚举 $r\in[2,p-2]$，求对应多项式 $f(x) = \sum\limits_{i=0}^{n-1}c_ix^i$ 的点值，只要有一个 $r$ 对应点值等于 0，则其为答案。

对于 **随机** 输入的 $r$，将 $f(r)$ 也视作在 $[0,p-1]$ 上的 **随机** 输出。即我们选定一个素数 $p$，如果将 $f(r)$ 视作随机数，那么对于 $r\in[2,p-2]$，所有点值都不等于 0 的概率为 $(1-\frac{1}{p})^p \approx e^{-1} \approx \frac{1}{3}$。由于下界 $m\leq 1e5$，视 $ p$ 是 $1e5$ 规模的，大概取几次 $p$ ，求对应点值，就有可能找到一个点值是 0。

普通求点值的复杂度 $O(n^2)$，而若是能把 $r^i$ 相同的项并在一起计算，复杂度可降低不少。

从数论的角度思考， $r^i \equiv r^{i+k}(\bmod p)$ ，即等同于 $r^k\equiv 1(\bmod p)$ 。根据 **阶** 的理论，设 r 对 p 的阶为 d，则 k 是 d 的倍数。同时阶又整除 $\varphi(p)$，即 $r^d\equiv r^{\varphi(p)}(\bmod p)$。从这个启发，若能找到一个非 1 的值 $x$，满足 $x \equiv r^{\frac{\varphi(p)}{d}} \ne 1(\bmod p)$，$x^d\equiv 1(\bmod p)$， 则此时可以把多项式缩成 $O(d)$ 的长度，多点求值的复杂度就降至 $O(d^2)$ 了。

那么整个算法的流程就很清晰了：

> 1. 选取一个 $d$（推荐从小到大的质数，比如 $3,5,7,11,\dots$），然后生成一个质数 $p = kd + 1,p\ is\ prime \land p\geq m$
>
> 2. 按模 $d$ 合并多项式的同余项，得到 $f(x) = \sum\limits_{i=0}^{d-1}\alpha_ix^i$
>
> 3. 在$[2,p-2]$下 random 一个$r_0$，使得$r_0^{\frac{p-1}{d}}\neq 1(\bmod p)$，令$r = r_0^{\frac{p-1}{d}}$
>
> 4. 求$f(x)$在 $r,r_2,\dots,r^d$ 下的点值，有一个为 0 即结束，否则重复1,2,3。

# 类欧几里得

类欧几里德算法由洪华敦在 2016 年冬令营营员交流中提出的内容，其本质可以理解为，使用一个类似辗转相除法来做函数求和的过程。

## 引入

设

$$
f(a,b,c,n)=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor
$$

其中 $a,b,c,n$ 是常数。需要一个 $O(\log n)$ 的算法。

这个式子和我们以前见过的式子都长得不太一样。带向下取整的式子容易让人想到数论分块，然而数论分块似乎不适用于这个求和。但是我们是可以做一些预处理的。

如果说 $a\ge c$ 或者 $b\ge c$，意味着可以将 $a,b$ 对 $c$ 取模以简化问题：

$$
\begin{split}
f(a,b,c,n)&=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor\\
&=\sum_{i=0}^n\left\lfloor
\frac{\left(\left\lfloor\frac{a}{c}\right\rfloor c+a\bmod c\right)i+\left(\left\lfloor\frac{b}{c}\right\rfloor c+b\bmod c\right)}{c}\right\rfloor\\
&=\frac{n(n+1)}{2}\left\lfloor\frac{a}{c}\right\rfloor+(n+1)\left\lfloor\frac{b}{c}\right\rfloor+
\sum_{i=0}^n\left\lfloor\frac{\left(a\bmod c\right)i+\left(b\bmod c\right)}{c}
\right\rfloor\\
&=\frac{n(n+1)}{2}\left\lfloor\frac{a}{c}\right\rfloor
+(n+1)\left\lfloor\frac{b}{c}\right\rfloor+f(a\bmod c,b\bmod c,c,n)
\end{split}
$$

那么问题转化为了 $a<c,b<c$ 的情况。观察式子，你发现只有 $i$ 这一个变量。因此要推就只能从 $i$ 下手。在推求和式子中有一个常见的技巧，就是条件与贡献的放缩与转化。具体地说，在原式 $\displaystyle f(a,b,c,n)=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor$ 中，$0\le i\le n$ 是条件，而 $\left\lfloor \dfrac{ai+b}{c} \right\rfloor$ 是对总和的贡献。

要加快一个和式的计算过程，所有的方法都可以归约为 **贡献合并计算**。但你发现这个式子的贡献难以合并，怎么办？**将贡献与条件做转化** 得到另一个形式的和式。具体地，我们直接把原式的贡献变成条件：

$$
\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor
=\sum_{i=0}^n\sum_{j=0}^{\left\lfloor \frac{ai+b}{c} \right\rfloor-1}1\\
$$

现在多了一个变量 $j$，既然算 $i$ 的贡献不方便，我们就想办法算 $j$ 的贡献。因此想办法搞一个和 $j$ 有关的贡献式。这里有另一个家喻户晓的变换方法，笔者概括为限制转移。具体来说，在上面的和式中 $n$ 限制 $i$ 的上界，而 $i$ 限制 $j$ 的上界。为了搞 $j$，就先把 j 放到贡献的式子里，于是我们交换一下 $i,j$ 的求和算子，强制用 $n$ 限制 $j$ 的上界。

$$
\begin{split}
&=\sum_{j=0}^{\left\lfloor \frac{an+b}{c} \right\rfloor-1}
\sum_{i=0}^n\left[j<\left\lfloor \frac{ai+b}{c} \right\rfloor\right]\\
\end{split}
$$

这样做的目的是让 $j$ 摆脱 $i$ 的限制，现在 $i,j$ 都被 $n$ 限制，而贡献式看上去是一个条件，但是我们仍把它叫作贡献式，再对贡献式做变换后就可以改变 $i,j$ 的限制关系。于是我们做一些放缩的处理。首先把向下取整的符号拿掉

$$
j<\left\lfloor \frac{ai+b}{c} \right\rfloor
\iff j+1\leq \left\lfloor \frac{ai+b}{c} \right\rfloor
\iff j+1\leq \frac{ai+b}{c}\\
$$

然后可以做一些变换

$$
j+1\leq \frac{ai+b}{c} \iff jc+c\le ai+b \iff jc+c-b-1< ai
$$

最后一步，向下取整得到：

$$
jc+c-b-1< ai\iff \left\lfloor\frac{jc+c-b-1}{a}\right\rfloor< i
$$

这一步的重要意义在于，我们可以把变量 $i$ 消掉了！具体地，令 $m=\left\lfloor \frac{an+b}{c} \right\rfloor$，那么原式化为

$$
\begin{split}
f(a,b,c,n)&=\sum_{j=0}^{m-1}
\sum_{i=0}^n\left[i>\left\lfloor\frac{jc+c-b-1}{a}\right\rfloor \right]\\
&=\sum_{j=0}^{m-1}
(n-\left\lfloor\frac{jc+c-b-1}{a}\right\rfloor)\\
&=nm-f\left(c,c-b-1,a,m-1\right)
\end{split}
$$

这是一个递归的式子。并且你发现 $a,c$ 分子分母换了位置，又可以重复上述过程。先取模，再递归。这就是一个辗转相除的过程，这也是类欧几里德算法的得名。

容易发现时间复杂度为 $O(\log n)$。

## 扩展

理解了最基础的类欧几里德算法，我们再来思考以下两个变种求和式：

$$
g(a,b,c,n)=\sum_{i=0}^ni\left\lfloor \frac{ai+b}{c} \right\rfloor\\
h(a,b,c,n)=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor^2
$$

### 推导 g

我们先考虑 $g$，类似地，首先取模：

$$
g(a,b,c,n)
=g(a\bmod c,b\bmod c,c,n)+\left\lfloor\frac{a}{c}\right\rfloor\frac{n(n+1)(2n+1)}{6}+\left\lfloor\frac{b}{c}\right\rfloor\frac{n(n+1)}{2}
$$

接下来考虑 $a<c,b<c$ 的情况，令 $m=\left\lfloor\frac{an+b}{c}\right\rfloor$。之后的过程我会写得很简略，因为方法和上文略同：

$$
\begin{split}
&g(a,b,c,n)=\sum_{i=0}^ni\left\lfloor \frac{ai+b}{c} \right\rfloor\\
&=\sum_{j=0}^{m-1}
\sum_{i=0}^n\left[j<\left\lfloor\frac{ai+b}{c}\right\rfloor\right]\cdot i
\end{split}
$$

这时我们设 $t=\left\lfloor\frac{jc+c-b-1}{a}\right\rfloor$，可以得到

$$
\begin{split}
&=\sum_{j=0}^{m-1}\sum_{i=0}^n[i>t]\cdot i\\
&=\sum_{j=0}^{m-1}\frac{1}{2}(t+n+1)(n-t)\\
&=\frac{1}{2}\left[mn(n+1)-\sum_{j=0}^{m-1}t^2-\sum_{j=0}^{m-1}t\right]\\
&=\frac{1}{2}[mn(n+1)-h(c,c-b-1,a,m-1)-f(c,c-b-1,a,m-1)]
\end{split}
$$

### 推导 h

同样的，首先取模：

$$
\begin{split}
h(a,b,c,n)&=h(a\bmod c,b\bmod c,c,n)\\
&+2\left\lfloor\frac{b}{c}\right\rfloor f(a\bmod c,b\bmod c,c,n)
+2\left\lfloor\frac{a}{c}\right\rfloor g(a\bmod c,b\bmod c,c,n)\\
&+\left\lfloor\frac{a}{c}\right\rfloor^2\frac{n(n+1)(2n+1)}{6}+\left\lfloor\frac{b}{c}\right\rfloor^2(n+1)
+\left\lfloor\frac{a}{c}\right\rfloor\left\lfloor\frac{b}{c}\right\rfloor n(n+1)
\end{split}
$$

考虑 $a<c,b<c$ 的情况，$m=\left\lfloor\dfrac{an+b}{c}\right\rfloor, t=\left\lfloor\dfrac{jc+c-b-1}{a}\right\rfloor$.

我们发现这个平方不太好处理，于是可以这样把它拆成两部分：

$$
n^2=2\dfrac{n(n+1)}{2}-n=\left(2\sum_{i=0}^ni\right)-n
$$

这样做的意义在于，添加变量 $j$ 的时侯就只会变成一个求和算子，不会出现 $\sum\times \sum$ 的形式：

$$
\begin{split}
&h(a,b,c,n)=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor^2
=\sum_{i=0}^n\left[\left(2\sum_{j=1}^{\left\lfloor \frac{ai+b}{c} \right\rfloor}j \right)-\left\lfloor\frac{ai+b}{c}\right\rfloor\right]\\
=&\left(2\sum_{i=0}^n\sum_{j=1}^{\left\lfloor \frac{ai+b}{c} \right\rfloor}j\right) -f(a,b,c,n)\\
\end{split}
$$

接下来考虑化简前一部分：

$$
\begin{split}
&\sum_{i=0}^n\sum_{j=1}^{\left\lfloor \frac{ai+b}{c} \right\rfloor}j\\
=&\sum_{i=0}^n\sum_{j=0}^{\left\lfloor \frac{ai+b}{c} \right\rfloor-1}(j+1)\\
=&\sum_{j=0}^{m-1}(j+1)
\sum_{i=0}^n\left[j<\left\lfloor \frac{ai+b}{c} \right\rfloor\right]\\
=&\sum_{j=0}^{m-1}(j+1)\sum_{i=0}^n[i>t]\\
=&\sum_{j=0}^{m-1}(j+1)(n-t)\\
=&\frac{1}{2}nm(m+1)-\sum_{j=0}^{m-1}(j+1)\left\lfloor \frac{jc+c-b-1}{a} \right\rfloor\\
=&\frac{1}{2}nm(m+1)-g(c,c-b-1,a,m-1)-f(c,c-b-1,a,m-1)
\end{split}
$$

因此

$$
h(a,b,c,n)=nm(m+1)-2g(c,c-b-1,a,m-1)-2f(c,c-b-1,a,m-1)-f(a,b,c,n)
$$

在代码实现的时侯，因为 $3$ 个函数各有交错递归，因此可以考虑三个一起整体递归，同步计算，否则有很多项会被多次计算。这样实现的复杂度是 $O(\log n)$ 的。

??? note "[模板题代码实现](https://www.luogu.com.cn/problem/P5170)"
    ```cpp
    #include <bits/stdc++.h>
    #define int long long
    using namespace std;
    const int P = 998244353;
    int i2 = 499122177, i6 = 166374059;
    

~~~cpp
struct data {
  data() { f = g = h = 0; }

  int f, g, h;
};  // 三个函数打包

data calc(int n, int a, int b, int c) {
  int ac = a / c, bc = b / c, m = (a * n + b) / c, n1 = n + 1, n21 = n * 2 + 1;
  data d;
  if (a == 0) {  // 迭代到最底层
    d.f = bc * n1 % P;
    d.g = bc * n % P * n1 % P * i2 % P;
    d.h = bc * bc % P * n1 % P;
    return d;
  }
  if (a >= c || b >= c) {  // 取模
    d.f = n * n1 % P * i2 % P * ac % P + bc * n1 % P;
    d.g = ac * n % P * n1 % P * n21 % P * i6 % P + bc * n % P * n1 % P * i2 % P;
    d.h = ac * ac % P * n % P * n1 % P * n21 % P * i6 % P +
          bc * bc % P * n1 % P + ac * bc % P * n % P * n1 % P;
    d.f %= P, d.g %= P, d.h %= P;

    data e = calc(n, a % c, b % c, c);  // 迭代

    d.h += e.h + 2 * bc % P * e.f % P + 2 * ac % P * e.g % P;
    d.g += e.g, d.f += e.f;
    d.f %= P, d.g %= P, d.h %= P;
    return d;
  }
  data e = calc(m - 1, c, c - b - 1, a);
  d.f = n * m % P - e.f, d.f = (d.f % P + P) % P;
  d.g = m * n % P * n1 % P - e.h - e.f, d.g = (d.g * i2 % P + P) % P;
  d.h = n * m % P * (m + 1) % P - 2 * e.g - 2 * e.f - d.f;
  d.h = (d.h % P + P) % P;
  return d;
}

int T, n, a, b, c;

signed main() {
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
    data ans = calc(n, a, b, c);
    printf("%lld %lld %lld\n", ans.f, ans.h, ans.g);
  }
  return 0;
}
```
~~~

# 离散对数&BSGS

## 离散对数

在实数领域，对数定义由 $a^x = b\Rightarrow x = log_ab$ 而来。

在模系，考虑底数为原根 g 的同余方程 $x\equiv g^b(\%p)$ ：此时离散对数 $Ind_gx\equiv b(\%\varphi(p))$ 。

举个模 5 的例子， $3^1\equiv 3(\%5),3^2\equiv 4(\%5),3^3\equiv 2(\%5),3^4\equiv 1(\%5)$ ，则 3 是模 5 下的原根。

那么有： $Ind_31 = 0(\%4),Ind_32 = 3(\%4),Ind_33 = 1(\%4),Ind_34 = 2(\%4)$ 

离散对数同样具有幂转系数，加乘减除的性质。

有了离散对数，可以处理含高次项的同余方程，对于底数为原根，原理一定成立。

预处理可以通过不断叠原根 $g$ 来映射每个值的离散对数（即指数）。直接求的话则可以用 BSGS $O(\sqrt{p})$ 求解。

## BSGS

### 基础

$O(\sqrt{p})$ 解 $a^x\equiv b(\%p),(a,p)=1 $

流程：

令 $x=A\lceil\sqrt{p}\rceil-B, $ 其中 $ 0 \leq A, B \leq\lceil\sqrt{p}\rceil, $ 则有 $a^{A\lceil\sqrt{p}\rceil-B} \equiv b(\bmod p) \Leftrightarrow a^{A*\lceil\sqrt{p}\rceil} \equiv b a^{B}(\bmod p)$

枚举 B，存 $ba^B$ 入hash里，枚举A查$a^{A*\lceil\sqrt{p}\rceil}$是否在hash里，如果存在，得到得到特解$x = A\lceil\sqrt{p}\rceil-B$

关于约束条件$(a,p)=1$、、如果$(a,p)\ !=1$，则$a$可能不存在逆元、、而推导的等价式子中回推时需要逆元的运算，故基础解法需保证$(a,p)=1$

基于上述算法，便可以 $O(\sqrt{p})$ 算出某数 a 的阶，即 $a^x = 1(\bmod p)$ 。

### 进阶

解 $x^a\equiv b(\%p),p$ 是质数。

质数必有原根 $g$ ，令 $x \equiv g^c(\%p)$ ，则有原式 $(g^c)^a\equiv b(\%p)\Rightarrow (g^a)^c\equiv b(\%p)$

$a,b$是已知数，套用熟悉的BSGS解得特解$c$，则$x = g^c$、、

另一种方法利用离散对数，$x \equiv g^c,b \equiv g^d\Rightarrow g^{ac}\equiv g^d(\%p)\Rightarrow ac\equiv d(\%\varphi(p))$

关于未知数$d$可用BSGS来求，原始则用$exgcd$来做、、

### 通解

注意，这里是 $x^a\equiv b(\%p)$ 的通解。

$a^x\equiv b(\%p),(a,p)=1$ 的通解是什么在**扩展**那有写。

求得$x\equiv g^c(\%p)$、、根据欧拉定理有$g^{\varphi(p)}\equiv 1(\%p)$

原式$x^a\equiv b\equiv g^{ac}\equiv g^{ac + k\varphi(p)}(\%p),$整数$k$满足$a|k\varphi(p)$

由于$x$存在逆元，$x\equiv g^{c+\frac{k\varphi(p)}{a}}(\%p)$

要找到通解，就要找最小正间距、、$\frac{k\varphi(p)}{a}\in Z,k\in Z$，~~易想到~~$k$的形式$k = \frac{a}{h}$（找最小正间距等价让$k$尽量小）

由$h|a,a*h|a*\varphi(p)=h|\varphi(p)$，可得最大的可行$h = (a,\varphi(p))$

故通解$x = g^{c+k*\frac{\varphi(p)}{gcd(\varphi(p),a)}}$

### 扩展

解决 $a^x\equiv b(\%p),(a,p)\ !=1$ ：尽量让底数 $a$ 与模数互质，转化成 BSGS 。

提一个 $a$ ，除一个 $d_1 = (a,p) $ 方程为 $\frac{a}{d_1}*a^{x-1}\equiv \frac{b}{d_1}(\%\frac{p}{d_1})$，当然若 $d_1\nmid b$ ，则无解

此时 $(\frac{a}{d_1},\frac{p}{d_1})=1$ ，可以将 $\frac{a}{d_1}$ 除过去，但若$(a,\frac{p}{d_1})\ !=1$，问题仍没解决。

故重复除 $(a,\frac{p}{d_1d_2...})$ 直到 $(a,\frac{p}{d_1d_2...d_k})=1$

$\frac{a}{d'}*a^{x-o}\equiv \frac{b}{d'}(\%\frac{p}{d'})$ 的过程中，若$\frac{a}{d'} = \frac{b}{d'}$时，由于$gcd(\frac{a}{d'},\frac{p}{d'})=1,$故此时的解为$x = o$，且只有唯一解、、

等$gcd(a,\frac{p}{d'})=1$后，处在环中，则bsgs求出一个特解$x'$后，用$bsgs(a,1,\frac{p}{d'})$求出$a$在模$\frac{p}{d'}$的阶$H$（正整数），则通解$x = x' + k*H$，此时有无数解。

猜测不断约$d'$的过程中环的几何结构不发生变化，仅跟$gcd(\frac{p}{d'},a)=1$的$\frac{p}{d'}$大小有关。~~但无证明。~~

感性证明：对于$(a,p)>1$，$(a^k,p)$随着$k$的增大达到最值对应的$k’$，此时$k$增大不改变gcd内值。

转化成等价式：$a^o - \frac{b}{a^{k’}} = q * \frac{p}{a^{k’}}\Rightarrow a^o \equiv \frac{b}{a^{k’}} (\%\frac{p}{a^{k’}})$、、这个底数$a$关于$p’$的$(a,p’)$环问题不就等价于边除的几何结构、、

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef long long ll;
constexpr int mod = 1e9 + 7;

template <class T>
T power(T a, int b, int p = mod) {
    T res = 1;
    for (; b; b /= 2, a *= a, a %= p) {
        if (b % 2) {
            res *= a;
            res %= p;
        }
    }
    return res;
}

/*
用于解一元同余高次方程a^x = b(\mod p)，且gcd(a,p) = 1
的最小非负整数解。无解输出-1 。gcd(a,p)!=1，由于推导式子不等价，会得出错误结果
*/
int bsgs(int a, int b, int p)  //应该记住的版本
{
    unordered_map<int, int> m;
    int sq = ceil(sqrt(p));
    i64 base = 1;
    for (int i = 1; i <= sq; i++) {
        base = base * a % p;
        m[b * base % p] = i;
    }
    int res = 1;
    for (int i = 1; i <= sq; i++) {
        res = res * base % p;
        if (m.count(res)) {
            return i * sq - m[res];
        }
    }
    return -1;
}

//求x^a = b (%p),p是素数的公式。用时将其放入 BSGS 中
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
/*
求x^a = b(\bmod p),且p是素数（保证了gcd(a,p)=1且p有原根）的公式。
假设x = g^c，则(g^c)^a=b(\bmod p) -> (g^a)^c=b(\bmod p)
使用bsgs求出特解c，则求出x=g^c
通解是x = g^{ c + k * \frac{\varphi(p)}{gcd(\varphi(p),a)} }
*/
i64 formula1(int a, int b, int p) {
    int g = generator(p);
    int c = bsgs(power(g, a, p), b, p);
    if (c == -1) {
        return -1;
    }
    return power(g, c, p);
}

/*
求解 a^x=b(\bmod p)，gcd(a,p)!=1的情况
通过提取a，来尽量使 p / d'与 a 互质，其中d' = gcd(a^k,p)
如果合法地得到该式：A*a^{x-o}\equiv \frac{b}{d'}(\bmod \frac{p}{d'}) ，其中A =
\frac{a}{d'} 当\frac{a}{d'} = \frac{b}{d'}：此时x有唯一解x； 否则有无穷解x = x'
+ k*H，其中x’是上式用bsgs解出的特解，H是bsgs(a,1,\frac{p}{d'})解出的解
*/

ll ExBsgs(int a, int b, int p) {
    ll A = 1, o = 0;
    {
        ll div;
        while ((div = __gcd(a, p)) != 1) {
            if (A == b) {
                return o;
            }
            if (b % div != 0) {
                return -1;
            }
            b /= div;
            p /= div;
            A = A * a / div % p;
            o++;
        }
    }
    int phi = p;
    {
        int tmp = p;
        for (int i = 2; i * i <= tmp; i++) {
            if (tmp % i == 0) {
                phi = phi / i * (i - 1);
                while (tmp % i == 0)
                    tmp /= i;
            }
        }
        if (tmp > 1) {
            phi = phi / tmp * (tmp - 1);
        }
    }
    int X = bsgs(a, b * power(A, phi - 1, p) % p, p);
    // X是特解
    int H = bsgs(a, 1, p);  // H是最小间距，也即a的阶
    return X == -1 ? -1 : X + o;
}

```



## 一些习题

### P3306 [SDOI2013] 随机数生成器

有一本页数$0\sim p-1$的书，每天读一页。决定第一天阅读的页数$x_1$,第$i$天阅读的页数由公式$x_{i} \equiv a*x_{i-1}+b(\%p)$决定。

问最早读到第$k$页是第几天，或者永远不会读到。



首先$p$是质数，在实数域上面方程明显是类等比数列，设$x_i+c \equiv a*(x_{i-1}+c)\Rightarrow c(a-1)\equiv b(\%p),c\equiv b*inv_{a-1}(\%p)$（*）

有$x_{i+1}+c\equiv a^i(x_1+c)(\%p)\Rightarrow a^i\equiv(x^{i+1}+c)*inv_{x_1+c}(\%p)$（*）

令$x^{i+1}=k$，求出的$i+1$即是答案。

考虑特例，包括式子的*、、

1、$x_1=k$，返回1。

2、当$a=0$，如果$b=k$，返回2，否则无解。

3、当$a=1$，$a-1$无逆元，式子$x_{i+1} \equiv x_1 + i*b(\%p)$，用$exgcd$求$i$。

4、当$(x_1+c)\%p=0$，如果$p-c=k$，返回2，否则无解。

5、一般情况，用BSGS求解即可。

###  CodeForces - 1106F Lunar New Year and a Recursive Sequence

现有个递推式$f_{i}=\left(f_{i-1}^{b_{1}} \cdot f_{i-2}^{b_{2}} \cdots \cdot f_{i-k}^{b_{k}}\right) \bmod p$

给定$f_n = m,$及$f_1 = f_2 = ... = f_{k-1} = 1$（当然还有$\{b_i\}$），求$f_k$的取值，多个答案输出一个，无答案输出-1。



由于递推式是累乘形式，套个对数得$Ind_{f_{i+1}} = \sum\limits_{j=1}^{k}b_jInd_{f_{i+1-j}}(\%\varphi(p))$

由于原根g可表示$[0,p)$的数，$g^c\equiv m(\%p)\Rightarrow c$即为$Ind_{f_{i+1}}$的值，用$BSGS$做一做。

递推式展成多项式，构造矩阵用矩阵快速幂求出关于$f_n$的等式，可以用exgcd来做、、

记得矩阵快速幂模数为$\varphi(p)$。

### P5345 【XR-1】快乐肥宅

一道能~~卡死你~~帮助理解BSGS和扩展CRT的题目。

解决诸如$k_i^x \equiv r_i(\%g_i)$的方程组的解，且解要小于等于$U = 1e9$

形如$ex\_BSGS$的方程组形式实质有三类解：唯一解，无限解，无解。具体在**扩展**那有写，，即链上唯一解，环中无限解（搭配$minX$,最小符合解和$H$,环的阶），以及无解。

求出每个方程的解，将无限解扔入$ex\_CRT$求解，，由于题目要求解不大于$U$，当合并到模数$N_{i-1}>U$，且当前的最小非负解$x_{i-1}\neq a_i$，则一定在范围内无解、、由于$x_{i-1}\neq a_i$，则前面方程必定要和当前方程合并，，合并后$x_i = x_{i-1} + N_{i-1}*p(\%N_{i})$（详细在$CRT$章节）、、由于$x_{i-1}<N_{i-1},p\neq0$，不论$p$的取值如何得到的$x_i$都不在满足条件的区间内，此时就可以判无解了。

合并完求完解，再和唯一解的关系处理一下，该题就做完了，，大概是个$ex\_BSGS$和$ex\_CRT$的深入理解题目。

# 莫比乌斯反演

## 前置知识

### 引理1

$\left\lfloor \frac{a}{bc} \right\rfloor = \left\lfloor \frac{\left\lfloor\frac{a}{b}\right\rfloor}{c} \right\rfloor$



证明：$\frac{a}{c} = \left\lfloor \frac{a}{c} \right\rfloor + r,r\in[0,1)$、、

$\left\lfloor \frac{a}{bc} \right\rfloor = \left\lfloor \frac{a}{b}*\frac{1}{c} \right\rfloor = \left\lfloor \frac{(\left\lfloor\frac{a}{b}\right\rfloor + r)}{c} \right\rfloor$

$\left\lfloor \frac{(\left\lfloor\frac{a}{b}\right\rfloor + r)}{c} \right\rfloor = \left\lfloor \frac{\left\lfloor\frac{a}{b}\right\rfloor }{c} + \frac{\frac{a\%b}{b}}{c} \right\rfloor = \left\lfloor \left\lfloor \frac{\left\lfloor\frac{a}{b}\right\rfloor }{c}\right\rfloor + \frac{\left\lfloor\frac{a}{b}\right\rfloor\%c}{c} + \frac{a\%b}{bc} \right\rfloor = \left\lfloor \left\lfloor \frac{\left\lfloor\frac{a}{b}\right\rfloor }{c}\right\rfloor + \frac{(\left\lfloor\frac{a}{b}\right\rfloor\%c) * b}{bc} + \frac{a\%b}{bc} \right\rfloor \leq \left\lfloor \left\lfloor \frac{\left\lfloor\frac{a}{b}\right\rfloor }{c}\right\rfloor + \frac{(c-1)*b}{bc} + \frac{b-1}{bc} \right\rfloor$

$ = \left\lfloor \left\lfloor \frac{\left\lfloor\frac{a}{b}\right\rfloor }{c}\right\rfloor + \frac{b*c - b + b - 1}{bc}\right\rfloor$

其中$\left\lfloor \frac{\left\lfloor\frac{a}{b}\right\rfloor }{c}\right\rfloor\in Z,\frac{bc-1}{bc}<1$，故$\left\lfloor \frac{(\left\lfloor\frac{a}{b}\right\rfloor + r)}{c} \right\rfloor = \left\lfloor \frac{\left\lfloor\frac{a}{b}\right\rfloor}{c} \right\rfloor$、、

### 引理2

$\forall n\in N,|\{\left\lfloor \frac{n}{d} \right\rfloor,d\in N\}| \leq 2\sqrt{n}$

证明：$d<=\sqrt{n}$，有至多$\sqrt{n}$种结果。

$d>\sqrt{n},\left\lfloor \frac{n}{d} \right\rfloor$有至多$\sqrt{n} $种结果。

故 $\forall n\in N,|\{\left\lfloor \frac{n}{d} \right\rfloor,d\in N\}| \leq 2\sqrt{n}$，证毕。

### 数论分块

首先要找到$\left\lfloor \frac{n}{i} \right\rfloor = \left\lfloor \frac{n}{j} \right\rfloor,i<=j$中最大的$j$。

$j$满足：

$\left\{\begin{array}{}
\left\lfloor \frac{n}{i} \right\rfloor \leq \frac{n}{j} \\
\left\lfloor \frac{n}{i} \right\rfloor > \frac{n}{j+1}
\end{array}\right.$

只化简第一个式子、、

$\left\lfloor \frac{n}{i} \right\rfloor \leq \frac{n}{j}\Rightarrow \frac{n}{\left\lfloor \frac{n}{i} \right\rfloor} \geq \frac{n}{\frac{n}{j}} = j\Rightarrow j \leq \frac{n}{\left\lfloor \frac{n}{i} \right\rfloor}$

另一个式子用同样方法、、

得到$j \leq \frac{n}{\left\lfloor \frac{n}{i} \right\rfloor} < j+1,$由于$j\in N,$故$j = \left\lfloor\frac{n}{\left\lfloor \frac{n}{i} \right\rfloor}\right\rfloor$

每次处理相同数值的区间$[i,j]$，复杂度$O(\sqrt{n})$、、

### 积性函数

若$\forall x,y, (x,y) = 1$,都有$f(xy) = f(x) * f(y)$，则$f$是积性函数。

#### 性质

若$f,g$是积性函数，则下列$h$均是积性函数：

$h(x) = f(x^k)$

$h(x) = f^k(x)$

$h(x) = f(x)*g(x)$

$h(x) = \sum\limits_{d|x}f(d)*g(\frac{x}{d})$

$h(x) = \sum\limits_{d|x}f(d)*g(d)$

前三个易证，证倒数第二个、、最后一个证明根据积性函数定义，展开后按笛卡尔积理解。

$h(xy) = \sum\limits_{d|xy}f(d)*g(\frac{xy}{d})$、、$(x,y)=1,d$的因子可划分为整除$x$的约数集合和整除$y$的约数集合，两个集合独立没有交集，也即$(d_1,d_2)=1$。即可写成：$h(xy) = \sum\limits_{d_1|x\\d_2|y}f(d_1*d_2)*g(\frac{x}{d_1}*\frac{y}{d_2}) = \sum\limits_{d_1|x\\d_2|y}f(d_1)*f(d_2)*g(\frac{x}{d_1})*g(\frac{y}{d_2})$

另外$h(x) * h(y) = (\sum\limits_{d_1|x}f(d_1)*g(\frac{x}{d_1})) * (\sum\limits_{d_2|y}f(d_2)*g(\frac{y}{d_2}))$

观察两个式子，$h(xy)$中$d_1,d_2$两个变量相互独立，对应二元函数，构成一个二维矩阵；$h(x) * h(y)$ 为笛卡尔积形式，也构成相同的二维矩阵、、其实看式子就很显然了：$\sum\limits_{d_1|x\\d_2|y}f(d_1)*f(d_2)*g(\frac{x}{d_1})*g(\frac{y}{d_2}) = (\sum\limits_{d_1|x}f(d_1)*g(\frac{x}{d_1})) * (\sum\limits_{d_2|y}f(d_2)*g(\frac{y}{d_2}))$

证毕、、

#### 会用到的积性函数

单位函数：$\varepsilon(n) = [n=1]$

常数函数：$1(n) = 1$

恒等函数：$id_k(n) = n^k $，一般简记$id_1(n) = id(n) = n$

除数函数：$\sigma_{k}(n)=\sum_{d \mid n} d^{k}$，一般简记$\sigma_1(n) = \sigma(n) = \sum_{d \mid n} d$，即约数和。

约数个数函数：$d(n) = \sum_{d \mid n} 1$

欧拉函数：$\varphi(n) = \sum_{i=1}^{n}[\operatorname{gcd}(i, n)=1]$

莫比乌斯函数（容斥系数）：$\mu(n)=\left\{\begin{array}{ll}
1 & n=1 \\
0 & n \text { 含有大于一次幂的因子 } \\
(-1)^{k} & \text {其他情况，} k \text { 为 } n \text { 的本质不同质因子个数 }
\end{array}\right.$

#### 积性函数与线性筛

线性筛的每个数由其最小素因子所筛得，利用这一特性，若知道一个积性函数的表达式，则基本可以使用其求所有的积性函数，尽管方法不尽相同。

线性筛分三种情况：

> 1. $i\ is\ prime$
> 2. $i \% prime[j]\ != 0,g(i*prime[j]) = g(i) * g(prime[j])$
> 3. $i \% prime[j]=0,$处理最小质因子指数加1的情况，如果卷积含$\mu$，参考习题[公约数]解法。

### Dirichlet 卷积

$(f * g)(n) = \sum\limits_{d|n}d(d)*g(\frac{n}{d})$

dirichlet卷积运算满足交换律（显然）与结合律（不知道原理）

几个基础的卷积：

$\begin{aligned}
\varepsilon &=\mu * 1 \Longleftrightarrow \varepsilon(n)=\sum_{d \mid n} \mu(d) \\
d &=1 * 1 \Longleftrightarrow d(n)=\sum_{d \mid n} 1 \\
\sigma &=\mathrm{id} * 1 \Longleftrightarrow \sigma(n)=\sum_{d \mid n} d \\
\varphi &=\mu * \mathrm{id} \Longleftrightarrow \varphi(n)=\sum_{d \mid n} d \cdot \mu\left(\frac{n}{d}\right)
\end{aligned}$

后面会讲。

### 莫比乌斯函数

$\mu(n)=\left\{\begin{array}{ll}
1 & n=1 \\
0 & n \text { 含有大于一次幂的因子 } \\
(-1)^{k} & \text {其他情况，} k \text { 为 } n \text { 的本质不同质因子个数 }
\end{array}\right.$

有个神奇性质：$\sum\limits_{d|n}\mu(d) = \left\{\begin{array}{ll}
1 & n=1 \\
0 & otherwise
\end{array}\right.$

证明：

设$n' = \prod\limits_{i=1}^k p_i$、、

根据莫比乌斯函数定义得$\sum\limits_{d|n}\mu(d) = \sum\limits_{d|n'}\mu(d) = \sum\limits_{i=0}^k\left(\begin{array}{ll}i\\k \end{array}\right)*(-1)^i = (1 + (-1))^k$

当$k>0$时该式为0，$k=0$即$n=1$时该式1、、恰巧和单位函数同构、、故$\sum\limits_{d|n}\mu(d) = (1 * \mu)(n) = \varepsilon(n)$

由上面原理可推出反演结论：$[\operatorname{gcd}(i, j)=1] \Longleftrightarrow \sum\limits_{d \mid \operatorname{gcd}(i, j)} \mu(d)$、、用上面原理手撕一下就出来了、、

将$[\operatorname{gcd}(i, j)=1]$用$\varepsilon(\operatorname{gcd}(i, j))$代替，就开始有反演味道了、、

关于$[(i,j)=1]$即$[i \perp j]$的形式，还有一种递归的解决方法，详见习题**密码解锁**,**循环之美**.

### 恒等函数与欧拉函数

$id(n) = (\varphi * 1)(n)$

证明：

先证$n' = p^c$成立、、

$(\varphi * 1)(n') = \sum\limits_{d|n'}\varphi(d)$,其中$d = p^0,p^1,...,p^c$

原式$ = \sum\limits_{i=0}^c\varphi(p^i) = 1 + \varphi(p) + p\varphi(p) + ... p^{c-1}\varphi(p) = 1 + (1 + p + ... + p^{c-1})(p-1) = 1 + \frac{p^c - 1}{p-1}*(p-1) = p^c = id(p^c)$

故对于单纯素因子的组合的数成立。

对于一般数$n = \prod\limits_{i=1}^{k}p_i^{t_i}$、、

$id(n) = \prod\limits_{i=1}^{k}id(p_i^{t_i}) = \prod\limits_{i=1}^{k}(\sum\limits_{d_i|p_i^{t_i}}\varphi(d))$，变量$d_i$两两独立，构成高维矩阵表，与$\sum\limits_{d|n}\varphi(d)$相等。（利用积性函数$\varphi(d') = \varphi(d_{w_1})*\varphi(d_{w_2})*...*\varphi(d_{w_m})$）

根据dirichlet的结合律，有$\varphi * 1 = id\Rightarrow \varphi * 1 * \mu = id * \mu\Rightarrow \varphi * (1 * \mu) = id * \mu\Rightarrow \varphi = \sum\limits_{d|n}d*\mu(\frac{n}{d})$

得到$\varphi = \sum\limits_{d|n}d*\mu(\frac{n}{d})$、、

## 莫比乌斯反演

### 形式1

对于两个数论函数$f,g$，

若$f(n) = \sum\limits_{d|n}g(d)$，且知道$f(n)$的值，，

则$g(n) = \sum\limits_{d|n}\mu(d) * f(\frac{n}{d})$

证明1：

原式$\sum\limits_{d|n}\mu(d) * f(\frac{n}{d}) = \sum\limits_{d|n}\mu(d) * \sum\limits_{k|\frac{n}{d}}g(k) = \sum\limits_{d|n}\sum\limits_{k|\frac{n}{d}}\mu(d) * g(k) = \sum\limits_{k|n}\sum\limits_{d|\frac{n}{k}}\mu(d) * g(k) = \sum\limits_{k|n}g(k)\sum\limits_{d|\frac{n}{k}}\mu(d)$

根据莫比乌斯函数性质，当$\frac{n}{k} = 1$时$\sum\limits_{d|\frac{n}{k}}\mu(d) = 1$，即原式$ = \sum\limits_{k|n}g(k)*\varepsilon(\frac{n}{k}) = g(n)$

证明2：

利用dirichlet的结合律，即证$f = g * 1\Rightarrow g = \mu * f$

$f = g * 1\Rightarrow f * \mu =g * 1 * \mu \Rightarrow g = \mu * f$、、

### 形式2

$f(n) = \sum\limits_{n|d}g(d) \Rightarrow g(n) = \sum\limits_{n|d}\mu(\frac{d}{n})f(d)$

证明：令$k = \frac{d}{n}$、、

原式$ = \sum\limits_{k=1}^{+\infty}\mu(k)f(nk) = \sum\limits_{k=1}^{+\infty}\mu(k)\sum\limits_{nk|d}g(d)$

在直方图上用垒盘子的形式转化遍历方式得到$\sum\limits_{n|d}g(d)\sum\limits_{k|\frac{d}{n}}\mu(k) = \sum\limits_{n|d}g(d)[\frac{d}{n}=1] = g(n)$

证毕、、

直方图要多画画，能够加深变换的理解。

## 扩展莫比乌斯反演

$f(n)=\sum_{i=1}^{n} t(i) g\left(\left\lfloor\frac{n}{i}\right\rfloor\right) 
\Longleftrightarrow g(n)=\sum_{i=1}^{n} \mu(i) t(i) f\left(\left\lfloor\frac{n}{i}\right\rfloor\right)$,其中$t$是完全积性函数、、

没太大兴趣证明、、目前还没遇到题目，见到类似类型会使用就完事了。

## 整除偏序的结构、zeta变换、Möbius变换、lcm卷积、gcd卷积

偏学术的定义Möbius变换、、

整除偏序：对于整除关系$<a,b>$即（$a|b$）是满足偏序关系的：

自反性：$\forall a,<a,a>\in R$

反对称性：$<a,b>,<b,a>\in R \Rightarrow a = b$

可传递性：$<a,b>,<b,c>\in R \Rightarrow <a,c>$

那么Möbius变换就是基于整除偏序结构的性质推出来的。

所谓的 $zeta  $ 变换，比如$g(n) = \sum\limits_{d|n}f(d)$，即将$g$称作$f$的 zeta 变换，记作 $g =  f\zeta $。

Möbius 变换就是，比如$f(n) = \sum\limits_{d|n}\mu(d)g(\frac{n}{d})$，即将$f$称作 $g$ 的 Möbius 变换，记作$f =  g\mu$。

易看出 $f \zeta \mu = f $，即两个变换互为逆变换。



## 一些结论

结论的证明在题目中、、

- $(i,n) = (n-i,n)$
- $d(i j)=\sum_{x \mid i} \sum_{y \mid j}[{gcd}(x, y)=1]$，$i,j$可以不互质
- $gcd(ij,jk,ik) = \frac{gcd(i,j)*gcd*(j,k)*gcd(i,k)}{gcd(i,j,k)}$
- $[d|j][j \perp k] = [dj\perp k] = [d\perp k][j\perp k]$
- $(i,k) = (i\%k,k)$（例如可以用到这种地方：如果遍历i，则$(i,k)=(i+k,k)$，循环节为$k$）
- $h(n)=\sum_{i} \sum_{j} f(i) g(j)[\operatorname{lcm}(i, j)=n] \Leftrightarrow h \zeta(n)=f \zeta(n) g \zeta(n)$
- 求$1\sim n$的Zeta变换（$g(n) = \sum\limits_{d|n} f(d)$的$g(1)\sim g(n)$）：
  将$f(1)$贡献给$g(1),g(2),\dots,g(n)$,$f(2)$贡献给$g(2),g(4),\dots,g(\lfloor\frac{n}{2}\rfloor*2)$，...，复杂度为$O(n\log n)$。
- 求$1\sim n$的Zeta变换（$f(n) = \sum\limits_{d|n} \mu(\frac{n}{d})g(d)$的$f(1)\sim f(n)$）：
  一样的思路，预处理一波$\mu$。



## 关于分母划分

在题目**YY的GCD**那，过程详细。

# 取整

$\begin{array}{l}
a \leq\left\lfloor\frac{b}{c}\right\rfloor \Leftrightarrow a c \leq b \\
a \geq\left\lceil\frac{b}{c}\right\rceil \Leftrightarrow a c \geq b \\
a<\left\lceil\frac{b}{c}\right\rceil \Leftrightarrow a c<b \\
a>\left\lfloor\frac{b}{c}\right\rfloor \Leftrightarrow a c>b
\end{array}$

**c均>0**

证明第一条：$a \leq\left\lfloor\frac{b}{c}\right\rfloor \Rightarrow a c \leq b$
即证$a\leq\frac{b}{c}$。

由 $\frac{b}{c} \geq \left\lfloor\frac{b}{c}\right\rfloor,a \leq\left\lfloor\frac{b}{c}\right\rfloor$，可推出 $ a\leq\frac{b}{c}$。

$ a c \leq  b\Rightarrow a\leq\left\lfloor\frac{b}{c}\right\rfloor $

即 $a\leq\frac{b}{c}\Rightarrow a\leq\left\lfloor\frac{b}{c}\right\rfloor$

将$a$视为整型常量，此时即使$\frac{b}{c}=4.9999$，依旧可推出满足不等式的集合等价于$a\leq\left\lfloor\frac{b}{c}\right\rfloor=4$所构成的集合。（非严格证明，不过足矣）

故$a \leq\left\lfloor\frac{b}{c}\right\rfloor \Leftrightarrow a c \leq b$

其他原理类似。

# 上指标求和

$\sum_{0 \leq k \leq n}\dbinom{k}{m}=\dbinom{n+1}{m+1}$

$\sum_{1 \leq k \leq n}\dbinom{k}{m}=\dbinom{n+1}{m+1} - [m=0]$

# 三平方之和表示一个数

有一个四平方和定理：

> 每个自然数都可以表示为四个整数平方和。

同时还有个三平方和定理：
$$
n \neq 4^{k}(8 m+7) \Longleftrightarrow n=a_{0}^{2}+a_{1}^{2}+a_{2}^{2},a_i\ge 0
$$
综合来看，即一个数最多需要 4 个平方项来表示。若满足了三平方和，则有可能是平方数或者能满足二平方和的数。对于后者， $O(\sqrt{n})$ 可以判定。

# 斯特林数

斯特林数能用来解决不少组合数学问题。其分为两类，分别为**第一类斯特林数，第二类斯特林数**。**拉赫数**由于与斯特林数关系密切，所以有时其也被称为**第三类斯特林数**。

## 递降/递增阶乘

数学上定义了 **递降/递增阶乘**：

递增阶乘$x^{(n)} = x^{\overline{n}} = x(x+1)(x+2)...(x+n-1)$

递减阶乘$(x)_n = x^{\underline{n}} = x(x-1)(x-2)...(x-n+1)$

另外, 值得一提的是递降阶乘实际上是排列 $P_{n}^{x}$。

## 第一类斯特林数

第一类斯特林数分 **有符号** 与 **无符号** 两种（其实就是一个有正负，另一个均为正）。有符号斯特林数记为$s(n,k)$，可由递降阶乘来定义：

$(x)_{n}=\sum_{k=0}^{n} s(n, k) x^{k}$

无符号则可以用递增阶乘来定义：

$(x)^{\bar{n}}=\sum_{k=0}^{n}\left[\begin{array}{l}n \\ k\end{array}\right] x^{k}$

两个第一类斯特林数的相互转化：$s(n, k)=(-1)^{n-k}\left[\begin{array}{l}n \\ k\end{array}\right]$

而对于 **无符号** 的第一类斯特林数，也有对应的组合意义：有 $n$ 个两两不同的数，组成 $k$ 个圆排列的方案数。

其满足递推式：

$\left[\begin{array}{l}n \\ k\end{array}\right]=\left[\begin{array}{l}n-1 \\ k-1\end{array}\right]+(n-1)\left[\begin{array}{c}n-1 \\ k\end{array}\right]$

边界是：$\left[\begin{array}{l}
n \\
0
\end{array}\right]=[n=0]$

关于无符号第一类斯特林数跟递降阶乘为什么有联系不太清楚，虽然可以用数学归纳法来证明其正确性（利用无符号第一类斯特林数的递推式+数归）。

## 第二类斯特林数

第二类斯特林数的定义：

$x^{n}=\sum_{k=0}^{n}\left\{\begin{array}{l}n \\ k\end{array}\right\}x^{\underline{k}}$

记为$S(n,k)$。

其组合意义为将$n$个数划分成$k$个非空集合的方案数。

递推式为$\left\{\begin{array}{l}
n \\
k
\end{array}\right\}=\left\{\begin{array}{l}
n-1 \\
k-1
\end{array}\right\}+k\left\{\begin{array}{c}
n-1 \\
k
\end{array}\right\}$

边界条件：$\left\{\begin{array}{l}
n \\
0
\end{array}\right\}=[n=0]$

## 斯特林数行与列

斯特林数的 **行** 指的是（以第一类斯特林数举例）$\left[\begin{array}{l}n \\ i\end{array}\right]$，$n$是常量，$i\in [0,k]$

斯特林数的 **列** 指的是（以第一类斯特林数举例）$\left[\begin{array}{l}i \\ k\end{array}\right]$，$k$是常量，$ i \in [0,n]$

听说有时需要用到某一行or某一列的斯特林数，可以通过多项式计算来快速求得。具体在 **多项式** 文档里的 「斯特林数的行与列」有写。



# 整数划分

将一个整数 N 划分成很多个正整数的和，有多少种分法。不考虑顺序，比如 4=1+3 和 4=3+1 算是相同的。 N<120 。

将拿多少个 1 写成生成函数： $1:1+x+x^2+x^3+...$​​
将拿多少个 2 写成生成函数： $2:1+x^2+x^4+x^6+...$​​
将拿多少个 3 写成生成函数： $3:1+x^3+x^6+x^9+...$​​​

可以发现，将这些多项式乘在一起，对应的次数等于 N 的项就是答案。​

## 整数划分2

将一个整数 N 分成 k 个数，满足 N = a1 + a2 + a3 + … + ak. (0<=a<=N) 。

换个角度思考问题：选 k 次，每次从 0~N 中挑一个数。那么生成函数就是 $G(x) = 1 + x + x^1 + x^2 + ... + x^n+...$​​。由于每次只是选一个数，所以系数都为1。答案为 k 个生成函数相乘对应的项的系数。

这里的G(x)是个很特殊的级数，即$G(x) = \frac{1}{1-x}$（称作多项式的闭形式）。

要求 $G(x)^k = \frac{1}{(1-x)^k} = (1-x)^{-k} = \sum^{\infty}_{i=0}(-1)^iC^i_{k+i-1}(-x)^i = \sum^{\infty}_{i=0}C^i_{k+i-1}x^i$​​ ，求当 i = n 的项的组合数：$C(n,k+n-1)$ ​​​​就是答案。

## 整数划分3

求 $x_1+2x_2+3x_3+...+nx_n=n,x_i\in[0,n]$ ​的方案数。这个方案数在一个函数上，记为分割函数 $p(n)$​。

数 $i$​ ​选 $0,1,2,...\Rightarrow 1 + x^i + x^{2i} + ... = \frac{1}{1-x^i}$​​。故 $\sum_{n=0}^{\infty} p(n) x^{n}=\prod_{k=1}^{\infty}\left(\frac{1}{1-x^{k}}\right)$​​。$p(n)$ ​​即为所求答案。

## Ferrers图

Ferrers 图 ：一个点表示整数 1，一行表示一个分部量（即5= 2 + 3，其中 2 是 5 的一个分布量）。共轭即转置。如 5 的一个二分拆 5 = 3+2 的 Ferrers 图，其共轭为 5 的最大分部量为 2 的分拆：

![v2-63ae22bb1ff3a091c3a0f5313a720503_1440w](https://raw.githubusercontent.com/Falicitas/Image-Hosting/main/v2-63ae22bb1ff3a091c3a0f5313a720503_1440w.jpg)

由于共轭后方案数不变，所以原问题（将 5 分成两个分布量的方案）可以转为讨论将 5 分成分布量不超过 2 的方案。

## 欧拉函数

这个欧拉函数是复变函数？（wiki是这样定义的）数学定义：
$$
\phi(q)=\prod_{k=1}^{\infty}\left(1-q^{k}\right) = (1-q)*(1-q^2)*(1-q^3)*...
$$

## 五边形数

源自五边形向外加点形成更大的五边形的点的数量的变化。

$f_{1}=1, f_{n}=f_{n-1}+3 n-2$

对差分求前缀和，得到 $f_{n}=\frac{n(3 n-1)}{2}$​

$1,5,12,22,35,51,70,92,117,145,176,210,247,287 \dots$

### 广义五边形数

在公式 $f_{n}=\frac{n(3 n-1)}{2}$ 中, $n$ 取 $0,1,-1,2,-2 \dots$

$0,1,2,5,7,12,15,22,26,35,40,51,57,70,77,92,100,117,126 \dots$

### 五边形数定理

来自于对欧拉定理 $\phi(x)$ ​展开式的特性。欧拉函数的展开式如下：

$$
\prod_{n=1}^{\infty}\left(1-x^{n}\right)=\sum_{k=-\infty}^{\infty}(-1)^{k} x^{\frac{k(3 k-1)}{2}}=\sum_{k=0}^{\infty}(-1)^{k} x^{\frac{k(3 k\pm1)}{2}}
$$
亦即
$$
(1-x)\left(1-x^{2}\right)\left(1-x^{3}\right) \cdots=1-x-x^{2}+x^{5}+x^{7}-x^{12}-x^{15}+x^{22}+x^{26}+\cdots
$$


式子很好证明， $\prod_{n=1}^{\infty}\left(1-x^{n}\right)$​​ 中，低次项不会受高次项的影响，再根据次项的规律是广义五边形数，从此把欧拉函数展开成幂级数形式。

可以发现，分割函数的幂级数形式 $A$ ​与欧拉函数互为乘法逆，将欧拉函数也展成幂级数 $C,AC=1$​ 即 $\left(1-x-x^{2}+x^{5}+x^{7}-x^{12}-x^{15}+x^{22}+x^{26}+\cdots\right)\left(1+p(1) x+p(2) x^{2}+p(3) x^{3}+\cdots\right)=1$​

找到 $x^n$​ ​的系数为:$p(n)-p(n-1)-p(n-2)+p(n-5)+p(n-7)+\cdots$​​，而等式右侧对应次数的项的系数为0，故$p(n)-p(n-1)-p(n-2)+p(n-5)+p(n-7)+\cdots=0$​​,得出分割函数p(n)的递归式
$p(n)=p(n-1)+p(n-2)-p(n-5)-p(n-7)+\cdots$​​

以 n=10 为例

$p(10)=p(9)+p(8)-p(5)-p(3)=30+22-7-3=42$​​​

由于广义五边形数的递增速度为 $O(n)$​​​​，故使用递推求分割函数的复杂度为 $O(n\sqrt{n})$​​​​ 。

亦或者将 $\sum_{k=0}^{\infty}(-1)^{k} x^{\frac{k(3 k\pm1)}{2}}$ $O(n)$ 构造后，对多项式取逆。复杂度 $O(n\log n)$ 。

## 更一般的分割数$P_{n,m}$

前面的分割数 $x_1+2x_2+3x_3+...+nx_n=n,x_i\in[0,n]$​​，即 $x_i$​​ 的取值对于$n$​​来说 **充分大** 。

对于一般的情况，即$x_1+2x_2+3x_3+...+nx_n=n,x_i\in[0,m]$来说，考虑如下dp：

设 $dp(i,j)$ 为分割$i$个数，用上$j$个可重数的方案数。考虑$j$个可重数按照非递减的顺序排成序列，则有：

$dp(i,j) = dp(i-j,j) + dp(i,j-1)$，前一个状态考虑将序列集体$+1$，后一种状态考虑序列开头加个$0$，从而保证新序列也是非递减的序列（好神奇qwq）。

此时生成$P_{i,j}$的OGF，有$F_i(x) = \sum\limits_{j=0}P_{j,i}x^j$

根据递推式，有$F_i(x) = F_i(x) * x^i + F_{i-1}$，即$F_i(x) = \frac{F_{i-1}}{1-x^i}$

故$F_m(x) = \prod\limits_{i=1}^m\frac{1}{(1-x^i)}$，此时就是 **付公主的背包** 的套路了。

复杂度 $O(mlogm)$​​ 。当 $m$​ ​充分大时， $m = n$​​​ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
constexpr int P = 998244353;
vector<i64> GetCutNumbers(int n) {
    vector<i64> p(n + 1);
    int i, j, k, l;
    i64 sum;
    p[0] = 1;
    for (i = 1; i <= n; i++) {
        sum = 0;
        for (j = 1, k = 1, l = 1; j > 0; k++, l = -l) {
            j = i - (3 * k * k - k) / 2;
            if (j >= 0)
                sum += l * p[j];
            j = i - (3 * k * k + k) / 2;
            if (j >= 0)
                sum += l * p[j];
            sum = (sum % P + P) % P;
        }
        p[i] = sum;
    }
}
```

#  Bertrand-契比雪夫定理

定理：对于$\forall n>3,$必存在质数$p$，满足$n < p < 2*n - 2$。

一种较弱的说明为对于$n>1$，必存在质数$p$满足$n<p<2n$、、



# Pollard-rho算法

```cpp
//#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
using namespace std;

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

namespace Pollard_rho {
bool mr32(u32 n, u32 a) {
    if (!(a %= n))
        return 1;
    uint8_t r = __builtin_ctz(n - 1);
    u32 d = n >> r, p = 1;
    for (; d; d >>= 1, a = u64(a) * a % n) {
        if (d & 1)
            p = u64(p) * a % n;
    }
    if (p == 1)
        return 1;
    while (p != n - 1 && --r) {
        p = u64(p) * p % n;
    }
    return p == n - 1;
}
bool mr64(u64 n, u64 a) {
    if (!(a %= n))
        return 1;
    u8 r = __builtin_ctzll(n - 1);
    u64 d = n >> r, p = 1;
    for (; d; d >>= 1, a = u128(a) * a % n) {
        if (d & 1)
            p = u128(p) * a % n;
    }
    if (p == 1)
        return 1;
    while (p != n - 1 && --r) {
        p = u128(p) * p % n;
    }
    return p == n - 1;
}
bool dmr32(u32 n) {
    return mr32(n, 2) && mr32(n, 7) && mr32(n, 61);
}
bool dmr64(u64 n) {
    if (n <= 0xFFFFFFFF)
        return dmr32(n);
    return mr64(n, 2) && mr64(n, 325) && mr64(n, 9375) && mr64(n, 28178) &&
           mr64(n, 450775) && mr64(n, 9780504) && mr64(n, 1795265022);
}
vector<u64> factorise(u64 n) {
    // factorises integers 1 ≤ n < 2^62
    vector<u64> pf;
    for (u8 i : {2, 3, 5})
        while (!(n % i))
            pf.push_back(i), n /= i;
    for (u32 i = 7; i * i <= n && i <= 211; i += 6)
        for (u32 j : {0, 4})
            while (n % (i + j) == 0)
                pf.push_back(i + j), n /= i + j;
    if (n == 1)
        return pf;
    vector<pair<u64, u8>> q{{n, 1}};
    while (!q.empty()) {
        auto n = q.back().first;
        auto c = q.back().second;
        q.pop_back();
        if (n < 49729) {
            while (c--)
                pf.push_back(n);
            continue;
        }
        u64 r = sqrt(n) + 0.5;
        if (r * r == n) {
            q.emplace_back(r, c * 2);
            continue;
        }
        if (dmr64(n)) {
            while (c--)
                pf.push_back(n);
            continue;
        }
        u64 ni = -n;
        for (u8 _ = 5; _--;)
            ni *= 2 + ni * n;
        auto redc = [&](u128 x) -> u64 {
            return u64(x) * ni * u128(n) + x >> 64;
        };
        auto f = [&](u64 x) { return redc(u128(x) * x + 1); };

        u64 g = n;
        const u64 m = 1LL << (__lg(n) / 5);
        for (u64 x0 = 0; g == n; ++x0) {
            u64 x, y = x0, q = 1, ys;
            g = 1;
            for (u64 r = 1; g == 1; r <<= 1) {
                x = y;
                for (u64 _ = r; _--;)
                    y = f(y);
                for (u64 k = 0; k < r && g == 1; k += m) {
                    ys = y;
                    for (u64 _ = min(m, r - k); _--;)
                        y = f(y), q = redc(u128(max(x, y) - min(x, y)) * q);
                    g = __gcd(q, n);
                }
            }
            if (g == n) {
                for (; g == 1;) {
                    ys = f(ys);
                    g = __gcd(max(x, ys) - min(x, ys), n);
                }
            }
        }
        q.emplace_back(g, c);
        q.emplace_back(n / g, c);
    }
    sort(pf.begin(), pf.end());
    return pf;  //返回有重素因子集，累乘=n
}
}  // namespace Pollard_rho

```
