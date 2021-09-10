#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int maxn=100000+10;
int n,m,c[maxn<<1],ans[maxn],cnt;

struct Element{
    int a,b,c,w,f;
}e[maxn],t[maxn];

bool cmp(Element x,Element y){
    if(x.a!=y.a) return x.a<y.a;
    if(x.b!=y.b) return x.b<y.b;
    return x.c<y.c;
}

inline int read(){
    register int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return (f==1)?x:-x;
}

void update(int x,int y){
    for(;x<=m;x+=lowbit(x)) c[x]+=y;
}
int sum(int x){
    int ans=0;
    for(;x;x-=lowbit(x)) ans+=c[x];
    return ans;
}

void CDQ(int l,int r){
    int mid=(l+r)>>1;
    if(l==r) return ;
    CDQ(l,mid);CDQ(mid+1,r);
    int p=l,q=mid+1,tot=l;
    while(p<=mid||q<=r){
        if(q>r||(p<=mid&&e[p].b<=e[q].b) update(e[p].c,e[p].w),t[tot++]=e[p++];
        else e[q].f+=sum(e[q].c),t[tot++]=e[q++];
    }
    for(int i=l;i<=mid;i++) update(e[i].c,-e[i].w);
    for(int i=l;i<=r;i++) e[i]=t[i];
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
        e[i].a=read(),e[i].b=read(),e[i].c=read(),e[i].w=1;
    sort(e+1,e+n+1,cmp);
    cnt=1;
    for(int i=2;i<=n;i++){
        if(e[i].a==e[cnt].a&&e[i].b==e[cnt].b&&e[i].c==e[cnt].c) e[cnt].w++;//相同的元素摆一起，避免等级跳跃1,1,1,4...
        else e[++cnt]=e[i];
    }
    CDQ(1,cnt);
    for(int i=1;i<=cnt;i++) ans[e[i].f+e[i].w-1]+=e[i].w;
    for(int i=0;i<n;i++) printf("%d\n",ans[i]);
    return 0;
}
