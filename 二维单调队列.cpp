struct node {int id,val;node(int id=0,int val=0):id(id),val(val){}};
namespace Deque_2D//处理静态矩阵的矩阵最值
{
    int a[maxn][maxn],s[maxn][maxn],n,m,k;//k * k矩阵
    deque<node> deq;
    void init()
    {
        memset(s,0,sizeof s);
    }
    void act()
    {
        REP(i,1,n){
            deq.clear();
            REP(j,1,k-1){
                while(!deq.empty()&&deq.back().val<=a[i][j]) deq.pop_back();//举个例子，求静态矩阵最大值
                deq.push_back(node(j,a[i][j]));
            }
            REP(j,k,m){
                while(!deq.empty()&&deq.front().id<=j-k) deq.pop_front();
                while(!deq.empty()&&deq.back().val<=a[i][j]) deq.pop_back();
                deq.push_back(node(j,a[i][j]));
                s[i][j] = deq.front().val;
            }
        }
        REP(i,1,n) REP(j,k,m) a[i][j] = s[i][j];
        REP(j,k,m){
            deq.clear();
            REP(i,1,k-1){
                while(!deq.empty()&&deq.back().val<=a[i][j]) deq.pop_back();//举个例子，求静态矩阵最大值
                deq.push_back(node(i,a[i][j]));
            }
            REP(i,k,n){
                while(!deq.empty()&&deq.front().id<=i-k) deq.pop_front();
                while(!deq.empty()&&deq.back().val<=a[i][j]) deq.pop_back();
                deq.push_back(node(i,a[i][j]));
                s[i][j] = deq.front().val;
            }
        }
    }
}
