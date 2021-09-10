namespace Newton_Interpolation
{
    double x[maxn],y[maxn],table[maxn][maxn],tmp[maxn];
    int n = -1;//初始状态
    void add()
    {
        n++;
        table[n][0] = y[n];
        REP(i,1,n) table[n][i] = (table[n][i-1] - table[n-1][i-1]) / (x[n] - x[n-i]);
    }
    double cal(double x0)
    {
        double res = 0;
        tmp[0] = 1;
        REP(i,1,n) tmp[i] = tmp[i-1] * (x0 - x[i-1]);
        REP(i,0,n) res += table[i][i] * tmp[i];
        return res;
    }
}
