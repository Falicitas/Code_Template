/*
1.可选步数为1-m的连续整数，直接取模即可，SG(x) = x % (m+1);//巴什博弈
2.可选步数为任意步，SG(x) = x;//Nim游戏
3.可选步数为一系列不连续的数，用GetSG(计算) */
int SG[maxn],in[maxn];
void Get_SG(int *Array)//array[0]为可选数字，array[1~m]要从小到大排序
{
    int n = maxn - 1;
    memset(SG, 0, sizeof(SG));
    REP(i,0,n){
        for(int j = 1; j <= Array[0]; ++j){
            if(i < Array[j]) break;
            in[SG[i - Array[j]]] = i+1;//这样就不用清空in了
        }
        for(int j = 0; j <= n; ++j){
            if(in[j]!=i+1){
                SG[i] = j;
                break;
            }
        }
    }
}
