#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct BigInt {  // a = 0时size = 0
    vector<int> a;
    BigInt() { a = {}; }
    BigInt(int a0) {
        a = vector<int>();
        while (a0) {
            a.emplace_back(a0 % 10);
            a0 /= 10;
        }
    }
    BigInt(const std::string& s0) {
        int n = s0.length();
        a = vector<int>(n);
        for (int i = n - 1; i >= 0; i--) {
            a[n - i - 1] = s0[i] - '0';
        }
        while (!a.empty() && !a.back())
            a.pop_back();
    }
    BigInt(const std::vector<int>& a1) : a(a1) {
        while (!a.empty() && !a.back())
            a.pop_back();
    }
    int size() const { return a.size(); }
    int operator[](int idx) const {
        if (idx < 0 || idx >= size())
            return 0;
        return a[idx];
    }
    i64 get() {  //前提是BigInt在i64范围内
        i64 num = 0;
        for (int i = (int)a.size() - 1; i >= 0; i--) {
            num = num * 10 + a[i];
        }
        return num;
    }
    friend BigInt operator/(const BigInt& x, int y)  //低精除，返回商
    {
        assert(y != 0);
        i64 r = 0;
        vector<int> b(x.size());
        for (int i = (int)x.a.size() - 1; i >= 0; i--) {
            r = r * 10 + x[i];
            if (r >= y) {
                b[i] = r / y;
                r %= y;
            } else {
                b[i] = 0;
            }
        }
        return BigInt(b);
    }
    friend i64 operator%(const BigInt& x, int y)  //低精除，返回余数
    {
        assert(y != 0);
        i64 r = 0;
        for (int i = (int)x.a.size() - 1; i >= 0; i--) {
            r = r * 10 + x[i];
            if (r >= y) {
                r %= y;
            }
        }
        return r;
    }
    friend bool operator<(const BigInt& x,
                          const BigInt& y)  // x>y:1 x==y:0 x<y:-1
    {
        if (x.size() != y.size()) {
            return x.size() < y.size();
        }
        for (int i = (int)x.size() - 1; i >= 0; i--) {
            if (x[i] != y[i]) {
                return x[i] < y[i];
            }
        }
        return 0;
    }
};  // namespace BigInt

i64 power(i64 base, i64 n, int P) {
    i64 res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= P;
        (base *= base) %= P;
        n >>= 1;
    }
    return res;
}

i64 ExEuler(BigInt base, BigInt n, i64 P) {  //只适用于i32的P，除非power上光速幂
    i64 phi;
    {
        phi = P;
        i64 N = P;
        for (i64 i = 2; i * i <= N; i++)
            if (N % i == 0) {
                phi = phi / i * (i - 1);
                while (N % i == 0)
                    N /= i;
            }
        if (N > 1)
            phi = phi / N * (N - 1);
    }
    i64 Base = base % P, N;  //只要取模的余数，不改变被除数
    BigInt Phi(phi);
    if (n < Phi) {
        N = n % phi;
    } else {
        N = n % phi + phi;
    }
    return power(Base, N, P);
}

int main() {
    string a, b;
    int P;
    cin >> a >> P >> b;
    cout << Ex(a, b, P) << "\n";
    return 0;
}