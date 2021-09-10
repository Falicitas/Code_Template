#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000;
int tree[MAXN];
int A[MAXN];
int lowbit(int x)
{
    return x & -x;
}
int query(int l,int r)
{
    int res=0;
    while(l<=r)
    {
        res=max(res,A[r]);
        for(r--;r-lowbit(r)>=l;r-=lowbit(r))
            res=max(res,tree[r]);
    }
    return res;
}
void modify(int x,int v)
{
    tree[x]=A[x]=v;
    for(int i=1;i<lowbit(x);i<<=1)
        tree[x]=max(tree[x],tree[x-i]);
}
int main()
{
    int n,m,q;cin>>m>>q;
    while(m--)
    {
        int a,b;cin>>a>>b;
        modify(a,b);
    }
    while(q--)
    {
        int a,b;cin>>a>>b;
        cout<<query(a,b)<<endl;
    }
}
