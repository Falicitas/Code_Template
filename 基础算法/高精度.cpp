#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct BigInt {  // a = 0时size = 0
    vector<int> a;
    BigInt() { a = {}; }
    BigInt(i64 a0) {
        a = vector<int>();
        while (a0) {
            a.emplace_back(a0 % 10);
            a0 /= 10;
        }
    }
    BigInt(const std::vector<int>& a1)
        : a(a1) {
        while (!a.empty() && !a.back())
            a.pop_back();
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
    friend BigInt operator+(const BigInt& a, const BigInt& b) {  //返回BigInt +
        std::vector<int> res(std::max(a.size(), b.size()) + 1);
        for (int i = 0; i < int(res.size()); ++i) {
            res[i] = a[i] + b[i];
            if (res[i] >= 10) {
                res[i + 1]++;
                res[i] -= 10;
            }
        }
        return BigInt(res);
    }
    friend BigInt operator*(const BigInt& a, const BigInt& b) {  //返回BigInt +
        std::vector<int> res(a.size() + b.size() + 1);
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < b.size(); j++) {
                res[i + j] += a[i] * b[j];
            }
        }
        for (int i = 0; i < int(res.size()); ++i) {
            if (res[i] >= 10) {
                res[i + 1] += res[i] / 10;
                res[i] %= 10;
            }
        }
        return BigInt(res);
    }
    BigInt& operator+=(BigInt b) {  // Poly +=
        return (*this) = (*this) + b;
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
    friend ostream& operator<<(ostream& os, BigInt& cc) {
        for (int i = (int)cc.size() - 1; i >= 0; i--) {
            os << cc[i];
        }
        return os;
    }
};  // namespace BigInt
