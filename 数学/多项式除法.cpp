void PolyInv(int deg,vector<int> &f,vector<int> &g)
{
    if(deg==1) {g[0] = qp(f[0],mod-2);return ;}
    PolyInv((deg+1)>>1,f,g);
    int lim = 1;
    while(lim<(2*deg)) lim <<= 1;
    vector<int> h(lim);
    REP(i,0,deg-1) h[i] = f[i];
    ntt(g,lim,1),ntt(h,lim,1);
    REP(i,0,lim-1) g[i] = 1LL * (2LL + mod - 1LL * g[i] * h[i] % mod) % mod * g[i] % mod;
    ntt(g,lim,-1);
    REP(i,deg,lim-1) g[i] = 0;
}

void Get_Q(int n,int m,vector<int> &f,vector<int> &g,vector<int> &Q)//取商
{
    int lim = 1,deg = 2*n - m + 10;
    while(lim<(deg)) lim <<= 1;
    vector<int> fT(lim),gT(lim),_gT(lim);
    REP(i,0,n-1) fT[i] = f[n-1-i];
    REP(i,0,m-1) gT[i] = g[m-1-i];
    PolyInv(n-m+1,gT,_gT);
    ntt(fT,lim,1),ntt(_gT,lim,1);
    REP(i,0,lim-1) fT[i] = 1LL * fT[i] * _gT[i] % mod;
    ntt(fT,lim,-1);
    REP(i,0,n-m) Q[i] = fT[i];
    reverse(Q.begin(),Q.begin()+n-m+1);
}

void PolyModulo(int n,int m,vector<int> &f,vector<int> &g,vector<int> &R)//只关心取模后的多项式。m是模多项式deg+1。R不用提前申请空间。被取模的f的n不需要恰好等于deg-1，众多实验中成立（理论也成立）
{
    if(n<m) return (void)(R = f);
    int lim = 1,deg = 2*n - m + 10;
    while(lim<(deg)) lim <<= 1;
    vector<int> fT(lim),gT(lim),_gT(lim),Q(lim);
    REP(i,0,n-1) fT[i] = f[n-1-i];
    REP(i,0,m-1) gT[i] = g[m-1-i];
    PolyInv(n-m+1,gT,_gT);
    ntt(fT,lim,1),ntt(_gT,lim,1);
    REP(i,0,lim-1) fT[i] = 1LL * fT[i] * _gT[i] % mod;
    ntt(fT,lim,-1);
    REP(i,0,n-m) Q[i] = fT[i];
    reverse(Q.begin(),Q.begin()+n-m+1);//这里的Q之后不改变，如果需要商，直接返回Q即可（或者函数参数那引用Q）

    lim = 1,deg = n + 10;
    while(lim<(deg)) lim <<= 1;
    vector<int> f1 = f,g1 = g,Q1 = Q;
    f1.resize(lim),g1.resize(lim),Q1.resize(lim),R.resize(lim);
    ntt(f1,lim,1),ntt(g1,lim,1),ntt(Q1,lim,1);
    REP(i,0,lim-1) R[i] = (1LL * f1[i] + mod - 1LL * g1[i] * Q1[i] % mod) % mod;
    ntt(R,lim,-1);
}
