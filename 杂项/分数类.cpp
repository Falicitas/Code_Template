#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
i64 gcd(i64 x, i64 y) {
    return y == 0 ? x : gcd(y, x % y);
}
class frac {  //用于结果为分数且取模的打表
   public:
    i64 x, y;  //x/y
   private:
    void yf() {  //约分
        if (y < 0)
            x = -x, y = -y;
        i64 a = gcd(abs(x), y);
        x /= a, y /= a;
    }

   public:
    frac(i64 x = 0, i64 y = 1)  //初始化为0.
        : x(x), y(y) { yf(); }
    frac(i64 num, i64 mod, i64 t) {  //将取模后的值转为分数。t是极可能的分子值域上限，需要人工确定
        for (int i = 1; i <= 1000000; i++) {
            i64 z = i * num % mod;
            if (z <= t) {
                x = z, y = i;
                return;
            }
        }
        assert(1 == 0);  //到了这就不对了
    }
    double todb() { return (double)x / (double)y; }
    frac operator=(frac b) {
        x = b.x, y = b.y;
        return *this;
    }
    friend ostream& operator<<(ostream& os, frac& cc) {
        os << cc.x << "/" << cc.y;
        return os;
    }
};
frac operator+(frac a, frac b) {
    i64 d = gcd(a.y, b.y);
    b.y /= d, a.y /= d;
    return frac(a.x * b.y + a.y * b.x, d * a.y * b.y);
}
frac operator-(frac a) {
    return frac(-a.x, a.y);
}
frac operator-(frac a, frac b) {
    return a + (-b);
}
frac operator*(frac a, frac b) {
    return frac(a.x * b.x, a.y * b.y);
}
frac operator/(frac a, frac b) {
    return frac(a.x * b.y, a.y * b.x);
}
frac operator+=(frac& a, frac b) {
    return a = a + b;
}
frac operator-=(frac& a, frac b) {
    return a = a - b;
}
frac operator*=(frac& a, frac b) {
    return a = a * b;
}
frac operator/=(frac& a, frac b) {
    return a = a / b;
}
bool operator>(frac a, frac b) {
    return a.x * b.y > b.x * a.y;
}
bool operator<(frac a, frac b) {
    return b > a;
}
bool operator>=(frac a, frac b) {
    return !(b > a);
}
bool operator<=(frac a, frac b) {
    return !(a > b);
}
bool operator==(frac a, frac b) {
    return !(a < b) && !(b < a);
}
bool operator!=(frac a, frac b) {
    return (a < b) || (b < a);
}

i64 qp(i64 base, i64 n, i64 mod) {
    i64 res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    int mod = 998244353;
    auto t = frac(4 * qp(14, mod - 2, mod) % mod, mod, 100);
    cout << t << "\n";
    return 0;
}