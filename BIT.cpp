#include<bits/stdc++.h>
using namespace std;

template<typename T>
struct BIT
{
    const static int N = 2e5 + 5;
    int n;
    T tr[N];
    void init(int _n)
    {
        n = _n;
        memset(tr,0,sizeof tr);
    }
    void add(int x,T v)
    {
        for(int i=x;i<=n;i+=i&-i) tr[i] += v;
    }
    T sum(T x)
    {
        T sum = 0;
        for(int i=x;i;i-=i&-i) sum += tr[i];
        return sum;
    }
};

struct BIT//区间修改，区间查询
{
    int t1[MAXN], t2[MAXN], n;

    int lowbit(int x) { return x & (-x); }

    void add(int k, int v) {
        int v1 = k * v;
        while (k <= n) {
            t1[k] += v, t2[k] += v1;
            k += lowbit(k);
        }
    }

    int getsum(int *t, int k) {
        int ret = 0;
        while (k) {
            ret += t[k];
            k -= lowbit(k);
        }
        return ret;
    }

    void add1(int l, int r, int v) {
        add(l, v), add(r + 1, -v);  // 将区间加差分为两个前缀加
    }

    long long getsum1(int l, int r) {
        return (r + 1ll) * getsum(t1, r) - 1ll * l * getsum(t1, l - 1) - (getsum(t2, r) - getsum(t2, l - 1));
    }
};
