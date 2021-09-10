const int MAXN=1e6+5;//sqrt(n)
int prime[MAXN+1];//+1
bool Flag[MAXN+1];//0Ϊ������1Ϊ����
void getPrime()//��ɸ��sqrt(n)������
{
    memset(Flag,0,sizeof Flag);
    for(int i=2;i<=MAXN;i++)
    {
        if(!Flag[i])
            prime[++prime[0]]=i;
        for(int j=1;j<=prime[0]&&prime[j]<=MAXN/i; j++) //maxn/i����int
        {
            Flag[prime[j]*i]=1;
            if(i%prime[j]==0)
                break;
        }
    }
}
long long factor[100][2];//0����������1���������ĸ��������ݷ�Χ1~n
int fatCnt;
int getFactors(long long x) ///���ز�ͬ���������ܸ�����factor��Χ1~fatcnt-1��1Ҫ����
{
    fatCnt=1;
    long long tmp=x;
    for(int i=1;prime[i]<=tmp/prime[i];i++) //����int
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
