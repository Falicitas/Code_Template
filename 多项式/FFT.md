# FFT & Poly

## 小结

NTT（包括MTT）不能解决的：系数是浮点数；系数为负数且题目不取模（在取模意义上会出错）；系数大于模数。此时要使用 FFT。

## $e^{i\theta}$

$e^{i\theta}$​ 在极坐标上的代表含义为从原点指向单位圆从 (1,0) 点逆时针绕圆走 $\theta$​ 弧度的点，即一个 **复数向量**。

复数 **相乘** 遵循：**模长相乘，幅角相加** 的原则。由于复数 $z = a(\cos ({\theta})+i \cdot \sin (\theta)] = a\cdot e^{i\theta}$​​​，即 $z$​ ​​由唯一的 $(a,\theta)$​ ​​​表示，可利用其来证明系数相乘，指数相加。

## 单位复根

令 $\omega_n = e^{\frac{2\pi i}{n}},e^{\frac{2 \pi i}{n}}=\cos \left(\frac{2 \pi}{n}\right)+i \cdot \sin \left(\frac{2 \pi}{n}\right)$​​（对 $e^{i\theta}$​​ 泰勒展开，可得到此式）。对于不定方程 $x^n=1$​​ 的复数领域解可以有 $n$​​ 个：$\{\omega^k_n|k=0,1,...,n-1\}$​​，此时称 $\omega_n$​​ 为 n 次单位复根。对于任意 $(w_n^i)^n = 1[\cos (0)+i \cdot \sin (0)] = 1$​​​ 。

### 单位复根的性质

$$
\begin{array}{}
\omega_{n}^{n}=1 \\
\omega_{n}^{k}=\omega_{2 n}^{2 k} \\
\omega_{2 n}^{k+n}=-\omega_{2 n}^{k}
\end{array}
$$

## FFT

FFT实际是求 $(w_n^0,w_n^1,...,w_n^{n-1})$​​​ ​这 n 个点值的，朴素的过程单是代值就是 $O(n)$​​​​ 了。FFT的目的要将整个过程优化到 $O(nlogn)$​​​​。

采用分治的思想，将次数分为奇偶两部分，分别对其进行分治：

$f(x)=\left(a_{0}+a_{2} x^{2}+a_{4} x^{4}+a_{6} x^{6}\right)+\left(a_{1} x+a_{3} x^{3}+a_{5} x^{5}+a_{7} x^{7}\right)\\
=\left(a_{0}+a_{2} x^{2}+a_{4} x^{4}+a_{6} x^{6}\right)+x\left(a_{1}+a_{3} x^{2}+a_{5} x^{4}+a_{7} x^{6}\right)$

令$G(x) = \{a_0,a_2,a_4,a_6\},H(x) = \{a_1,a_3,a_5,a_7\}$

则$F(x)=G\left(x^{2}\right)+x \times H\left(x^{2}\right)$

利用单位复根的性质得到

$$
\begin{aligned}
\operatorname{DFT}\left(f\left(\omega_{n}^{k}\right)\right) &=\operatorname{DFT}\left(G\left(\left(\omega_{n}^{k}\right)^{2}\right)\right)+\omega_{n}^{k} \times \operatorname{DFT}\left(H\left(\left(\omega_{n}^{k}\right)^{2}\right)\right) \\
&=\operatorname{DFT}\left(G\left(\omega_{n}^{2 k}\right)\right)+\omega_{n}^{k} \times \operatorname{DFT}\left(H\left(\omega_{n}^{2 k}\right)\right) \\
&=\operatorname{DFT}\left(G\left(\omega_{n / 2}^{k}\right)\right)+\omega_{n}^{k} \times \operatorname{DFT}\left(H\left(\omega_{n / 2}^{k}\right)\right)
\end{aligned}
$$
同理可得
$$
\begin{aligned}
\operatorname{DFT}\left(f\left(\omega_{n}^{k+n / 2}\right)\right) &=\operatorname{DFT}\left(G\left(\omega_{n}^{2 k+n}\right)\right)+\omega_{n}^{k+n / 2} \times \operatorname{DFT}\left(H\left(\omega_{n}^{2 k+n}\right)\right) \\
&=\operatorname{DFT}\left(G\left(\omega_{n}^{2 k}\right)\right)-\omega_{n}^{k} \times \operatorname{DFT}\left(H\left(\omega_{n}^{2 k}\right)\right) \\
&=\operatorname{DFT}\left(G\left(\omega_{n / 2}^{k}\right)\right)-\omega_{n}^{k} \times \operatorname{DFT}\left(H\left(\omega_{n / 2}^{k}\right)\right)
\end{aligned}
$$
意思直白点就是
> 当递归到 n=1 时 $f(a_i) = a_i$​;
> 否则 $f[k] = g[k] + \omega_{n}^{k} * h[k],k\in [0,n/2)\\
f[k] = g[k-n/2] + \omega_{n}^{k-n/2} * h[k-n/2],k\in [n/2,n)$​

ps:第二个公式通常写成：$f[k+n/2] = g[k] + \omega_{n}^{k} * h[k],k\in [0,n/2)$这样可以跟着上个式子的循环一块走。

## 蝴蝶变换

当尝试去模拟分治的过程：

$\text { 设初始序列为 }\left\{x_{0}, x_{1}, x_{2}, x_{3}, x_{4}, x_{5}, x_{6}, x_{7}\right\}$

$\text { 一次二分之后 }\left\{x_{0}, x_{2}, x_{4}, x_{6}\right\},\left\{x_{1}, x_{3}, x_{5}, x_{7}\right\}$

$\text { 两次二分之后 }\left\{x_{0}, x_{4}\right\}\left\{x_{2}, x_{6}\right\},\left\{x_{1}, x_{3}\right\},\left\{x_{5}, x_{7}\right\}$

$\text { 三次二分之后 }\left\{x_{0}\right\}\left\{x_{4}\right\}\left\{x_{2}\right\}\left\{x_{6}\right\}\left\{x_{1}\right\}\left\{x_{5}\right\}\left\{x_{3}\right\}\left\{x_{7}\right\}$


会发现系数的坐标变换是有规律的，即更改后的位置跟更改前的位置在长度为 len，二进制表示下照中心对称。此时将递归的式子改成循环，模拟分治的反过程，完成计算的操作。原理与递归的完全一样，节约了递归产生的额外空间占用。

## IDFT

IDFT 则是将多项式的 DFT （即多项式的若干点值）转化成多项式的系数。

对于 $A(x)=a_{0}+a_{1} x+a_{2} x^{2}+\ldots+a_{n-1} x^{n-1}$​（这里的 $n$​ 补成 $2^m$ ​的形式）来说，设其带入单位根 $w_n^0,w_n^1,\dots,w_n^{n-1}$ ​得到点值 $y_0,y_1,\dots,y_{n-1}$​。有 $y_k = \sum\limits_{i=0}^{n-1}a_i (w_n^k)^i$​。

令 $Q(x) = y_0 + y_1x + \dots + y_{n-1}x^{n-1}$​​​​ ，即 $A(x)$​ 的 DFT。此时带入共轭单位根 $w_n^{-0},w_n^{-1},\dots,w_n^{-(n-1)}$​，设得到 $z_0,z_1,\dots,z_{n-1}$​。对于 $z_k$​​​ ​有：

$z_k = \sum\limits_{i=0}^{n-1}y_i(w_n^{-k})^i$

$ = \sum\limits_{i=0}^{n-1}\sum\limits_{j=0}^{n-1}a_j(w_n^{i})^j(w_n^{-k})^i$

$ = \sum\limits_{j=0}^{n-1}a_j\sum\limits_{i=0}^{n-1}(w^{j-k})^i$​。看右边的式子像什么？嗯，是单位根反演，故有

$z_k = \sum\limits_{j=0}^{n-1}a_j n[n|j-k] = a_kn$

故 $a_k = \frac{z_k}{n}$​​ 。

故IDFT的实质为带入共轭单位根，最后除以 $n$​，就得到了原多项式的系数了。

## FFT 和 NTT

在模域中，模数 $p$ 的原根 g 的 $g^i$ 的循环节是 $\varphi(p)$。将 g 作为多项式运算的单位复根，也拥有 FFT 中单位复根的三个性质。此时便可在模域下使用快速傅里叶变换了，即称作 NTT。

## 代码（FFT）

```cpp
#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
struct Complex {  //不用C++自带的是由于complex测试慢了3~5倍
    double x, y;
    Complex(double _x = 0.0, double _y = 0.0) { x = _x, y = _y; }
    Complex operator-(const Complex& b) const {
        return Complex(x - b.x, y - b.y);
    }
    Complex operator+(const Complex& b) const {
        return Complex(x + b.x, y + b.y);
    }
    Complex operator*(const Complex& b) const {
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};
void fft(Complex* a, int N, int opt) {
    int i, j, t, k;
    for (i = 1, j = 0; i < N - 1; i++) {
        for (t = N; j ^= (t >>= 1), ~j & t;)
            ;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (i = 1; i < N; i <<= 1) {
        Complex wn(cos(PI / i), opt * sin(PI / i));
        t = i << 1;
        for (j = 0; j < N; j += t) {
            Complex w(1, 0);
            for (k = 0; k < i; k++, w = w * wn) {
                Complex x(a[j + k]), y(w * a[j + i + k]);
                a[j + k] = x + y;
                a[j + i + k] = x - y;
            }
        }
    }
    if (opt == -1) {
        for (i = 0; i < N; i++)
            a[i] = Complex(a[i].x / N, a[i].y / N);
    }
}

constexpr int N = 1e6 + 5;
Complex A[N << 2], B[N << 2];

int main() {
    int n, m;
    cin >> n >> m;
    n++, m++;
    for (int i = 0; i < n; i++) {
        cin >> A[i].x;
    }
    for (int i = 0; i < m; i++) {
        cin >> B[i].x;
    }
    int lim = 1;
    while (lim < (n + m)) {
        lim <<= 1;
    }
    fft(A, lim, 1), fft(B, lim, 1);
    for (int i = 0; i < lim; i++) {
        A[i] = A[i] * B[i];
    }
    fft(A, lim, -1);
    for (int i = 0; i < n + m - 1; i++) {
        cout << (int)floor(A[i].x + 0.5) << " ";
    }
    cout << "\n";
    return 0;
}
```


