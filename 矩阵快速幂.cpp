struct mat {
    ll c[maxn][maxn];
    int n, m;
    mat(){
    	memset(c, 0, sizeof(c));
    	n=m=maxn;
    }
    mat(int a, int b) : n(a), m(b) {
        memset(c, 0, sizeof(c));
    }
    void clear(){
		memset(c, 0, sizeof(c));
    }
    mat operator * (const mat& temp) {
        mat ans(n, temp.m);
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < temp.m; j ++){
                for (int k = 0; k < m; k ++){
					ans.c[i][j] += c[i][k] * temp.c[k][j]%MOD;//能不取模 尽量不取模
                	//这里maxn=2 故不会超过ll 视具体情况 改变取模情况
                	while(ans.c[i][j]>=MOD)ans.c[i][j]-=MOD;
                }
            }
        }
        return ans;
    }
    friend mat operator ^(mat M, ll n)//要加括号，避免被优先级卡
	{
   		mat ans(M.n, M.n);
    	for (int i = 0; i < M.n; i ++)
            ans.c[i][i] = 1;
        while (n > 0) {
            if (n & 1) ans = ans * M;
            M = M * M;
            n >>= 1;
    	}
        return ans;
	}
};
