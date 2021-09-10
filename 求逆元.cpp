namespace INV
{
    ll qp(ll base,ll n)
    {
        ll res = 1;
        while(n){
            if(n&1) (res *= base) %= mod;
            (base *= base) %= mod;
            n >>= 1;
        }
        return res;
    }
    ll Inv(ll x)//费马小定理.mod为质数
    {
        return qp(x,mod-2);
    }
}

namespace _INV
{
    int inv[maxn+10],p = mod;
    void init()// p 必须为质数，p / i 为整除.线性求
    {
        inv[1] = 1;
        for (int i = 2; i <= maxn; ++i) {
            inv[i] = 1LL * (p - p / i) * inv[p % i] % p;
        }
    }
}

namespace __INV//线性求任意n个逆元，前提是原来的数必须为正数！不然整体求逆元为0。。而且0也没有逆元
{
    int a[maxn],s[maxn],sv[maxn],inv[maxn],p = mod;
    ll ex_gcd(ll a, ll b, ll& x, ll& y)
    {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        ll d = ex_gcd(b, a % b, x, y);
        ll temp = x;
        x = y;
        y = temp - a / b * y;
        return d;
    }
    ll get_inv(ll a)
    {
        ll x,y;
        ex_gcd(a,p,x,y);
        return (x % mod + mod) % mod;
    }
    void init()
    {
        s[0] = 1;
        for (int i = 1; i <= n; ++i) s[i] = 1LL * s[i - 1] * a[i] % p;
        sv[n] = get_inv(s[n]);
        // 当然这里也可以用 exgcd 来求逆元,视个人喜好而定.
        for (int i = n; i >= 1; --i) sv[i - 1] = 1LL * sv[i] * a[i] % p;
        for (int i = 1; i <= n; ++i) inv[i] = 1LL * sv[i] * s[i - 1] % p;
    }
}
