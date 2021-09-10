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

//ll mul(ll a,ll b){return (a*b-(ll)((long double)a*b/mod)*mod+mod)%mod;}//自然溢出快速乘
//光速乘有精度问题，别用。基本支持__int128
