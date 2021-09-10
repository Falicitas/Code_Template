
//ʹ��Int���˷����ҽ���IFTʱ��������ʽ��ֵ���
//��Int���Ͷ���ʽf����ʼ����ʽ��ֵgʱʹ��g[i] = f[i].get()��������Ȼ��WA��
//������ԭ����ʽ��ָ�����������������㣬�õ��Ķ���ʽ����Ҫf[i] = f[i].get()

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int mod;
namespace Math {
    int qp(ll base, ll n, const int mod) {
        ll res = 1;
        while(n){
            if(n&1) (res *= base) %= mod;
            (base *= base) %= mod;
            n>>=1;
        }
        return (int)res;
    }
    int inv(int x,const int mod) { return qp(x, mod - 2, mod); }
}

const int mod1 = 998244353, mod2 = 1004535809, mod3 = 469762049, G = 3;
const ll mod_1_2 = 1LL * mod1 * mod2;
const int inv_1 = Math::inv(mod1, mod2), inv_2 = Math::inv(mod_1_2 % mod3, mod3);
struct Int {
    int A, B, C;
    Int():A(0),B(0),C(0) {}
    Int(int __num) : A(__num), B(__num), C(__num) { }
    Int(int __A, int __B, int __C) : A(__A), B(__B), C(__C) { }
    static Int reduce(const Int &x) {
        return Int(x.A + (x.A >> 31 & mod1), x.B + (x.B >> 31 & mod2), x.C + (x.C >> 31 & mod3));
    }
    friend Int operator + (const Int &lhs, const Int &rhs) {
        return reduce(Int(lhs.A + rhs.A - mod1, lhs.B + rhs.B - mod2, lhs.C + rhs.C - mod3));
    }
    friend Int operator - (const Int &lhs, const Int &rhs) {
        return reduce(Int(lhs.A - rhs.A, lhs.B - rhs.B, lhs.C - rhs.C));
    }
    friend Int operator * (const Int &lhs, const Int &rhs) {
        return Int(1LL * lhs.A * rhs.A % mod1, 1LL * lhs.B * rhs.B % mod2, 1LL * lhs.C * rhs.C % mod3);
    }
    int get() {
        ll x = 1LL * (B - A + mod2) % mod2 * inv_1 % mod2 * mod1 + A;
        return (1LL * (C - x % mod3 + mod3) % mod3 * inv_2 % mod3 * (mod_1_2 % mod) % mod + x) % mod;
    }
} ;

#define maxn 131072

namespace Poly {
#define N (maxn << 1)
    int lim, s, rev[N];
    Int Wn[N | 1];
    void init(int n) {//init������DFT��IDFT��nΪ���㳤��
        s = -1, lim = 1; while(lim < n) lim <<= 1, ++s;
        for (int i = 1; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
        const Int t(Math::qp(G, (mod1 - 1) / lim, mod1), Math::qp(G, (mod2 - 1) / lim, mod2), Math::qp(G, (mod3 - 1) / lim, mod3));
        *Wn = Int(1); for (Int *i = Wn; i != Wn + lim; ++i) *(i + 1) = *i * t;
    }
    void ntt(vector<Int> &A, int op = 1) {
        for (int i = 1; i < lim; ++i) if (i < rev[i]) swap(A[i], A[rev[i]]);
        for (int mid = 1; mid < lim; mid <<= 1) {
            int t = lim / mid >> 1;
            for (int i = 0; i < lim; i += mid << 1) {
                for (int j = 0; j < mid; ++j) {
                    Int W = op == 1 ? Wn[t * j] : Wn[lim - t * j];
                    Int X = A[i + j], Y = A[i + j + mid] * W;
                    A[i + j] = X + Y, A[i + j + mid] = X - Y;
                }
            }
        }
        if (op==-1) {
            Int ilim(Math::inv(lim, mod1), Math::inv(lim, mod2), Math::inv(lim, mod3));
            for(int i=0;i<lim;i++) A[i] = A[i] * ilim;
        }
    }
#undef N
}
using Poly::init;
using Poly::ntt;
vector<Int> A, B;

namespace fastIO//֧��int,ll,__int128.ullû�в��Թ�
{
    static char buf[100000],*h=buf,*d=buf;//���濪��ɼ��ٶ���ʱ�䡢������Ŀ���Ŀռ�
    #define gc h==d&&(d=(h=buf)+fread(buf,1,100000,stdin),h==d)?EOF:*h++//������fread�򻻳�getchar
    template<typename T>
    inline void read(T&x)
    {
        int f = 1;x = 0;
        register char c(gc);
        while(c>'9'||c<'0'){
            if(c == '-') f = -1;
            c=gc;
        }
        while(c<='9'&&c>='0')x=(x<<1)+(x<<3)+(c^48),c=gc;
        x *= f;
    }
    template<typename T>
    void output(T x)
    {
        if(x<0){putchar('-');x=~(x-1);}
        static int s[20],top=0;
        while(x){s[++top]=x%10;x/=10;}
        if(!top)s[++top]=0;
        while(top)putchar(s[top--]+'0');
    }
}
using fastIO::read;
using fastIO::output;


int n, m;
int main() {
    read(n),read(m),read(mod);
    n++,m++;
	A.resize(maxn<<1),B.resize(maxn<<1);
	for (int i = 0, x; i < n; ++i) read(x), A[i] = x;
	for (int i = 0, x; i < m; ++i) read(x), B[i] = x;
	Poly::init(n + m);
	Poly::ntt(A), Poly::ntt(B);
	for (int i = 0; i < Poly::lim; ++i) A[i] = A[i] * B[i];
	Poly::ntt(A, -1);
	for (int i = 0; i < n + m - 1; ++i) printf("%d%c", A[i].get(),i == n + m - 2 ? '\n' : ' ');
	return 0;
}
