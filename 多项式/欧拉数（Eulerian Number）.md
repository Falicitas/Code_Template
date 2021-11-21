# 欧拉数（Eulerian Number）

~~Karry老师说这是常见的组合递推数列？~~

欧拉数的定义：对于长度为 $n$​ ​的排列，从左到右有 $k$​​ 个上升沿的排列的方案数，记为$\left\langle\begin{array}{l}n \\ k\end{array}\right\rangle$​​。

对于排列的方案数的考虑有个trick，即仅考虑子排列中的 **大小关系** ，而不考虑子排列中的元素选择。比如这个问题：

定义 $\left\langle\begin{array}{l} i\\ j\end{array}\right\rangle = dp(i,j)$​​​ 为长度为 $i$​​ ​的排列有 $j$​​​ 个上升沿，有 $dp(i,j) = (i-j)dp(i-1,j-1) + (j+1)dp(i-1,j)$​​​。可以从排列长度为 $i$​​​ 的元素中考虑最小的一个，先去排其他的 $i-1$​ ​​个。对于 $dp(i-1,j-1)$​ ​​中，仅将最小元素插入到原先的下降沿，会使上升沿增加1，其一共有 $(i-j)$​​​ 个位置可以插入；对于 $dp(i-1,j)$​​​ 中，仅将最小元素插入到原先的上升沿，上升沿不变，其一共有 $(j+1)$​​​ 个位置可以插入。故有此 $dp$ ​​​​​方程。

另外根据《具体数学》给出的公式，有

$f(n, k)=\sum\limits_{i=0}^{k+1}\left(\begin{array}{c}n+1 \\ i\end{array}\right)(k+1-i)^{n}(-1)^{i} = \sum\limits_{i=0}^{k+1}\left(\begin{array}{c}n+1 \\ k+1-i\end{array}\right)i^{n}(-1)^{k+1-i}$

​（可以发现跟第二斯特林数很相似，比较明显的不同在于上指标一个是 n+1，一个是k）

$\Rightarrow \frac{f(n,k)}{(n+1)!} = \sum\limits_{i=0}^{k+1}\frac{(-1)^i}{i!(n+1-i)!} * (k+1-i)^n$

令 $g(x) = \sum\limits_{k=0} \frac{(-1)^k}{k!(n+1-k)!}x^k,h(x) = \sum\limits_{k=0}k^nx^k$​，则$f(n,m) = (n+1)! * ((g*h)(m+1))$​。复杂度为 $O(nlogn)$​。

## 欧拉数的等价变式

$\left\langle\begin{array}{l} n \\ m \end{array}\right\rangle = \sum_{j=0}^{n}\left\{\begin{array}{l}n \\ j \end{array}\right\}\left(\begin{array}{c} n-j \\ m \end{array}\right)(-1)^{n-j-m} j !$

## 一些题目

### Luogu P5825 排列计数

欧拉数裸题。

### P6073 『MdOI R1』Epic Convolution

对于 $f_{n}=\sum_{k=0}^{n} k^{n} g_{k} h_{n-k}$​​，给定 $g,f$​​，要求给定四种约束条件，分别求出在这四种条件下的 $f_n$​​ 的值。

**Subtask1**

给一个 $n$​​，有多组询问，每次给一个 $m$​​，$g_k,h_k$​​ 如下：

$g_{k}=\left\{\begin{array}{ll}
1, & k<m \\
0, & k \geq m
\end{array}\right.$

$ h_{k}=1$

求 $f_n$​。

第一个比较简单，发现其为 $\sum\limits_{k=0}^{m-1}k^n$​。预处理出幂次项，取前缀和即可。

**Subtask2**

~~开始变态了~~

多组询问，每次给定 $n,m$​，$g_k,f_k$​ 如下：

$g_{k}=\frac{1}{(k+m+1) !}$

$h_{k}=\left\{\begin{array}{ll}0, & k<m \\ \frac{(-1)^{k-m}}{(k-m) !}, & k \geq m\end{array}\right.$

求 $f_n$​。

首先先不管 $m$​ ​的限制，考虑卷积 $\sum\limits_{k=0}^n k^n \frac{1}{(k+m+1)!}\frac{(-1)^{n-k-m}}{(n-k-m)!}$​​ 的值。

分母两个阶乘 $k+m+1+n-k-m = n+1$​，相对卷积是定值，考虑构造二项式：

$(n+1)!f_n = \sum\limits_{k=0}^n k^n (-1)^{n-k-m}\dbinom{n+1}{k+m+1}$

这里给出一个引理：

> 引理1：$\dbinom{n+1}{k+m+1} = \sum\limits_{j=0}^{n}\dbinom{j}{k}\dbinom{n-j}{m}$
>
> 证明：
>
> 式子里是卷积的形式，故从 **生成函数** 的角度思考：
>
> 构造 $f(x) = \sum\limits_{i=0} \dbinom{i}{k}x^i$​。发现其 $i<k$​ 项皆为 0，考虑位移，有 $f'(x) = \sum\limits_{i=0}\dbinom{i+k}{k}x^i$​。故有 $f(x) = x^k f'(x)$​。
>
> 对于 $f'(x)$ ​来说，有一个很明显的关于**广义二项式**的闭形式：$f'(x) = \frac{1}{(1-x)^{k+1}}$​（广义二项式很明显的特征即是下指标为一个常量$k$​，上指标为 $k+i$​，$i$​ 为变量。当然不要漏了符号）故 $f(x) = \frac{x^k}{(1-x)^{k+1}}$​，同理有后一项系数的生成函数 $g(x) = \frac{x^m}{(1-x)^{m+1}}$​​​​。
>
> 两式作乘，原答案为 $[x^n]\frac{x^{k+m}}{(1-x)^{k+m+2}}$​​​​，由上文可知 $\frac{x^{q}}{(1-x)^{q+1}}$​​​​的形式已求得，所以转化成 $G(x) = \sum\limits_{i=0}\dbinom{i}{k+m}x^i$​​​​ 与 $\frac{1}{1-x}$​​​​ 作乘。而根据之前「P5488 差分与前缀和」可知，乘 $\frac{1}{1-x}$​​​​ 就是做一阶前缀和，故有 $[x^n]\frac{x^{k+m}}{(1-x)^{k+m+2}} = \sum\limits_{i=0}^n\dbinom{i}{k+m}$​​​​，其为上指标求和，等于 $\dbinom{n+1}{k+m+1}$​​​​，证毕。

回到原式，展开组合数：

$(n+1)!f_n = \sum\limits_{k=0}^n k^n (-1)^{n-k-m}\sum\limits_{j=0}^{n}\dbinom{j}{k}\dbinom{n-j}{m}$​，由于 $j=0\ to\ n$​ 中 $j<k$​ ​时没有值，调整一下上下限，将遍历放前面：

$\Rightarrow (n+1)!f_n = \sum\limits_{k=0}^n\sum\limits_{j=k}^{n} k^n (-1)^{n-k-m}\dbinom{j}{k}\dbinom{n-j}{m}$。考虑变换遍历顺序：

$(n+1)!f_n = \sum\limits_{j=0}^{n}\sum\limits_{k=0}^j k^n (-1)^{n-k-m}\dbinom{j}{k}\dbinom{n-j}{m}$，根据遍历顺序移动一下位置，顺便分配$(-1)$：

$=\sum\limits_{j=0}^n (-1)^{n-m-j}\dbinom{n-j}{m}\sum\limits_{k=0}^{j}k^n(-1)^{j-k}\dbinom{j}{k}$

后面那个的形式是关于 **第二斯特林数** 的（$\left\{\begin{array}{l}n \\ k\end{array}\right\}$​展开式为$ k!\left\{\begin{array}{l} n \\ k \end{array}\right\} = \sum\limits_{i=0}^{k}(-1)^{k-i}i^n\dbinom{k}{i}$​特征是带有遍历变量 $i$ ​的 $n$​ 次幂，即$i^n$​ 的形式）

故有 $(n+1)!f_n = \sum\limits_{j=0}^n(-1)^{n-m-j}\left\{\begin{array}{l} n \\ j \end{array}\right\}\dbinom{n-j}{m}j!$​。又**第二斯特林数**的，**组合数和阶乘**的，~~可能~~是欧拉数。等式右侧恰为$\left\langle\begin{array}{l}n \\ m\end{array}\right\rangle$​，故$f_n = \frac{\left\langle\begin{array}{l}n \\ m\end{array}\right\rangle}{(n+1)!}$​

由于 $n\leq m$ ​时上式为 $0$​，即可证明与原问题给定的 $g,h$​​ 所做的卷积是等价的。

由于 $m$​ 很小，故可以根据这个式子，

$\left\langle\begin{array}{l}n \\ m\end{array}\right\rangle=\sum_{k=0}^{m}\left(\begin{array}{c}n+1 \\ k\end{array}\right)(m+1-k)^{n}(-1)^{k}$​​，

$O(nm)$​​ 预处理幂。由于组合数的计算仅受下指标的大小的影响（即 $min(m,n-m)$​​）也可以 $O(m)$​​ 线求，故复杂度为 $O(nm+qm)$​​。至于为什么不用 $dp$​​​​​ 求，是考虑到此方法也可在 **Subtask3** 用上。

**Subtask3**

询问变少，$n\in[0,mod-1]$，唯一难快速计算的就只有阶乘了。但考虑模数不变，可以 **分块打阶乘的表** ，然后可以在 $\sqrt{M},M$ 为模数（这里即将块的大小设为$\sqrt{M}$），然后就可以过了。tql，分块打阶乘表。

**Subtask4**

多组询问，每次给定 $n,m$​，$g_k,f_k$​ 如下：

$g_{k}=\frac{k^{m}}{k !}$

$h_{k}=\frac{(-1)^{k}}{k !}$

求 $f_n$​。

式子为 $\sum\limits_{k=0}^n k^n \frac{k^m}{k!}\frac{(-1)^{n-k}}{(n-k)!}$​，这个还是比较明显的，即为斯特林数$\left\{\begin{array}{c}n+m \\ n\end{array}\right\}$​。

引入两个重要恒等式：

$\left\{\begin{array}{c}x \\ x-n\end{array}\right\}=\sum_{k}\left\langle\left\langle\begin{array}{c}n \\ k\end{array}\right\rangle\right\rangle\left(\begin{array}{c}x+n-1-k \\ 2 n\end{array}\right)$

$\left[\begin{array}{c}x \\ x-n\end{array}\right]=\sum_{k}\left\langle\left\langle\begin{array}{l}n \\ k\end{array}\right\rangle\right\rangle\left(\begin{array}{c}x+k \\ 2 n\end{array}\right)$

其中 $\left\langle\left\langle\begin{array}{l}n \\ k\end{array}\right\rangle\right\rangle$​ 为二阶欧拉数。

考虑一式，组合数 $\left(\begin{array}{c}x+n-1-k \\ 2 n\end{array}\right)$​​ ​按降阶幂考虑，次数为 $2n$​​​，可推出 $\left\{\begin{array}{c}x \\ x-n\end{array}\right\}$​​​ 次数也为 $2n$​​​。

由于本题的 $m$ ​很小，**插值计算** $m\in [0,10]$​ 的多项式，最后用秦九韶计算就行了。

**Subtask5**

计算 $\sum_{k=0}^{m}(k+1)^{m} \frac{(k+1)^{n+1}}{(k+1) !} \sum_{i=0}^{m-k} \frac{\left(\begin{array}{c}2 n+1 \\ i\end{array}\right)(-1)^{m-k}}{(m-k-i) !(k+1)^{i}}$​

~~也是常规的变换遍历顺序，拆项分配的推式子操作~~

推出$a n s=\sum_{i=0}^{m}\left(\begin{array}{c}2 n+1 \\ i\end{array}\right)(-1)^{i}\left\{\begin{array}{c}n+m+1-i \\ m+1-i\end{array}\right\} = \left\langle\left\langle\begin{array}{l}n \\ m\end{array}\right\rangle\right\rangle$

其中二阶欧拉数也有组合意义：对于多重集 $\{1,1,2,2,\dots,n,n\}$​ ​来说，对于某个数 $m\in[1,n]$​​，$m$​​ 出现两次之间的数均大于 $m$​​ 的排列个数。

~~这里苟了Karry老师的dp式~~

令 $dp(n,k) = \left\langle\left\langle\begin{array}{l}n \\ k\end{array}\right\rangle\right\rangle$​，有 $dp(n,k) = (k+1)dp(n-1,k) + (2n-1-k)dp(n-1,k-1)$​，边界条件为

$\left\langle\left\langle\begin{array}{l}n \\ 0\end{array}\right\rangle\right\rangle = 1,\left\langle\left\langle\begin{array}{l}n \\ k\end{array}\right\rangle\right\rangle = 0,k>n$​​​

$dp$一下就完事了。









由于组合数在 OI 中十分重要，因此在此介绍一些组合数的性质。

$$ \binom{n}{m}=\binom{n}{n-m}\tag{1} $$

相当于将选出的集合对全集取补集，故数值不变。（对称性）

$$ \binom{n}{k} = \frac{n}{k} \binom{n-1}{k-1}\tag{2} $$

由定义导出的递推式。

$$ \binom{n}{m}=\binom{n-1}{m}+\binom{n-1}{m-1}\tag{3} $$

组合数的递推式（杨辉三角的公式表达）。我们可以利用这个式子，在 $O(n^2)$ 的复杂度下推导组合数。

$$ \binom{n}{0}+\binom{n}{1}+\cdots+\binom{n}{n}=\sum_{i=0}^n\binom{n}{i}=2^n\tag{4} $$

这是二项式定理的特殊情况。取 $a=b=1$ 就得到上式。

$$ \sum_{i=0}^n(-1)^i\binom{n}{i}=[n=0]\tag{5} $$

二项式定理的另一种特殊情况，可取 $a=1, b=-1$。式子的特殊情况是取 $n=0$ 时答案为 $1$。

$$ \sum_{i=0}^m \binom{n}{i}\binom{m}{m-i} = \binom{m+n}{m}\ \ \ (n \geq m)\tag{6} $$

拆组合数的式子，在处理某些数据结构题时会用到。

$$ \sum_{i=0}^n\binom{n}{i}^2=\binom{2n}{n}\tag{7} $$

这是 $(6)$ 的特殊情况，取 $n=m$ 即可。

$$ \sum_{i=0}^ni\binom{n}{i}=n2^{n-1}\tag{8} $$

带权和的一个式子，通过对 $(3)$ 对应的多项式函数求导可以得证。

$$ \sum_{i=0}^ni^2\binom{n}{i}=n(n+1)2^{n-2}\tag{9} $$

与上式类似，可以通过对多项式函数求导证明。

$$ \sum_{l=0}^n\binom{l}{k} = \binom{n+1}{k+1}\tag{10} $$

可以通过组合意义证明，在恒等式证明中较常用。

$$ \binom{n}{r}\binom{r}{k} = \binom{n}{k}\binom{n-k}{r-k}\tag{11} $$

通过定义可以证明。

$$ \sum_{i=0}^n\binom{n-i}{i}=F_{n+1}\tag{12} $$

其中 $F$ 是斐波那契数列。

$$ \sum_{l=0}^n \binom{l}{k} = \binom{n+1}{k+1}\tag{13} $$

通过组合分析——考虑 $S={a_1, a_2, \cdots, a_{n+1}}$ 的 $k+1$ 子集数可以得证。