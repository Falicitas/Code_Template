#include<bits/stdc++.h>
using namespace std;
struct node{int l,r,v,id;};
struct segtree{
	int n;
	static const int N = 1e5 + 5;
	const int inf = 0x3f3f3f3f;
	node e[N<<2];
	#define l(p) e[p].l
	#define r(p) e[p].r
	#define v(p) e[p].v
	#define id(p) e[p].id
	void up(int p) {
	    if(v(p<<1)<=v(p<<1|1)) v(p) = v(p<<1),id(p) = id(p<<1);
        else v(p) = v(p<<1|1),id(p) = id(p<<1|1);
    }
	void bld(int p,int l,int r){
		l(p)=l;r(p)=r;
		if(l==r){v(p)=inf,id(p)=l;return;}//it might should be changed.
		int mid=l+r>>1;
		bld(p<<1,l,mid);bld(p<<1|1,mid+1,r);
		up(p);
	}
	void init(int _n){n=_n;bld(1,1,n);} //use it, instead of bld.
	void chg(int p,int x,int v){
		if(l(p)==r(p)){v(p)=v,id(p)=l(p);return;}
		int mid=l(p)+r(p)>>1;
		chg(p<<1|(x>mid),x,v);
		up(p);
	}
	node query(int p,int ql,int qr){
		if(ql<=l(p)&&r(p)<=qr)return e[p];  //complete block return val(and lazy,lazy don't need to down),or else down the lazy.
		int mid=l(p)+r(p)>>1;//when it takes min,res should be changed to inf
		node res = {0,0,inf,0};
		if(ql<=mid){
            res = query(p<<1,ql,qr);
		}
		if(qr>mid){
		    node q = query(p<<1|1,ql,qr);
            if(res.v>q.v){
                res = q;
            }
		}
		return res;
	}
}seg;

//seg-modify query id: compare it with seg-modify segtree.

/*test
int main()
{
    freopen("in.txt","r",stdin);
    for(int i=1;i<=10;i++) scanf("%d",&a[i]);
    seg.init(10);
    int op,l,r;
    while(scanf("%d%d%d",&op,&l,&r)==3){
        if(op) printf("%d %d\n",seg.query(1,l,r).id,seg.query(1,l,r).v);
        else seg.chg(1,l,r);
    }
    return 0;
}
*/
