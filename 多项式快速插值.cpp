namespace interpolation//结果是f[1][0~n-1]，
{
    namespace mul_Eva
    {
        vector<int> g[maxn<<1],g_(maxn<<1),h(maxn<<1),G(maxn<<1);//存储点值
        vector<int> mulT(vector<int> a,vector<int> b,int n)//除去idft之外的卷积转置，需要保证a和b是个数相同的点值，n是保留的项数
        {
            int lim=a.size();
            for(int i=0;i<lim;i++)a[i]=1ll*a[i]*b[i]%mod;
            ntt(a,lim,1);
            return vector<int>(&a[0],&a[n]);//取a[0]-a[n-1]
        }
        void solve(int p,int l,int r,vector<int> h)
        {
            if(l==r){G[l]=h[0];return;}//我们把b作为存答案的数组
            int mid=(l+r)>>1,lim=1;
            while(lim<(r-l+2))lim<<=1;
            h.resize(lim);
            ntt(h,lim,-1);
            solve(p<<1,l,mid,mulT(g[p<<1|1],h,mid-l+1));
            solve(p<<1|1,mid+1,r,mulT(g[p<<1],h,r-mid));
        }
        void get_g(int p,int l,int r)
        {
            if(l==r){
                g[p].resize(2);
                g[p][0] = 1,g[p][1] = (mod - x[l]) % mod;
                return ;
            }
            int mid = l + r >> 1;
            get_g(p<<1,l,mid),get_g(p<<1|1,mid+1,r);
            int lim = 1,len = r - l + 2;
            while(lim<len) lim <<= 1;
            g[p<<1].resize(lim),g[p<<1|1].resize(lim),g[p].resize(lim);
            ntt(g[p<<1],lim,1),ntt(g[p<<1|1],lim,1);
            REP(i,0,lim-1) g[p][i] = 1LL * g[p<<1][i] * g[p<<1|1][i] % mod;
            ntt(g[p],lim,-1);//除了g[1]其他为点值
            g[p].resize(len);
        }
        void get_G(int n)
        {
            PolyInv(n,g[1],g_);
            int lim = 1;
            while(lim<(n<<1)) lim <<= 1;
            g_.resize(lim),f_.resize(lim);
            ntt(g_,lim,1);ntt(f_,lim,-1);
            solve(1,0,n-1,mulT(g_,f_,n));
        }
    }

    vector<int> g[maxn<<1],f[maxn<<1];

    void get_g(int p,int l,int r)
    {
        if(l==r){
            g[p].resize(2);
            g[p][0] = (mod - x[l]) % mod,g[p][1] = 1;
            return ;
        }
        int mid = l + r >> 1;
        get_g(p<<1,l,mid),get_g(p<<1|1,mid+1,r);
        int lim = 1,len = r - l + 2;
        while(lim<len) lim <<= 1;
        g[p<<1].resize(lim),g[p<<1|1].resize(lim),g[p].resize(lim);
        ntt(g[p<<1],lim,1),ntt(g[p<<1|1],lim,1);
        REP(i,0,lim-1) g[p][i] = 1LL * g[p<<1][i] * g[p<<1|1][i] % mod;
        ntt(g[p],lim,-1);//除了g[1]其他为点值
        g[p].resize(len);
    }

    void solve(int p,int l,int r)
    {
        if(l==r){
            f[p].resize(1);
            f[p][0] = 1LL * y[l] * qp(mul_Eva::G[l],mod-2) % mod;
            return ;
        }
        int mid = l + r >> 1;
        solve(p<<1,l,mid),solve(p<<1|1,mid+1,r);
        int lim = g[p<<1].size();//g[p<<1]本来开的就是自己两倍空间的lim，所以完全可行
        f[p<<1].resize(lim),f[p<<1|1].resize(lim),g[p<<1].resize(lim),g[p<<1|1].resize(lim),f[p].resize(lim);
        ntt(f[p<<1],lim,1),ntt(f[p<<1|1],lim,1);
        REP(i,0,lim-1) f[p][i] = (1LL * g[p<<1|1][i] * f[p<<1][i] % mod + 1LL * g[p<<1][i] * f[p<<1|1][i] % mod) % mod;
        ntt(f[p],lim,-1);
    }

    void derivative(int deg,vector<int> &f,vector<int> &g)
    {
        REP(i,0,deg-2) g[i] = 1LL * f[i+1] * (i + 1) % mod;
        g[deg-1] = 0;
    }

    void work(int n)
    {
        get_g(1,0,n-1);
        mul_Eva::get_g(1,0,n-1);
        f_ = g[1];
        derivative(n+1,f_,f_);
        mul_Eva::get_G(n);
        solve(1,0,n-1);
    }
}
