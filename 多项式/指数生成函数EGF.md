# 指数生成函数EGF

可以用来解决一些 **排列计数** 的问题。

式子为

$\hat{G}(x)=a_{0}+a_{1} x+a_{2} \frac{x^{2}}{2 !}+a_{3} \frac{x^{3}}{3 !}+a_{4} \frac{x^{4}}{4 !}+\cdots=\sum_{i=0}^{\infty} a_{i} \frac{x^{i}}{i !}$​

## 基本运算与常用式子

### 基本运算，闭形式

对于每一项来说，指数生成函数同样产生卷积运算。这里以两个指数生成函数的乘积为例：

$\begin{aligned}
\hat{F}(x) \cdot \hat{G}(x) &=\left(\sum_{i=0}^{\infty} a_{i} \frac{x^{i}}{i !}\right)\left(\sum_{i=0}^{\infty} b_{i} \frac{x^{i}}{i !}\right) \\
&=\sum_{n=0}^{\infty}\left(\sum_{i=0}^{n} \frac{a_{i} x^{i}}{i !} \cdot \frac{b_{n-i} x^{n-i}}{(n-i) !}\right) x^{n} \\
&=\sum_{n=0}^{\infty}\left(\sum_{i=0}^{n}\left(\begin{array}{l}
n \\
i
\end{array}\right) a_{i} b_{n-i}\right) \frac{x^{n}}{n !}
\end{aligned}$

看起来十分的复杂。其实对于一般的指数生成函数的乘积的情况可以转化为其闭形式，能 **极大地** 简化生成函数的计算，以及快速推出某一项的系数。

最基本的闭形式为：$\hat{G}(x)=1+x+\frac{x^{2}}{2 !}+\frac{x^{3}}{3 !}+\ldots=e^{x}$，剩余的放在 **常用的** 的式子中。

### 常用的式子

* $\hat{G}(x)=1+x+\frac{x^{2}}{2 !}+\frac{x^{3}}{3 !}+\ldots=e^{x}$ 

* $\hat{G}(x)=1-x+\frac{x^{2}}{2 !}-\frac{x^{3}}{3 !}+\ldots=e^{-x}$

* $\hat{G}(x)=1+\frac{x^{2}}{2 !}+\frac{x^{4}}{4 !}+\frac{x^{6}}{6 !}+\ldots=\frac{e^{x}+e^{-x}}{2}$

* $\hat{G}(x)=x+\frac{x^{3}}{3 !}+\frac{x^{5}}{5 !}+\frac{x^{7}}{7 !}+\ldots=\frac{e^{x}-e^{-x}}{2}$

* $\hat{G}(x)=x-\frac{1}{2} x^{2}+\frac{1}{3} x^{3}+\cdots=\ln (1+x)$

* $\hat{G}(x)=x+\frac{1}{2} x^{2}+\frac{1}{3} x^{3}+\cdots=-\ln (1-x)$

$\hat{G}(x)=x-\frac{1}{3 !} x^{3}+\frac{1}{5 !} x^{5}+\cdots=\sin x$

$\hat{G}(x)=x+\frac{1}{2} \times \frac{x^{3}}{3}+\frac{1 \times 3}{2 \times 4} \times \frac{x^{5}}{5}+\frac{1 \times 3 \times 5}{2 \times 4 \times 6} \times \frac{x^{7}}{7} + \dots=\arcsin x$

$\hat{G}(x)=1-\frac{1}{2 !} x^{2}+\frac{1}{4 !} x^{4}+\cdots=\cos x$

$\hat{G}(x)=1+\frac{a}{1 !} x+\frac{a(a-1)}{2 !} x^{2}+\frac{a(a-1)(a-2)}{3 !} x^{3}+\cdots=(1+x)^{a}$

## 可重排列，指数生成函数

$n$ 个元素由 k 种元素组成，每种元素个数为 $|S_i|$，此时可重排列产生的方案数为 $\frac{n!}{\prod\limits|S_i|!}$。

感性证明：仅考虑有一种元素是重复的，记作 $a_1$​​。全排列个数为 $n!$​​，要减去 $a_1$​​ 带来的重复。那么有 $n! - \genfrac(){0}{0}{n}{a_1}(n-a_1)!*(a_1!-1)$​​，由于对于 $a_1$​​，仅算一种方案。原式变为 $\frac{n!}{a_1!}$​​​。多个元素则按类似的证明来。

两个 EGF 相乘的意义是什么？考虑其中两项，$\frac{x^3}{3!},\frac{6x^5}{5!}$​，乘起来为$6 * \frac{\frac{8!}{3!5!}}{8!}x^8$​，此时 $6 * \frac{8!}{5!3!}$​​ 即为两状态的可重排列的方案数。

## 排列与圆排列，树与森林，连通块与图

全排列的指数生成函数为 $f(x) = \frac{1}{1-x}$​

圆排列的指数生成函数为

$g(x) = \sum\limits_{i=1}\frac{x^i}{i} = -\ln(1-x) = \ln(\frac{1}{1-x})$​

在函数性质上，可以看出 $f(x) = e^{g(x)}$​，其也具有实际意义：

「置换环」（亦有**轮换**一说）：一个排列，由若干个置换环置换一次后恢复 $1,2,3,...,n$​​​，置换环即由 $P_i\rightarrow i$​ ​​构成的环（当然是可以逆过来的，换个方向即可。形状可见[OI WIKI-指数生成函数](https://oi-wiki.org/math/gen-func/egf/)）。即对于一个排列，其由一个置换环 or 两个置换环 or...or $n$​​​个置换环构成。对于由 $m$​​​ 个置换环构成的排列，置换环间构成 **可重排列关系** （即它们是对 $1\sim n$​​​ 的划分），而每个大小为 $i$​​​ 的置换环内有 $(i-1)!$​​​ 中排列形式，故用 EGF 来生成圆排列 $g$​​​，有 $f = \sum\limits_{i=0}\frac{g^i}{i!}$​​​，这里的$i$​​​除掉生成函数累乘的顺序。所以 $f = e^g$​​​​。

类似的：

如果 $n$​ 个点**带标号**生成树的 EGF 是 $\hat{F}(x)$​，那么 $n$​ 个点 **带标号** 生成森林的 EGF 就是 $\exp \hat{F}(x)$​ ——直观理解为，将 $n$​ 个点分成若干个集合, 每个集合构成一个生成树的方案数之积。

如果 $n$​ 个点 **带标号** 无向连通图的 EGF 是 $\hat{F}(x)$​，那么 $n$​ 个点带标号无向图的 EGF 就是 $\exp \hat{F}(x),$​ 后者可以很容易计算得到 $\exp \hat{F}(x)=\sum_{n \geq 0} 2^{\left(\begin{array}{c}n \\ 2\end{array}\right)} \frac{x^{n}}{n !}$​​。因此要计算前者，需要一次多项式 ln 即可。

### P4841 [集训队作业2013]城市规划

OGF 版本见「普通生成函数OGF」。

一改 QAQ 原题解写的比较长，但有些问题。

依据上面的公式求解即可。

### 错排和错排数

错排数就是规模为 $n$​​ 的错排数目的方案数。对于一个错排，即由若干个置换环构成，且任意置换环大小大于 1。

对于一个置换环来说，列出指数生成函数：

$f(x) = \sum\limits_{i=2} \frac{x^i}{i} = -\ln(1-x) - x$​​

易知错排的 EGF 为：

$g(x) = e^f$。

### 不动点

发现问题为一个深度不超过 k 的基环森林的方案数（基环树就是一个图上有个环，环上的某一点代表一个树的根节点，这里的环包括自环），由于只是自环，等价于深度不超过k的森林的方案数。

根据上面的知识，套路的设 $\hat{F_k(x)}$​​ ​为深度不超过k的有根树的方案数，明显 $\hat{F}$​​​ 间是**错排关系**。$F_k$​​​ 与 $F_{k-1}$​​​ 的关系是，$F_{k-1}$​​​ 所组合构成的森林上再加个节点（因为 $F_k$​ ​​代表的还是一棵树嘛），故 $F_k(x) = xe^{F_{k-1}}$​​​。明显 $F_1(x) = x$​​​​。

深部不超过 $k$​ 的森林，obviously，$G_k(x) = e^{F_k}$​。

卡常，对于深度不超过 1 的森林的方案数提前预处理出来，可减少一半的复杂度。

### CF891E Lust

对于 $a_1,a_2,\dots,a_n$​，有 $k$ ​次操作，每次操作随机选 $x\in [1,n]$​，将 $a_x$ ​减 1，同时答案加上 $\prod\limits_{i\neq x} a_i$​。询问答案的期望。

发现答案为 $S = \prod\limits_{i=1}a_i - \prod\limits_{i=1}(a_i-b_i),\sum\limits_{i=1}b_i = k$​。

所以问题转化为求 $\prod\limits_{i=1}(a_i-b_i)$​​ ​的期望。要使 $\sum\limits_{i=1}b_i = k$​​​，而 $a_i$​​​ 各异，即可以往 EGF 方向思考：$[x^i]f_j(x) = c_i\frac{x^i}{i!}$​​​ 为第 $j$ ​​​个数被减了 $i$​​​ 次的方案数，由于答案求得是 $\prod\limits_{i=1}(a_i - b_i)$​​​，当 $c_i = (a_j - i)$ ​​​去构造答案的生成函数是正确的qwq所以有 $f_j(x) = \sum\limits_{i=0}(a_j - i)\frac{x^i}{i!}$​​​。用 EGF 的闭形式**简化运算**：

$f_j(x) = a_j\sum\limits\frac{x^i}{i!} - \sum\limits\frac{x^i}{(i-1)!} = (a_j - x)e^x $​​​​​​

期望的生成函数为 $e^{nx}\prod\limits_{i=1}(a_i - x) $​​​，对于前者，由于 $n=5e3$​​​，可以暴力算；设算完的多项式为 $g(x) = \sum c_i x^i$​​​，两式的卷积为 $G(x) = \sum\limits_{i=0} x^i \sum\limits_{j=0}^{i} c_j\frac{1}{(i-j)!} = \sum\limits_{i=0} x^i \sum\limits_{j=0}^{i} n^{i-j} i^{\underline{j}} c_{j}$​​​，只需要求第 $k$​​​ 项。由于 $c_j$​​​ 的项很少，$deg = n$​​​，故答案为 $\prod\limits_{i=1}a_i - \sum\limits_{j=0}^{k}\frac{n^{k-j}k^{\underline{j}}c^j}{n^k}$​​​​​​，分母为方案的所有可能性。

