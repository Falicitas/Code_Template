

//具体见同名题目


struct Chairman_Tree
{
    const static int N = 2e5 + 5;
    struct node{int v,ls,rs;}e[N<<5];
    int T[N],cnt = 0;
	#define v(p) e[p].v
	#define ls(p) e[p].ls
	#define rs(p) e[p].rs
	int bld(int l,int r)//这里的l,r是区间
	{
	    int p = ++cnt;
	    v(p) = 0;
	    if(l<r){
            int mid = l + r >> 1;
            ls(p) = bld(l,mid);
            rs(p) = bld(mid+1,r);
	    }
	    return p;
	}
	int update(int pre,int l,int r,int x)
	{
	    int p = ++cnt;
	    e[p] = e[pre],v(p)++;
	    if(l<r){
            int mid = l + r >> 1;
            if(x<=mid) ls(p) = update(ls(pre),l,mid,x);
            else rs(p) = update(rs(pre),mid+1,r,x);
	    }
	    return p;
	}
	int query(int p,int l,int r,int k)
	{
	    if(l >= r) return v(p);//返回id版本在位置k的值
	    int x = v(ls(p)),mid = l + r >> 1;//左区间有多少个小于等于mid的值
	    if(k<=x) return query(ls(s1),ls(s2),l,mid,k);
	    else return query(rs(s1),rs(s2),mid+1,r,k-x);
	}
}seg;
