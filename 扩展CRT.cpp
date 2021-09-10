namespace ExCRT
{
    __int128 ex_gcd(__int128 a, __int128 b, __int128& x, __int128& y)
    {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        __int128 d = ex_gcd(b, a % b, x, y);
        __int128 temp = x;
        x = y;
        y = temp - a / b * y;
        return d;
    }
    bool liEu(__int128 a, __int128 b, __int128 c, __int128& x, __int128& y)
    {
        __int128 d = ex_gcd(a, b, x, y);
        if (c % d != 0) return 0;
        __int128 k = c / d;
        x *= k;//得到一组特解，求最小非负整数，则$x = (x % (b / d) + b / d) % (b / d)$
        y *= k;
        return 1;
    }
    const int maxn = 1e5 + 5;
    __int128 a[maxn],n[maxn],N;
    __int128 ex_CRT()
    {
        REP(i,2,N){
            __int128 x,y;
            if(!liEu(n[1],-n[i],a[i]-a[1],x,y)) return -1;
            __int128 lc = n[1] / __gcd(n[1],n[i]) * n[i];
            (a[1] += n[1] * x) %= lc;
            n[1] = lc;
        }
        a[1] = (a[1] % n[1] + n[1]) % n[1];
        return a[1];
    }
}

namespace _ExCRT//没验过，非__int128的模板
{
    const int MAXN = 100010;
    typedef long long ll;
    int n;
    ll a[MAXN], b[MAXN], ans, M, x, y;
    ll exgcd(ll a, ll b, ll &x, ll &y){
        if(!b){ x = 1; y = 0; return a; }
        ll d = exgcd(b, a % b, x, y);
        ll z = x; x = y; y = z - (a / b) * y;
        return d;
    }
    ll Slow_Mul(ll n, ll k, ll mod){
        ll ans = 0;
        while(k){
          if(k & 1) ans = (ans + n) % mod;
          k >>= 1;
          n = (n + n) % mod;
        }
        return ans;
    }
    ll ex_CRT()
    {
        ans = a[1];
        M = b[1];
        for(int i = 2; i <= n; ++i){
           ll B = ((a[i] - ans) % b[i] + b[i]) % b[i];
           ll GCD = exgcd(M, b[i], x, y);
           x = Slow_Mul(x, B / GCD, b[i]);
           ans += M * x;
           M *= b[i] / GCD;
           ans = (ans + M) % M;
        }
        return ans;
    }
}
