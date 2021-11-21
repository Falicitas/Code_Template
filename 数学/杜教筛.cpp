#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

namespace linear_table {
int S[10000007];
}

namespace Du_table  //g函数既要好与f卷，其前缀和也要好求，不需要预处理的那种
{
using linear_table::S;  //在线性筛里的前缀和

map<i64, i64> S_map;

i64 dirichlet(i64 n) {  //dirichlet(n)为sum{i=1~n}(f*g)(i)的值
    return 1;
}

i64 gSum(i64 n) {  //g(i)为g的前缀和
    return 1;
}

i64 cal(i64 n) {
    if (n < 10000007) {
        return S[n];
    }
    if (S_map.count(n)) {
        return S_map[n];
    }
    i64 res = dirichlet(n);
    for (i64 i = 2, j; (n / i); i = j + 1) {
        j = n / (n / i);
        res -= (gSum(j) - gSum(i - 1)) * cal(n / i);
    }
    return S_map[n] = res;
}
}  // namespace Du_table
