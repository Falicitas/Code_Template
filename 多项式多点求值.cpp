namespace mul_Eva//f是多项式，deg = n-1,x[0~m-1]是点。使用时保证m = max(m,n)。
{
    int x[maxn],y[maxn];
    vector<int> f(maxn<<1),h(maxn<<1),g[maxn<<1],_g,g_(maxn<<1);
    void Get_g(int p,int l,int r)
    {
        if(l==r){
            g[p].resize(2);
            g[p][0] = 1,g[p][1] = (mod - x[l]) % mod;
            return ;
        }
        int mid = l + r >> 1;
        Get_g(p<<1,l,mid),Get_g(p<<1|1,mid+1,r);
        int lim = 1,deg = r-l+2;
        while(lim<deg) lim <<= 1;
        g[p<<1].resize(lim),g[p<<1|1].resize(lim),g[p].resize(lim);
        ntt(g[p<<1],lim,1),ntt(g[p<<1|1],lim,1);
        REP(i,0,lim-1) g[p][i] = 1LL * g[p<<1][i] * g[p<<1|1][i] % mod;
        ntt(g[p],lim,-1);//做完以后除了g[1]每一个g都是点值形式
        g[p].resize(deg);
    }
    vector<int> mulT(vector<int> a,vector<int> b,int n)//除去idft之外的卷积转置，需要保证a和b是个数相同的点值，n是保留的项数
    {
        int lim=a.size();
        for(int i=0;i<lim;i++)a[i]=1ll*a[i]*b[i]%mod;
        ntt(a,lim,1);
        return vector<int>(&a[0],&a[n]);//取a[0]-a[n-1]
    }
    void solve(int p,int l,int r,vector<int> h)
    {
        if(l==r){y[l]=h[0];return;}//把y作为存答案的数组
        int mid=(l+r)>>1,lim=1;
        while(lim<(r-l+2))lim<<=1;
        h.resize(lim);
        ntt(h,lim,-1);
        solve(p<<1,l,mid,mulT(g[p<<1|1],h,mid-l+1));
        solve(p<<1|1,mid+1,r,mulT(g[p<<1],h,r-mid));
    }
    void work(int m)
    {
        Get_g(1,0,m-1);
        _g = g[1];
        PolyInv(m,_g,g_);
        int lim = 1;
        while(lim<((m+1)<<1)) lim <<= 1;
        g_.resize(lim),f.resize(lim);
        ntt(g_,lim,1);ntt(f,lim,-1);
        solve(1,0,m-1,mulT(g_,f,m));
    }
}
