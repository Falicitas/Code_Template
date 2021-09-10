struct ScanLine
{
    double x;
    double upy,dny;
    int st;//1 in, -1 out
    ScanLine(double x0=0,double upy=0,double dny=0,int st=0):upy(upy),dny(dny),st(st){x=x0;}//confrontation to define x(p)
    bool operator<(const ScanLine&rhs) const
    {
        return x < rhs.x;
    }
}S[maxn<<1];

double Y[maxn];
struct segtree{
	int n;
	static const int N = 1e5 + 5;
	struct node{int l,r,v;double len;}e[N<<2];
	#define l(p) e[p].l
	#define r(p) e[p].r
	#define v(p) e[p].v
	#define len(p) e[p].len
	#define ls p<<1
	#define rs p<<1|1
	void up(int p)
	{
	    if(v(p)) len(p) = Y[r(p)+1] - Y[l(p)];
	    else len(p) = len(ls) + len(rs);
	}
	void bld(int p,int l,int r){
		l(p)=l;r(p)=r;
		if(l==r){v(p) = 0,len(p) = 0;return;}//what decide v(p) = 0 is whether initial value is zero.Another initial function is to link p to l and r.
		int mid=l+r>>1;
		bld(ls,l,mid);bld(rs,mid+1,r);
		up(p);
	}
	void init(int _n){n=_n;bld(1,1,n);} //use it, instead of bld.
	void chg(int p,int cl,int cr,int v){
	    if(cl<=l(p)&&r(p)<=cr){
            v(p) += v;
            up(p);
            return ;
	    }
		int mid=l(p)+r(p)>>1;
		if(cl<=mid) chg(ls,cl,cr,v);
		if(cr>mid) chg(rs,cl,cr,v);
		up(p);
	}
}seg;
