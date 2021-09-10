namespace Comb
{
    ll Finv[N+10],fac[N+10],inv[N+10];
    ll qp(ll base,ll n) {
        ll res = 1;
        base%=mod;
        while(n){
            if(n&1) (res *= base) %= mod;
            (base *= base) %= mod;
            n >>= 1;
        }
        return res;
    }
    void init()//n<N
    {
        int n = N;
        inv[1]=1;
        for(int i=2;i<=n;++i)inv[i]=((mod-mod/i)*inv[mod%i])%mod;
        fac[0]=Finv[0]=1;
        for(int i=1;i<=n;++i)fac[i]=fac[i-1]*i%mod,Finv[i]=Finv[i-1]*inv[i]%mod;
    }
    ll C(ll n,ll m)
    {
        if(m<0||m>n)return 0;
        return fac[n]*Finv[n-m]%mod*Finv[m]%mod;
    }
}
