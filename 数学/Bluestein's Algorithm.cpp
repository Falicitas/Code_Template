// code sourced from kinesis
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

const int maxn = 1 << 17;
const double PI = acos(-1.0);

namespace FFT {
struct Complex {
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
    Complex operator/(const Complex& b) const {
        return Complex((x * b.x + y * b.y) / (b.x * b.x + b.y * b.y),
                       (y * b.x - x * b.y) / (b.x * b.x + b.y * b.y));
    }
};
int rev[maxn << 2];
void change(Complex* x, int len) {
    int bit = 0;
    while ((1 << bit) < len)
        bit++;
    for (int i = 0; i < len; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        if (i < rev[i])
            swap(x[i], x[rev[i]]);
    }
}

}  // namespace FFT
// using FFT::fft;
using FFT::Complex;

void fft(Complex* a, int N, int f) {
    int i, j, t, k;
    for (i = 1, j = 0; i < N - 1; i++) {
        for (t = N; j ^= (t >>= 1), ~j & t;)
            ;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    for (i = 1; i < N; i <<= 1) {
        Complex wn(cos(PI / i), f * sin(PI / i));
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
    if (f == -1) {
        for (i = 0; i < N; i++) {
            a[i] = a[i] / N;
        }
    }
}

Complex w[maxn];

void init(int n) {
    for (int i = 0; i < n; i++) {
        w[i] = Complex(cos(2 * PI * i / n), sin(2 * PI * i / n));
    }
}

void bluestein(Complex* x,
               int n,
               int opt)  // opt=1时是bluestein的DFT，-1是bluestein的IDFT
{
    static Complex f[maxn << 2], g[maxn << 2];
    int lim = 1;
    while (lim < (3 * n))
        lim <<= 1;
    for (int i = 0; i < lim; i++) {
        f[i] = g[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        f[i] = x[i] * (opt == 1 ? w[(n - 1LL * i * (i - 1) / 2 % n) % n]
                                : w[1LL * i * (i - 1) / 2 % n]);
    }
    reverse(f, f + n);
    for (int i = 0; i < 2 * n; i++) {
        g[i] = (opt == -1 ? w[(n - 1LL * i * (i - 1) / 2 % n) % n]
                          : w[1LL * i * (i - 1) / 2 % n]);
    }
    fft(g, lim, 1), fft(f, lim, 1);
    for (int i = 0; i < lim; i++) {
        f[i] = f[i] * g[i];
    }
    fft(f, lim, -1);
    for (int i = 0; i < n; i++) {
        x[i] = (opt == 1 ? w[(n - 1LL * i * (i - 1) / 2 % n) % n]
                         : w[1LL * i * (i - 1) / 2 % n]) *
               f[n - 1 + i];
    }
    if (opt == -1) {
        for (int i = 0; i < n; i++) {
            x[i] = x[i] / n;
        }
    }
}

Complex c[maxn], b[maxn], a[maxn];

int main() {  //实现长度为n的c/b的循环卷积
    int n;
    cin >> n;
    init(n);  //记得使用bluestein前调用init(n)
    for (int i = 0; i < n; i++) {
        cin >> b[i].x;
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i].x;
    }
    bluestein(b, n, 1), bluestein(c, n, 1);
    for (int i = 0; i < n; i++) {
        a[i] = c[i] / b[i];
    }
    bluestein(a, n, -1);
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(5) << a[i].x << "\n";
    }
    return ~~(0 - 0);
}