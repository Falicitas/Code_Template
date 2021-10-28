#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

namespace Twice_Remainder  //先判断剩余是否为0，为0则有唯一解0。然后判断是否有解；有解的话就一定有两个解，套solve
{
int mod;
i64 I_2;  // 虚数单位的平方
struct complex {
    i64 real, i;
    complex(i64 real = 0, i64 i = 0)
        : real(real), i(i) {}
};
inline bool operator==(complex x, complex y) {
    return x.real == y.real && x.i == y.i;
}
inline complex operator*(complex x, complex y) {
    return complex((x.real * y.real + I_2 * x.i % mod * y.i) % mod, (x.i * y.real + x.real * y.i) % mod);
}
complex qp(complex x, int k) {
    complex res = 1;
    while (k) {
        if (k & 1)
            res = res * x;
        x = x * x;
        k >>= 1;
    }
    return res;
}
bool check_if_residue(int x) {
    return qp(x, (mod - 1) >> 1) == 1;
}  //判断常数项是否有解
void solve(int b, int p, int& x0, int& x1) {
    mod = p;
    i64 a = rand() % mod;
    while (!a || check_if_residue((a * a + mod - b) % mod))
        a = rand() % mod;
    I_2 = (a * a + mod - b) % mod;
    x0 = int(qp(complex(a, 1), (mod + 1) >> 1).real), x1 = mod - x0;
}
}  // namespace Twice_Remainder
