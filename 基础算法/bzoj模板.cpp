//code sourced from kinesis
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<set>
#include<list>
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

#define _REP(i,a,b) for(int i = (a) ; i >= (int)(b) ; --i )
#define REP(i,a,b) for(int i = (a) ; i <= (int)(b) ; ++i )
#define UREP(i,u) for(int i = p[(u)] ; i + 1 ; i = edge[i].next)
//iterator: for(int u:x),x is container
#define x(p) (p).first
#define y(p) (p).second
#define pii pair<int,int>
#define mp(x,y) make_pair((x), (y))
#define sign(x) (fabsl(x) < eps ? 0 : ((x) > 0 ? 1 : -1))
#define ll long long
#define L7 __int128//1<<7 bit
#define ull unsigned long long
#define ld long double
const int inf = 0x3f3f3f3f;
//const ll inff = 0x3f3f3f3f3f3f3f3f;
const int mod = 998244353;//inv2 = 499122177。奇素数的inv2 = (mod/2) + 1
const double eps = 1e-9;
#define ri1(x) scanf("%d", &(x))
#define ri2(x,y) scanf("%d%d", &(x), &(y))
#define ri3(x,y,z) scanf("%d%d%d", &(x), &(y), &(z))
#define ri4(a,b,c,d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
#define dbg1(x) cerr<<#x<<"="<<(x)<<" "
#define dbg2(x) cerr<<#x<<"="<<(x)<<"\n"
//sort(f,f+n,[](int x,int y){return g[x] < g[y];});绑定sort
//fflush(stdout);交互题仅输出需要清空缓冲区.最后的输出也清空
//#define Debug
#ifdef Debug
#endif // Debug

int main()
{
    #ifndef ONLINE_JUDGE
    //freopen("in.txt","r",stdin);//cf,atcoder,nowcoder needn't delete this
    #endif // ONLINE_JUDGE

    return 0;
}
