# FWT

对于下标按位运算的卷积，即 $C_{k} = \sum\limits_{i\oplus j=k}A_i B_j$​，其中 $\oplus$​​​ 是二元位运算，FWT 可以加速卷积的过程。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int P = 998244353;

void add(int& x, int y) {
    (x += y) >= P && (x -= P);
}
void sub(int& x, int y) {
    (x -= y) < 0 && (x += P);
}
/*使用时直接调用Or,And,Xor,无需额外开2^k空间*/
struct FWT {
    int extend(int n) {
        int N = 1;
        for (; N < n; N <<= 1)
            ;
        return N;
    }
    void FWTor(std::vector<int>& a, bool rev) {
        int n = a.size();
        for (int l = 2, m = 1; l <= n; l <<= 1, m <<= 1) {
            for (int j = 0; j < n; j += l)
                for (int i = 0; i < m; i++) {
                    if (!rev)
                        add(a[i + j + m], a[i + j]);
                    else
                        sub(a[i + j + m], a[i + j]);
                }
        }
    }
    void FWTand(std::vector<int>& a, bool rev) {
        int n = a.size();
        for (int l = 2, m = 1; l <= n; l <<= 1, m <<= 1) {
            for (int j = 0; j < n; j += l)
                for (int i = 0; i < m; i++) {
                    if (!rev)
                        add(a[i + j], a[i + j + m]);
                    else
                        sub(a[i + j], a[i + j + m]);
                }
        }
    }
    void FWTxor(std::vector<int>& a, bool rev) {
        int n = a.size(), inv2 = (P + 1) >> 1;
        for (int l = 2, m = 1; l <= n; l <<= 1, m <<= 1) {
            for (int j = 0; j < n; j += l)
                for (int i = 0; i < m; i++) {
                    int x = a[i + j], y = a[i + j + m];
                    if (!rev) {
                        a[i + j] = (x + y) % P;
                        a[i + j + m] = (x - y + P) % P;
                    } else {
                        a[i + j] = 1LL * (x + y) * inv2 % P;
                        a[i + j + m] = 1LL * (x - y + P) * inv2 % P;
                    }
                }
        }
    }
    std::vector<int> Or(std::vector<int> a1, std::vector<int> a2) {
        int n = std::max(a1.size(), a2.size()), N = extend(n);
        a1.resize(N), FWTor(a1, false);
        a2.resize(N), FWTor(a2, false);
        std::vector<int> A(N);
        for (int i = 0; i < N; i++)
            A[i] = 1LL * a1[i] * a2[i] % P;
        FWTor(A, true);
        return A;
    }
    std::vector<int> And(std::vector<int> a1, std::vector<int> a2) {
        int n = std::max(a1.size(), a2.size()), N = extend(n);
        a1.resize(N), FWTand(a1, false);
        a2.resize(N), FWTand(a2, false);
        std::vector<int> A(N);
        for (int i = 0; i < N; i++)
            A[i] = 1LL * a1[i] * a2[i] % P;
        FWTand(A, true);
        return A;
    }
    std::vector<int> Xor(std::vector<int> a1, std::vector<int> a2) {
        int n = std::max(a1.size(), a2.size()), N = extend(n);
        a1.resize(N), FWTxor(a1, false);
        a2.resize(N), FWTxor(a2, false);
        std::vector<int> A(N);
        for (int i = 0; i < N; i++)
            A[i] = 1LL * a1[i] * a2[i] % P;
        FWTxor(A, true);
        return A;
    }
} fwt;
```

## 一些习题

### CF662C Binary Table

这题，首先按逻辑推一推。

对于行的翻转，可以抽象成一个值域为 $[0,2^n-1]$​​ 的集合 $X$​​。那么此时的最少的 1 可以写成：

$ans[X] = \sum\limits_{i=1}^{m}f(S_i\oplus X)$​​，其中 $ f(S_i\oplus X)$​ ​是对于某列取反或者不取反取最小值。那么原答案就是 $ans = \min\{ans[X]\}$​​

发现有些列的状态是一样的。换一种枚举方式：

$ans[X] = \sum\limits_{i=0}^{2^n-1}cnt_if(i\oplus X)$​，$cnt_i$​ 为状态为 $i$ ​的列的个数。

$ans[X] = \sum\limits_{i=0}^{2^n-1}\sum\limits_{j=0}^{2^n-1}cnt_if(j)[i\oplus X = j]$。贡献的套路划分计算。由于异或满足异或两次等于其他数原数，有

$ans[X] = \sum\limits_{i=0}^{2^n-1}\sum\limits_{j=0}^{2^n-1}cnt_if(j)[i\oplus j = X] = ans[X] = \sum\limits_{i\oplus j = X}cnt_i f_j$​，然后就开心的 AC 了。复杂度为 $O(n2^n)$​​。

## P6097 【模板】子集卷积

求 $c_{k}=\sum\limits_{i \& j=0 \atop i \mid j=k} a_{i} b_{j}$​ ， $k\in[0,2^n-1],n\in[0,20]$​。

$i | j = k$​ 可以使用 FWT 来计算。考虑提出 $i\&j = 0$​，这个即为 $|i| + |j| = |i \cup j|$​​。

令 $f_{i, j}=\left\{\begin{array}{l}a_{j}(|j|=i) \\ 0\end{array}, g_{i, j}=\left\{\begin{array}{l}b_{j}(|j|=i) \\ 0\end{array}\right.\right.$​，$h_{i}=\sum_{k=0}^{i} f_{k} * g_{i-k}$​，此时的 $h_{|i|,i}$​ 即满足了 $|i| + |j| = |i \cup j|$​。但还需满足 $i | j = k$​​，故形式应为

$\begin{aligned} h_{i} &=\sum_{i} \operatorname{IFWT}\left(\operatorname{FWT}\left(f_{k}\right) \cdot \operatorname{FMT}\left(g_{i-k}\right)\right) \\ &=\operatorname{IFWT}\left(\sum_{i} \operatorname{FMT}\left(f_{k}\right) \cdot \operatorname{FMT}\left(g_{i-k}\right)\right) \end{aligned}$

推得的下式，是由于 FWT，IFWT 具有可加性，可以加完后再 IFWT。

```cpp
//code sourced from kinesis
#include <bits/stdc++.h>
using namespace std;

constexpr int P = 998244353;

int cal(int x) {
    return __builtin_popcount(x);
}

const int N = 1 << 21 | 1;
int lim;

void OR(int* f, int opt = 1)  //opt = 1 or mod - 1
{
    for (int o = 2, k = 1; o <= lim; o <<= 1, k <<= 1)
        for (int i = 0; i < lim; i += o)
            for (int j = 0; j < k; j++)
                (f[i + j + k] += 1LL * f[i + j] * opt % P) %= P;
}

int a[22][N], b[22][N], c[22][N];

int main() {
    int n;
    cin >> n;
    lim = 1 << n;
    for (int i = 0; i < lim; i++)
        cin >> a[cal(i)][i];
    for (int i = 0; i < lim; i++)
        cin >> b[cal(i)][i];
    for (int i = 0; i < n; i++)
        OR(a[i]), OR(b[i]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < lim; k++) {
                (c[i][k] += 1LL * a[j][k] * b[i - j][k] % P) %= P;
            }
        }
    }
    for (int i = 0; i < n; i++)
        OR(c[i], P - 1);
    for (int i = 0; i < lim; i++)
        cout << (c[cal(i)][i] % P + P) % P << " ";
    cout << "\n";
    return 0;
}

```

