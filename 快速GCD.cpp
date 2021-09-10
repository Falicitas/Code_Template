namespace Q_GCD
{
    const int M = 1e6+5,T = 1e3+5;//M为gcd对象的值域上界
    int pre[T+5][T+5],prime[M+5],p,fac[M+5][3];
    bool isp[M+5];
    void init()
    {
        fac[1][0] = fac[1][1] = fac[1][2] = 1;
        for(int i = 2; i <= M; i++){
            if(!isp[i]) prime[++p] = i;
            for(int j = 1; j <= p&&i * prime[j] <= N; j++){
                int now = i * prime[j];
                isp[now] = true;
                fac[now][0] = fac[i][0] * prime[j];
                fac[now][1] = fac[i][1];
                fac[now][2] = fac[i][2];
                if(fac[now][0]>fac[now][1]) swap(fac[now][0],fac[now][1]);
                if(fac[now][1]>fac[now][2]) swap(fac[now][1],fac[now][2]);
                if(i % prime[j] == 0) break;
            }
        }
        REP(i,0,T) pre[i][0] = pre[0][i] = i;
        REP(i,1,T) REP(j,1,i) pre[i][j] = pre[j][i] = pre[j][i%j];
    }
    int gcd(int a,int b)
    {
        int ans = 1;
        REP(i,0,2){
            int div = (fac[a][i] > T ? (b % fac[a][i] == 0 ? fac[a][i] : 1) : pre[fac[a][i][b%fac[a][i]]);//fac[a][i]铁定为素数
            ans *= div;
            b /= div;
        }
        return ans;
    }
}
