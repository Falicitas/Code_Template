namespace Gauss
{
    const int maxn = 25;
    double a[maxn][maxn];
    int gauss()
    {
        int now=1,to;
        double t;
        for(int i=1; i<=n; i++)
        {
            for(to=now; to<=n; to++) if(fabs(a[to][i])>eps) break;
            if(to>n) continue;
            if(to!=now) swap(a[to],a[now]);
            t=a[now][i];
            for(int j=1; j<=n+1; j++) a[now][j]/=t;
            for(int j=1; j<=n; j++)
                if(j!=now){
                    t=a[j][i];
                    for(int k=1; k<=n+1; k++) a[j][k]-=t*a[now][k];
                }
            now++;
        }
        for(int i=now; i<=n; i++)
            if(fabs(a[i][n+1])>eps)
                return 0;//1~n的变量系数为0，常数项不为0，则无解
        return now==n+1 ? 1 : 2;//其中now-1就是秩。now-1!=n，则有无穷解
    }
}
