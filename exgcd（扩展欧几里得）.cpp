namespace Exgcd
{
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
    bool liEu(ll a, ll b, ll c, ll& x, ll& y)
    {
        ll d = ex_gcd(a, b, x, y);
        if (c % d != 0) return 0;
        ll k = c / d;
        x *= k;//得到一组特解，求最小非负整数，则x = (x % (b / d) + b / d) % (b / d);
        y *= k;
        return 1;
    }
}
