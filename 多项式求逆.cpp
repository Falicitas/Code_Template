ll qp(ll base,ll n)
{
    base %= mod;
    ll res = 1;
    while(n){
        if(n&1) (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return res;
}

void PolyInv(int deg,vector<int> &f,vector<int> &g)
{
    if(deg==1) {g[0] = qp(f[0],mod-2);return ;}
    PolyInv((deg+1)>>1,f,g);
    int lim = 1;
    while(lim<(deg<<1)) lim <<= 1;
    vector<int> h(lim);
    REP(i,0,deg-1) h[i] = f[i];
    ntt(g,lim,1),ntt(h,lim,1);
    REP(i,0,lim-1) g[i] = 1LL * (2LL + mod - 1LL * g[i] * h[i] % mod) % mod * g[i] % mod;
    ntt(g,lim,-1);
    REP(i,deg,lim-1) g[i] = 0;
}
