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