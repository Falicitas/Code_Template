# FHQ-treap

Treap（笛卡尔树） = BST（二叉搜索树）+ Heap（堆）。一种不需要自旋，靠分裂和合并来尽可能贴近平衡的 DS。

结构的基本还是 BST 树，不过当给每个点随机打上了 rnk 标记，跟据这个 rnk 标记将该树构建成小根堆的结构（即左右两子树的rnk都比根节点的大）。

由于同时满足BST和堆的性质，**Treap的结构是一定的** 。对于一棵树，rnk 最小的当做根节点，此时左右两边的 rnd 都比根节点大。同时左子树所有元素的 val 比根小，右子树所有元素的 val 比根大，那么便将除根节点的节点划分成两部分。每一部分取最小的 rnd 当做对应根节点的左右儿子，故树结构确定。

由于 rnk 随机，故树高期望为 $O(\log n)$​。

给出快速随机函数：

```cpp
int rnd()
{
    static int seed = 233;
    return seed = (int) seed * 482711LL % 2147483647;
}
```

## 分裂

由于 BST 的中序遍历性质（见 splay「二叉树」），每个节点对应的子树可以视作一个区间 $[l,r]$​​​。

关于分裂，见图：![](https://raw.githubusercontent.com/Falicitas/Image-Hosting/main/FHQ-treap1.png)

在如何理解这个区间上，对应着 **两种分裂方式**：

将区间视作 val 值的值域。一般用于处理集合里的数。代码：

```cpp
void split(int now,int k,int &x,int &y){
    if(!now) return (void)(x = y = 0);
    if(tree[now].val<=k) x=now,split(tree[now].rs,k,tree[now].rs,y);
    else y=now,split(tree[now].ls,k,x,tree[now].ls);
    up(now);
}
```

将区间视作顺序排名。一般用于序列。代码：

```cpp
void split(int now,int k,int &x,int &y)//对于空树算是有特判的
{
    if(!now) return (void)(x = y = 0);
    if(T[T[now].ch[0]].siz>=k) y = now,split(T[now].ch[0],k,x,T[now].ch[0]);
    else x = now,split(T[now].ch[1],k-T[T[now].ch[0]].siz-1,T[now].ch[1],y);
    up(now);
}
```

上传的操作跟线段树类似。

如果要分裂区间 $[l,r]$​ ​中的 $[ql,qr]$​​，可以先将 $[l,qr],[qr+1,r]$​​分出来，再分$[l,ql-1],[ql,qr]$​​。

分裂出来的两颗树也是 Treap，即它们的结构也唯一确定。

## 合并

对于要合并的两个树 $x,y$​​​（这里假定 $val_x<val_y$​​​），既可以让 y 接到 x 的右子树，也可以将 x 接到 y 的左子树。但要保证 Treap 的 **堆** 的性质，merge 过程需按 rnk 来确定谁做父节点。

![](https://raw.githubusercontent.com/Falicitas/Image-Hosting/main/FHQ-treap2.png)

代码：

```cpp
int merge(int u,int v)
{
    if(!u||!v) return u|v;//如果有任意一个树为空就返回非空的一棵的根
    if(T[u].rnd<T[v].rnd){//如果u为当前根
        tree[u].rs=merge(T[u].rs,v);//继续合并
        up(u);//上传
        return u;//返回根
    }
    else{//如果v为当前根
        T[v].ls=merge(u,T[v].ls);
        up(v);
        return v;
    }
}
```

## 插入

插入数据时：

如果是按 val 进行排序（对于按排名排序的插入操作，与这没有差别），则将树 split 成 $[l,val],[val+1,r]$​ ​​​两个区间，然后让 val 和左区间合并，再和右区间合并。代码：

```cpp
int newnode(int s)
{
    int u = nw();//这里用了内存池
    T[u].key = rnd(),T[u].fa = 0,T[u].siz = 1;
    //...
    return u;
}

void insert(int s,int k)
{
    split(root,k,r1,r2);
    root = merge(merge(r1,newnode(s)),r2);
}
```

一般来说，合并时要保证两个区间不交叉。但对于插入单个节点（比如 insert 的 $[l,val],[val,val]$​​​），由于节点被一直下放到右子树（直到 rnk 小于剩余节点），就结果而言是没问题的。

自己实现的无旋 treap 无合并相同 val 的节点。由于 merge 和 split 很方便，不需要合并就可以轻松统计同 val 的个数。

## 删除

将 val 值孤立出来，然后合并 val 的左右子树（即不要根节点，相当于去掉了一个值）。代码：

```cpp
void erase(int s)
{
    split(root,s,r1,r3);
    split(r1,s-1,r1,r2);
    root = merge(r1,r3);
    del(r2);
}
```

## 查找

### 查找指定排名的数

根据左子树的大小来判即可。

```cpp
int kth(int k)
{
    int now = root;
    while(233){
        if(T[T[now].ch[0]].siz>=k) now = T[now].ch[0];
        else if(k==T[T[now].ch[0]].siz+1) return now;
        else k -= T[T[now].ch[0]].siz+1,now = T[now].ch[1];
    }
}
```

### 查找某个数/节点的排名

这里需分是按排名分裂还是按权值分裂。具体的：

> 当按权值分裂，很简单，只需要将[l,val-1]的区间分裂出来，统计子树大小即可。
>
> 当按排名分裂，由于插入，删除等操作，不能知道某节点当前的排名。这时则用 **回溯法** 来确定当前节点的排名。

具体回溯法的实现：

```cpp
int findsiz(int now)
{
    if(!root) return 0;
    int res = T[now].siz - T[T[now].ch[1]].siz;
    while(now!=root){
        if(now==T[T[now].fa].ch[1]) res += T[T[now].fa].siz - T[now].siz;
        now = T[now].fa;
    }
    return res;
}
```

<img src="https://raw.githubusercontent.com/Falicitas/Image-Hosting/main/FHQ-treap3.png" style="zoom:67%;" />

结合图片理解，即当当前节点向上回溯时，左拐时根节点及其左子树比当前节点的排名小，则此时统计进答案里。

> 按排名分裂的Treap，实际上不需要存当前节点的排名作为val（由于也维护不了），所以才需要采取回溯法。而对于按val分裂的Treap，则可以分出小于val的树进行大小统计。两者的差别需细致体会。

## 前驱、后驱

仅举 val 分裂的情况（按排名的不难写）：

```cpp
int findpre(int a){
    split(root,a-1,x,y);//分裂为(l,queryval-1)与(queryval,r)
    int tmp=tree[findkth(x,tree[x].siz)].val;//分出来的树的最右边
    root=merge(x,y);
    return tmp;
}

int findaft(int a){
    split(root,a,x,y);//分裂为(l,queryval)与(queryval+1,r)
    int tmp=tree[findkth(y,1)].val;/分出来的树的最左边
    root=merge(x,y);
    return tmp;
}
```

## 完整代码

```cpp
//放一些基本的函数

int rnd() {
    static int seed = 233;
    return seed = (int)seed * 482711LL % 2147483647;
}

int root, pool[maxn], cnt, r1, r2, r3;

struct node {
    int fa, ch[2], siz, key, val;
    void clear() {
        fa = ch[0] = ch[1] = siz = key = 0;
    }
} T[maxn];

void del(int x) {
    T[x].clear(), pool[--cnt] = x;
}
int nw() {
    return pool[cnt++];
}

void init() {
    REP(i, 1, maxn - 1)
    pool[i] = i;
    cnt = 1;
}

void upd(int now) {
    if (!now)
        return;
    T[now].siz = 1;
    if (T[now].fa && T[T[now].fa].ch[0] != now && T[T[now].fa].ch[1] != now)
        T[now].fa = 0;  //在split时可能now节点会作为根节点
    if (T[now].ch[0])
        T[now].siz += T[T[now].ch[0]].siz, T[T[now].ch[0]].fa = now;
    if (T[now].ch[1])
        T[now].siz += T[T[now].ch[1]].siz, T[T[now].ch[1]].fa = now;
}

void dosth(int now, int tag) {
    //对于当前点now的维护值改变
    //now的懒标记进行修改
    //有必要时清空当前点的其它懒标记
}

void down(int now) {
    if (T[now].tag) {
        if (T[now].ch[0])
            dosth(T[now].ch[0], T[now].tag);  //各种操作
        if (T[now].ch[1])
            dosth(T[now].ch[1], T[now].tag);  //各种操作
        T[now].tag = 0;                       //懒标记已下传
    }
}

int newnode(int x) {
    int u = nw();
    T[u].val = x, T[u].key = rnd(), T[u].fa = 0, T[u].siz = 1, T[u].ch[0] = T[u].ch[1] = 0;
    return u;
}

void split(int now, int k, int& x, int& y)  //按排名分裂
{
    if (!now)
        return (void)(x = y = 0);
    if (T[T[now].ch[0]].siz >= k)
        y = now, split(T[now].ch[0], k, x, T[now].ch[0]);
    else
        x = now, split(T[now].ch[1], k - T[T[now].ch[0]].siz - 1, T[now].ch[1], y);
    upd(now);
}

void split(int now, int k, int& x, int& y)  //按值分裂
{
    if (!now)
        return (void)(x = y = 0);
    if (T[now].val <= k)
        x = now, split(T[now].ch[1], k, T[now].ch[1], y);
    else
        y = now, split(T[now].ch[0], k, x, T[now].ch[0]);
    upd(now);
}

int merge(int u, int v)  //u左区间树，v右区间树。调用merge记得给root赋值
{
    if (!u || !v)
        return u | v;
    if (T[u].key < T[v].key) {
        T[u].ch[1] = merge(T[u].ch[1], v);
        upd(u);
        return u;
    } else {
        T[v].ch[0] = merge(u, T[v].ch[0]);
        upd(v);
        return v;
    }
}

int findsiz(int now)  //按排名分裂，回溯找某个节点的排名
{
    if (!root)
        return 0;
    int res = T[now].siz - T[T[now].ch[1]].siz;
    while (now != root) {
        if (now == T[T[now].fa].ch[1])
            res += T[T[now].fa].siz - T[now].siz;
        now = T[now].fa;
    }
    return res;
}

int kth(int k)  //排名第k小的节点
{
    int now = root;
    while (233) {
        if (T[T[now].ch[0]].siz >= k)
            now = T[now].ch[0];
        else if (k == T[T[now].ch[0]].siz + 1)
            return now;
        else
            k -= T[T[now].ch[0]].siz + 1, now = T[now].ch[1];
    }
}

void insert(int x) {
    split(root, x, r1, r2);
    root = merge(merge(r1, newnode(x)), r2);
}

void erase(int x)  //删一个
{
    split(root, x, r1, r3);
    split(r1, x - 1, r1, r2);
    root = merge(merge(r1, merge(T[r2].ch[0], T[r2].ch[1])), r3);
    del(r2);
}

```

## 一些习题

### P2042 [NOI2005]维护数列

一些编程技巧：

将区间修改&区间翻转单独写成一个函数，对完整块、该下放的左区间右区间直接调用函数。

以及建树时用分治来 $O(n)$​ 建树。

### P3586 [POI2015]LOG

关注操作序列：操作 s 次，每次选出 c 个两两不相同的位置将其减1。对于值 >=s 的位置，可以放入 s 个操作序列里。对于值 val<s 的位置则可以全部放入 val 个操作序列中。则可以写出有解的条件：$sum>=(c-t)*s$​，$sum$​ 为序列中 <s 的值的和，$t$​ 为 >=s 的值的个数。写个平衡树维护值，$O(\log n)$​​ 找 <s 的个数即可。

### P4309 [TJOI2013]最长上升子序列

这个题啊，要注意 **插入的数是从1~n顺序插入的** ，即当前插入的数一定是区间最大的数。

离线的做法：

由于后插入的数都比当前的大，若考虑用树状数组取值域前的 max来做 LIS，可以知道后插入的数对当前位置的数的答案统计无影响。故用 rope 先构造出序列，计算出每个数在当前序列的最大值后，做个前缀 max 即可。还想不通，就比如 n=20，当当前 i=10 的时候，把其他数忽略掉，求出 ans[1~10] 对应的 LIS 后，取 max 即是原构造的答案。

在线的做法：

split 左右区间，当前插入的点的 dp 值为左区间的 max{dp}+1。push_up 的时机在于树发生改变后，故其实就是裸的平衡树。