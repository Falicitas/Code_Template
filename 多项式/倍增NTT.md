# 倍增NTT

倍增 NTT，适用于解决一类带卷积的 dp 方程。

其核心是考虑将 dp 方程的状态表示成多项式的形式，并考虑**两个状态的合并**，从而实现在可接受的时间复杂度内完成程序运行。

设 $dp(i,j)$​​ 为操作 $i$​​ 次状态 $j$​​ 的方案数，要求操作 $n$​​ 次后对应的状态方案数。有诸如 $dp(i,j) = \sum\limits_{k=0}^{j} dp(i-1,k) * g(j-k)$​​​ 的式子，此时就可用倍增 NTT 来加速规划过程：

> 考虑将两个状态合并，即需要 $dp(n+m,j)$​ 与 $dp(n,k),dp(m,j-k),k\in[0,j]$ ​的**合并关系**，写成类似$dp(n+m,j) = \sum\limits_{k=0}^{j}dp(n,k) * g_1(k) * dp(m,j-k) * g_2(j-k)$​的形式。此时将 $m$​ 换成 $n$​，即$dp(2n,j) = \sum\limits_{k=0}^{j}dp(n,k) * g_1(k) * dp(n,j-k) * g_2(j-k)$​​。
>
> 将操作 $n$​​ 次按二进制分解，从高到低将操作数通过**倍乘和+1**从初始操作 $1$​​ 次运算到 $n$​​ 次。

## 代码

由于有两个操作，**倍乘和+1**，故需要两个方程：

$dp(n,k),dp(n,j-k) \rightarrow dp(2n,j)$

$dp(n,k) \rightarrow dp(n+1,j)$

```cpp
for(i=1 to k) f[i] = ...;//初始化操作数为1的多项式f
ub = log2(n)
for(int i=ub-1;i!=-1;i--){
    mul(f);//n -> 2n
    if(n&(1<<i)) add(f);// n -> n+1
}
get f//此时多项式f为操作n次后的f
```

## 一些习题

### CF755G PolandBall and Many Other Balls

有 $n$​ ​个球，每次可以将 $1$​ ​个球或者连续的 $2$​ ​个球归为一组。问分成 $1,2,...,k$​​ 个球的方案数。$n\leq 1e9,k\leq 3e4$​​​。

考虑 $dp$​​​。令 $dp(i,j)$​​​ 为前 $i$ ​​​个球构成 $j$ ​​​组的方案数，易得$dp(i,j) = dp(i-1,j-1) + dp(i-2,j-1) + dp(i-1,j)$​​​。

考虑两个状态的合并：有

$dp(2n,j) = \sum\limits_{k=0}^{j}dp(n,k)*dp(n,j-k) + \sum\limits_{k=0}^{j-1}dp(n-1,k)*dp(n-1,j-1-k)$​

由于

$dp(2n) = dp(n) * dp(n) + x * dp(n-1) * dp(n-1)$​​

$dp(2n-1) = dp(n-1) * dp(n) + x * dp(n-2) * dp(n-1)$

$dp(2n-2) = dp(n-1) * dp(n-1) + x * dp(n-2) * dp(n-2)$

故需要维护三个多项式 $f_{i},f_{i-1},f_{i-2}$​。

注意常数QAQ

### CF623E Transforming Sequence

问题等价于：$n$ 个元素，$m$ 种操作，每次取之前操作没取过的至少一个元素，之前取过的元素随意，问方案数。

首先易设出 $dp$，$f(i,j)$ 为第 $i$ 次操作，有 $j$ 个元素的方案数。$f(i,j) = \sum\limits_{k=1}^{j}f(i-1,j-k)\dbinom{n-(j-k)}{k}2^{j-k}$​​。

其不方便写成卷积式，故状态改为：$g(i,j)$​​ 为 $i$​​ 次操作，取**特定** $j$​​ 个元素的方案数，有 $g(i,j) = \frac{f(i,j)}{\dbinom{n}{j}}$​​

考虑前 $j$​ 个元素，其相当于**特定**了 $j$​ 个位置，故有方程：$g(n+m,j) = \sum\limits_{k=0}^{j}g(n,k)*g(m,j-k) * \dbinom{j}{k} * (2^{k})^{m}$​

可以这样理解：分两步来取元素，第一步从前 $j$​​​​​ 个位置中挑 $k$​​​​​ 个特定位置给 $dp(n,k)$​​​​​，故有 $\dbinom{j}{k}$​​​​​；第二步放置 $g(m,j-k)$​​ ​​​时，每一步的放置前都已有$k$​​​​​个位置了，共操作 $m$​​ ​​​步，故有 $(2^{k})^m$​​​​​，相当于状态 $g(m,j-k)$​​​​​ 中扩展了二维矩阵 $k \times m$​​​​​

由于 $g(i,j)$​​ 为 $i$​ ​次操作，取**特定** $j$​​ 个元素的方案数，故 $g(1,j) = [1\leq j \leq n]$​​​.

将**倍乘与+1**两个方程列出：

$g(2n,i) = i! \sum\limits_{j=0}^{i}\frac{g(n,j)2^{jn}}{j!} * \frac{g(n,i-j)}{(i-j)!}$

$g(n+1,i) = \sum\limits_{j=1}^{i}\frac{g(n,i-j)*2^{i-j}}{(i-j)!} * \frac{1}{j!}$​（注意 $\frac{1}{j!}$ ​在常数项没有值，即值取0）

由于模数为 $1e9+7$​，用 MTT 来整。

### CF773F Test Data Generation

生成测试数据并非简单的任务！生成大的随机数据通常不能够完全保证解法的正确性。举个例子，考虑以前 Codeforces round 的一道题。它的输入格式如下:

第一行是一个整数 $n\left(1 \leq n \leq m a x_{n}\right)$ 表示集合的大小，第二行包含 $n$ 个互不相同的整数 $a_{1}, a_{2}, \ldots, a_{n}\left(1 \leq a_{i} \leq m a x_{a}\right)$​ 表示集合中的元素，升序排列。

如果你不注意题目的解法，看起来生成一个好的测试数据是非常容易的。令 $n=\max _{n}$, 从 $1 \sim \max _{a}$ 中生成 $n$ 个不相同的数，并排序。但是马上你就会知道这不那么简单。
下面是这道题目的真实解法。令 $g$ 为 $a_{1}, a_{2}, \ldots, a_{n}$ 的最大公约数，令 $x=a_{n} / g-n$，如果 $x$ 是奇数输 出 Alice, 如果 $x$ 是偶数输出 Bob
考虑这道题两个错误的解法，它们与正解只在计算 $x$ 中不同。
第一个解法令 $x=a_{n} / g \quad$（不减去 $n$）
第二个解法令 $x=a_{n}-n$（不除以 $g$）
如果一个测试数据令这两个解法都输出错误的答案，称这个数据是有趣的。
给定 $\max _{n}, \max _{a}, q$ 求满足限制且有趣的测试数据的数量对 $q$ 取模的结果。
$1 \leq \max _{n} \leq 30000, \max _{n} \leq \max _{a} \leq 10^{9}, 10^{4} \leq q \leq 10^{5}+129$​​​

基本是照着[Vocalise的题解](https://www.luogu.com.cn/blog/vocalise/solution-cf773f)来写的。

当初写的时候是想照着枚举公因数为 $2^{w_i}*c$​​​ 来描述状态 $dp(w_i,n)$​ ​​的，发现明显 $dp$​​​ 式基本不可能写递推。

个人觉得将状态设计成 $f_p(a,n)$​​​ 表示范围 $[1,a]$​​​ 中取 $n$​ ​​个数，且末尾为 $p$​​​​ 数（p=1 时为奇数）的出发点有：

> 之前的状态明显无法递推。
>
> 奇偶性，跟答案为 $\sum\limits_{k=1}f_1(\frac{max_a}{2^k},n)$​ 有关，同时跟合并信息有关。主观觉得分奇偶是设计该状态的主要因素。
>
> 上限 $max_a$​ ​是 $1e9$ ​​级别的- -所以倍增的对象很大可能是它。

然后多练，感觉，应该还是可以设计正确的状态及方程的。

