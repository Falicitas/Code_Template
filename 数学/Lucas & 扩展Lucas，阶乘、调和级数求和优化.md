# Lucas & 扩展Lucas，阶乘、调和级数求和优化

## Lucas

用于 $C(m,n)\%p$ 中 $n,m$ 很大而模数不大（且为质数）的情况下，用复杂度 $O(p)$ 预处理， $O(logn)$ 查询的定理。

公式
$$
\left(\begin{array}{l}
n \\
m \\
\end{array}\right) \% p=\left(\begin{array}{c}
\lfloor n / p\rfloor \\
\lfloor m / p\rfloor
\end{array}\right) \cdot\left(\begin{array}{c}
n \% p \\
m \% p
\end{array}\right) \% p
$$
其中前一个系数可以继续递归，后一个系数由预处理后可以 $O(1)$ 计算。

证明：考虑 $\left(\begin{array}{c}
p \\
n \\
\end{array}\right)\%p = \frac{p!}{n!(p-n)!}\%p$ ，对于 $p$ 是质数来说，分子中质因数分解后素因子 $p$ 的指数为 1 。当且仅当 $n=0\ |\ n=p$ 时原式为 1 ，其余情况为 0 。故
$$
\left(\begin{array}{l}
p \\
n \\
\end{array}\right) \%p = [n=0\ |\ n=p]
$$
考虑一个二项式 $f(x) = (ax^m+bx^n)^p\%p \equiv a^px^{pm} + b^px^{pn} \equiv ax^{pm}+bx^{pn}(\%p) $ 

$\left(\begin{array}{c}
n \\
m \\
\end{array}\right)$ 对应 $(1+x)^n$ 中 $x^m$ 的系数，对 $n$ 照 $p$ 除模分解有 $n = p\lfloor n / p\rfloor + n\%p$

则 $(1+x)^n = (1+x)^{p\lfloor n / p\rfloor} * (1+x)^{n\%p} = (1+x^p)^{\lfloor n / p\rfloor}*(1+x)^{n\%p}$

要从卷积中获取 $x^m$ 。令 $m = A*p+ B,\ A,B\in[0,p)$ ，根据除模分解原理当且仅当存在一组 $A,B$ 满足解，且 $A = \lfloor m / p\rfloor, B = m\%p$ ，故卷积中仅有一项卷积可得 $x^m$ 。故其系数来自两个多项式构成 $x^m$ 的系数的乘积：
$$
\left(\begin{array}{l}
n \\
m \\
\end{array}\right) \% p=\left(\begin{array}{c}
\lfloor n / p\rfloor \\
\lfloor m / p\rfloor \\
\end{array}\right) \cdot\left(\begin{array}{c}
n \% p \\
m \% p \\
\end{array}\right) \% p​
$$

## 扩展Lucas

### 威尔逊定理、快速阶乘、快速调和级数求和

$$
(p-1)!\equiv -1 (\%p)
$$

当且仅当 $p$ 为质数。对证明没啥兴趣、、

> 性质1：
> $$
> \dbinom{p-1}{n} \equiv (-1)^n(\bmod p)
> $$
> 当 $p$ 为奇素数。
>
> 感性证明：按照下降幂展开后， 
> $$
> \begin{aligned}
> 原式&\equiv \frac{(p-1)^{\underline{n}}}{n^{\underline{n}}}
> \\
> &\equiv \frac{(p-1)(p-2)\dots(p-n)}{1*2*\dots*n}
> \\
> &\equiv \frac{-1*-2*\dots*-n}{1*2*\dots*n} 
> \\
> &\equiv (-1)^n(\bmod p)
> \end{aligned}
> $$
> 

>阶乘常数优化计算：
>$$
>n! \equiv (-1)^{p-n}\frac{1}{(p-1-n)!}(\bmod p )
>$$
>可以缩减阶乘的运算次数（其实就缩为互补的一段区间）
>
>证明：
>
>移项构造组合数，有
>$$
>\frac{-1}{n!(p-1-n)!} \equiv (-1)^{n-p+1} (\bmod p)
>$$
>转化为性质 1 的式子，得证。

>调和级数常数优化计算：
>$$
>H_n \equiv H_{p-1-n}(\bmod p)
>$$
>证明：
>
>首先有 $\frac{1}{i} \equiv \frac{-1}{p - i}(\bmod p)$
>
>于是
>$$
>\begin{aligned}
>H_{p-1-n} - H_{n} 
>&= \sum\limits_{i=1}^{p-1-n}\frac{1}{i} - \sum\limits_{i=1}^n \frac{1}{i} 
>\\
>&= \sum\limits_{i=1}^{p-1-n}\frac{1}{i} + \sum\limits_{i=1}^n \frac{1}{p-i} 
>\\
>&= H_{p-1}
>\end{aligned}
>$$
>而 $H_{p-1}$ 的构成运算的元素恰好构成一个 **缩系** ，故
>$$
>H_{p-1} \equiv \frac{(1+p-1)(p-1)}{2} = p*\frac{p-1}{2} \equiv 0(\bmod p)
>$$
>得证。

#### 高斯泛化的威尔逊定理

$\prod\limits_{k=1 \atop \operatorname{gcd}(k, m)=1}^{m} k \equiv\left\{ {\begin{array}{}
-1  (\% m), if\ m = 2,4,p^{\alpha}, 2 p^{\alpha},p为奇素数 \\
1(\% m) , otherwise 
\end{array}}\right.$

由高斯证明。从单纯素数拓展到 ${2,4,p^{\alpha}, 2 p^{\alpha}}$ ，从阶乘拓展至 **互质数相乘** 。

证明方法暂不感兴趣，先放置一边。

### 扩展Lucas算法流程

对于组合数 $C(m,n)\%P$ ， $n,m$ 很大， $P$ 较小但不一定是质数，先质因数分解，构建 CRT 方程：

$$
\left\{\begin{aligned}
C(n,m) & \equiv a_{1}(\bmod n_{1}^{k_1}) \\
C(n,m) & \equiv a_{2}(\bmod n_{2}^{k_1}) \\
& \vdots \\
C(n,m) & \equiv a_{k}(\bmod n_{k}^{k_1})
\end{aligned}\right.
$$
模数两两互质，必有解。

考虑其中一个方程 $C(n,m) \equiv \frac{n!}{m!*(n-m)!}\equiv a(\% p^{k})$

尝试计算 $n!$ ，
$$
\begin{aligned}
f(n) 
&= n! 
\\
&= 1 * 2 * ...n 
\\
&= 1 * 2 * ... * p * (p+1) * ... *n 
\\
&= 1*2*..*(p-1)*(p+1)*...*n*(p*2p*3p*...) 
\\
&= 1*2*..*(p-1)*(p+1)*...*n*p^{\lfloor \frac{n}{p}\rfloor}*(1*2*3*...) 
\\
&= 1*2*..*(p-1)*(p+1)*...*n*p^{\lfloor \frac{n}{p}\rfloor} * f(\lfloor \frac{n}{p}\rfloor)
\end{aligned}
$$
观察到 $1*2*..*(p-1)*(p+1)*...*n$ 中， $[0,p^k)$ 区间与 $p^k$ 互质的 数 累乘与 $[p^k,2p^k)$ 区间的 数 累乘 **同余** 。而根据高斯泛化的威尔逊定理，区间的数均与 $p^k$ 互质，且覆盖 $p^k$ 的互质类，故在模 $p^k$ 下同余 $-1$ 。

最后一段不完整区间可以用累乘预处理 $O(1)$ 得来，由于预处理所需要的只有 $P$ 。

故组合数 $n!$ 对应的函数 $f(n)$ 可以用 $O(logn)$ 递归求解。

还有个问题，分母的阶乘可能不存在逆元。观察函数 $f(n)$ ，可发现只有 $p^{\lfloor\frac{n}{p}\rfloor}$ 和递归函数 $ f(\lfloor \frac{n}{p}\rfloor)$ 存在质因子 $p$ 其余的均与 $p^k$ 互质。故每次递归将含 $p$ 的项提出，原组合数转化为 $\frac{\frac{n !}{p^{x}}}{\frac{m !}{p^{y}} \frac{(n-m) !}{p^{z}}} p^{x-y-z} \bmod p^{k}$ 。然后求得 $a$ 。

最后套个CRT就完事了。

