const int N = 1e5 + 5;
int n, root, tot;
struct node
{
	int fa,siz,cnt,val,ch[2];//cnt为同val的个数
}T[N];

void upd(int x)
{
	T[x].siz = T[T[x].ch[0]].siz + T[T[x].ch[1]].siz + T[x].cnt;//子树的加上自己的size
}

void rotate(int x)
{
	int y = T[x].fa,z = T[y].fa,w = (T[y].ch[1] == x);
	if(z) T[z].ch[T[z].ch[1] == y] = x;T[x].fa = z;//x->z
	T[y].ch[w] = T[x].ch[w ^ 1],T[T[x].ch[w ^ 1]].fa = y;//son_x->y
	T[x].ch[w ^ 1] = y,T[y].fa = x;//y->x
	upd(y),upd(x);//旋和被旋的点
}

void splay(int x,int goal)
{
	while(T[x].fa != goal){
		int y = T[x].fa,z = T[y].fa;
		if (z != goal) ((T[y].ch[1] == x) ^ (T[z].ch[1] == y)) ? rotate(x) : rotate(y);
        rotate(x);
	}
	if(!goal) root = x;
}

void find(int x)
{
	int u = root;
	if (!u) return ;
	while (T[u].ch[x>T[u].val] && x != T[u].val) u = T[u].ch[x>T[u].val];
	splay(u,0);//挪至根节点
}

void insert(int x)
{
	int u = root,fa = 0;
	while(u && x != T[u].val) fa = u, u = T[u].ch[x > T[u].val];
	if(u) T[u].cnt++;
	else{
		u = ++tot;
		if(fa) T[fa].ch[x>T[fa].val] = u;
		T[u].fa = fa,T[u].siz = T[u].cnt = 1,T[u].ch[0] = T[u].ch[1] = 0,T[u].val = x;
	}
	splay(u,0);
}

int next_bound(int x, int f)
{
	find(x);
	int u = root;
	if(T[u].val > x && f) return u;//此时把>x的最小点传到了根节点上
	if(T[u].val < x && !f) return u;//此时将<x的最大点传到了根节点上（由于x不存在）
	u = T[u].ch[f];
	while(T[u].ch[f^1]) u = T[u].ch[f^1];
	return u;
}

void erase(int x)
{
	int last = next_bound(x, 0);
	int next = next_bound(x, 1);
	splay(last,0),splay(next,last);
	int del = T[next].ch[0];
	if (T[del].cnt > 1) T[del].cnt--,splay(del, 0);
	else T[next].ch[0] = 0;
}

int kth(int x)
{
	int u = root;
	if (T[u].siz < x) return 0;
	while(233){
		int y = T[u].ch[0];
		if (x > T[y].siz + T[u].cnt) x -= T[y].siz + T[u].cnt,u = T[u].ch[1];
		else if (T[y].siz >= x) u = y;
		else return T[u].val;
	}
}

//初始插入inf,-inf避免处理边界情况
