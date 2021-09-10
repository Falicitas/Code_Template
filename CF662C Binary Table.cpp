//code sourced from kinesis
#include<bits/stdc++.h>
using namespace std;

#define _REP(i,a,b) for(int i = (a) ; i >= (int)(b) ; --i )
#define REP(i,a,b) for(int i = (a) ; i <= (int)(b) ; ++i )
#define UREP(i,u) for(int i = p[(u)] ; i + 1 ; i = edge[i].next)
//iterator: for(int u:x),x is container
#define x(p) (p).first
#define y(p) (p).second
#define pii pair<int,int>
#define mp(x,y) make_pair((x), (y))
#define sign(x) (fabs(x) < eps ? 0 : ((x) > 0 ? 1 : -1))
#define ll long long
#define L7 __int128//1<<7 bit
#define ull unsigned long long
const int inf = 0x3f3f3f3f;
const ll inff = 0x3f3f3f3f3f3f3f3f;
const int mod = 998244353;
const double eps = 1e-9;
#define ri1(x) scanf("%d", &(x))
#define ri2(x,y) scanf("%d%d", &(x), &(y))
#define ri3(x,y,z) scanf("%d%d%d", &(x), &(y), &(z))
#define ri4(a,b,c,d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
//sort(f,f+n,[](int x,int y){return g[x] < g[y];});绑定sort
//#define Debug
#ifdef Debug
#endif // Debug

const int maxn = 1<<21;

ll f[maxn],g[maxn];
int a[21][100005],st[100005],lim;

void XOR(ll *f, int opt)//求逆时x = 1 / 2.不在模系时需要直接修改成 / 2
{   for (int o = 2, k = 1; o <= lim; o <<= 1, k <<= 1)
        for (int i = 0; i < lim; i += o)
            for (int j = 0; j < k; j++)
                (f[i+j] += f[i+j+k]),
                f[i+j+k] = (f[i+j] - f[i+j+k] - f[i+j+k]),
                //f[i+j] = 1LL * f[i+j] * opt % mod, f[i+j+k] = 1LL * f[i+j+k] * opt % mod;
                f[i+j] = 1LL * f[i+j] / (opt == 1 ? 1 : 2), f[i+j+k] = 1LL * f[i+j+k] / (opt == 1 ? 1 : 2);
}

char s[100005];

int main()
{
    #ifndef ONLINE_JUDGE
    //freopen("in.txt","r",stdin);//cf,atcoder,nowcoder needn't delete this
    #endif // ONLINE_JUDGE
    int n,m;ri2(n,m);
    lim = 1 << n;
    REP(i,1,n){
        scanf("%s",s+1);
        REP(j,1,m) a[i][j] = s[j] - '0';
    }
    REP(i,1,lim-1) f[i] = f[i>>1] + (i & 1);
    REP(i,0,lim-1) f[i] = min(f[i],n-f[i]);
    REP(j,1,m){
        st[j] = 0;
        REP(i,1,n){
            st[j] = st[j] * 2 + a[i][j];
        }
        g[st[j]]++;
    }
    XOR(f,1),XOR(g,1);
    REP(i,0,lim-1) f[i] = f[i] * g[i];
    XOR(f,-1);
    ll ans = inf;
    REP(i,0,lim-1) ans = min(ans,f[i]);
    printf("%lld\n",ans);
    return 0;
}

