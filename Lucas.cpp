#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

using i64 = long long;

struct LC {
    vector<i64> fac, finv, inv;  //根据模数大小开空间
    int P;
    LC(int P_)
        : P(P_) {
        fac = vector<i64>(P), finv = inv = fac;
        fac[0] = finv[0] = fac[1] = finv[1] = inv[1] = 1;
        for (ll i = 2; i < P; i++) {
            inv[i] = (P - P / i) * inv[P % i] % P;
            fac[i] = fac[i - 1] * i % P;
            finv[i] = finv[i - 1] * inv[i] % P;
        }
    }
    ll power(ll base, ll n) {
        ll res = 1;
        while (n) {
            if (n & 1)
                (res *= base) %= P;
            (base *= base) %= P;
            n >>= 1;
        }
        return res;
    }

    ll C(ll n, ll m)  //组合数
    {
        if (n < m || m < 0)
            return 0;
        return fac[n] * finv[m] % P * finv[n - m] % P;
    }
    ll Lucas(ll n, ll m)  //Lucas定理
    {
        if (n < m || m < 0)
            return 0;
        if (!n)
            return 1;
        return Lucas(n / P, m / P) * C(n % P, m % P) % P;
    }
};  // namespace LC

int main() {
    ll n, m, p = 10003;
    LC lucas(p);
    while (scanf("%lld%lld", &m, &n) == 2) {
        printf("%lld\n", lucas.Lucas(n, m));
    }
    return 0;
}
