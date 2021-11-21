#  Bertrand-契比雪夫定理

定理：对于$\forall n>3,$必存在质数$p$，满足$n < p < 2*n - 2$。

一种较弱的说明为对于$n>1$，必存在质数$p$满足$n<p<2n$、、

## 不等式1

对于正整数$n,\left(\begin{array}{c}
2 n \\
n
\end{array}\right) \geq \frac{4^{n}}{2 n}$

证明：

$\begin{array}{l}
\text { 对于 } k \leq 2 n, \quad\left(\begin{array}{c}
2 n \\
n
\end{array}\right) \geq\left(\begin{array}{c}
2 n \\
k
\end{array}\right) \\
\text { 若 } k \neq n,\left(\begin{array}{c}
2 n \\
n
\end{array}\right)>\left(\begin{array}{c}
2 n \\
k
\end{array}\right) \\
\text { 因此2 } n\left(\begin{array}{c}
2 n \\
n
\end{array}\right) \geq \sum_{i=1}^{2 n}\left(\begin{array}{c}
2 n \\
i
\end{array}\right)+1=2^{2 n}=4^{n}
\end{array}$

利用二项式定理、、人才、、用于求$\left(\begin{array}{c}
2 n \\
n
\end{array}\right)$的下界。

## 

## 引理1

对于阶乘$n!$，含质数的幂次$s = \sum\limits_{i=1}^{\infty}\left\lfloor\frac{n}{p^i}\right\rfloor$。

证明：对于$s$，其易知$s = \sum\limits_{i=1}^{n}s_i,s_i$为$i$中$p$的幂次、、条件与贡献转化$s = \sum\limits_{i=1}^{n}\sum\limits_{j=1}^{s_i}1$,转化遍历顺序，$\sum\limits_{j=1}^{\infty}\sum\limits_{p^j|i}1 = \sum\limits_{j=1}^{\infty}\frac{n}{p^j}$

得证。

$\left(\begin{array}{c}2 n \\n\end{array}\right) = \frac{(2n)!}{(n!)^2}$、、下面对$\frac{(2n)!}{(n!)^2}$分析，等价于对$\left(\begin{array}{c}2 n \\n\end{array}\right)$分析、、

推论1.1 $\frac{(2n)!}{(n!)^2}$中含$p$的幂次$s = \sum\limits_{i=1}^{\infty}\frac{2n}{p^i} - 2 * \sum\limits_{i=1}^{\infty}\frac{n}{p^i}$、、

易证、、在计数的意义上，除法等价于幂的减法、、

推论1.2.1 $\frac{(2n)!}{(n!)^2}$中$p$的最高次幂$s$满足$p^s\leq2n$、、

证明：对于原式来说，令$m$为满足$p^m\leq 2n$的最大值、、对于$s$的公式的上界就为$m$、、由于$\sum\limits_{i=1}^m([2x] - 2*[x])$中$[2x] - 2*[x]\leq 1$，故$[2x] - 2*[x]$要不0要不1、、所以$s \leq m\Rightarrow p^s\leq p^m\leq 2n$、、证毕，，

推论1.2.2 $\frac{(2n)!}{(n!)^2}$ 中若$p>\sqrt{2n},$则$s<=1$、、

证：$p\geq\sqrt{2n}$,则$p^2>2n$，故只有$i=1$时有值、、所以$s<=1$、、

推论1.2.3 若$\frac{2n}{3}< p \leq n,$则$s=0$、、

当$n\geq3$时，$p^2>2n$,故只有$i=1$项有值、、$\frac{2n}{3} < p \leq n\Rightarrow 1 \leq \frac{n}{p} < \frac{3}{2}$、、有$s = 2 - 2 = 0$、、

由1.2的三个推论确定了在$\left(\begin{array}{c}2 n \\n\end{array}\right)$中质数$p$的3个幂次上界：

> * $ p^s \leq 2n $
> * $ p\geq \sqrt{2n},s<=1 $
> * $\frac{2n}{3}<p\leq n,s = 0$（注意，$n<p<2n$时$s$的取值不是0，，这在后面证）

## 引理2

$\prod\limits_{k+1<p \leq 2 k+1} p<4^{k}$
证明：注意到所有大于 $k+1$ 而小于 $2k+1$ 的质数都在$(2k+1)! $中而不在$(k+1)! $或$ k!$
中, 于是 $\prod_{k+1<p \leq 2 k+1} p$ 是 $\left(\begin{array}{c}2 k+1 \\ k+1\end{array}\right)$ 的因子。

即$\prod_{k+1<p \leq 2 k+1} p \mid\left(\begin{array}{c}2 k+1 \\ k+1\end{array}\right)$、、
同时又有 $2\left(\begin{array}{c}2 k+1 \\ k+1\end{array}\right)=\left(\begin{array}{c}2 k+1 \\ k+1\end{array}\right)+\left(\begin{array}{c}2 k+1 \\ k\end{array}\right)<\sum_{i=0}^{2 k+1}\left(\begin{array}{c}2 k+1 \\ i\end{array}\right)=2 \cdot 4^{k}$（写成两倍形式其实就是更贴近准确上界罢了）
于是就有 $\prod_{k+1<p \leq 2 k+1} p \leq\left(\begin{array}{c}2 k+1 \\ k+1\end{array}\right)<4^{k}$ 

再扩展：$\prod\limits_{p\leq n} p <4^{n}$

用数学归纳法证、、已证$n<16$均成立、、

$n>=16$,对于$n$为偶数$2k$，$\prod\limits_{p\leq 2k} p = \prod\limits_{p\leq 2k-1} p$

对于奇数，假设$k+1$成立，则当$n=2k+1$,$\prod\limits_{p\leq 2k+1} p  = \prod\limits_{p\leq k+1} p * \prod\limits_{k+1< p\leq 2k+1}*p < 4^{k+1} * 4^k = 4^n$

故$\prod\limits_{p\leq n} p <4^{n}$

## 核心部分

回到原命题，，反证法：设存在p有，使得$n<p<2n$不成立、、

对于二项式$\left(\begin{array}{c}2 n \\n\end{array}\right) = \prod\limits_{p\leq2n}p^{sq} = \prod\limits_{p\leq\frac{2n}{3}}p^{sq} * \prod\limits_{n\leq p\leq2n}p^{sq} = \prod\limits_{p\leq\frac{2n}{3}}p^{sq} $（由于推论1.2.3 和 假设）

$\Rightarrow \prod\limits_{p\leq\frac{2n}{3}}p^{sq} \leq \prod\limits_{p\leq \sqrt{2n}}p^{sq-1} * \prod\limits_{p\leq \frac{2n}{3}}p < (2n)^{\frac{\sqrt{2n}}{2}-1} * 4^{\frac{2n}{3}}$（关于指数的分母2，其实应该是$logn$，根据素数定理、、这里做了放缩）

由$\left(\begin{array}{c}2 n \\n\end{array}\right)$的下界$\frac{4^n}{2n}$得$\frac{4^n}{2n} < (2n)^{\frac{\sqrt{2n}}{2}-1} * 4^{\frac{2n}{3}}\Rightarrow 4^{\frac{n}{3}} < 2n^{{\frac{\sqrt{2n}}{2}}}$、、取对数$x \ln 2-3 \ln x<0,x = \sqrt{2n}$

当$x>16,n>128$时与不等式矛盾、、即$n>128$时Bertrand-契比雪夫定理成立、、

当$n<128$，则一个个证、、

故$n>=3$，必存在$p$满足$n<p<2n$.

### 性质

在区间$[1,n],n\geq2$里挑一个合数$x$，则该合数$x$必不包括一个质数$p,n<p<2n$、、由较弱的说明得到、、

## 相关的素数定理

令$\pi(x)$为不大于$x$的素数个数，有$\pi(x) \approx \frac{x}{\ln x}$

证明（没看）貌似十分高深，用到了些非初等证明（不知道是啥）、、记结论、、、、、、、、、、、、

## 一些习题

### P5535 【XR-3】小道消息

1、如果$k+1$是质数、、当$2(k+1)$不存在于$n$中，则一天就可完成、、否则为两天、、

2、如果$k+1$是合数，由于契比雪夫定理可得必存在质数满足$\frac{n+1}{2} < p < n+1$，且$k+1$不包含该质数、、故也只需要两天、、
