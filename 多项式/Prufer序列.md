# Prufer序列

Prufer序列是一个与**有标号无根树**满足双射关系的序列。即一个有标号无根树唯一对应一个 Prufer 序列 ，而一个 Prufer 序列唯一构造一个有标号无根树。

## 用无根树线性构造Prufer序列

初始先把指针指向编号最小的叶节点。

- 将叶节点 u 从树上删掉。
- 当删掉后，将与 u 相连的点 v 加入 prufer 序列。与其相连的点成为了叶节点，且编号 v<u，则继续删 v，直至与其相连的点 v>u，或者与其相连的不成为叶节点。
- 不断单调往编号大的移指针，直至构造出大小为 n-2 的 prufer 序列。

为什么这样是正确的：考虑删了某叶节点 u，若相邻的比 u 小，且成为了叶节点，那必然是现存的最小的叶节点，必删；若相邻的比 u 大，那么指针移到后面也会考虑它，所以不影响结果。

## 用Prufer序列线性构造无根树

首先，Prufer 序列的性质有：

- 对于剩下来的两个节点，必有一个为 n。
- 节点的度为 prufer 序列里出现的次数 +1。（没出现的节点就说明初始是叶节点）。

```cpp
vector<int> G[N];
vector<int> fa;

void dfs(int v) {
  for(int u:G[v]){
    if (u != fa[v]) fa[u] = v, dfs(u);
  }
}

vector<int> prufer_code()
{
  fa.resize(n+1),fa[n] = 0;
  dfs(n);//保证根不会被当做被删点。间接保证被删的都是除根节点以外的点
  int ptr = 0;
  vector<int> deg(n+1);
  REP(i,1,n){
    deg[i] = G[i].size();
    if(deg[i]==1&&ptr==0) ptr = i;//要跑完循环，否则deg会错
  }
  vector<int> code(n - 1);
  int leaf = ptr;
  REP(i,1,n-2){
    int nxt = fa[leaf];
    code[i] = nxt;
    if(--deg[nxt]==1&&nxt<ptr){
      leaf = nxt;
    }
    else{
      ptr++;
      while(deg[ptr]!=1) ptr++;
      leaf = ptr;
    }
  }
  return code;
}

vector<pair<int, int>> prufer_decode(vector<int> const& code)
{
  int n = code.size() + 2;
  vector<int> deg(n+1, 1);deg[0] = 0;
  for(int i:code) deg[i]++;
  int ptr = 1;
  while (deg[ptr] != 1) ptr++;
  int leaf = ptr;
  vector<pair<int, int>> edges;
  for (int v:code) {
    edges.emplace_back(leaf, v);
    if(--deg[v]==1&&v<ptr){
      leaf = v;
    }
    else{
      ptr++;
      while(deg[ptr]!=1) ptr++;
      leaf = ptr;
    }
  }
  edges.emplace_back(leaf,n);
  return edges;
}
```

## Cayley 公式

对于一个完全图，有标号生成树的个数为 $n^{n-2}$​。

可以用 Prufer 序列来证明：对于长度为 $n-2$ 的任意元素值域为 $[1,n]$ 都能唯一构造一个有标号生成树，所以个数为 $n^{n-2}$。

$F(x)=\sum_{i=1}^n A(a_ix)\prod_{j=1,j\neq i}^nB(a_jx)$

## prufer 求 S 个联通块构成树的方案数

设 S 个联通块，每个联通块的大小为 $a_i$​。那么需要加 $S-1$ 条边，总度数 +2S-2。设每个联通块的度数为 $d_i$。

那么方案数为：
$$
\sum_{\sum d_i = 2*S-2} \prod a_i^{d_i}
$$
由于 prufer 序列中，点的度数等于 prufer 序列出现次数 +1，故有
$$
\sum_{\sum d'_i = S-2} \prod a_i^{d'_i+1},d' = d+1
$$
（以下简记 d = d'）
$$
\sum_{\sum d_i = S-2} \prod a_i^{d_i+1} =  \prod a_i\sum_{\sum d_i = S-2} \prod a_i^{d_i}
$$
后面的式子可以理解为：在 prufer 序列出现一次，方案 * a_i。那么根据 Cayley 公式，$\sum_{\sum d_i = S-2} \prod a_i^{d_i} = (\sum a_i)^{S-2} = n^{S-2}$

所以原式 $=n^{S-2}\prod a_i$​

