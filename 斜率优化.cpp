ll getans(int i,int j){return ;}

ll Y(int j){return ;}

ll X(int j){return ;}

//bool slope(int j2,int j1,int i){return 1LL * (Y(j2) - Y(j1)) * (X(j1) - X(i)) >= 1LL * (Y(j1) - Y(i)) * (X(j2) - X(j1));}//下凸包
bool slope(int j2,int j1,int i){return 1.0 * (Y(j2) - Y(j1)) / (X(j2) - X(j1)) + eps > 1.0 * (Y(j1) - Y(i)) / (X(j1) - X(i));}//爆long long时换这个。eps=1e-13
//bool slope(int j2,int j1,int i){return 1.0 * (Y[j2] - Y[j1]) / (X[j2] - X[j1]) + eps > 1.0 * (Y[j1] - Y[i]) / (X[j1] - X[i]);}


void solve1()//状态i的斜率单增且b[j]单增：单调队列可弹队首
{
    static int q[maxn];
    int head = 1,tail = 1;//[)
    q[tail++] = f[0] = 0;
    REP(i,1,n){
        while(head+1<tail && getans(i,q[head]) >= getans(i,q[head+1])){
            head++;
        }
        f[i] = getans(i,q[head]);

        while(head+1<tail && slope(q[tail-2],q[tail-1],i)){
            tail--;
        }
        q[tail++] = i;
    }
}

void solve2()//状态i的斜率不单调但b[j]单增：单调栈凸包上二分
{
    static int stk[maxn];
    int top = 1;
    stk[top++] = f[0] = 0;
    REP(i,1,n){
        int l = 1,r = top-1;
        while(l<r){
            mid = l + (r - l) / 2;
            if(getans(i,stk[mid])>=getans(i,stk[mid+1])) l = mid + 1;
            else r = mid;
        }
        f[i] = getans(i,stk[l]);
        while(top>2 && slope(stk[top-2],stk[top-1],i)){
            top--;
        }
        stk[top++] = i;
    }
}

//cdq分治版本。用单调栈

bool cmp(int i,int j)
{
    return b[i] < b[j];
}

void solve(int i)
{
    int l = 1,r = top - 1;
    if(top<=1) return ;
    while(r - l > 4){
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        if(getans(i,stk[m1])>getans(i,stk[m2]))
            l = m1;
        else
            r = m2;
    }
    while(l<=r) g[i] = min(g[i],getans(i,stk[l++]));
}

void cdq(int l,int r)
{
    static int L[maxn],R[maxn];
    if(l>=r) return ;
    int cl,cr;
    cl = cr = 0;
    int mid = l + (r - l) / 2;
    cdq(l,mid);
    REP(i,l,mid) if(!h[i][1]) L[++cl] = h[i][0];
    REP(i,mid+1,r) if(h[i][1]) R[++cr] = h[i][0];
    top = 1;
    sort(L+1,L+cl+1,cmp),sort(R+1,R+cr+1,cmp);
    for(int i=1,j=1;j<=cr;j++){
        while(i<=cl&&...){//some comparing factors
            if(top>1&&b[stk[top-1]]==b[L[i]]) top--;//stk中的最头元素是top-1. =_=
            while(top>2&&slope(stk[top-2],stk[top-1],L[i])) top--;
            stk[top++] = L[i++];
        }
        solve(R[j]);
    }
    cdq(mid+1,r);
}
