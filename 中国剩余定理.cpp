namespace _CRT
{
    const int maxp = 1e2 + 5;
    ll a[maxp],m[maxp],n;
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
    ll CRT()
    {
        ll M = 1;
        ll ans = 0;
        for(int i = 1; i <= n; i++) {
            M *= m[i];
        }
        for(int i = 1; i <= n; i++) {
            ll x, y;
            ll Mi = M / m[i];
            ex_gcd(Mi, m[i], x, y);//求逆元
            (ans += Mi * x * a[i]) % M;
        }
        ans = (ans % M + M) % M;
        return ans;
    }
}
