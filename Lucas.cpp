#include<bits/stdc++.h>
typedef long long ll;
namespace LC
{
    int farc[50010];//根据模数大小开空间
    ll qp(ll base,ll n,ll p)
    {
        ll res = 1;
        while(n){
            if(n&1) (res *= base) %= p;
            (base *= base) %= p;
            n >>= 1;
        }
        return res;
    }
    void init(ll p)//预处理
    {
        farc[0]=1;
        for(ll i=1;i<=p;i++) farc[i]=farc[i-1]*i%p;
    }
    ll C(ll n,ll m,ll p)//组合数
    {
        if(n<m) return 0;
        return farc[n]*qp(farc[m],p-2,p)%p*qp(farc[n-m],p-2,p)%p;
    }
    ll Lucas(ll n,ll m,ll p)//Lucas定理
    {
        if(n<m) return 0;if(!n) return 1;
        return Lucas(n/p,m/p,p)*C(n%p,m%p,p)%p;
    }
}

int main()
{
    ll n,m;
    while(scanf("%lld%lld",&m,&n)==2){
        printf("%lld\n",LC::Lucas(n,m));
    }
    return 0;
}
