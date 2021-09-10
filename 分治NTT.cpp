void cdq(vector<int> &f,vector<int> &g,int l,int r)
{
    if(l==r) return ;
    int mid = l + r >> 1;
    cdq(f,g,l,mid);
    int lim = 1,deg = r - l + 1;
    while(lim<(deg<<1)) lim <<= 1;
    vector<int> g1(lim),g2(lim);
    for(int i=l,j=0;i<=r;i++,j++) g1[j] = (i <= mid ? f[i] : 0),g2[j] = g[j];
    ntt(g1,lim,1),ntt(g2,lim,1);
    REP(i,0,lim-1) g1[i] = 1LL * g1[i] * g2[i] % mod;
    ntt(g1,lim,-1);
    REP(i,mid+1,r) (f[i] += g1[i-l]) %= mod;
    cdq(f,g,mid+1,r);
}
