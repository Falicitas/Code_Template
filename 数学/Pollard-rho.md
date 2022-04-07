# Pollard-rho算法

```cpp
//#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
using namespace std;

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

namespace Pollard_rho {
bool mr32(u32 n, u32 a) {
    if (!(a %= n))
        return 1;
    uint8_t r = __builtin_ctz(n - 1);
    u32 d = n >> r, p = 1;
    for (; d; d >>= 1, a = u64(a) * a % n) {
        if (d & 1)
            p = u64(p) * a % n;
    }
    if (p == 1)
        return 1;
    while (p != n - 1 && --r) {
        p = u64(p) * p % n;
    }
    return p == n - 1;
}
bool mr64(u64 n, u64 a) {
    if (!(a %= n))
        return 1;
    u8 r = __builtin_ctzll(n - 1);
    u64 d = n >> r, p = 1;
    for (; d; d >>= 1, a = u128(a) * a % n) {
        if (d & 1)
            p = u128(p) * a % n;
    }
    if (p == 1)
        return 1;
    while (p != n - 1 && --r) {
        p = u128(p) * p % n;
    }
    return p == n - 1;
}
bool dmr32(u32 n) {
    return mr32(n, 2) && mr32(n, 7) && mr32(n, 61);
}
bool dmr64(u64 n) {
    if (n <= 0xFFFFFFFF)
        return dmr32(n);
    return mr64(n, 2) && mr64(n, 325) && mr64(n, 9375) && mr64(n, 28178) &&
           mr64(n, 450775) && mr64(n, 9780504) && mr64(n, 1795265022);
}
vector<u64> factorise(u64 n) {
    // factorises integers 1 ≤ n < 2^62
    vector<u64> pf;
    for (u8 i : {2, 3, 5})
        while (!(n % i))
            pf.push_back(i), n /= i;
    for (u32 i = 7; i * i <= n && i <= 211; i += 6)
        for (u32 j : {0, 4})
            while (n % (i + j) == 0)
                pf.push_back(i + j), n /= i + j;
    if (n == 1)
        return pf;
    vector<pair<u64, u8>> q{{n, 1}};
    while (!q.empty()) {
        auto n = q.back().first;
        auto c = q.back().second;
        q.pop_back();
        if (n < 49729) {
            while (c--)
                pf.push_back(n);
            continue;
        }
        u64 r = sqrt(n) + 0.5;
        if (r * r == n) {
            q.emplace_back(r, c * 2);
            continue;
        }
        if (dmr64(n)) {
            while (c--)
                pf.push_back(n);
            continue;
        }
        u64 ni = -n;
        for (u8 _ = 5; _--;)
            ni *= 2 + ni * n;
        auto redc = [&](u128 x) -> u64 {
            return u64(x) * ni * u128(n) + x >> 64;
        };
        auto f = [&](u64 x) { return redc(u128(x) * x + 1); };

        u64 g = n;
        const u64 m = 1LL << (__lg(n) / 5);
        for (u64 x0 = 0; g == n; ++x0) {
            u64 x, y = x0, q = 1, ys;
            g = 1;
            for (u64 r = 1; g == 1; r <<= 1) {
                x = y;
                for (u64 _ = r; _--;)
                    y = f(y);
                for (u64 k = 0; k < r && g == 1; k += m) {
                    ys = y;
                    for (u64 _ = min(m, r - k); _--;)
                        y = f(y), q = redc(u128(max(x, y) - min(x, y)) * q);
                    g = __gcd(q, n);
                }
            }
            if (g == n) {
                for (; g == 1;) {
                    ys = f(ys);
                    g = __gcd(max(x, ys) - min(x, ys), n);
                }
            }
        }
        q.emplace_back(g, c);
        q.emplace_back(n / g, c);
    }
    sort(pf.begin(), pf.end());
    return pf;  //返回有重素因子集，累乘=n
}
}  // namespace Pollard_rho

```
