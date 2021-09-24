#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef long long ll;
constexpr int mod = 1e9 + 7;

template <class T>
T power(T a, int b, int p = mod) {
    T res = 1;
    for (; b; b /= 2, a *= a, a %= p) {
        if (b % 2) {
            res *= a;
            res %= p;
        }
    }
    return res;
}

/*
用于解一元同余高次方程a^x = b(\mod p)，且gcd(a,p) = 1
的最小非负整数解。无解输出-1 。gcd(a,p)!=1，由于推导式子不等价，会得出错误结果
*/
int bsgs(int a, int b, int p)  //应该记住的版本
{
    unordered_map<int, int> m;
    int sq = ceil(sqrt(p));
    i64 base = 1;
    for (int i = 1; i <= sq; i++) {
        base = base * a % p;
        m[b * base % p] = i;
    }
    int res = 1;
    for (int i = 1; i <= sq; i++) {
        res = res * base % p;
        if (m.count(res)) {
            return i * sq - m[res];
        }
    }
    return -1;
}

//求x^a = b (%p),p是素数的公式。用时将其放入 BSGS 中
int generator(int p) {
    {
        if (p != 2 && p != 4) {
            if (p % 2 == 0) {
                p /= 2;
            }  //此时只有p^e才能有原根
            for (int i = 2; i * i <= p; i++) {
                if (p % i == 0) {
                    while (p % i == 0) {
                        p /= i;
                    }
                    if (i == 2 || p != 1) {
                        return -1;
                    }
                    break;
                }
            }
        }
    }  //能过这个无名函数，说明p必有原根

    int phi = p;
    {
        int tmp = p;
        for (int i = 2; i * i <= tmp; ++i) {
            if (tmp % i == 0) {
                phi = phi / i * (i - 1);
                while (tmp % i == 0) {
                    tmp /= i;
                }
            }
        }
        if (tmp > 1) {
            phi = phi / tmp * (tmp - 1);
        }
    }  // O(\sqrt{p}) 得到 p 的 phi 值

    vector<int> fact;
    {
        int n = phi;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                fact.push_back(i);
                while (n % i == 0) {
                    n /= i;
                }
            }
        }
        if (n > 1) {
            fact.push_back(n);
        }
    }  //得到 phi 的素因子

    for (int g = 1; g <= p; ++g) {
        if (__gcd(g, p) != 1) {
            continue;
        }  //原根与模数互质
        bool ok = true;
        for (int factor : fact) {
            if (power(g, phi / factor, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) {
            return g;
        }
    }
    assert(0);
    return -1;
}
/*
求x^a = b(\bmod p),且p是素数（保证了gcd(a,p)=1且p有原根）的公式。
假设x = g^c，则(g^c)^a=b(\bmod p) -> (g^a)^c=b(\bmod p)
使用bsgs求出特解c，则求出x=g^c
通解是x = g^{ c + k * \frac{\varphi(p)}{gcd(\varphi(p),a)} }
*/
i64 formula1(int a, int b, int p) {
    int g = generator(p);
    int c = bsgs(power(g, a, p), b, p);
    if (c == -1) {
        return -1;
    }
    return power(g, c, p);
}

/*
求解 a^x=b(\bmod p)，gcd(a,p)!=1的情况
通过提取a，来尽量使 p / d'与 a 互质，其中d' = gcd(a^k,p)
如果合法地得到该式：A*a^{x-o}\equiv \frac{b}{d'}(\bmod \frac{p}{d'}) ，其中A =
\frac{a}{d'} 当\frac{a}{d'} = \frac{b}{d'}：此时x有唯一解x； 否则有无穷解x = x'
+ k*H，其中x’是上式用bsgs解出的特解，H是bsgs(a,1,\frac{p}{d'})解出的解
*/

ll ExBsgs(int a, int b, int p) {
    ll A = 1, o = 0;
    {
        ll div;
        while ((div = __gcd(a, p)) != 1) {
            if (A == b) {
                return o;
            }
            if (b % div != 0) {
                return -1;
            }
            b /= div;
            p /= div;
            A = A * a / div % p;
            o++;
        }
    }
    int phi = p;
    {
        int tmp = p;
        for (int i = 2; i * i <= tmp; i++) {
            if (tmp % i == 0) {
                phi = phi / i * (i - 1);
                while (tmp % i == 0)
                    tmp /= i;
            }
        }
        if (tmp > 1) {
            phi = phi / tmp * (tmp - 1);
        }
    }
    int X = bsgs(a, b * power(A, phi - 1, p) % p, p);
    // X是特解
    int H = bsgs(a, 1, p);  // H是最小间距，也即a的阶
    return X == -1 ? -1 : X + o;
}
