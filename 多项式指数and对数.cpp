void derivative(int deg,vector<int> &f,vector<int> &g)//g可以等于f
{
    REP(i,0,deg-2) g[i] = 1LL * f[i+1] * (i + 1) % mod;
    g[deg-1] = 0;
}

void integrate(int deg,vector<int> &f,vector<int> &g)//g可以等于f
{
    _REP(i,deg-1,1) g[i] = 1LL * f[i-1] * inv[i] % mod;
    g[0] = 0;//c
}

void PolyLn(int deg,vector<int> &f,vector<int> &g)/* g = ln f = ∫ f' f^-1 dx */
{
    assert(f[0] == 1);
    int lim = 1;
    while(lim<(deg<<1)) lim <<= 1;
    vector<int> f_(lim),_f(lim);//f',f^-1
    derivative(deg,f,f_);
    PolyInv(deg,f,_f);
    ntt(_f,lim,1),ntt(f_,lim,1);
    REP(i,0,lim-1) f_[i] = 1LL * f_[i] * _f[i] % mod;
    ntt(f_,lim,-1);
    integrate(deg,f_,g);
}

void PolyExp(int deg,vector<int> &f,vector<int> &g)/* g = exp(f) = g_0 (1 - ln g_0 + f) */
{
    assert(f[0] == 0);
    if(deg==1) {g[0] = 1;return ;}
    PolyExp((deg+1)>>1,f,g);
    int lim = 1;
    while(lim<(deg<<1)) lim <<= 1;
    vector<int> gLn(lim);
    PolyLn(deg,g,gLn);
    REP(i,0,deg-1) gLn[i] = (1LL * f[i] - gLn[i] + mod) % mod;
    gLn[0] = (gLn[0] + 1) % mod;

    ntt(g,lim,1),ntt(gLn,lim,1);
    REP(i,0,lim-1) g[i] = 1LL * g[i] * gLn[i] % mod;
    ntt(g,lim,-1);
    REP(i,deg,lim-1) g[i] = 0;
}
