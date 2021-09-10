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
    ll Inv(ll x)//����С����.modΪ����
    {
        return qp(x,mod-2);
    }
}

namespace _INV
{
    int inv[maxn+10],p = mod;
    void init()// p ����Ϊ������p / i Ϊ����.������
    {
        inv[1] = 1;
        for (int i = 2; i <= maxn; ++i) {
            inv[i] = 1LL * (p - p / i) * inv[p % i] % p;
        }
    }
}

namespace __INV//����������n����Ԫ��ǰ����ԭ����������Ϊ��������Ȼ��������ԪΪ0��������0Ҳû����Ԫ
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
        // ��Ȼ����Ҳ������ exgcd ������Ԫ,�Ӹ���ϲ�ö���.
        for (int i = n; i >= 1; --i) sv[i - 1] = 1LL * sv[i] * a[i] % p;
        for (int i = 1; i <= n; ++i) inv[i] = 1LL * sv[i] * s[i - 1] % p;
    }
}
