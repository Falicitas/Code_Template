const int maxn = 1e3 + 5;
int G[maxn][maxn];
void floyd()
{
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(G[i][k]+G[k][j]<G[i][j]){//���������.���ݱհ����ҵ����֮���������ϵ��Ҳ�����Դ���·
                    G[i][j] = G[i][k] + G[k][j];
                }
            }
        }
    }
}
