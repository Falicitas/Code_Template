# Pollard-rho算法

## Mandelbrot set曼德勃罗集

定义：利用迭代公式$Z_{n+1} = Z_n^2 + C,c\in C,Z_0 = 0$,在复数领域中使迭代点$Z_i$ 序列不延伸至无限大的所有复参数C的点集。点集构成的图形类似于这样（近乎黑色的均是收敛的点集解）：

<img src="C:\Users\Administrator\Desktop\markdown图片\曼德勃罗集.jpg" style="zoom:16%;" />

##  生日悖论&组合随机采样

倘若想要一个班里的同学的生日都不在4.1那天，概率是很大的、、而若需满足同学两两生日不同，则概率则会骤减。每增加一个同学，使两两生日不同的概率会越来越小，是概率变化的几何概型、、

生日悖论模型给了启发，对于离散区间 $[0,d]$不断随机$k$次以找到特定值$q\in [1,d]$,不如随机$k$个数$x_1,x_2,...,x_k$，使$|x_i - x_j|$去碰撞更容易碰到$q$（前提$q$不要太接近d，否则碰撞几率骤减）、、

## Pollard_rho

利用组合随机采样的思路去碰撞待检测数$n$,找到$n$的非平凡因子。根据组合随机取样的弊端，得先排除$n$是质数的情况，之后采取碰撞$n$所构成的约数集合的元素。此时，哪怕是最难碰撞，当$n$恰好为整数$\sqrt{n}$的二次幂，期望碰撞次数也是完全可以接受的。

目标是找到$n$的一个非平凡因子，通过找$gcd(|x_i-x_j|,n)>1$的$gcd(|x_i-x_j|,n)$，此必为n的因子。$x_i$由曼德勃罗的递推式确定，$x_{i+1} = x_i ^ 2 + c(\%n)$。可以想到，当$x_i$等于之前走过的某一步，必会进入循环、、是个链加环结构类似$\rho$。由于每次$gcd$复杂度高，而若存在样本值$w = |x_i-x_j|,gcd(w,n)>1$，则$gcd(kw,n)>1,gcd(kw\%n,n)>1$、、故获取一系列样本值在模$n$下累乘后再去$gcd$，可以默认忽略复杂度$O(logN)$.具体则用上倍增，算法流程类似于在$\rho$上指针$p_1,p_2$，$p_2$走$k$步后$p_1$跟上，$p_2$再走$2k$步、、给走的步数定个上界$128$，大概率走进环内，计算重复结果了、、这时该换$c$值了、、

基本原理还是基于生日悖论的蒙特卡洛方法，以求尽快碰撞到$n$的因子再不断往下分解，由于序列$x_1,x_2,...,x_k$的取值在$\rho$上面，等价floyd判环讨论的问题，故又有$\_rho$的后缀、、会用就完事了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

mt19937_64 rnd(233);

ll qp(ll base, ll n, ll mod) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        n >>= 1;
    }
    return res;
}

const int maxnS = 20;
bool miller_rabin(ll n) {
    if (n == 2 || n == 3 || n == 5 || n == 7 || n == 11)
        return true;
    if (n == 1 || !(n % 2) || !(n % 3) || !(n % 5) || !(n % 7) || !(n % 11))
        return false;

    ll x, pre, u;
    int i, j, k = 0;
    u = n - 1;  //要求x^u % n

    while (!(u & 1)) {  //如果u为偶数则u右移，用k记录移位数
        k++;
        u >>= 1;
    }

    for (i = 0; i < maxnS; ++i) {  //进行S次测试
        x = rnd() % (n - 2) + 2;   //在[2, n)中取随机数
        if ((x % n) == 0)
            continue;

        x = qp(x, u, n);  //先计算(x^u) % n，
        pre = x;
        for (j = 0; j < k; ++j) {  //把移位减掉的量补上，并在这地方加上二次探测
            x = (__int128)x * x % n;
            if (x == 1 && pre != 1 && pre != n - 1)
                return false;  //二次探测定理，这里如果x = 1则pre 必须等于 1，或则 n-1否则可以判断不是素数
            pre = x;
        }
        if (x != 1)
            return false;  //费马小定理
    }
    return true;
}

vector<int> vec, fac;
namespace Pollard_rho {
ll f(ll x, ll c, ll n) {
    return (x * x + c) % n;
}
ll PR(ll x) {
    ll s = 0, t = 0, c = 1ll * rand() % (x - 1) + 1, val = 1;
    for (int goal = 1;; goal <<= 1, s = t, val = 1) {
        for (int stp = 1; stp <= goal; ++stp) {
            t = f(t, c, x);
            val = val * abs(t - s) % x;
            if ((stp % 127) == 0) {
                ll d = __gcd(val, x);
                if (d > 1)
                    return d;
            }
        }
        ll d = __gcd(val, x);
        if (d > 1)
            return d;
    }
}
set<int> S;
void init() {
    vec.clear(), fac.clear(), S.clear();
}
void get_fac(int x) {
    if (x < 2)
        return;
    if (miller_rabin(x)) {
        if (!S.count(x))
            vec.push_back(x), S.insert(x);
        return;
    }
    ll p = x;
    while (p >= x)
        p = PR(x);
    while ((x % p) == 0)
        x /= p;
    get_fac(x), get_fac(p);
}
void dfs(int dep, int x) {
    if (dep == vec.size())
        return void(fac.push_back(x));
    int c = 1;
    while (1) {
        if (x % c == 0) {
            dfs(dep + 1, x / c);
            c *= vec[dep];
        } else
            break;
    }
}
}  // namespace Pollard_rho

```



## 一些习题

### P2441 角色属性树

给一棵树，树上有点权$w_i$。需要查询节点$u$距离最近的祖先节点$fa$，使$w[fa]$与$w[u]$存在共同的质因子、、有修改近50次、、

正解过不了，反倒是直接暴力往上搜$gcd(u,fa)>1$能过- -

初始对每个权值用$Pollard\_rho$分解质因子，然后由根节点开始遍历，，

$x_1+x_2+...+x_t = n,$