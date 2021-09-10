int bsgs(int a,int b,int p)//应该记住的版本
{
    unordered_map<int,int> m;
    int sq = ceil(sqrt(p)),base = 1;
    REP(i,1,sq){
        base = 1LL * base * a % p;
        m[1LL * b * base % p] = i;
    }
    int res = 1;
    REP(i,1,sq){
        res = 1LL * res * base % p;
        if(m.count(res)) return i * sq - m[res];
    }
    return -1;
}


namespace HASH
{
    const int NHASH = 100003;
    int head[NHASH],eid;
    struct node
    {
        int val,B,next;
    }N[NHASH];//注意存储空间
    void init()
    {
        memset(head,-1,sizeof head);
        eid = 0;
    }
    int HASH_num(int num)
    {
        return (num % NHASH + NHASH) % NHASH;
    }
    void HASH_insert(int val,int B)//注意下面搜到存过的值
    {
        int num = HASH_num(val);
        for(int i=head[num];i+1;i=N[i].next){
            if(N[i].val==val){//相同的B取最大，保证之后第一个找到的是最小的
                N[i].B = B;
                return ;
            }
        }
        N[eid].val = val;
        N[eid].B = B;
        N[eid].next = head[num];
        head[num] = eid++;
    }
    int HASH_search(int val)
    {
        int num = HASH_num(val);
        for(int i=head[num];i+1;i=N[i].next){
            if(N[i].val==val) return N[i].B;
        }
        return -1;
    }
}

namespace _BSGS
{
    using namespace HASH;
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
    int BSGS(int a,int b,int p)//令a^X = b的X = A * ceil(sqrt{p}) - B，A,B \in [0,ceil(sqrt{p})]
    {
        a %= p,b %= p;
        if(a==0){
            if(b==0) return 0;//0^0 = 1
            else return -1;
        }
        init();
        int sq = ceil(sqrt(p)+0.5);//保证枚举上界符合要求
        int tmp = 1,base = qp(a,sq,p);
        REP(i,0,sq){
            HASH_insert(1LL * b * tmp % p,i);
            tmp = 1LL * tmp * a % p;
        }
        tmp = base;
        REP(i,1,sq){//从1开始枚举保证最小
            int fin = HASH_search(tmp);
            if(fin != -1) return i * sq - fin;
            tmp = 1LL * base * tmp % p;
        }
        return -1;
    }
}

/*{//求x^a \equiv b (%p),p是素数的公式、、用时将其放入BSGS中
    int generator(int p)
    {
        if(p<2) return -1;
        int phi = p - 1,n = phi;
        vector<int> fact;
        for (int i = 2; i * i <= n; ++i){
            if (n % i == 0){
                fact.push_back(i);
                while (n % i == 0) n /= i;
            }
        }
        if (n > 1) fact.push_back(n);
        for (int res = 1; res <= p; ++res){
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

    int formula1(int a,int b,int p)//求x^a \equiv b (%p),p是素数的公式、、用时将其放入BSGS中
    {
        int g = generator(p);
        int c = BSGS(qp(g,a,p),b,p);
        if(c==-1) return -1;
        return qp(g,c,p);
    }
}*/

namespace _Ex_BSGS
{
    using namespace HASH;
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
    int BSGS(int a,int b,int p)
    {
        init();
        int sq = ceil(sqrt(p)+0.5);
        int tmp = 1,base = qp(a,sq,p);
        REP(i,0,sq){
            HASH_insert(1LL * b * tmp % p,i);
            tmp = 1LL * tmp * a % p;
        }
        tmp = base;
        REP(i,1,sq){
            int fin = HASH_search(tmp);
            if(fin != -1) return i * sq - fin;
            tmp = 1LL * base * tmp % p;
        }
        return -1;
    }
    int Ex_BSGS(int a,int b,int p)
    {
        int div,_a = 1,k = 0;
        while((div = __gcd(a,p)) != 1){
            if(_a == b) return k;
            if(b % div != 0) return -1;
            b /= div;
            p /= div;
            _a = 1LL * _a * a / div % p;
            k++;
        }
        int phi = p,tmp = p;
        for(int i=2;i*i<=tmp;i++){
            if(tmp%i==0){
                phi = phi / i * (i - 1);
                while(tmp%i==0) tmp /= i;
            }
        }
        if(tmp>1) phi = phi / tmp * (tmp - 1);
        int ans = BSGS(a,1LL*b*qp(_a,phi-1,p)%p,p);
        return ans == -1 ? -1 : ans + k;
    }
}

namespace _Ex_BSGS//求通解版本
{
    using namespace HASH;
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
    int BSGS(int a,int b,int p)
    {
        init();
        int sq = ceil(sqrt(p)+0.5);
        int tmp = 1,base = qp(a,sq,p);
        REP(i,0,sq){
            HASH_insert(1LL * b * tmp % p,i);
            tmp = 1LL * tmp * a % p;
        }
        tmp = base;
        REP(i,1,sq){
            int fin = HASH_search(tmp);
            if(fin != -1) return i * sq - fin;
            tmp = 1LL * base * tmp % p;
        }
        return -1;
    }
    pair<ll,ll> Ex_BSGS(int a,int b,int p)//返回特解与最小间距、、
    {
        int div,_a = 1%p,k = 0;
        while((div = __gcd(a,p)) != 1){
            if(_a == b) return mp(k,-1);//唯一解
            if(b % div != 0) return mp(-1,-1);
            b /= div;
            p /= div;
            _a = 1LL * _a * a / div % p;
            k++;
        }
        int phi = p,tmp = p;
        for(int i=2;i*i<=tmp;i++){
            if(tmp%i==0){
                phi = phi / i * (i - 1);
                while(tmp%i==0) tmp /= i;
            }
        }
        if(tmp>1) phi = phi / tmp * (tmp - 1);
        int ans = BSGS(a,1LL*b*qp(_a,phi-1,p)%p,p);
        int H = BSGS(a,1%p,p);
        return ans == -1 ? mp(-1,-1) : mp(ans+k,H);
    }
}
