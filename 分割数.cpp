#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
constexpr int P = 998244353;
vector<i64> GetCutNumbers(int n) {
    vector<i64> p(n + 1);
    int i, j, k, l;
    i64 sum;
    p[0] = 1;
    for (i = 1; i <= n; i++) {
        sum = 0;
        for (j = 1, k = 1, l = 1; j > 0; k++, l = -l) {
            j = i - (3 * k * k - k) / 2;
            if (j >= 0)
                sum += l * p[j];
            j = i - (3 * k * k + k) / 2;
            if (j >= 0)
                sum += l * p[j];
            sum = (sum % P + P) % P;
        }
        p[i] = sum;
    }
}