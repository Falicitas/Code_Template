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
//#define Debug
#ifdef Debug
#endif // Debug

const int maxn = 1e5 + 5;
namespace NTT
{
    const int mod = 998244353;//998244353,1004535809,469762049,985661441. g = 3
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
    int rev[maxn<<2];
    void change(vector<int> &x,int len)
    {
        int bit = 0;
        while ((1<<bit)<len) bit++;
        REP(i,1,len-1){
            rev[i] = (rev[i>>1] >> 1) | ((i & 1) << (bit - 1));
            if (i<rev[i]) swap(x[i],x[rev[i]]);
        }//前面和FFT一样
    }
    void ntt(vector<int> &x, int lim, int opt)
    {
        change(x,lim);
        for (int m = 2; m <= lim; m <<= 1){
            int k = m >> 1;
            int gn = qp(3, (mod - 1) / m);
            for (int i = 0; i < lim; i += m){
                int g = 1;
                for (int j = 0; j < k; ++j, g = 1ll * g * gn % mod){
                    int tmp = 1ll * x[i + j + k] * g % mod;
                    x[i + j + k] = (x[i + j] - tmp + mod) % mod;
                    x[i + j] = (x[i + j] + tmp) % mod;
                }
            }
        }
        if (opt == -1){
            reverse(x.begin() + 1, x.begin() + lim);
            int inv = qp(lim, mod - 2);
            REP(i,0,lim-1) x[i] = 1ll * x[i] * inv % mod;
        }
    }
}
using NTT::ntt;

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

void PolyInv(int deg,vector<int> &f,vector<int> &g)//蝴蝶变换的rev[maxn<<2],f.resize(n<<2),g.resize(n<<2)
{
    if(deg==1) {g[0] = qp(f[0],mod-2);return ;}
    PolyInv((deg+1)>>1,f,g);
    int lim = 1;
    while(lim<(2*deg-1)) lim <<= 1;
    vector<int> h(lim);
    REP(i,0,deg-1) h[i] = f[i];
    ntt(g,lim,1),ntt(h,lim,1);
    REP(i,0,lim-1) g[i] = 1LL * (2LL + mod - 1LL * g[i] * h[i] % mod) % mod * g[i] % mod;
    ntt(g,lim,-1);
    REP(i,deg,lim-1) g[i] = 0;
}

namespace _INV
{
    int inv[maxn+10],p = mod;
    void init()// p 必须为质数，p / i 为整除.线性求
    {
        inv[1] = 1;
        for (int i = 2; i <= maxn; ++i) {
            inv[i] = 1LL * (p - p / i) * inv[p % i] % p;
        }
    }
}
using _INV::inv;

void derivative(int deg,vector<int> &f,vector<int> &g)
{
    REP(i,0,deg-2) g[i] = 1LL * f[i+1] * (i + 1) % mod;
    g[deg-1] = 0;
}

void integrate(int deg,vector<int> &f,vector<int> &g)
{
    _REP(i,deg-1,1) g[i] = 1LL * f[i-1] * inv[i] % mod;
    g[0] = 0;//c
}

void PolyLn(int deg,vector<int> &f,vector<int> &g)
{
    /* g = ln f = ∫ f' f^-1 dx */
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

void PolyExp(int deg,vector<int> &f,vector<int> &g)
{
    /* g = exp(f) = g_0 (1 - ln g_0 + f) */
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

void Polyex1(int deg,vector<int> &f,int k,vector<int> &g)//deg限制%x^deg，不改变运算结果。这里f[0] = 1
{
    vector<int> h(deg);
    PolyLn(deg,f,h);
    REP(i,0,deg-1) h[i] = 1LL * h[i] * k % mod;
    PolyExp(deg,h,g);
}

void Polyex2(int deg,vector<int> &f,int k,vector<int> &g)//deg限制%x^deg，不改变运算结果。这里f[0] != 1
{
    vector<int> h(deg),f_(deg);
    int id = 0,f_id,inv,base;
    while(!f[id]) id++;//找到第一项不为0的为x^id,然后多项式除f_id，最后exp后再还原回来
    f_id = f[id];
    base = qp(f_id,k),inv = qp(f_id,mod-2);  //这里要模数为素数才可用！！！！！
    REP(i,0,deg-id-1) f_[i] = 1LL * f[i+id] * inv % mod;
    PolyLn(deg,f_,h);
    REP(i,0,deg-1) h[i] = 1LL * h[i] * k % mod;
    PolyExp(deg,h,g);
    _REP(i,deg-1,k*id) g[i] = 1LL * g[i-k*id] * base % mod;
    _REP(i,k*id-1,0) g[i] = 0;
}

void Polyex(int deg,vector<int> &f,int k,vector<int> &g)
{
    if(f[0]==1) Polyex1(deg,f,k,g);
    else Polyex2(deg,f,k,g);
}

vector<int> g(maxn<<2),f(maxn<<2);

int main()
{
    #ifndef ONLINE_JUDGE
    //freopen("in.txt","r",stdin);//cf needn't delete this
    #endif // ONLINE_JUDGE
    clock_t start = clock();
    f[2] = 1,f[3] = 1;
    _INV::init();//别忘了加。。
    Polyex(maxn,f,3,g);
    REP(i,0,10) printf("%d\n",g[i]);
    clock_t ends = clock();
    printf("running time:%Lf\n",(long double)(ends - start) / CLOCKS_PER_SEC);
    return ~~(0-0);
}
