#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int mod = 1e9 + 7;

ll power(ll a, int b, int p = mod) {
    ll res = 1;
    for (; b; b /= 2, a *= a, a %= p) {
        if (b % 2) {
            res *= a;
            res %= p;
        }
    }
    return res;
}

/*
首先，一个正整数 n 有原根的充要条件是 n=2,4,p^e,2p^e，其中，p奇素数，e为正整数。
当保证有原根时，对于原根g，满足对于所有phi的素因子{p_i}，都有g^{\frac{phi}{p_i}}!=
1(\mod p) 所以从小到大枚举g，就得出g是多少。常见的原根都很小
*/

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

int main() {
    int T;
    int P;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &P);
        int g = generator(P);
        printf("%d\n", g);
    }
    return 0;
}
