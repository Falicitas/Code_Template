//code sourced from kinesis
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;

#define _REP(i,a,b) for(int i = (a) ; i >= (int)(b) ; --i )
#define REP(i,a,b) for(int i = (a) ; i <= (int)(b) ; ++i )
#define UREP(i,u) for(int i = p[(u)] ; i + 1 ; i = edge[i].next)
//iterator: for(int u:x),x is container
#define x(p) (p).first
#define y(p) (p).second
#define pii pair<int,int>
#define mp(x,y) make_pair((x), (y))
#define ll long long
const int inf = 0x3f3f3f3f;
const ll inff = 0x3f3f3f3f3f3f3f3f;
const int mod = 998244353;
#define mem(x,v) memset((x), (v), sizeof (x))
#define ri1(x) scanf("%d", &(x))
#define ri2(x,y) scanf("%d%d", &(x), &(y))
#define ri3(x,y,z) scanf("%d%d%d", &(x), &(y), &(z))
#define ri4(a,b,c,d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
#define pi1(a) printf("%d\n", (a))
#define pi2(a,b) printf("%d%d\n", (a), (b))
//#define Debug
#ifdef Debug
#endif // debug

const int maxn = 1e5 + 5;
int qp(ll base,ll n)//快速幂
{
    ll res = 1;
    while(n){
        if(n&1) (res *= base) %= mod;
        (base *= base) %= mod;
        n>>=1;
    }
    return (int)res;
}

int rev[maxn];

void change(vector<int>&x,int len)
{
    int bit=0;
    while ((1<<bit)<len) bit++;
    REP(i,0,len-1){
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
        if (i<rev[i])
            swap(x[i],x[rev[i]]);
    }//前面和FFT一样
}

void ntt(vector<int>&x, int lim, int opt)
{
    int i, j, k, m, gn, g, tmp;
    change(x,lim);
    for (m = 2; m <= lim; m <<= 1){
        k = m >> 1;
        gn = qp(3, (mod - 1) / m);
        for (i = 0; i < lim; i += m){
            g = 1;
            for (j = 0; j < k; ++j, g = 1ll * g * gn % mod){
                tmp = 1ll * x[i + j + k] * g % mod;
                x[i + j + k] = (x[i + j] - tmp + mod) % mod;
                x[i + j] = (x[i + j] + tmp) % mod;
            }
        }
    }
    if (opt == -1){
        reverse(x.begin() + 1, x.begin() + lim);
        int inv = qp(lim, mod - 2);
        for (i = 0; i < lim; ++i)
            x[i] = 1ll * x[i] * inv % mod;
    }
}

#define REP(i,a,b) for(int i = (a) ; i <= (int)(b) ; ++i )

ll Finv[maxn],fac[maxn],inv[maxn];

void init(int n)//n<N
{
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

vector<int> G[maxn];

struct node
{
    int i;
    node(int i=0):i(i){}
    bool operator<(const node&rhs) const
    {
        return G[i].size() > G[rhs.i].size();
    }
};

priority_queue<node> pq;
int n;

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);//cf needn't delete this
    #endif // ONLINE_JUDGE
    ri1(n);
    REP(i,1,maxn-5) G[i].resize(0);
    int tnt = 0;
    REP(i,1,n){
        REP(j,0,n) G[i].push_back(1);
    }
    REP(i,2,n){
        int len = 1;
        while(len<G[1].size()+G[i].size()) len <<= 1;
        while(G[1].size()<len) G[1].push_back(0);
        while(G[i].size()<len) G[i].push_back(0);
        ntt(G[1],len,1);
        ntt(G[i],len,1);
        REP(j,0,len-1) G[1][j] = 1LL * G[1][j] * G[i][j] % mod;
        ntt(G[1],len,-1);
        for(int i=0;i<G[1].size();i++) printf("%d ",G[1][i]);
        printf("\n");
    }
    //for(int i=0;i<G[1].size();i++) printf("%d ",G[1][i]);
    return 0;
}
