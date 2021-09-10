namespace Du_table//g函数既要好与f卷，其前缀和也要好求，不需要预处理的那种
{
    using linear_table::S;//在线性筛里的前缀和
    map<ll,ll> S_map;
    ll cal(ll n)
    {
        if(n<=MAXN) return S[n];
        if(S_map.count(n)) return S_map[n];
        ll res = dirichlet(n);//dirichlet(n)为sum{i=1~n}(f*g)(i)的值
        for(ll i=2,j;(n / i);i = j + 1){
            j = n / (n / i);
            res -= (g(j) - g(i-1)) * cal(n / i);//g(i)为g的前缀和
        }
        return S_map[n] = res;
    }
}
