# Min_25筛

能 $O(\frac{n^\frac{3}{4}}{\log n})$ **求积性函数的前缀和** 。

对 **积性函数** 有一定要求： $f(p)$ 是简单的多项式或可以快速求值； $f(p^c)$ 能快速求值（求S函数需要用到）。

令 P 为 n 中的素数集合。把问题转化成求前缀和中 $i\in P$ 的答案（即**统计 i 是素数的 f(i) 前缀和**）加上 $i\notin P$ 的答案（即**统计 i 为合数的答案**）。

## Step1

令 $g(n,j) = \sum\limits_{i=1}^n[i\in P \or \operatorname{minp}(i)>p_j]f'(i)$ ，其中 $\operatorname{minp}(i)$ 返回 i 的最小质因子， $p_j$ 为第 j 个质因子， $f'$ 为完全积性函数，且在取素数点时，通过组合 $f'$ 能使值等于 $f$ 。（比如 $f(p) = p^2 - p$ ，那么就构造两个 g ，分别代 $f' = p^2$ ， $f' = p$ ）

当 $p_j^2 > n$ 时， $g(n,j) = g(n,j-1)$ 。考虑 $[1,n]$ 使用埃筛的过程，当选到了一个质数 p ，会从 $p^2,p(p+1),p(p+2),\dots$ 开始筛数。当 $p^2_j > n$ 相当于 $g(n,j-1)$ 已经把数给筛完了。所以 $g(n,j) = g(n,j-1)$ 。

反之，当 $p_j^2 \leq n$ 时，考虑从 $g(n,j-1)$ 中转移。很明显，要减去以 $p_j$ 为最小质因子的i的贡献。式子可以写成：

$g(n,j) = g(n,j-1) - f'(p_j)(g(n / p_j,j-1) - \sum\limits_{k=1}^{j-1}f'(p_k))$

具体意思是，当以 $p_j$ 为最小素因子的数提取因子 $p_j$ 时，由于 $f'$ 是完全积性函数，那么就可以将 $f'(p_j)$ 提取出来。对于提取出来的剩下的因子的素因子都大于等于 $p_j$ 。但减去的 $g(n/p_j,j-1)$ 还包含了小于等于 $p_{j-1}$ 的素数，补回来后就是该式子。

于是，

$g(n, j)=\left\{\begin{array}{l}g(n, j-1) \left(P_{j}^{2}>n\right) \\ g(n, j-1)-f^{\prime}\left(P_{j}\right)\left(g\left(\frac{n}{P_{j}}, j-1\right)-\sum_{i=1}^{j-1} f^{\prime}\left(P_{i}\right)\right)\left(P_{j}^{2} \leq n\right)\end{array}\right.$

那么对于素数的前缀和，明显就等于 $g(n,|P|)$ （此时 $[1,n]$ 只保留了素数的$f'$值，其余的都被筛掉了），其中 $P$ 是所有质数均小于等于 $\sqrt{n}$ 的集合。

不可能把 $g(n,|P|)$ 所有的 n 求出来。但发现递归求 $g$ 的过程，只涉及 $g(\frac{n}{x},j)$ 的计算。即第一个参数的状态个数为 $O(\sqrt{n})$ 。那么把所有的 $\frac{n}{x}$ 预处理出来，然后滚动 dp 求解 $g(n,j)$ 的值。其中 $g(n,0) = \sum\limits_{i=2}^n f'(i)$ （默认 $p_0 = 1$ ，留意 $g$ 的定义）

具体地，先求出 $g(\frac{n}{x},0)$ 的值：

```cpp
for(ll l = 1, r; l <= n; l = r + 1) {
    r = (n / (n / l)), w[++m] = n / l;//m为n/x的编号。可以发现m增加，n/x减小，于是下面的滚动dp就是正着来
    g[m] = sf_(w[m]) - 1;// 处理 g(n / l, 0)。sf_是f'的前缀和，下面的f_是单点求值
    if(w[m] <= sq) id1[w[m]] = m;
    else id2[n / w[m]] = m;
}
```

然后再通过滚动 dp 求出 $g(\frac{n}{x},|P|)$ 的值。

```cpp
ll getid(ll x) {
	if(x <= sq) return id1[x];
	else return id2[n / x];
}
REP(i, 1, tot) { // dp 处理 g 函数 。tot = |P| ,sum[i] 为不大于i的质数位置的f'前缀和
	for(int j = 1; j <= m && prime[i] * prime[i] <= w[j]; j++) {
		g[j] = (g[j] - f_(prime[i]) * (g[getid(w[j] / prime[i])] - sum[i - 1]) % mod + mod) % mod;
	}
}
```

## Step2

令 $S(n,j) = \sum\limits_{i=1}^n [\operatorname{minp}(i)>p_j]f(i)$ 。分成质数和合数两个部分：

$S(n, j)=g(n,|P|)-\sum\limits_{i=1}^{j} f'\left(P_{i}\right)+\sum\limits_{k>j} \sum\limits_{e=1}^{P_{k}^{e} \leq n} f\left(P_{k}^{e}\right)\left[S\left(\frac{n}{P_{k}^{e}}, k\right)+[e>1]\right]$

前面两项是 **质数部分** 。这里就要考虑将 $f'$ 组合成 $f$ 了（比如 $f = p^2 + p ,g(f'=p^2) = g_1,g(f'=p)=g_2$ ， **质数部分** 为 $(g 2(n, |P|)-\sum\limits f_2'(j))+(g 1(n, |P|)-\sum\limits f_1'(j))$ ）。由于 $g(n,|P|)$ 保留了不大于 $P_j$ 的质数，所以要减去。 后面的，当 e = 1 时，后面的式子不加 1 ，由于当 e = 1 时，若后面的贡献为 1 就等于统计了一个质数。而前面已经把该质数统计进去了。

要求的自然是 $S(n,0) + f(1)$ （同样根据定义p_0 = 1，1是没统计进去的）

```cpp
ll S(ll x, int j) {
	if(prime[j] > x) return 0;
	ll Ans = (g[getid(x)] % mod - sum[j] + mod) % mod;//sum[j] = \sum_{i=1}^j f'(P_i)
	for(int i = j + 1; i <= tot && prime[i] * prime[i] <= x; i ++) 
		for(ll e = 1, sp = prime[i]; sp <= x; sp *= prime[i], e ++) 
			Ans = (Ans + f(sp) * (S(x / sp, i) + (e > 1)) % mod) % mod;//留意这里是f，不是f'
	return Ans;
}
```

## SP20173 DIVCNT2 - Counting Divisors (square)

求解 $\sum\limits_{i=1}^{n}d(i^2),n \in [0,1e12]$ 。

min_25 筛的两个必要条件：积性函数 $f(p)$ 为有限项多项式， $f(p^c)$ 可以快速求值。

令 $f(p) = d(p^2)$ ，有 $f(p) = 3,f(p^c) = 2c+1$ ，满足条件。

目前所掌握的知识里，完全积性函数 $f'$ 均由 $i^k$ 担任，即 $f$ 多项式中项数为k，那么就要有 $f'_k = i^k$  。

这里发现 $f(p)$ 的常数项是带系数的（将 $f$ 某项不为1的称作带系数）。回头看 $g$ 的定义：$g(n,j) = \sum\limits_{i=1}^n[i\in P \or \operatorname{minp}(i)>p_j]f'(i)$ ，那么只需要让最初的 $g(n,0) = c \sum\limits_{i=2}^n f'(i)$ ，c为常数（这道题即为3），即可完成min_25筛。

那么 $f' = 1$ ，然后在 $g$ 的初始化中将系数带上。

```cpp
for(ll l = 1, r; l <= n; l = r + 1)
{
    r = n / (n / l);
    val[++m] = n / l;
    if(val[m] <= lim) id1[val[m]] = m;
    else id2[n/val[m]] = m;
    g[m] = 3 * val[m] - 3;//g(n,0)带系数
}
for(int j = 1; j <= tot; j++)
{
    for(int i = 1; 1LL * prime[j] * prime[j] <= val[i]; i++)
    {
        ll tmp = val[i] / prime[j];
        if(tmp <= lim) tmp = id1[tmp];
        else tmp = id2[n/tmp];
        g[i] -= (g[tmp] - sp[j-1]);//注意这里。f'(i) = 1,所以系数为1
    }
}
```

求解好 g ，求解 S 就不会遇到什么问题了。（避免后面觉得求S有问题，把后续代码挂上）

```cpp
ll S(ll x, int y)
{
    if(x < prime[y]) return 0;
    ll tmp = (x <= lim ? id1[x] : id2[n/x]);
    ll ret = g[tmp] - sp[y];
    for(int i = y + 1; i <= tot && 1LL * prime[i] * prime[i] <= x; i++)
    {
        ll pe = prime[i];
        for(int e = 1; pe <= x; e++, pe *= prime[i])
        {
            ret += (2 * e + 1) * (S(x/pe, i) + (e!=1));//f(p^c)
        }
    }
    return ret;
}
```

