# 基于值域的快速gcd

基于值域预处理的gcd、、复杂度在$O(3)\sim O(1)$左右、、

## 引理1

任何数n均可被分解成三个因子$\{a,b,c\},a\leq b\leq c,$且$c$要不$\leq \sqrt{n}$ ,要不是素数$p$、、

证明：当$c > \sqrt{n}$且$c$是合数，将$c$分解成$\{d,e\},d\leq e$,由于$c> \sqrt{n},ab = \frac{n}{c} \leq \sqrt{n} $,则$n$的三个因子可以表示成：$\{ab,d,e\}$

倘若$e>\sqrt{n}$，且是合数则继续分解，直到对应的第三项$\leq \sqrt{n}$或者不能再分解（此时为素数）

## 引理2

任何数$n$可以由最小质因子$p_0$与$\frac{n}{p_0}$的三个升序因子$\{a,b,c\}$的组合$\{ap_0,b,c\}$所构成，且$ap_0\leq \sqrt{n}\ or\ ap$是素数。

证明：当$n$是质数时显然成立：$[n=p_0]+[\{1,1,1\}] = \{1,1,p_0\}$,对应的$ap_0$为素数、、

当$n$为合数，最小素因子必满足$p_0 \leq \sqrt{n}$。给$n$的最小素因子限定上界$p_0\leq n^{\frac{1}{4}}$,带入$a\leq{\frac{n}{p_0}}^{\frac{1}{3}}$，解得$ap_0\leq n^{\frac{1}{2}}$、、若$p_0 > n^{\frac{1}{4}}$，对$\frac{n}{p_0}$进行讨论：

当$\frac{n}{p_0}$是质数时，三个因子必是$\{1,1,\frac{n}{p}\},$此时$a = 1,ap \leq \sqrt{n}$；

当$\frac{n}{p_0}$的形式为$p_1^2\ or\ p_1*p_2,p_0\leq p_1,p_0\leq p_2,$三个因子为$\{1,p_1,p_1\}\ or\ \{1,p_1,p_2\},a = 1,ap_0\leq \sqrt{n}$；

否则，$\frac{n}{p_0}$三个因子$\{a,b,c\}$必均$\geq p_0$，由于$n = p_0 * a * b * c > n$，此时便不存在$p_0>n^{\frac{1}{4}}$，即不存在当$p_0>n^{\frac{1}{4}}$时，存在$\frac{n}{p_0} = a*b*c$使$n = p_0 * a * b *c$成立的等式。

综上，$p_0\leq n^{\frac{1}{4}}\ or\ p_0>n^{\frac{1}{4}}$都是存在的，但$ap\leq \sqrt{n}\ or\ ap $是素数均成立。证明**分解**的必要性在于$ap$不是素数则必然是合数，若$ap>\sqrt{n}$，则由**分解**递推得来的三个因子不符合定理1，即希望由递推得到的就是正好满足引理1而不需额外操作。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct QuickGCD {
    int M, T;  //M为gcd对象的值域上界
    vector<vector<int>> pre, fac;
    vector<int> prime, isp;
    int p;
    QuickGCD()
        : M(1e6 + 5), T(1e3 + 5) {
        pre = vector<vector<int>>(T + 5, vector<int>(T + 5));
        prime = vector<int>(M + 5);
        fac = vector<vector<int>>(M + 5, vector<int>(3));
        isp = vector<int>(M + 5);

        fac[1][0] = fac[1][1] = fac[1][2] = 1;
        for (int i = 2; i <= M; i++) {
            if (!isp[i])
                prime[++p] = i;
            for (int j = 1; j <= p && i * prime[j] <= M; j++) {
                int now = i * prime[j];
                isp[now] = true;
                fac[now][0] = fac[i][0] * prime[j];
                fac[now][1] = fac[i][1];
                fac[now][2] = fac[i][2];
                if (fac[now][0] > fac[now][1]) {
                    swap(fac[now][0], fac[now][1]);
                }
                if (fac[now][1] > fac[now][2]) {
                    swap(fac[now][1], fac[now][2]);
                }
                if (i % prime[j] == 0) {
                    break;
                }
            }
        }
        for (int i = 0; i <= T; i++) {
            pre[i][0] = pre[0][i] = i;
        }
        for (int i = 1; i <= T; i++) {
            for (int j = 1; j <= i; j++) {
                pre[i][j] = pre[j][i] = pre[j][i % j];
            }
        }
    }
    int gcd(int a, int b) {
        int ans = 1;
        for (int i = 0; i < 3; i++) {
            int div = (fac[a][i] > T ? (b % fac[a][i] == 0 ? fac[a][i] : 1) : pre[fac[a][i]][b % fac[a][i]]);  //fac[a][i]铁定为素数
            ans *= div;
            b /= div;
        }
        return ans;
    }
};  // namespace Q_GCD

```

