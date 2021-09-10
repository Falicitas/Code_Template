typedef pair<double,double> line;//k and b,y = kx + b
line li[maxn+7];//N = 询问次数
int cnt;
double f(line l1,int X){return x(l1)*X+y(l1);}
double inter(line l1,line l2){return (y(l2)-y(l1))/(x(l1)-x(l2));}

struct LC_Segtree//eps = 1e-9
{
    int n;
    static const int N = 1e5 + 5;//N = 线段的最大横坐标
    struct node{bool mark;int id,l,r;}e[N<<2];
    #define l(p) e[p].l
	#define r(p) e[p].r
	#define id(p) e[p].id
	#define mark(p) e[p].mark
	#define ls p<<1
	#define rs p<<1|1
	void bld(int p,int l,int r)
	{
	    l(p) = l,r(p) = r,id(p) = mark(p) = 0;
	    if(l==r) {return ;}
	    int mid = l + r >> 1;
	    bld(ls,l,mid),bld(rs,mid+1,r);
	}
	void init(int _n) {n = _n,bld(1,1,n);}
	void add(int p,int cl,int cr,int x)
	{
	    int mid = l(p) + r(p) >> 1;
	    if(cl <= l(p) && r(p) <= cr){
            if(!mark(p)) {mark(p) = 1,id(p) = x;return ;}
            double ly1 = f(li[x],l(p)),ry1 = f(li[x],r(p)),ly = f(li[id(p)],l(p)),ry = f(li[id(p)],r(p));
            if(ly1<=ly&&ry1<=ry) return ;
            if(ly1>=ly&&ry1>=ry) return void(id(p) = x);
            double in = inter(li[id(p)],li[x]);
            if(ly1>=ly){
                if(in<=mid) add(ls,cl,cr,x);
                else add(rs,cl,cr,id(p)),id(p) = x;
            }
            else{
                if(in>mid) add(rs,cl,cr,x);
                else add(ls,cl,cr,id(p)),id(p) = x;
            }
            return ;
	    }
        if(mid>=cl) add(ls,cl,cr,x);
        if(mid<cr) add(rs,cl,cr,x);
	}
    int lcmp(int X,int x,int y) {return fabs(f(li[x],X) - f(li[y],X)) < eps ? min(x,y) : (f(li[x],X) < f(li[y],X) ? y : x);}//相同取线段最小编号
    int get(int p,int X)
    {
        int res=0;
        if(mark(p)) res = lcmp(X,res,id(p));//有疑问
        if(l(p)==r(p)) return res;
        int mid= l(p) + r(p) >> 1;
        if(mid>=X) res = lcmp(X,res,get(ls,X));
        else res = lcmp(X,res,get(rs,X));
        return res;
    }
}tr;
