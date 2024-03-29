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