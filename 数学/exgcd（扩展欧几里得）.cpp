#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
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
bool liEu(i64 a, i64 b, i64 c, i64& x, i64& y) {
    i64 d = ex_gcd(a, b, x, y);
    if (c % d != 0)
        return 0;
    i64 k = c / d;
    x *= k;  //得到一组特解，求最小非负整数，则x = (x % (b / d) + b / d) % (b / d);
    y *= k;
    return 1;
}