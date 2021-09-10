const int MAXN=1e6+5;//sqrt(n)
int prime[MAXN+1];//+1
bool Flag[MAXN+1];//0为质数，1为合数
void getPrime()//线筛出sqrt(n)的素数
{
    memset(Flag,0,sizeof Flag);
    for(int i=2;i<=MAXN;i++)
    {
        if(!Flag[i])
            prime[++prime[0]]=i;
        for(int j=1;j<=prime[0]&&prime[j]<=MAXN/i; j++) //maxn/i防爆int
        {
            Flag[prime[j]*i]=1;
            if(i%prime[j]==0)
                break;
        }
    }
}
long long factor[100][2];//0是质因数，1是质因数的个数。数据范围1~n
int fatCnt;
int getFactors(long long x) ///返回不同质因数的总个数。factor范围1~fatcnt-1。1要特判
{
    fatCnt=1;
    long long tmp=x;
    for(int i=1;prime[i]<=tmp/prime[i];i++) //防爆int
    {
        factor[fatCnt][1]=0;
        if(tmp%prime[i]==0)
        {
            factor[fatCnt][0]=prime[i];
            while(tmp%prime[i]==0)
            {
                factor[fatCnt][1]++;
                tmp/=prime[i];
            }
            fatCnt++;
        }
    }
    if(tmp!=1)
    {
        factor[fatCnt][0]=tmp;
        factor[fatCnt++][1]=1;
    }
    return fatCnt;
}
