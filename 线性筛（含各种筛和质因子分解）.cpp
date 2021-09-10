namespace linear_table
{
    bool isp[MAXN+10];
    int phi[MAXN+10];
    int prime[MAXN+10];
    int p;
    void init()
    {
        int N = MAXN;
        phi[1] = 1;
        for(int i = 2; i <= N; i++){
            if(!isp[i]) prime[++p] = i,phi[i] = i-1;
            for(int j = 1; j <= p&&i * prime[j]<=N; j++){
                isp[i * prime[j]] = true;
                if(i % prime[j] == 0){
                    phi[i * prime[j]] = phi[i] * prime[j];
                    break;
                }
                else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}

/*在线筛里的
long long factor[20][2];//0是质因数，1是质因数的个数。
int fatCnt;
int getFactors(long long x)
{
    fatCnt=0;
    long long tmp=x;
    for(int i=1;prime[i]*prime[i]<=tmp;i++){
        factor[fatCnt][1]=0;
        if(tmp%prime[i]==0){
            factor[fatCnt][0]=prime[i];
            while(tmp%prime[i]==0){
                factor[fatCnt][1]++;
                tmp/=prime[i];
            }
            fatCnt++;
        }
    }
    if(tmp!=1){
        factor[fatCnt][0]=tmp;
        factor[fatCnt++][1]=1;
    }
    return fatCnt;
}
*/

namespace Resolve_factor//偷懒版，复杂度O(sqrt n)
{
    long long factor[20][2];//[0]是质因数，[1]是质因数的个数。
    int fatCnt;
    int getFactors(long long x) ///返回不同质因数的总个数
    {
        fatCnt=0;
        long long tmp=x;
        for(int i=2;1LL*i*i<=tmp;i++){
            factor[fatCnt][1]=0;
            if(tmp%i==0){
                factor[fatCnt][0]=i;
                while(tmp%i==0){
                    factor[fatCnt][1]++;
                    tmp/=i;
                }
                fatCnt++;
            }
        }
        if(tmp!=1){
            factor[fatCnt][0]=tmp;
            factor[fatCnt++][1]=1;
        }
        return fatCnt;
    }
    /*//筛约数
    vector<ll> div;
    void dfs(ll tnt,int dep)
    {
        if(dep==fatCnt){
            div.push_back(tnt);
            return ;
        }
        ll tmp = 1;
        REP(i,0,factor[dep][1]){
            dfs(tnt*tmp,dep+1);
            tmp *= factor[dep][0];
        }
    }
    */
}

/*求i约数个数d[i],num[i]为最小质因子个数
void init(int N) {
    d[1] = 1;
    for (int i = 2; i <= N; ++i) {
        if (!isp[i]) isp[i] = 1, prime[++p] = i, d[i] = 2, num[i] = 1;
        for (int j = 1; j <= p && i * prime[j] <= N; ++j) {
            isp[prime[j] * i] = 1;
            if (i % prime[j] == 0) {
                num[i * prime[j]] = num[i] + 1;
                d[i * prime[j]] = d[i] / num[i * prime[j]] * (num[i * prime[j]] + 1);
                break;
            } else {
                num[i * prime[j]] = 1;
                d[i * prime[j]] = d[i] * 2;
            }
        }
    }
}
*/

/*求i约数和f[i],g[i]为最小质因子p的1+p+p^2+...+p^k
void init(N) {
    g[1] = f[1] = 1;
    for (int i = 2; i <= N; ++i) {
        if (!isp[i]) isp[i] = 1, prime[++p] = i, g[i] = i + 1, f[i] = i + 1;
        for (int j = 1; j <= p && i * prime[j] <= N; ++j) {
            isp[prime[j] * i] = 1;
            if (i % p[j] == 0) {
                g[i * prime[j]] = g[i] * prime[j] + 1;
                f[i * prime[j]] = f[i] / g[i] * g[i * prime[j]];
                break;
            } else {
                g[i * prime[j]] = 1 + prime[j];
                f[i * prime[j]] = f[i] * g[i * prime[j]];
            }
        }
    }
}
*/
/*
void init(int N)//求莫比乌斯函数
{
    memset(isp,false,sizeof(isp));
    mu[1] = 1;
    for(int i = 2; i <= N; i++){
        if( !isp[i] ){
            prime[++p] = i;
            mu[i] = -1;
        }
        for(int j = 1; j <= p&&i * prime[j]<=N; j++){
            isp[i * prime[j]] = true;
            if( i % prime[j] == 0){
                phi[i * prime[j]] = phi[i] * prime[j];
                mu[i * prime[j]] = 0;
                break;
            }
            else{
                mu[i * prime[j]] = -mu[i];
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}
*/
