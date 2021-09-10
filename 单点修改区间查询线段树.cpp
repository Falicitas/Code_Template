#include<bits/stdc++.h>
using namespace std;

struct segtree{
	int n;
	static const int N = 1e5 + 5;
	struct node{int l,r,v;}e[N<<2];
	#define l(p) e[p].l
	#define r(p) e[p].r
	#define v(p) e[p].v
	#define ls p<<1
	#define rs p<<1|1
	void up(int p) {v(p)=max(v(ls),v(rs));}
	void bld(int p,int l,int r){
		l(p)=l;r(p)=r;
		if(l==r){v(p)=0;return;}//what decide v(p) = 0 is whether initial value is zero.Another initial function is to link p to l and r.
		int mid=l+r>>1;
		bld(ls,l,mid);bld(rs,mid+1,r);
		up(p);
	}
	void init(int _n){n=_n;bld(1,1,n);} //use it, instead of bld.
	void chg(int p,int x,int v){
		if(l(p)==r(p)){v(p)=max(v(p),v);return;}//it sees that you want cover the val or renew the val.In here it renews the val.
		int mid=l(p)+r(p)>>1;
		chg(p<<1|(x>mid),x,v);
		up(p);
	}
	int mx(int p,int ql,int qr){
		if(ql<=l(p)&&r(p)<=qr)return v(p);  //complete block return val(and lazy,lazy don't need to down),or else down the lazy.
		int mid=l(p)+r(p)>>1,res=0;//when it takes min,res should be changed to inf
		if(ql<=mid)res=max(res,mx(ls,ql,qr));
		if(qr>mid)res=max(res,mx(rs,ql,qr));
		return res;
	}
}seg;
