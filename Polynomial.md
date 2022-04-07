[toc]

# 贝尔数

贝尔数，即 $Bell(n)$​，其组合意义为：将有标号的 $n$ ​​个球分成若干非空集合的个数。

最简单的计算方法：

> 令 $f(x)$​​ 为非空集合的指数生成函数，易知 $f(x) = e^x - 1$​​。
>
> 显然答案的生成函数为 $G(x) = e^{f(x)}$​

看到有暴力推式子的，也记录下来。

显然答案为 $\sum_{i=1}^{n}\left\{\begin{array}{l}n \\ i\end{array}\right\}$​

考虑答案的 EGF：$G(x) = \sum\limits_{n \geq 0} \frac{x^{n}}{n !} \sum\limits_{i \geq 0}\left\{\begin{array}{l}n \\ i\end{array}\right\}$​

暴力展开斯特林数，有

$G(x) = \sum\limits_{n \geq 0} \frac{x^{n}}{n !} \sum\limits_{i \geq 0} \frac{1}{i !} \sum\limits_{j \geq 0}(-1)^{i-j}\left(\begin{array}{l}i \\ j\end{array}\right) j^{n}$

后面的式子只有一项系数跟$n$有关，将$n$的遍历顺序放在后面，构成生成函数的闭形式：$G(x) = \sum\limits_{i \geq 0} \frac{1}{i !} \sum\limits_{j \geq 0}(-1)^{i-j}\left(\begin{array}{l}i \\ j\end{array}\right) e^{j x}$

后面的式子显然是二项式的展开形式，有

$G(x) = \sum\limits_{i \geq 0} \frac{1}{i !}\left(e^{x} - 1\right)^{i}$

$G(x) = e^{e^x - 1}$

# 常系数齐次线性递推

求 $f_{n}=\sum_{i=1}^{k} a_{i} f_{n-i}$，既没有常数项系数为 0。$k<32000,n<1e9$​

考虑递推矩阵 $A$​,

$A = \left[\begin{array}{cccc}a_1 & a_2 & \cdots & a_{k-1} & a_k \\
1 & 0 & \cdots & 0 & 0 \\
0 & 1 & \cdots & 0 & 0 \\
\vdots & \vdots & \ddots & \vdots & \vdots \\
0 & 0 & \cdots & 1 & 0\end{array}\right]$。

用矩阵快速幂是 $O(k^3logn)$ 的，显然不行。

实际只关心转移矩阵 $A^nSt$​​​ ​的第 $k$​​​​ 项，$St = \left[\begin{array}{cccc} f_{k-1} \\ f_{k-2} \\ \vdots \\ f_0\end{array}\right]$​​​​为初始向量。由于 $A^n$​​ ​​实际是对 $A$​​​​ 的若干次线性变换，假设能够造出一个 **神奇** 的序列 $c_i$​​​​，使得 $A^n = \sum\limits_{i=0}^{k-1}c_iA^i$​​​​ 成立。

由于我们只关心 $A^nSt$​​ ​的第 $k$​ ​​项，左右乘 $St$​​​，有

$A^nSt = \sum\limits_{i=0}^{k-1}c_iA^i St$​​​​，发现右侧为 $k$​​​ ​个向量的加法结果，故有 $(A^nSt)_k = (\sum\limits_{i=0}^{k-1}c_iA^i St)_k$​​​​，即只取其第 $k$​​​​ 项，记 $Ans = (A^nSt)_k$​​​​，$Ans = (\sum\limits_{i=0}^{k-1}c_iA^i St)_k$​​​​。$(A_iSt)_k$​ ​​​等于什么？不就等于 $f_0,f_1,\dots,f_{k-1}$​ ​​​嘛。故 $Ans = \sum\limits_{i=0}^{k-1}c_if_i$​​​​。现在要求的就是 $c_i$​​​​​ 序列了。

基于式子 $A^n = \sum\limits_{i=0}^{k-1}c_iA^i$​​​，考虑除法多项式 $F(x) = Q(x)G(x) + R(x)$​​​，将矩阵当做多项式的输入，即 $F(A) = Q(A)G(A) + R(A)$​​​（用除法多项式的原理是基于式子由一个类多项式取模构成。不得不说很nb）。钦定 $deg(G(x)) = k,F(x) = x^n$​​​，此时 $R(x)$​​​ 就可以表示成$R(x) = \sum\limits_{i=0}^{k-1}c_ix^i$​​​的形式（由于 $deg(R(x))\leq k-1$​​​），即 $A^n = Q(A)G(A) + \sum\limits_{i=0}^{k-1}c_iA^i$​​​。要是此时 $G(A) = 0$​​​，即$\sum\limits_{i=0}^{k}g_iA^i = 0$​​​，此时求得的 $R(x)$ ​​​的系数就是我们想要的 $c_i$​​​​​​​。

即现在要求 $G(x),G(x)$​ ​满足 $\sum\limits_{i=0}^{k}g_iA^i = 0$​​。

基于上式的思路，将上述式子的主元看成矩阵，即要构造以矩阵为主元的多项式 $G(A)$​ ​使得 $G(A) = 0$​​。

这里引入**特征向量**与**特征值**的知识，具体的在「特征值 & 特征向量」有详细讲。

引入**Cayley-Hamilton定理**：$\prod_{k}\left(\lambda_{k} I-A\right)=0$​​ 在 $A$​​ 满秩时恒成立，$\lambda_k$ ​​为 $A$​​ 的第 $k$ ​​个特征值。

证明：

首先形如 $(\lambda_1I - A)(\lambda_2I - A) = \lambda_1I\lambda_2I - \lambda_1IA - A\lambda_2I + A^2 = (\lambda_2I - A)(\lambda_1I - A)$​，即形如 $(\lambda_iI - A)$​ 的矩阵相乘具有交换律。

要证 $\prod_{k}\left(\lambda_{k} I-A\right)=0$​​，只需证这个矩阵乘上任意向量都等于向量 $0$​​。由于 $A$​ ​满秩，有 $n$​ ​组线性无关的特征向量，以这 $n$ ​​组向量可构成 $n$​​ 维的向量空间。即只需证对于任意特征向量乘该矩阵均为 $0$​​​​。

$\prod_{k}\left(\lambda_{k} I-A\right) *v_i = \prod_{k\neq i}(\lambda_kI - A) (\lambda_iI - A)*v = \prod_{k\neq i}(\lambda_kI - A) * 0 = 0$，得证。

此时 $\prod_{k}\left(\lambda_{k} I-A\right)$​​​​​​ ​不就是想要的 $R(A)$​​​​​​​ 嘛。只要关于主元 $A$​​​​​​​ 的系数 $g_0,g_1,\dots,g_k$​​​​ ​​​即可。明显很难求（毕竟是矩阵运算）。可当主元 $A$​​​​​​​ 可以写成该形式 $\lambda I$​​​​​​​（此时的主元 $A$​​​​​​​ 是单位矩阵的倍数形式），就可把 $\lambda$​​​​​​​ 当做主元，其多项式的根就为 $\lambda_1,\lambda_2,\dots,\lambda_k$​​​​​​​。而回顾**特征多项式**的定义，$f(\lambda) = det(\lambda I - A)$​​​​​​​，$f$​​​​​​​ 的根就是 $\lambda_1,\lambda_2,\dots,\lambda_k$​​​​​​​，也与上面的函数同阶，根据**插值定理**可知两个式子的系数相同。对于一般的 $det(\lambda I - A)$​​​​​​​ 是很难算的，除非其有**特殊**的矩阵结构。而恰好本题的转移矩阵$A$​​​​​​​就很特殊，手动行列式展开余子式有 $f(\lambda)=(-1)^{k}\left(\lambda^{k}-\sum\limits_{i-1}^{k} a_{i} \lambda^{k-i}\right)$​​​​​​​。由于等式 $=0$​​​​​​​，故以 $x$​​​​​​​ 轴翻转函数也可以，故 $G(x) = \sum\limits_{i=0}^{k-1}a_{k-i}x^i - x^k$​​​​​​​​​。

由于 $x^n$​​ 的 $n$​​ 很大，要写倍增版取模。有个 trick，由于模数为同一个**特征多项式**，可以预处理求逆，翻转，求点值等，降低复杂度。

**初始值个数要跟递推系数个数相同，否则求不了**。

## 算法流程

转移系数 $a_i$​​​​（照式子 $f_{n}=\sum_{i=1}^{k} a_{i} f_{n-i}$​​​​）用来得到 $G(x)$​​​​，其中 $g_i = a_{k-i},i<k,g_k = -1$​​​​。求 $x^n \bmod G(x)$​​ ​​的结果多项式 $C(x) = \sum\limits_{i=0}^{k-1}c_ix^i$​​​​，则答案为 $Ans = \sum\limits_{i=0}^{k-1}c_if_i$​​​​​​​。

## 代码

```cpp
//code sourced from kinesis
#include<bits/stdc++.h>
using namespace std;

#define _REP(i,a,b) for(int i = (a) ; i >= (int)(b) ; --i )
#define REP(i,a,b) for(int i = (a) ; i <= (int)(b) ; ++i )
#define UREP(i,u) for(int i = p[(u)] ; i + 1 ; i = edge[i].next)
//iterator: for(int u:x),x is container
#define x(p) (p).first
#define y(p) (p).second
#define pii pair<int,int>
#define mp(x,y) make_pair((x), (y))
#define sign(x) (fabs(x) < eps ? 0 : ((x) > 0 ? 1 : -1))
#define ll long long
#define L7 __int128//1<<7 bit
#define ull unsigned long long
const int inf = 0x3f3f3f3f;
const ll inff = 0x3f3f3f3f3f3f3f3f;
const int mod = 998244353;
const double eps = 1e-9;
#define ri1(x) scanf("%d", &(x))
#define ri2(x,y) scanf("%d%d", &(x), &(y))
#define ri3(x,y,z) scanf("%d%d%d", &(x), &(y), &(z))
#define ri4(a,b,c,d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
//#define Debug
#ifdef Debug
#endif // Debug

const int maxn = 65536;

namespace NTT//优化过的ntt，使用时记得初始化
{
    const int p = 998244353,g = 3;
    int w[maxn<<2],inv[maxn<<2],r[maxn<<2],last;
    int mod(int x){return x >= p ? x - p : x;}
    ll qp(ll base,ll n)
    {
        base %= p;
        ll res = 1;
        while(n){
            if(n&1) (res *= base) %= p;
            (base *= base) %= p;
            n >>= 1;
        }
        return res;
    }

    void init()
    {
        int lim = maxn << 1;
        inv[1] = 1;
        for(int i=2;i<=lim;i++) inv[i] = mod(p - 1ll * (p / i) * inv[p%i] % p);
        for(int i=1;i<lim;i<<=1)
        {
            int wn = qp(g,(p - 1) / (i<<1));
            for(int j=0,ww=1;j<i;j++,ww=1ll*ww*wn%p) w[i+j] = ww;
        }
    }

    void ntt(vector<int> &f,int n,int op)
    {
        if(last!=n)
        {
            for(int i=1;i<n;i++) r[i] = (r[i>>1]>>1)|((i&1)?(n>>1):0);
            last=n;
        }
        for(int i=1;i<n;i++) if(i<r[i])swap(f[i],f[r[i]]);
        for(int i=1;i<n;i<<=1)
        for(int j=0;j<n;j+=i<<1)
            for(int k=0;k<i;k++)
            {
                int x=f[j+k],y=1ll*f[i+j+k]*w[i+k]%p;
                f[j+k]=mod(x+y);f[i+j+k]=mod(x-y+p);
            }
        if(op==-1)
        {
            reverse(&f[1],&f[n]);
            for(int i=0;i<n;i++)f[i]=1ll*f[i]*inv[n]%p;
        }
    }
}
using NTT::ntt;

ll qp(ll base,ll n)
{
    base %= mod;
    ll res = 1;
    while(n){
        if(n&1) (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return res;
}

void PolyInv(int deg,vector<int> &f,vector<int> &g)
{
    if(deg==1) {g[0] = qp(f[0],mod-2);return ;}
    PolyInv((deg+1)>>1,f,g);
    int lim = 1;
    while(lim<(2*deg-1)) lim <<= 1;
    vector<int> h(lim);
    REP(i,0,deg-1) h[i] = f[i];
    ntt(g,lim,1),ntt(h,lim,1);
    REP(i,0,lim-1) g[i] = 1LL * (2LL + mod - 1LL * g[i] * h[i] % mod) % mod * g[i] % mod;
    ntt(g,lim,-1);
    REP(i,deg,lim-1) g[i] = 0;
}

namespace Recurrence//初始读入a[1~k],st[0~k-1]
{
    vector<int> g(maxn<<1),gT(maxn<<1),_gT(maxn<<1);

    void PolyModulo(int n,int m,vector<int> &f,vector<int> &R)//特别修改的多项式取模
    {
        int lim = 1,deg = 2*n - m + 10;
        while(lim<(deg)) lim <<= 1;
        vector<int> fT(lim),Q(lim);
        REP(i,0,n-1) fT[i] = f[n-1-i];
        ntt(fT,lim,1);
        REP(i,0,lim-1) fT[i] = 1LL * fT[i] * _gT[i] % mod;
        ntt(fT,lim,-1);
        REP(i,0,n-m) Q[i] = fT[i];
        reverse(Q.begin(),Q.begin()+n-m+1);
        lim = 1,deg = n + 10;
        while(lim<(deg)) lim <<= 1;
        vector<int> f1 = f;
        f1.resize(lim),Q.resize(lim),R.resize(lim);
        ntt(f1,lim,1),ntt(Q,lim,1);
        REP(i,0,lim-1) R[i] = (1LL * f1[i] + mod - 1LL * g[i] * Q[i] % mod) % mod;
        ntt(R,lim,-1);
    }
    void get_g(int n,int m)
    {
        int lim = 1,deg = 2*n - m + 10;
        while(lim<(deg)) lim <<= 1;
        REP(i,0,m-1) gT[i] = g[m-1-i];
        PolyInv(n-m+1,gT,_gT);
        ntt(_gT,lim,1);
        lim = 1,deg = n + 10;
        while(lim<(deg)) lim <<= 1;
        ntt(g,lim,1);
    }
    vector<int> f(maxn<<1);
    void mul(int k)
    {
        int lim = 1;
        while(lim<(2*k+1)) lim <<= 1;
        ntt(f,lim,1);
        REP(i,0,lim-1) f[i] = 1LL * f[i] * f[i] % mod;
        ntt(f,lim,-1);
        vector<int> R;
        PolyModulo(2*k+1,k+1,f,R);
        REP(i,0,k-1) f[i] = R[i];
        REP(i,k,lim-1) f[i] = 0;
    }
    void add(int k)
    {
        _REP(i,k,1) f[i] = f[i-1];f[0] = 0;
    }

    int a[maxn],st[maxn];//递推系数，初始值，长度均为k

    int work(int n,int k)//st_n = \sum_{i=1}^{k} st_{n-i}a_i
    {
        if(n==0) return st[0];//0值要特判
        REP(i,0,(maxn<<1)-1) f[i] = g[i] = gT[i] = _gT[i] = 0;
        REP(i,1,k) g[k-i] = a[i],g[k-i] = (g[k-i] % mod + mod) % mod;g[k] = mod-1;
        get_g(2*k+1,k+1);
        f[1] = 1;
        int cur = 1,lg = log2(n),ok = 0;
        _REP(i,lg-1,0){
            if(k<=(cur<<1)) ok = 1;
            if(!ok) f[cur<<1] = f[cur],f[cur] = 0,cur<<=1;
            else mul(k);
            if(n&(1<<i)){
                if(!ok) f[cur+1] = f[cur],f[cur] = 0,cur+=1;
                else add(k);
            }
        }
        vector<int> R;
        PolyModulo(2*k+1,k+1,f,R);
        REP(i,0,k-1) f[i] = R[i];
        int ans = 0;
        REP(i,0,k-1) (ans += 1LL * f[i] * st[i] % mod) %= mod;
        return (ans + mod) % mod;
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);//cf needn't delete this
    #endif // ONLINE_JUDGE
    NTT::init();
    int n,k;
    ri2(n,k);
    REP(i,1,k) ri1(Recurrence::a[i]);
    REP(i,0,k-1) ri1(Recurrence::st[i]);
    printf("%d\n",Recurrence::work(n,k));
    return 0;
}
```



## P3824 [NOI2017]泳池

一道关于极大矩阵的概率 dp 题目（同时细节很多）。

首先**恰好**不好求，有两种思路，差分 and 容斥。这里考虑 $P$​(恰好为 K 的概率) $= P$​(不大于K的概率) $- P$​(不大于 K-1 的概率)。

由于矩阵必须从低端构建，利用极大矩阵的一个 trick：用坏点来 **分割** 状态。

令 $p$​​ ​为坏点出现的概率，有 $p = 1-q$​​​。设 $F_n$​​​ 为长度为 $n$​​​ 的概率，用坏点来进行划分，枚举坏点 $n-i$​​​ 的位置，有 $F_n = \sum\limits_{i=1}^{k+1} F_{n-i}w_{i-1}p$​​​，其中 $w_{i}$ ​​​为长度为 $i$​ ​​​​的空间里极大矩阵为高度至少为 1，面积不大于 K 的概率。该式子为齐次线性递推，而由于**特征多项式**度数小，故可以用**长除法**来写。

现在来求 $w_{i}$​​。设 $dp_{i,j}$​ ​为长度为 $i$​​ 的空间，极大矩阵的高度至少为 $j$​​ 的概率。以从左到右第一个最低的白点为划分，有 $d p[i][j]=d p[i][j+1] +\sum_{k=1}^{i} q^{j}p \times d p[k-1][j+1] \times d p[i-k][j]$​​，易知 $w_{i} = dp_{i,1}$​​。边界情况为 $dp[0][i] = 1,dp[i][j] = 0,i*j>K$​​​​​。

答案应为 $F_n$​，然鹅实际答案为 $\frac{F_{n+1}}{p}$​，说是除坏点的概率，不知道为什么。。~~不过至少是正确的。~~

# 多项式习题

## 一些习题

### P4002 [清华集训2017]生成树计数

在一个 $s$ 个点的图中，存在 $s-n$ 条边, 使图中形成了 $n$ 个连通块，第 $i$ 个连通块中有 $a_{i}$ 个点。

现在我们需要再连接 $n-1$ 条边, 使该图变成一棵树。对一种连边方案, 设原图中第 $i$ 个连通块连出了 $d_{i}$ 条边，那么这棵树 $T$ 的价值为：

$\operatorname{val}(T)=\left(\prod_{i=1}^{n} d_{i}^{m}\right)\left(\sum_{i=1}^{n} d_{i}^{m}\right)$

现要求所有生成树的价值总和，对 998244353 取模。

对于有标号无根树，考虑构造prufer序列：

令 $d_i = d_i - 1$

$Ans = (n-2)!\sum\limits_{\sum d_i = n-2} \prod_k \frac{a_k^{d_k+1}}{d_k!} \left(\prod_{i=1}^{n} (d_{i}+1)^{m}\right)\left(\sum_{i=1}^{n} (d_{i}+1)^{m}\right)$ 。这里注意累乘累加的实际形式，变换一下累乘累加顺序：

$ = (n-2)!\prod_k a_k\sum\limits_{\sum d_i = n-2} \prod\limits_{i=1}^n \frac{a_i^{d_i}(d_i+1)^m}{d_i!}\sum\limits_{j=1}^n(d_j+1)^m$

$ = (n-2)! \prod_k a_k \sum\limits_{\sum d_i = n-2} \sum\limits_{i=1}^n \frac{a_i^{d_i}(d_i+1)^{2m}}{d_i!}\prod\limits_{j\neq i}^n\frac{a_j^{d_j}(d_j+1)^m}{d_j!}$

首先前面的 $(n-2)\prod_k a_k$ ，见到 $\sum d_i = n-2$，考虑构造生成函数（即乘上 x）：

$\sum\limits_{\sum d_i = n-2} \sum\limits_{i=1}^n \frac{a_i^{d_i}(d_i+1)^{2m}}{d_i!}x^{d_i}\prod\limits_{j\neq i}^n(d_j+1)^m x^{d_j} = \sum\limits_{\sum d_i = n-2} (\sum\limits_{i=1}^n \frac{a_i^{d_i}(d_i+1)^{2m}}{d_i!}\prod\limits_{j\neq i}^n(d_j+1)^m )x^{n-2}$ 。

故以 $d_i$ 为下标，构造生成函数。其中 $P(x) = \sum \frac{(i+1)^m}{i!}x^i,Q(x) = \sum \frac{(i+1)^{2m}}{i!},F(x) = \sum\limits_{i=1}^n Q(a_ix)\prod\limits_{j\neq i}P(a_jx)$ ，则原式：

$Ans = (n-2)!\prod_k a_k [x^{n-2}]F(x)$ 。

$F(x) = \prod_{i=1}^n P(a_ix) \sum\limits_{j=1}^n \frac{Q(a_jx)}{P(a_jx)} = \exp(\sum\ln(P(a_ix))) \sum\limits_{j=1}^n\frac{Q(a_jx)}{P(a_jx)}$ 。

那就求出 $\ln P,\frac{Q}{P}$ 这两个多项式后，要求的形式即为 $\sum\limits W(a_ix)$ 的形式，即要求 $A(x) = \sum\limits_{i=0}^{\infty} \sum\limits_{j=1}^n a_j^i x^i$ ，然后对应项乘起来。这个套路在总结板块有写，于是该题结束。

# 斯特林数与盒子计数

关于斯特林数的基本介绍在「斯特林数」一节。

## 第一类斯特林数 · 行

根据 $(x)^{n}=\sum_{k=0}^{n} S(n, k) x^{k}$ 来进行计算。

考虑倍增：根据倍增 NTT 的套路，列出两条递推式：

> $x^{\overline{2n}} = x^{\overline{n}} * (x+n)^{\overline{n}}$
>
> $x^{\overline{n+1}}  =x^{\overline{n}} * (x+n)$

二式线性求就行了；

假设已经求得 $x^{\overline{n}} = \sum\limits_{i=0}a_i x^i$，则

$g(x) = (x+n)^{\overline{n}} = \sum\limits_{i=0}a_i(x+n)^i$​

考虑其对每一项的贡献：

$[x^i]g(x) = \sum\limits_{j=0}a_j \dbinom{j}{i}n^{j-i} = \sum\limits_{j=0}a_j \frac{j!}{i!(j-i)!}n^{j-i}$​

即 $i![x^i]g(x) = \sum\limits_{j=0}a_j j! \frac{n^{j-i}}{(j-i)!}$

后面是个卷积式，NTT 一下就搞定。

故倍增 NTT 即可。

```cpp
//code sourced from kinesis
#include <bits/stdc++.h>
using namespace std;

#define _REP(i, a, b) for (int i = (a); i >= (int)(b); --i)
#define REP(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define UREP(i, u) for (int i = p[(u)]; i + 1; i = edge[i].next)
//iterator: for(int u:x),x is container
#define x(p) (p).first
#define y(p) (p).second
#define pii pair<int, int>
#define mp(x, y) make_pair((x), (y))
#define sign(x) (fabs(x) < eps ? 0 : ((x) > 0 ? 1 : -1))
#define ll long long
#define L7 __int128  //1<<7 bit
#define ull unsigned long long
const int inf = 0x3f3f3f3f;
const ll inff = 0x3f3f3f3f3f3f3f3f;
const int mod = 167772161;
const double eps = 1e-9;
#define ri1(x) scanf("%d", &(x))
#define ri2(x, y) scanf("%d%d", &(x), &(y))
#define ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
//#define Debug
#ifdef Debug
#endif  // Debug

const int maxn = 262144;
namespace NTT {
const int mod = 167772161;  //998244353,1004535809,469762049,985661441,167772161. g = 3
int qp(ll base, ll n)       //快速幂
{
    ll res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return (int)res;
}
int rev[maxn << 1];
void change(vector<int>& x, int len) {
    int bit = 0;
    while ((1 << bit) < len)
        bit++;
    REP(i, 1, len - 1) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        if (i < rev[i])
            swap(x[i], x[rev[i]]);
    }  //前面和FFT一样
}
void ntt(vector<int>& x, int lim, int opt) {
    change(x, lim);
    for (int m = 2; m <= lim; m <<= 1) {
        int k = m >> 1;
        int gn = qp(3, (mod - 1) / m);
        for (int i = 0; i < lim; i += m) {
            int g = 1;
            for (int j = 0; j < k; ++j, g = 1ll * g * gn % mod) {
                int tmp = 1ll * x[i + j + k] * g % mod;
                x[i + j + k] = (x[i + j] - tmp + mod) % mod;
                x[i + j] = (x[i + j] + tmp) % mod;
            }
        }
    }
    if (opt == -1) {
        reverse(x.begin() + 1, x.begin() + lim);
        int inv = qp(lim, mod - 2);
        REP(i, 0, lim - 1)
        x[i] = 1ll * x[i] * inv % mod;
    }
}
}  // namespace NTT
using NTT::ntt;

ll Finv[maxn + 10], fac[maxn + 10], inv[maxn + 10];
ll qp(ll base, ll n) {
    ll res = 1;
    base %= mod;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return res;
}
void Fac_init()  //n<N
{
    int n = maxn;
    inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        inv[i] = ((mod - mod / i) * inv[mod % i]) % mod;
    fac[0] = Finv[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod, Finv[i] = Finv[i - 1] * inv[i] % mod;
}

vector<int> f(maxn << 1);

void mul(int deg, int cur) {
    int lim = 1;
    while (lim < (2 * cur + 1))
        lim <<= 1;
    vector<int> g1(lim), g2(lim);
    int _cur = 1;
    REP(i, 0, cur)
    g1[i] = 1LL * f[i] * fac[i] % mod,
    g2[i] = 1LL * _cur * Finv[i] % mod, _cur = 1LL * _cur * cur % mod;
    reverse(g1.begin(), g1.begin() + cur + 1);
    ntt(g1, lim, 1), ntt(g2, lim, 1);
    REP(i, 0, lim - 1)
    g2[i] = 1LL * g1[i] * g2[i] % mod,
    g1[i] = 0;
    ntt(g2, lim, -1);
    REP(i, 0, cur)
    g1[i] = 1LL * g2[cur - i] * Finv[i] % mod;
    ntt(f, lim, 1), ntt(g1, lim, 1);
    REP(i, 0, lim - 1)
    f[i] = 1LL * f[i] * g1[i] % mod;
    ntt(f, lim, -1);
    REP(i, deg, lim - 1)
    f[i] = 0;
}

void add(int deg, int cur) {
    _REP(i, deg - 1, 0)
    f[i] = (1LL * f[i] * cur % mod + (i == 0 ? 0 : f[i - 1])) % mod;
}

int main() {
#ifndef ONLINE_JUDGE
//freopen("in.txt","r",stdin);//cf needn't delete this
#endif  // ONLINE_JUDGE
    Fac_init();
    f[1] = 1;
    int n, ub, cur = 1;
    ri1(n);
    if (n == 0)
        return printf("1\n"), 0;
    ub = log2(n);
    _REP(i, ub - 1, 0) {
        mul(n + 1, cur);
        cur <<= 1;
        if (n & (1 << i))
            add(n + 1, cur), cur++;
    }
    REP(i, 0, n)
    printf("%d%c", f[i], i == n ? '\n' : ' ');
    return ~~(0 - 0);
}

```



## 第一类斯特林数 · 列

发现是 $n$​​​​ 个元素构成 $k$​​​​ 个置换环，构造环排列的指数生成函数 $F = \sum\limits_{i=1}\frac{(i-1)!}{i!}x^i$​​​​，则 k 个置换环的生成函数为 $G = \frac{F^k}{k!}$​​​​。由于方案数在分子上，EGF 转 OGF 时乘个阶乘就好。这道题卡常- - $F$​​​​ 就不要求对数什么骚操作了，直接每项等于 $inv[i]$​ ​​​然后 $k$​​​​​​ 次方运算。

```cpp
//code sourced from kinesis
#include<bits/stdc++.h>
using namespace std;

#define _REP(i,a,b) for(int i = (a) ; i >= (int)(b) ; --i )
#define REP(i,a,b) for(int i = (a) ; i <= (int)(b) ; ++i )
#define UREP(i,u) for(int i = p[(u)] ; i + 1 ; i = edge[i].next)
//iterator: for(int u:x),x is container
#define x(p) (p).first
#define y(p) (p).second
#define pii pair<int,int>
#define mp(x,y) make_pair((x), (y))
#define sign(x) (fabs(x) < eps ? 0 : ((x) > 0 ? 1 : -1))
#define ll long long
#define L7 __int128//1<<7 bit
#define ull unsigned long long
const int inf = 0x3f3f3f3f;
const ll inff = 0x3f3f3f3f3f3f3f3f;
const int mod = 167772161;
const double eps = 1e-9;
#define ri1(x) scanf("%d", &(x))
#define ri2(x,y) scanf("%d%d", &(x), &(y))
#define ri3(x,y,z) scanf("%d%d%d", &(x), &(y), &(z))
#define ri4(a,b,c,d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
//#define Debug
#ifdef Debug
#endif // Debug

const int maxn = 131072;

namespace NTT
{
    const int mod = 167772161;//998244353,1004535809,469762049,985661441,167772161. g = 3.950009857,g=7
    int qp(ll base,ll n)//快速幂
    {
        ll res = 1;
        while(n){
            if(n&1) (res *= base) %= mod;
            (base *= base) %= mod;
            n>>=1;
        }
        return (int)res;
    }
    int rev[maxn<<1];
    void change(vector<int> &x,int len)
    {
        int bit = 0;
        while ((1<<bit)<len) bit++;
        REP(i,1,len-1){
            rev[i] = (rev[i>>1] >> 1) | ((i & 1) << (bit - 1));
            if (i<rev[i]) swap(x[i],x[rev[i]]);
        }//前面和FFT一样
    }
    void ntt(vector<int> &x, int lim, int opt)
    {
        change(x,lim);
        for (int m = 2; m <= lim; m <<= 1){
            int k = m >> 1;
            int gn = qp(3, (mod - 1) / m);
            for (int i = 0; i < lim; i += m){
                int g = 1;
                for (int j = 0; j < k; ++j, g = 1ll * g * gn % mod){
                    int tmp = 1ll * x[i + j + k] * g % mod;
                    x[i + j + k] = (x[i + j] - tmp + mod) % mod;
                    x[i + j] = (x[i + j] + tmp) % mod;
                }
            }
        }
        if (opt == -1){
            reverse(x.begin() + 1, x.begin() + lim);
            int inv = qp(lim, mod - 2);
            REP(i,0,lim-1) x[i] = 1ll * x[i] * inv % mod;
        }
    }
}
using NTT::ntt;

ll qp(ll base,ll n)
{
    base %= mod;
    ll res = 1;
    while(n){
        if(n&1) (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return res;
}

void PolyInv(int deg,vector<int> &f,vector<int> &g)//蝴蝶变换的rev[maxn<<2],f.resize(n<<2),g.resize(n<<2)
{
    if(deg==1) {g[0] = qp(f[0],mod-2);return ;}
    PolyInv((deg+1)>>1,f,g);
    int lim = 1;
    while(lim<(deg<<1)) lim <<= 1;
    vector<int> h(lim);
    REP(i,0,deg-1) h[i] = f[i];
    ntt(g,lim,1),ntt(h,lim,1);
    REP(i,0,lim-1) g[i] = 1LL * (2LL + mod - 1LL * g[i] * h[i] % mod) % mod * g[i] % mod;
    ntt(g,lim,-1);
    REP(i,deg,lim-1) g[i] = 0;
}

namespace Comb
{
    ll Finv[maxn+10],fac[maxn+10],inv[maxn+10];
    ll qp(ll base,ll n) {
        ll res = 1;
        base%=mod;
        while(n){
            if(n&1) (res *= base) %= mod;
            (base *= base) %= mod;
            n >>= 1;
        }
        return res;
    }
    void init()//n<N
    {
        int n = maxn;
        inv[1]=1;
        for(int i=2;i<=n;++i)inv[i]=((mod-mod/i)*inv[mod%i])%mod;
        fac[0]=Finv[0]=1;
        for(int i=1;i<=n;++i)fac[i]=fac[i-1]*i%mod,Finv[i]=Finv[i-1]*inv[i]%mod;
    }
}
using Comb::fac;
using Comb::inv;
using Comb::Finv;

void derivative(int deg,vector<int> &f,vector<int> &g)
{
    REP(i,0,deg-2) g[i] = 1LL * f[i+1] * (i + 1) % mod;
    g[deg-1] = 0;
}

void integrate(int deg,vector<int> &f,vector<int> &g)
{
    _REP(i,deg-1,1) g[i] = 1LL * f[i-1] * inv[i] % mod;
    g[0] = 0;//c
}

void PolyLn(int deg,vector<int> &f,vector<int> &g)
{
    /* g = ln f = ∫ f' f^-1 dx */
    assert(f[0] == 1);
    int lim = 1;
    while(lim<(deg<<1)) lim <<= 1;
    vector<int> f_(lim),_f(lim);//f',f^-1
    derivative(deg,f,f_);
    PolyInv(deg,f,_f);
    ntt(_f,lim,1),ntt(f_,lim,1);
    REP(i,0,lim-1) f_[i] = 1LL * f_[i] * _f[i] % mod;
    ntt(f_,lim,-1);
    integrate(deg,f_,g);
}

void PolyExp(int deg,vector<int> &f,vector<int> &g)
{
    /* g = exp(f) = g_0 (1 - ln g_0 + f) */
    assert(f[0] == 0);
    if(deg==1) {g[0] = 1;return ;}
    PolyExp((deg+1)>>1,f,g);
    int lim = 1;
    while(lim<(deg<<1)) lim <<= 1;
    vector<int> gLn(lim);
    PolyLn(deg,g,gLn);
    REP(i,0,deg-1) gLn[i] = (1LL * f[i] - gLn[i] + mod) % mod;
    gLn[0] = (gLn[0] + 1) % mod;

    ntt(g,lim,1),ntt(gLn,lim,1);
    REP(i,0,lim-1) g[i] = 1LL * g[i] * gLn[i] % mod;
    ntt(g,lim,-1);
    REP(i,deg,lim-1) g[i] = 0;
}

void Polyex1(int deg,vector<int> &f,int k,vector<int> &g)//deg限制%x^deg，不改变运算结果。这里f[0] = 1
{
    vector<int> h(deg);
    PolyLn(deg,f,h);
    REP(i,0,deg-1) h[i] = 1LL * h[i] * k % mod;
    PolyExp(deg,h,g);
}

void Polyex2(int deg,vector<int> &f,int k,vector<int> &g)//deg限制%x^deg，不改变运算结果。这里f[0] != 1
{
    vector<int> h(deg),f_(deg);
    int id = 0,f_id,inv,base;
    while(!f[id]) id++;//找到第一项不为0的为x^id,然后多项式除f_id，最后exp后再还原回来
    f_id = f[id];
    base = qp(f_id,k),inv = qp(f_id,mod-2);  //这里要模数为素数才可用！！！！！
    REP(i,0,deg-id-1) f_[i] = 1LL * f[i+id] * inv % mod;
    PolyLn(deg,f_,h);
    REP(i,0,deg-1) h[i] = 1LL * h[i] * k % mod;
    PolyExp(deg,h,g);
    _REP(i,deg-1,k*id) g[i] = 1LL * g[i-k*id] * base % mod;
    _REP(i,k*id-1,0) g[i] = 0;
}

void Polyex(int deg,vector<int> &f,int k,vector<int> &g)
{
    if(f[0]==1) Polyex1(deg,f,k,g);
    else Polyex2(deg,f,k,g);
}

vector<int> g(maxn<<1),f(maxn<<1);

namespace fastIO//支持int,ll,__int128.ull没有测试过
{
    static char buf[100000],*h=buf,*d=buf;//缓存开大可减少读入时间、、看题目给的空间
    #define gc h==d&&(d=(h=buf)+fread(buf,1,100000,stdin),h==d)?EOF:*h++//不能用fread则换成getchar
    template<typename T>
    inline void read(T&x)
    {
        int f = 1;x = 0;
        register char c(gc);
        while(c>'9'||c<'0'){
            if(c == '-') f = -1;
            c=gc;
        }
        while(c<='9'&&c>='0')x=(x<<1)+(x<<3)+(c^48),c=gc;
        x *= f;
    }
    template<typename T>
    void output(T x)
    {
        if(x<0){putchar('-');x=~(x-1);}
        static int s[20],top=0;
        while(x){s[++top]=x%10;x/=10;}
        if(!top)s[++top]=0;
        while(top)putchar(s[top--]+'0');
    }
}
using fastIO::read;
using fastIO::output;


int main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);//cf needn't delete this
    #endif // ONLINE_JUDGE
    Comb::init();
    int n,k;
    read(n),read(k);
    REP(i,1,n) g[i] = inv[i];
    Polyex(n+1,g,k,f);
    REP(i,0,n) output(1LL * f[i] * Finv[k] % mod * fac[i] % mod),putchar((i==n ? '\n' : ' '));
    return ~~(0-0);
}


```

## 第二类斯特林数 · 行

利用公式 $\left\{\begin{array}{l} n \\ k \end{array}\right\} = \sum\limits_{i=0}^{k}\frac{(-1)^i}{i!}\frac{(k-i)^n}{(k-i)!}$ ​来求。这个就不必深究了，归纳法可证。一些等价变式：

$\left\{\begin{array}{l} n \\ k \end{array}\right\} = \sum\limits_{i=0}^{k}\frac{(-1)^{k-i}}{(k-i)!}\frac{i^n}{i!}$

$\Rightarrow k!\left\{\begin{array}{l} n \\ k \end{array}\right\} = \sum\limits_{i=0}^{k}(-1)^{k-i}i^n\dbinom{k}{i}$​

```cpp
//code sourced from kinesis
#include <bits/stdc++.h>
using namespace std;

#define _REP(i, a, b) for (int i = (a); i >= (int)(b); --i)
#define REP(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define UREP(i, u) for (int i = p[(u)]; i + 1; i = edge[i].next)
//iterator: for(int u:x),x is container
#define x(p) (p).first
#define y(p) (p).second
#define pii pair<int, int>
#define mp(x, y) make_pair((x), (y))
#define sign(x) (fabs(x) < eps ? 0 : ((x) > 0 ? 1 : -1))
#define ll long long
#define L7 __int128  //1<<7 bit
#define ull unsigned long long
const int inf = 0x3f3f3f3f;
const ll inff = 0x3f3f3f3f3f3f3f3f;
const int mod = 167772161;
const double eps = 1e-9;
#define ri1(x) scanf("%d", &(x))
#define ri2(x, y) scanf("%d%d", &(x), &(y))
#define ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
//#define Debug
#ifdef Debug
#endif  // Debug

const int maxn = 262144;

namespace NTT {
const int mod = 167772161;  //998244353,1004535809,469762049,985661441,167772161. g = 3.950009857,g=7
int qp(ll base, ll n)       //快速幂
{
    ll res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return (int)res;
}
int rev[maxn << 2];
void change(vector<int>& x, int len) {
    int bit = 0;
    while ((1 << bit) < len)
        bit++;
    REP(i, 1, len - 1) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        if (i < rev[i])
            swap(x[i], x[rev[i]]);
    }  //前面和FFT一样
}
void ntt(vector<int>& x, int lim, int opt) {
    change(x, lim);
    for (int m = 2; m <= lim; m <<= 1) {
        int k = m >> 1;
        int gn = qp(3, (mod - 1) / m);
        for (int i = 0; i < lim; i += m) {
            int g = 1;
            for (int j = 0; j < k; ++j, g = 1ll * g * gn % mod) {
                int tmp = 1ll * x[i + j + k] * g % mod;
                x[i + j + k] = (x[i + j] - tmp + mod) % mod;
                x[i + j] = (x[i + j] + tmp) % mod;
            }
        }
    }
    if (opt == -1) {
        reverse(x.begin() + 1, x.begin() + lim);
        int inv = qp(lim, mod - 2);
        REP(i, 0, lim - 1)
        x[i] = 1ll * x[i] * inv % mod;
    }
}
}  // namespace NTT
using NTT::ntt;

ll qp(ll base, ll n) {
    base %= mod;
    ll res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return res;
}

namespace Comb {
ll Finv[maxn + 10], fac[maxn + 10], inv[maxn + 10];
ll qp(ll base, ll n) {
    ll res = 1;
    base %= mod;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return res;
}
void init()  //n<N
{
    int n = maxn;
    inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        inv[i] = ((mod - mod / i) * inv[mod % i]) % mod;
    fac[0] = Finv[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod, Finv[i] = Finv[i - 1] * inv[i] % mod;
}
ll C(ll n, ll m) {
    if (m < 0 || m > n)
        return 0;
    return fac[n] * Finv[n - m] % mod * Finv[m] % mod;
}
}  // namespace Comb
using Comb::Finv;

vector<int> f(maxn << 1), g(maxn << 1);

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);  //cf needn't delete this
#endif                              // ONLINE_JUDGE
    int n;
    Comb::init();
    ri1(n);
    int op = 1;
    REP(i, 0, n)
    f[i] = (1LL * op * Finv[i] % mod + mod) % mod,
    op = -op, g[i] = 1LL * qp(i, n) * Finv[i] % mod;
    int lim = 1;
    while (lim < ((n + 1) << 1))
        lim <<= 1;
    ntt(f, lim, 1), ntt(g, lim, 1);
    REP(i, 0, lim - 1)
    f[i] = 1LL * f[i] * g[i] % mod;
    ntt(f, lim, -1);
    REP(i, 0, n)
    printf("%d%c", f[i], i == n ? '\n' : ' ');
    return ~~(0 - 0);
}

```



## 第二类斯特林数 · 列

很明显可以用指数生成函数来做。将**第一类斯特林数 · 列**的方案数由圆排列换成 1 即可。

```cpp
//code sourced from kinesis
#include <bits/stdc++.h>
using namespace std;

#define _REP(i, a, b) for (int i = (a); i >= (int)(b); --i)
#define REP(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define UREP(i, u) for (int i = p[(u)]; i + 1; i = edge[i].next)
//iterator: for(int u:x),x is container
#define x(p) (p).first
#define y(p) (p).second
#define pii pair<int, int>
#define mp(x, y) make_pair((x), (y))
#define sign(x) (fabs(x) < eps ? 0 : ((x) > 0 ? 1 : -1))
#define ll long long
#define L7 __int128  //1<<7 bit
#define ull unsigned long long
const int inf = 0x3f3f3f3f;
const ll inff = 0x3f3f3f3f3f3f3f3f;
const int mod = 167772161;
const double eps = 1e-9;
#define ri1(x) scanf("%d", &(x))
#define ri2(x, y) scanf("%d%d", &(x), &(y))
#define ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
//#define Debug
#ifdef Debug
#endif  // Debug

const int maxn = 131072;

namespace NTT {
const int mod = 167772161;  //998244353,1004535809,469762049,985661441,167772161. g = 3.950009857,g=7
int qp(ll base, ll n)       //快速幂
{
    ll res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return (int)res;
}
int rev[maxn << 1];
void change(vector<int>& x, int len) {
    int bit = 0;
    while ((1 << bit) < len)
        bit++;
    REP(i, 1, len - 1) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        if (i < rev[i])
            swap(x[i], x[rev[i]]);
    }  //前面和FFT一样
}
void ntt(vector<int>& x, int lim, int opt) {
    change(x, lim);
    for (int m = 2; m <= lim; m <<= 1) {
        int k = m >> 1;
        int gn = qp(3, (mod - 1) / m);
        for (int i = 0; i < lim; i += m) {
            int g = 1;
            for (int j = 0; j < k; ++j, g = 1ll * g * gn % mod) {
                int tmp = 1ll * x[i + j + k] * g % mod;
                x[i + j + k] = (x[i + j] - tmp + mod) % mod;
                x[i + j] = (x[i + j] + tmp) % mod;
            }
        }
    }
    if (opt == -1) {
        reverse(x.begin() + 1, x.begin() + lim);
        int inv = qp(lim, mod - 2);
        REP(i, 0, lim - 1)
        x[i] = 1ll * x[i] * inv % mod;
    }
}
}  // namespace NTT
using NTT::ntt;

ll qp(ll base, ll n) {
    base %= mod;
    ll res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return res;
}

void PolyInv(int deg, vector<int>& f, vector<int>& g)  //蝴蝶变换的rev[maxn<<2],f.resize(n<<2),g.resize(n<<2)
{
    if (deg == 1) {
        g[0] = qp(f[0], mod - 2);
        return;
    }
    PolyInv((deg + 1) >> 1, f, g);
    int lim = 1;
    while (lim < (deg << 1))
        lim <<= 1;
    vector<int> h(lim);
    REP(i, 0, deg - 1)
    h[i] = f[i];
    ntt(g, lim, 1), ntt(h, lim, 1);
    REP(i, 0, lim - 1)
    g[i] = 1LL * (2LL + mod - 1LL * g[i] * h[i] % mod) % mod * g[i] % mod;
    ntt(g, lim, -1);
    REP(i, deg, lim - 1)
    g[i] = 0;
}

namespace Comb {
ll Finv[maxn + 10], fac[maxn + 10], inv[maxn + 10];
ll qp(ll base, ll n) {
    ll res = 1;
    base %= mod;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return res;
}
void init()  //n<N
{
    int n = maxn;
    inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        inv[i] = ((mod - mod / i) * inv[mod % i]) % mod;
    fac[0] = Finv[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod, Finv[i] = Finv[i - 1] * inv[i] % mod;
}
}  // namespace Comb
using Comb::fac;
using Comb::Finv;
using Comb::inv;

void derivative(int deg, vector<int>& f, vector<int>& g) {
    REP(i, 0, deg - 2)
    g[i] = 1LL * f[i + 1] * (i + 1) % mod;
    g[deg - 1] = 0;
}

void integrate(int deg, vector<int>& f, vector<int>& g) {
    _REP(i, deg - 1, 1)
    g[i] = 1LL * f[i - 1] * inv[i] % mod;
    g[0] = 0;  //c
}

void PolyLn(int deg, vector<int>& f, vector<int>& g) {
    /* g = ln f = ∫ f' f^-1 dx */
    assert(f[0] == 1);
    int lim = 1;
    while (lim < (deg << 1))
        lim <<= 1;
    vector<int> f_(lim), _f(lim);  //f',f^-1
    derivative(deg, f, f_);
    PolyInv(deg, f, _f);
    ntt(_f, lim, 1), ntt(f_, lim, 1);
    REP(i, 0, lim - 1)
    f_[i] = 1LL * f_[i] * _f[i] % mod;
    ntt(f_, lim, -1);
    integrate(deg, f_, g);
}

void PolyExp(int deg, vector<int>& f, vector<int>& g) {
    /* g = exp(f) = g_0 (1 - ln g_0 + f) */
    assert(f[0] == 0);
    if (deg == 1) {
        g[0] = 1;
        return;
    }
    PolyExp((deg + 1) >> 1, f, g);
    int lim = 1;
    while (lim < (deg << 1))
        lim <<= 1;
    vector<int> gLn(lim);
    PolyLn(deg, g, gLn);
    REP(i, 0, deg - 1)
    gLn[i] = (1LL * f[i] - gLn[i] + mod) % mod;
    gLn[0] = (gLn[0] + 1) % mod;

    ntt(g, lim, 1), ntt(gLn, lim, 1);
    REP(i, 0, lim - 1)
    g[i] = 1LL * g[i] * gLn[i] % mod;
    ntt(g, lim, -1);
    REP(i, deg, lim - 1)
    g[i] = 0;
}

void Polyex1(int deg, vector<int>& f, int k, vector<int>& g)  //deg限制%x^deg，不改变运算结果。这里f[0] = 1
{
    vector<int> h(deg);
    PolyLn(deg, f, h);
    REP(i, 0, deg - 1)
    h[i] = 1LL * h[i] * k % mod;
    PolyExp(deg, h, g);
}

void Polyex2(int deg, vector<int>& f, int k, vector<int>& g)  //deg限制%x^deg，不改变运算结果。这里f[0] != 1
{
    vector<int> h(deg), f_(deg);
    int id = 0, f_id, inv, base;
    while (!f[id])
        id++;  //找到第一项不为0的为x^id,然后多项式除f_id，最后exp后再还原回来
    f_id = f[id];
    base = qp(f_id, k), inv = qp(f_id, mod - 2);  //这里要模数为素数才可用！！！！！
    REP(i, 0, deg - id - 1)
    f_[i] = 1LL * f[i + id] * inv % mod;
    PolyLn(deg, f_, h);
    REP(i, 0, deg - 1)
    h[i] = 1LL * h[i] * k % mod;
    PolyExp(deg, h, g);
    _REP(i, deg - 1, k * id)
    g[i] = 1LL * g[i - k * id] * base % mod;
    _REP(i, k * id - 1, 0)
    g[i] = 0;
}

void Polyex(int deg, vector<int>& f, int k, vector<int>& g) {
    if (f[0] == 1)
        Polyex1(deg, f, k, g);
    else
        Polyex2(deg, f, k, g);
}

vector<int> g(maxn << 1), f(maxn << 1);

namespace fastIO  //支持int,ll,__int128.ull没有测试过
{
static char buf[100000], *h = buf, *d = buf;                                              //缓存开大可减少读入时间、、看题目给的空间
#define gc h == d && (d = (h = buf) + fread(buf, 1, 100000, stdin), h == d) ? EOF : *h++  //不能用fread则换成getchar
template <typename T>
inline void read(T& x) {
    int f = 1;
    x = 0;
    register char c(gc);
    while (c > '9' || c < '0') {
        if (c == '-')
            f = -1;
        c = gc;
    }
    while (c <= '9' && c >= '0')
        x = (x << 1) + (x << 3) + (c ^ 48), c = gc;
    x *= f;
}
template <typename T>
void output(T x) {
    if (x < 0) {
        putchar('-');
        x = ~(x - 1);
    }
    static int s[20], top = 0;
    while (x) {
        s[++top] = x % 10;
        x /= 10;
    }
    if (!top)
        s[++top] = 0;
    while (top)
        putchar(s[top--] + '0');
}
}  // namespace fastIO
using fastIO::output;
using fastIO::read;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);  //cf needn't delete this
#endif                              // ONLINE_JUDGE
    Comb::init();
    int n, k;
    read(n), read(k);
    REP(i, 1, n)
    g[i] = Finv[i];
    Polyex(n + 1, g, k, f);
    REP(i, 0, n)
    output(1LL * f[i] * Finv[k] % mod * fac[i] % mod), putchar((i == n ? '\n' : ' '));
    return ~~(0 - 0);
}

```



## 一些习题

### P4091 [HEOI2016/TJOI2016]求和

在2016年，佳媛姐姐刚刚学习了第二类斯特林数，非常开心。 现在他想计算这样一个函数的值:
$$
f(n)=\sum_{i=0}^{n} \sum_{j=0}^{i} S(i, j) \times 2^{j} \times(j !)
$$
$S(\mathrm{i}, \mathrm{j})$ 表示第二类斯特林数，递推公式为:
$$
S(i, j)=j \times S(i-1, j)+S(i-1, j-1), 1 \leq j \leq i-1
$$
边界条件为: $S(i, i)=1(0 \leq i), S(i, 0)=0(1 \leq i)$
你能帮帮他吗?

$\sum\limits_{i=0}^n \sum\limits_{j=0}^i S(i,j)2^j j!$，变换遍历顺序，有

$ = \sum\limits_{j=0}^n\sum\limits_{i=j}^n S(i,j)2^jj!$​，发现 $S(i,j) = 0,i<j$​，有

$\sum\limits_{j=0}^{n}2^jj!\sum\limits_{i=0}^n S(i,j)$。套路展开式子$S(i,j) = \sum\limits_{k=0}^{j}\frac{(-1)^k}{k!}\frac{(j-k)^i}{(j-k)!}$（嗯，跟mobius推式子一样，没有路了就暴力展开，~~前方就会延伸新的道路~~）

对于 $\sum\limits_{i=0}\sum\limits_{k=0}^{j}\frac{(-1)^k}{k!}\frac{(j-k)^i}{(j-k)!}$​​，仅 $(j-k)^i$​​ 跟 $i$​​ 有关，根据微积分基本定理（用在级数上），有 $\sum\limits_{k=0}^{j}\frac{(-1)^k}{k!}\frac{[n+1]_{j-k}}{(j-k)!}$​​，其中 $[n+1]_{q}$ ​​为整数$n+1$​​的 Q-analog（Q-模拟）。令 $f(x) = \sum \frac{(-1)^i}{i!},g(x) = \sum\frac{[n+1]_i}{i!}$​​，原式有 $\sum\limits_{j=0}^n 2^j j! (f * g)(j)$​​​​​，卷积一下就好了。

貌似EI佬有线性做法，以后再学吧。

### CF960G Bandit Blues

题意：对于一个大小为 $n$ 的排列，计算前缀最大的数的个数为 $a$，后缀最大的数的个数为 $b$​ 的这样的排列的方案数。

属实 dp 苦手（不过回忆了一些 dp 状态设计的套路）

设 $dp(i,j)$​ ​为前 $i$​ ​个数，有 $j$​​ 个前缀最大的数的方案数。有 $dp(i,j) = dp(i-1,j-1) + (i-1)dp(i-1,j)$​​​

后面的状态转移的理解：考虑 $i$​ 个数中的最小数 $w_i$​，先任意放剩余的数，剩 $i$​ 个空位共 $w_i$ ​插入。当且仅当 $w_i$​ 放在最前面，前缀最大个数会+1，其余的不会，故有倍数 $(i-1)$​。

发现确定了最高点，前缀个数与后缀个数分别在最高点之右和最高点之左的个数不再发生变化（也易知最高点的编号为 $n$​​），故有 $Ans = \sum\limits_{i=0}^{n-1}f(i,a-1)f(n-1-i,b-1)\dbinom{n-1}{i}$​​，后面的组合数表示 $n-1$​ ​个数分配给前 $i$ ​​​​的方案数。

$Ans$​​ 还能化成 $Ans=\left[\begin{array}{c}
n-1 \\
a+b-2
\end{array}\right] C_{a+b-2}^{a-1}$​​，~~原理我不是很能理解。。抓不住根。不过上面的足够用了。~~

被迫了解，可以见下一篇题解。

### [FJOI2016] 建筑师

小 $\mathrm{Z}$ 是一个很有名的建筑师，有一天他接到了一个很奇怪的任务: 在数轴上建 $n$ 个建筑，每个建筑的高度 是 1 到 $n$ 之间的一个整数。

小 Z 有很严重的强迫症，他不喜欢有两个建筑的高度相同。另外小 Z 觉得如果从最左边（所有建筑都在右 边) 看能看到 $A$ 个建筑，从最右边（所有建筑都在左边）看能看到 $B$ 个建筑，这样的建筑群有着独特的 美感。现在，小 Z想知道满足上述所有条件的建筑方案有多少种?

如果建筑 $i$ 的左(右)边没有任何建造比它高，则建筑 $i$​​ 可以从左(右)边看到。两种方案不同，当且仅当存在 某个建筑在两种方案下的高度不同。

跟上题一样的思路，直接 $O(nm)$​ 递推，由于$n = 5e4,m = 200$​。

由于模型跟上题一样，用这道题的思路来讲为什么是$Ans=\left[\begin{array}{c}
n-1 \\
a+b-2
\end{array}\right] \dbinom{a+b-2}{a-1}$。

首先确定最高点，由于$dp$​方程其实就是第二类斯特林数的递推方程，故知道了需要左边排$A-1$​个圆排列，右边排$B-1$​个圆排列，如果放在一块排，有 $\left[\begin{array}{c}
n-1 \\
a+b-2
\end{array}\right]$​ 种方案。对于每个圆排列，都有一个最大值（在该题语境中，即最高的一栋楼），明显圆排列间是没有顺序的。而现在要确定 $A-1$ ​个在左，$B-1$​ 个在右，则是原先的一个方案的 $\dbinom{a+b-2}{a-1}$ ​倍。

### P5824 十二重计数法

现在给 $n$ 个球， $m$ 个箱子。

$\text{I}$：球之间互不相同，盒子之间互不相同。

方案数为$m^n$。

$\text{II}$：球之间互不相同，盒子之间互不相同，每个盒子至多装一个球。

对于每个球，相当于每次放入还没有球的箱子里，方案数为 $m^{\underline{n}}$

$\text{III}$：球之间互不相同，盒子之间互不相同，每个盒子至少装一个球。

考虑容斥：随便放 - 挑一个盒子不放，其余随便 + 挑两个盒子不放... = $m^n - \dbinom{m}{1}(m-1)^n + \dbinom{m}{2}(m-2)^n - ... = \sum\limits_{i=0}^m (-1)^i\dbinom{m}{i}(m-i)^n$ 

$\text{IV}$：球之间互不相同，盒子全部相同。

考虑第二斯特林数的定义，方案数为 $\sum\limits_{i=1}^m S(n,i)$

$\text{V}$：球之间互不相同，盒子全部相同，每个盒子至多装一个球。

方案数为 $[n\leq m]\genfrac\{\}{0}{0}{n}{n} = [n\leq m]$ 。

$\text{VI}$：球之间互不相同，盒子全部相同，每个盒子至少装一个球。

考虑第二斯特林数的定义，方案数为 $S(n,m)$

$\text{VII}$：球全部相同，盒子之间互不相同。

满足隔板法模型，方案数为 $\dbinom{n+m-1}{m-1}$

当然也可用OGF来做，一样的。

$\text{VIII}$：球全部相同，盒子之间互不相同，每个盒子至多装一个球。

相当于选$n$个盒子放球，方案数为 $\dbinom{m}{n}$

$\text{IX}$：球全部相同，盒子之间互不相同，每个盒子至少装一个球。

满足隔板法模型，方案数为 $\dbinom{n-1}{m-1}$

$\text{X}$：球全部相同，盒子全部相同。

其对应分割数 $P_{n,m}$ ，即将 $n$ 个数分成 $m$ 种数的方案数（详见「整数划分」）

$\text{XI}$：球全部相同，盒子全部相同，每个盒子至多装一个球。

方案数为 $[n\leq m]$

$\text{XII}$：球全部相同，盒子全部相同，每个盒子至少装一个球。

对应分割数 $P_{n-m,m}$

```cpp
//code sourced from kinesis
#include <bits/stdc++.h>
using namespace std;

#define _REP(i, a, b) for (int i = (a); i >= (int)(b); --i)
#define REP(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define UREP(i, u) for (int i = p[(u)]; i + 1; i = edge[i].next)
//iterator: for(int u:x),x is container
#define x(p) (p).first
#define y(p) (p).second
#define pii pair<int, int>
#define mp(x, y) make_pair((x), (y))
#define sign(x) (fabs(x) < eps ? 0 : ((x) > 0 ? 1 : -1))
#define ll long long
#define L7 __int128  //1<<7 bit
#define ull unsigned long long
const int inf = 0x3f3f3f3f;
const ll inff = 0x3f3f3f3f3f3f3f3f;
const int mod = 998244353;
const double eps = 1e-9;
#define ri1(x) scanf("%d", &(x))
#define ri2(x, y) scanf("%d%d", &(x), &(y))
#define ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
//#define Debug
#ifdef Debug
#endif  // Debug

const int maxn = 262144;

namespace NTT {
const int mod = 998244353;  //998244353,1004535809,469762049,985661441,167772161. g = 3.950009857,g=7
int qp(ll base, ll n)       //快速幂
{
    ll res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return (int)res;
}
int rev[maxn << 2];
void change(vector<int>& x, int len) {
    int bit = 0;
    while ((1 << bit) < len)
        bit++;
    REP(i, 1, len - 1) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        if (i < rev[i])
            swap(x[i], x[rev[i]]);
    }  //前面和FFT一样
}
void ntt(vector<int>& x, int lim, int opt) {
    change(x, lim);
    for (int m = 2; m <= lim; m <<= 1) {
        int k = m >> 1;
        int gn = qp(3, (mod - 1) / m);
        for (int i = 0; i < lim; i += m) {
            int g = 1;
            for (int j = 0; j < k; ++j, g = 1ll * g * gn % mod) {
                int tmp = 1ll * x[i + j + k] * g % mod;
                x[i + j + k] = (x[i + j] - tmp + mod) % mod;
                x[i + j] = (x[i + j] + tmp) % mod;
            }
        }
    }
    if (opt == -1) {
        reverse(x.begin() + 1, x.begin() + lim);
        int inv = qp(lim, mod - 2);
        REP(i, 0, lim - 1)
        x[i] = 1ll * x[i] * inv % mod;
    }
}
}  // namespace NTT
using NTT::ntt;

ll qp(ll base, ll n) {
    base %= mod;
    ll res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return res;
}

ll Finv[maxn + 10], fac[maxn + 10], inv[maxn + 10];

void init_Comb()  //n<N
{
    int n = maxn;
    inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        inv[i] = ((mod - mod / i) * inv[mod % i]) % mod;
    fac[0] = Finv[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod, Finv[i] = Finv[i - 1] * inv[i] % mod;
}
ll C(ll n, ll m) {
    if (m < 0 || m > n)
        return 0;
    return fac[n] * Finv[n - m] % mod * Finv[m] % mod;
}

void derivative(int deg, vector<int>& f, vector<int>& g) {
    REP(i, 0, deg - 2)
    g[i] = 1LL * f[i + 1] * (i + 1) % mod;
    g[deg - 1] = 0;
}

void integrate(int deg, vector<int>& f, vector<int>& g) {
    _REP(i, deg - 1, 1)
    g[i] = 1LL * f[i - 1] * inv[i] % mod;
    g[0] = 0;  //c
}

void PolyInv(int deg, vector<int>& f, vector<int>& g)  //蝴蝶变换的rev[maxn<<2],f.resize(n<<2),g.resize(n<<2)
{
    if (deg == 1) {
        g[0] = qp(f[0], mod - 2);
        return;
    }
    PolyInv((deg + 1) >> 1, f, g);
    int lim = 1;
    while (lim < (2 * deg - 1))
        lim <<= 1;
    vector<int> h(lim);
    REP(i, 0, deg - 1)
    h[i] = f[i];
    ntt(g, lim, 1), ntt(h, lim, 1);
    REP(i, 0, lim - 1)
    g[i] = 1LL * (2LL + mod - 1LL * g[i] * h[i] % mod) % mod * g[i] % mod;
    ntt(g, lim, -1);
    REP(i, deg, lim - 1)
    g[i] = 0;
}

void PolyLn(int deg, vector<int>& f, vector<int>& g) {
    /* g = ln f = ∫ f' f^-1 dx */
    assert(f[0] == 1);
    int lim = 1;
    while (lim < (deg << 1))
        lim <<= 1;
    vector<int> f_(lim), _f(lim);  //f',f^-1
    derivative(deg, f, f_);
    PolyInv(deg, f, _f);
    ntt(_f, lim, 1), ntt(f_, lim, 1);
    REP(i, 0, lim - 1)
    f_[i] = 1LL * f_[i] * _f[i] % mod;
    ntt(f_, lim, -1);
    integrate(deg, f_, g);
}

void PolyExp(int deg, vector<int>& f, vector<int>& g) {
    /* g = exp(f) = g_0 (1 - ln g_0 + f) */
    assert(f[0] == 0);
    if (deg == 1) {
        g[0] = 1;
        return;
    }
    PolyExp((deg + 1) >> 1, f, g);
    int lim = 1;
    while (lim < (deg << 1))
        lim <<= 1;
    vector<int> gLn(lim);
    PolyLn(deg, g, gLn);
    REP(i, 0, deg - 1)
    gLn[i] = (1LL * f[i] - gLn[i] + mod) % mod;
    gLn[0] = (gLn[0] + 1) % mod;

    ntt(g, lim, 1), ntt(gLn, lim, 1);
    REP(i, 0, lim - 1)
    g[i] = 1LL * g[i] * gLn[i] % mod;
    ntt(g, lim, -1);
    REP(i, deg, lim - 1)
    g[i] = 0;
}

void solve1(int n, int m)  //球不同箱不同
{
    printf("%d\n", (int)qp(m, n));
}

void solve2(int n, int m)  //球不同箱不同，至多放一个
{
    printf("%d\n", n > m ? 0 : (1LL * fac[m] * Finv[m - n] % mod));
}

void solve3(int n, int m)  //球不同箱不同，至少放一个
{
    if (n < m)
        return (void)(printf("0\n"));
    int ans = 0, op = 1;
    REP(i, 0, m)
    (ans += (1LL * op * C(m, i) % mod * qp(m - i, n) % mod + mod) % mod) %= mod,
        op = -op;
    printf("%d\n", ans);
}

int Snm;

void solve4(int n, int m)  //球不同箱相同
{
    vector<int> f(maxn << 1), g(maxn << 1);
    int op = 1;
    REP(i, 0, m)
    f[i] = (1LL * op * Finv[i] % mod + mod) % mod,
    op = -op, g[i] = 1LL * qp(i, n) * Finv[i] % mod;
    int lim = 1;
    while (lim < ((m + 1) << 1))
        lim <<= 1;
    ntt(f, lim, 1), ntt(g, lim, 1);
    REP(i, 0, lim - 1)
    f[i] = 1LL * f[i] * g[i] % mod;
    ntt(f, lim, -1);
    int ans = 0;
    REP(i, 1, m)
    (ans += f[i]) %= mod,
        Snm = (i == m ? f[i] : 0);
    printf("%d\n", ans);
}

void solve5(int n, int m)  //球不同箱相同，至多放一个
{
    printf("%d\n", n > m ? 0 : 1);
}

void solve6(int n, int m)  //球不同箱相同，至少放一个
{
    printf("%d\n", Snm);
}

void solve7(int n, int m)  //球相同箱不同
{
    printf("%d\n", (int)C(n + m - 1, n));
}

void solve8(int n, int m)  //球相同箱不同，至多放一个
{
    printf("%d\n", C(m, n));
}

void solve9(int n, int m)  //球相同箱不同，至少放一个
{
    printf("%d\n", C(n - 1, m - 1));
}

vector<int> f(maxn << 1), g(maxn << 1);

void init_div_num(int n, int m) {
    REP(j, 1, m) {
        REP(i, 1, n / j) {
            f[i * j] = (f[i * j] + inv[i]) % mod;
        }
    }
    PolyExp(n + 1, f, g);
}

void solve10(int n, int m) {
    printf("%d\n", g[n]);
}

void solve11(int n, int m) {
    printf("%d\n", n > m ? 0 : 1);
}

void solve12(int n, int m) {
    printf("%d\n", n < m ? 0 : g[n - m]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);  //cf needn't delete this
#endif                              // ONLINE_JUDGE
    int n, m;
    ri2(n, m);
    init_Comb();
    init_div_num(n, m);
    solve1(n, m);
    solve2(n, m);
    solve3(n, m);
    solve4(n, m);
    solve5(n, m);
    solve6(n, m);
    solve7(n, m);
    solve8(n, m);
    solve9(n, m);
    solve10(n, m);
    solve11(n, m);
    solve12(n, m);
    return ~~(0 - 0);
}

```

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

# Poly



## 代码

```cpp
#include <bits/stdc++.h>
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int P = 998244353, g = 3;
std::vector<int> rev, roots{0, 1};

int power(int a, int b) {
    int res = 1;
    for (; b; b >>= 1, a = 1ll * a * a % P)
        if (b & 1)
            res = 1ll * res * a % P;
    return res;
}
void dft(std::vector<int>& a) {  //直接传数组进来。数组需要扩容至2^k
    int n = a.size();
    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; ++i)
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
    }
    for (int i = 0; i < n; ++i)
        if (rev[i] < i)
            std::swap(a[i], a[rev[i]]);
    if (int(roots.size()) < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            int e = power(g, (P - 1) >> (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); ++i) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = 1ll * roots[i] * e % P;
            }
            ++k;
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; ++j) {
                int u = a[i + j];
                int v = 1ll * a[i + j + k] * roots[k + j] % P;
                int x = u + v;
                if (x >= P)
                    x -= P;
                a[i + j] = x;
                x = u - v;
                if (x < 0)
                    x += P;
                a[i + j + k] = x;
            }
        }
    }
}
void idft(std::vector<int>& a) {
    int n = a.size();
    std::reverse(a.begin() + 1, a.end());
    dft(a);
    int inv = power(n, P - 2);
    for (int i = 0; i < n; ++i)
        a[i] = 1ll * a[i] * inv % P;
}
struct Poly {
    std::vector<int> a;
    Poly() {}
    Poly(int a0) {
        if (a0)
            a = {a0};
    }
    Poly(const std::vector<int>& a1)  //保留有效项
        : a(a1) {
        while (!a.empty() && !a.back())
            a.pop_back();
    }
    int size() const {
        return a.size();
    }
    int operator[](int idx) const {
        if (idx < 0 || idx >= size())
            return 0;
        return a[idx];
    }
    Poly mulxk(int k) const {  //返回Poly<<k（右移k位）的结果
        auto b = a;
        b.insert(b.begin(), k, 0);
        return Poly(b);
    }
    Poly modxk(int k) const {  //返回Poly 0~x^{k-1}项的结果。可能第k-1项会非法访问（没开空间）
        k = std::min(k, size());
        return Poly(std::vector<int>(a.begin(), a.begin() + k));
    }
    Poly divxk(int k) const {  //返回Poly 左移k位的结果
        if (size() <= k)
            return Poly();
        return Poly(std::vector<int>(a.begin() + k, a.end()));
    }
    friend Poly operator+(const Poly a, const Poly& b) {  //返回Poly +
        std::vector<int> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); ++i) {
            res[i] = a[i] + b[i];
            if (res[i] >= P)
                res[i] -= P;  //+法一个if解决模域外问题
        }
        return Poly(res);
    }
    friend Poly operator-(const Poly a, const Poly& b) {  //返回Poly -
        std::vector<int> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); ++i) {
            res[i] = a[i] - b[i];
            if (res[i] < 0)
                res[i] += P;
        }
        return Poly(res);
    }
    friend Poly operator*(Poly a, Poly b) {  //返回Poly *
        int sz = 1, tot = a.size() + b.size() - 1;
        while (sz < tot)
            sz *= 2;
        a.a.resize(sz);
        b.a.resize(sz);
        dft(a.a);
        dft(b.a);
        for (int i = 0; i < sz; ++i)
            a.a[i] = 1ll * a[i] * b[i] % P;
        idft(a.a);
        return Poly(a.a);
    }
    Poly& operator+=(Poly b) {  //Poly +=
        return (*this) = (*this) + b;
    }
    Poly& operator-=(Poly b) {  //Poly -=
        return (*this) = (*this) - b;
    }
    Poly& operator*=(Poly b) {  //Poly *=
        return (*this) = (*this) * b;
    }
    Poly deriv() const {  //Poly 微分
        if (a.empty())
            return Poly();
        std::vector<int> res(size() - 1);
        for (int i = 0; i < size() - 1; ++i)
            res[i] = 1ll * (i + 1) * a[i + 1] % P;
        return Poly(res);
    }
    Poly integr() const {  //Poly 积分
        if (a.empty())
            return Poly();
        std::vector<int> res(size() + 1);
        for (int i = 0; i < size(); ++i)
            res[i + 1] = 1ll * a[i] * power(i + 1, P - 2) % P;
        return Poly(res);
    }
    Poly inv(int m) const {  //Poly 求逆
        Poly x(power(a[0], P - 2));
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (2 - modxk(k) * x)).modxk(k);
        }
        return x.modxk(m);
    }
    Poly log(int m) const {  //Poly 取对数
        return (deriv() * inv(m)).integr().modxk(m);
    }
    Poly exp(int m) const {  //Poly 取指数
        Poly x(1);
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (1 - x.log(k) + modxk(k))).modxk(k);
        }
        return x.modxk(m);
    }
    Poly sqrt(int m) const {  //Poly 开方
        Poly x(1);
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (modxk(k) * x.inv(k)).modxk(k)) * ((P + 1) / 2);
        }
        return x.modxk(m);
    }
    Poly mulT(Poly b) const {  //转置
        if (b.size() == 0)
            return Poly();
        int n = b.size();
        std::reverse(b.a.begin(), b.a.end());
        return ((*this) * b).divxk(n - 1);
    }
    std::vector<int> eval(std::vector<int> x) const {  //多点求值
        if (size() == 0)
            return std::vector<int>(x.size(), 0);
        const int n = std::max(int(x.size()), size());
        std::vector<Poly> q(4 * n);
        std::vector<int> ans(x.size());
        x.resize(n);
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                q[p] = std::vector<int>{1, (P - x[l]) % P};
            } else {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        std::function<void(int, int, int, const Poly&)> work = [&](int p, int l, int r, const Poly& num) {
            if (r - l == 1) {
                if (l < int(ans.size()))
                    ans[l] = num[0];
            } else {
                int m = (l + r) / 2;
                work(2 * p, l, m, num.mulT(q[2 * p + 1]).modxk(m - l));
                work(2 * p + 1, m, r, num.mulT(q[2 * p]).modxk(r - m));
            }
        };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
};
```

## 任意模数

```cpp
//使用Int数乘法当且仅当IFT时两个多项式点值相乘
//用Int类型多项式f给初始多项式赋值g时使用g[i] = f[i].get()函数，不然会WA。
//包括对原多项式的指数，对数，求逆运算，得到的多项式都需要f[i] = f[i].get()
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int mod;
namespace Math {
int power(ll base, ll n, const int mod) {
    ll res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return (int)res;
}
int inv(int x, const int mod) {
    return power(x, mod - 2, mod);
}
}  // namespace Math

const int mod1 = 998244353, mod2 = 1004535809, mod3 = 469762049, G = 3;
const ll mod_1_2 = 1LL * mod1 * mod2;
const int inv_1 = Math::inv(mod1, mod2),
          inv_2 = Math::inv(mod_1_2 % mod3, mod3);
struct Int {
    int A, B, C;
    Int()
        : A(0), B(0), C(0) {}
    Int(int __num)
        : A(__num), B(__num), C(__num) {}
    Int(int __A, int __B, int __C)
        : A(__A), B(__B), C(__C) {}
    static Int reduce(const Int& x) {
        return Int(x.A + (x.A >> 31 & mod1), x.B + (x.B >> 31 & mod2),
                   x.C + (x.C >> 31 & mod3));
    }
    friend Int operator+(const Int& lhs, const Int& rhs) {
        return reduce(Int(lhs.A + rhs.A - mod1, lhs.B + rhs.B - mod2,
                          lhs.C + rhs.C - mod3));
    }
    friend Int operator-(const Int& lhs, const Int& rhs) {
        return reduce(Int(lhs.A - rhs.A, lhs.B - rhs.B, lhs.C - rhs.C));
    }
    friend Int operator*(const Int& lhs, const Int& rhs) {
        return Int(1LL * lhs.A * rhs.A % mod1, 1LL * lhs.B * rhs.B % mod2,
                   1LL * lhs.C * rhs.C % mod3);
    }
    int get() {
        ll x = 1LL * (B - A + mod2) % mod2 * inv_1 % mod2 * mod1 + A;
        return (1LL * (C - x % mod3 + mod3) % mod3 * inv_2 % mod3 *
                    (mod_1_2 % mod) % mod +
                x) %
               mod;
    }
};

#define maxn 131072

namespace Poly {
#define N (maxn << 1)
int lim, s, rev[N];
Int Wn[N | 1];
void init(int n) {  // init适用于DFT，IDFT，n为运算长度
    s = -1, lim = 1;
    while (lim < n)
        lim <<= 1, ++s;
    for (int i = 1; i < lim; ++i)
        rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
    const Int t(Math::power(G, (mod1 - 1) / lim, mod1),
                Math::power(G, (mod2 - 1) / lim, mod2),
                Math::power(G, (mod3 - 1) / lim, mod3));
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
        Int ilim(Math::inv(lim, mod1), Math::inv(lim, mod2),
                 Math::inv(lim, mod3));
        for (int i = 0; i < lim; i++)
            A[i] = A[i] * ilim;
    }
}
#undef N
}  // namespace Poly
using Poly::init;
using Poly::ntt;
vector<Int> A, B;

int n, m;
int main() {
    cin >> n >> m >> mod;
    n++, m++;
    A.resize(maxn << 1), B.resize(maxn << 1);
    for (int i = 0, x; i < n; ++i)
        cin >> x, A[i] = x;
    for (int i = 0, x; i < m; ++i)
        cin >> x, B[i] = x;
    Poly::init(n + m);
    Poly::ntt(A), Poly::ntt(B);
    for (int i = 0; i < Poly::lim; ++i)
        A[i] = A[i] * B[i];
    Poly::ntt(A, -1);
    for (int i = 0; i < n + m - 1; ++i)
        cout << A[i].get() << " ";
    cout << "\n";
    return 0;
}

```

# Prufer序列

Prufer序列是一个与**有标号无根树**满足双射关系的序列。即一个有标号无根树唯一对应一个 Prufer 序列 ，而一个 Prufer 序列唯一构造一个有标号无根树。

## 用无根树线性构造Prufer序列

初始先把指针指向编号最小的叶节点。

- 将叶节点 u 从树上删掉。
- 当删掉后，将与 u 相连的点 v 加入 prufer 序列。与其相连的点成为了叶节点，且编号 v<u，则继续删 v，直至与其相连的点 v>u，或者与其相连的不成为叶节点。
- 不断单调往编号大的移指针，直至构造出大小为 n-2 的 prufer 序列。

为什么这样是正确的：考虑删了某叶节点 u，若相邻的比 u 小，且成为了叶节点，那必然是现存的最小的叶节点，必删；若相邻的比 u 大，那么指针移到后面也会考虑它，所以不影响结果。

## 用Prufer序列线性构造无根树

首先，Prufer 序列的性质有：

- 对于剩下来的两个节点，必有一个为 n。
- 节点的度为 prufer 序列里出现的次数 +1。（没出现的节点就说明初始是叶节点）。

```cpp
vector<int> G[N];
vector<int> fa;

void dfs(int v) {
  for(int u:G[v]){
    if (u != fa[v]) fa[u] = v, dfs(u);
  }
}

vector<int> prufer_code()
{
  fa.resize(n+1),fa[n] = 0;
  dfs(n);//保证根不会被当做被删点。间接保证被删的都是除根节点以外的点
  int ptr = 0;
  vector<int> deg(n+1);
  REP(i,1,n){
    deg[i] = G[i].size();
    if(deg[i]==1&&ptr==0) ptr = i;//要跑完循环，否则deg会错
  }
  vector<int> code(n - 1);
  int leaf = ptr;
  REP(i,1,n-2){
    int nxt = fa[leaf];
    code[i] = nxt;
    if(--deg[nxt]==1&&nxt<ptr){
      leaf = nxt;
    }
    else{
      ptr++;
      while(deg[ptr]!=1) ptr++;
      leaf = ptr;
    }
  }
  return code;
}

vector<pair<int, int>> prufer_decode(vector<int> const& code)
{
  int n = code.size() + 2;
  vector<int> deg(n+1, 1);deg[0] = 0;
  for(int i:code) deg[i]++;
  int ptr = 1;
  while (deg[ptr] != 1) ptr++;
  int leaf = ptr;
  vector<pair<int, int>> edges;
  for (int v:code) {
    edges.emplace_back(leaf, v);
    if(--deg[v]==1&&v<ptr){
      leaf = v;
    }
    else{
      ptr++;
      while(deg[ptr]!=1) ptr++;
      leaf = ptr;
    }
  }
  edges.emplace_back(leaf,n);
  return edges;
}
```

## Cayley 公式

对于一个完全图，有标号生成树的个数为 $n^{n-2}$​。

可以用 Prufer 序列来证明：对于长度为 $n-2$ 的任意元素值域为 $[1,n]$ 都能唯一构造一个有标号生成树，所以个数为 $n^{n-2}$。

$F(x)=\sum_{i=1}^n A(a_ix)\prod_{j=1,j\neq i}^nB(a_jx)$

## prufer 求 S 个联通块构成树的方案数

设 S 个联通块，每个联通块的大小为 $a_i$​。那么需要加 $S-1$ 条边，总度数 +2S-2。设每个联通块的度数为 $d_i$。

那么方案数为：
$$
\sum_{\sum d_i = 2*S-2} \prod a_i^{d_i}
$$
由于 prufer 序列中，点的度数等于 prufer 序列出现次数 +1，故有
$$
\sum_{\sum d'_i = S-2} \prod a_i^{d'_i+1},d' = d+1
$$
（以下简记 d = d'）
$$
\sum_{\sum d_i = S-2} \prod a_i^{d_i+1} =  \prod a_i\sum_{\sum d_i = S-2} \prod a_i^{d_i}
$$
后面的式子可以理解为：在 prufer 序列出现一次，方案 * a_i。那么根据 Cayley 公式，$\sum_{\sum d_i = S-2} \prod a_i^{d_i} = (\sum a_i)^{S-2} = n^{S-2}$

所以原式 $=n^{S-2}\prod a_i$​

# 上指标求和

$\sum_{0 \leq k \leq n}\dbinom{k}{m}=\dbinom{n+1}{m+1}$

$\sum_{1 \leq k \leq n}\dbinom{k}{m}=\dbinom{n+1}{m+1} - [m=0]$

