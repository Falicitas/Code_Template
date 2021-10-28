#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct Crt {
    const int maxp = 1e2 + 5;
    vector<i64> a, P;
    int n;
    Crt(vector<i64> a_, vector<i64> P_)
        : a(a_), P(P_) {
        n = a.size();
    }
    i64 ex_gcd(i64 a, i64 b, i64& x, i64& y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        i64 d = ex_gcd(b, a % b, x, y);
        i64 temp = x;
        x = y;
        y = temp - a / b * y;
        return d;
    }
    i64 CRT() {
        i64 M = 1;
        i64 ans = 0;
        for (int i = 0; i < n; i++) {
            M *= P[i];
        }
        for (int i = 0; i < n; i++) {
            i64 x, y;
            i64 Mi = M / P[i];
            ex_gcd(Mi, P[i], x, y);  //求逆元
            (ans += Mi * x * a[i]) % M;
        }
        ans = (ans % M + M) % M;
        return ans;
    }
};  // namespace _CRT
