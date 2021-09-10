#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace get_G//求一般的原根、、多一步求phi的过程
{
    ll qp(ll base,ll n,ll mod)
    {
        ll res = 1;
        while(n){
            if(n&1) (res *= base) %= mod;
            (base *= base) %= mod;
            n >>= 1;
        }
        return res;
    }

    int generator(int p)
    {
        if(p<2) return -1;
        int phi = p,tmp = p;
        for (int i = 2; i * i <= tmp; ++i){
            if(tmp % i == 0){
                phi = phi / i * (i - 1);
                while(tmp % i == 0) tmp /= i;
            }
        }
        if(tmp > 1) phi = phi / tmp * (tmp - 1);
        int n = phi;
        vector<int> fact;
        for (int i = 2; i * i <= n; ++i){
            if (n % i == 0){
                fact.push_back(i);
                while (n % i == 0) n /= i;
            }
        }
        if (n > 1) fact.push_back(n);
        for (int res = 1; res <= p; ++res){
            if(__gcd(res,p) != 1) continue;
            bool ok = true;
            for (int factor : fact){
                if (qp(res, phi / factor, p) == 1){
                    ok = false;
                    break;
                }
            }
            if (ok) return res;
        }
        return -1;
    }
}

int main()
{
    int T;
    int P;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&P);
        int g = get_G::generator(P);
        printf("%d\n",g);
    }
    return 0;
}
