#include<bits/stdc++.h>
using namespace std;
//one rule: keep complete block,down-fresh uncomplete block.
//seg-modify to reserve max val
struct segtree{
	int n;
	static const int N = 1e5 + 5;
	struct node{int l,r,v,lazy;}e[N<<2];
	#define l(p) e[p].l
	#define r(p) e[p].r
	#define v(p) e[p].v
	#define c(p) e[p].lazy
	#define ls p<<1
	#define rs p<<1|1
	#define mid (l(p) + r(p) >> 1)
	void up(int p) {v(p)=max(v(ls),v(rs));}
    void down(int p){
	    if(c(p)){
            v(ls) += c(p);v(rs) += c(p);
            c(ls) += c(p);c(rs) += c(p);
            c(p) = 0;
	    }
	}
	void bld(int p,int l,int r){
		l(p)=l;r(p)=r;
		if(l==r){v(p)=0,c(p) = 0;return;}//what decide v(p) = 0 is whether initial value is zero.Another initial function is to link p to l and r.
		int mid=l+r>>1;
		bld(ls,l,mid);bld(rs,mid+1,r);
		up(p);
	}
	void init(int _n){n=_n;bld(1,1,n);} //use it, instead of bld.
	void chg(int p,int cl,int cr,int v){
	    if(cl<=l(p)&&r(p)<=cr){
            v(p) += v;
            c(p) += v;
            return ;
	    }
	    down(p);
		int mid=l(p)+r(p)>>1;
		if(cl<=mid) chg(ls,cl,cr,v);
		if(cr>mid) chg(rs,cl,cr,v);
		up(p);
	}
	int mx(int p,int ql,int qr){
		if(ql<=l(p)&&r(p)<=qr) return v(p);  //complete block return val(and lazy,lazy don't need to down),or else down the lazy.
		//don't add c(p)! c(p) is to lazy son-sequence, not for this sequence!
		down(p);
		int mid=l(p)+r(p)>>1,res=-inf;//when it takes min,res should be changed to inf
		if(ql<=mid)res=max(res,mx(ls,ql,qr));
		if(qr>mid)res=max(res,mx(rs,ql,qr));
		return res;
	}
}seg;
//complete block can stay lazy because it has formula to cal
//but when we check or we modify an imcomplete block, we should down the lazy for two of son-sequence needs to accurately iterate.
//up is to summary son-sequence's inforation.so every bld or chg should up the information.

/*test

int main()
{
    freopen("in.txt","r",stdin);
    for(int i=1;i<=10;i++) scanf("%d",&a[i]);
    seg.init(10);
    int op,l,r;
    while(scanf("%d%d%d",&op,&l,&r)==3){
        if(op) printf("%d\n",seg.mx(1,l,r));
        else {int v;scanf("%d",&v);seg.chg(1,l,r,v);}
    }
    return 0;
}
*/

struct segtree{
	int n;
	static const int N = 1e5 + 5;
	struct node{int l,r,v,lazy;}e[N<<2];
	#define l(p) e[p].l
	#define r(p) e[p].r
	#define v(p) e[p].v
	#define c(p) e[p].lazy
	#define ls p<<1
	#define rs p<<1|1
	void up(int p) {v(p)=v(ls)+v(rs);}
    void down(int p){
	    if(c(p)){
            v(ls) += c(p);v(rs) += c(p);
            c(ls) += c(p);c(rs) += c(p);
            c(p) = 0;
	    }
	}
	void bld(int p,int l,int r){
		l(p)=l;r(p)=r;
		if(l==r){v(p)=0,c(p) = 0;return;}//what decide v(p) = 0 is whether initial value is zero.Another initial function is to link p to l and r.
		int mid=l+r>>1;
		bld(ls,l,mid);bld(rs,mid+1,r);
		up(p);
	}
	void init(int _n){n=_n;bld(1,1,n);} //use it, instead of bld.
	void chg(int p,int cl,int cr,int v){
	    if(cl<=l(p)&&r(p)<=cr){
            v(p) += v;
            c(p) += v;
            return ;
	    }
	    down(p);
		int mid=l(p)+r(p)>>1;
		if(cl<=mid) chg(ls,cl,cr,v);
		if(cr>mid) chg(rs,cl,cr,v);
		up(p);
	}
	int query(int p,int ql,int qr){
		if(ql<=l(p)&&r(p)<=qr) return v(p);  //complete block return val(and lazy,lazy don't need to down),or else down the lazy.
		//don't add c(p)! c(p) is to lazy son-sequence, not for this sequence!
		down(p);
		int mid=l(p)+r(p)>>1,res=0;//when it takes min,res should be changed to inf
		if(ql<=mid)res+=query(ls,ql,qr);
		if(qr>mid)res+=query(rs,ql,qr);
		return res;
	}
}seg;
