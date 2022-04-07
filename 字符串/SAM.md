# SAM

一、SAM的性质:

SAM是个状态机。一个起点，若干终点。原串的所有子串和从SAM起点开始的所有路径一一对应，不重不漏。所以终点就是包含后缀的点。 每个点包含若干子串，每个子串都一一对应一条从起点到该点的路径。且这些子串一定是里面最长子串的连续后缀。

SAM问题中经常考虑两种边：

(1) 普通边，类似于Trie。表示在某个状态所表示的所有子串的后面添加一个字符。

(2) Link、Father。表示将某个状态所表示的最短子串的首字母删除。这类边构成一棵树。

二、SAM的构造思路

endpos(s)：子串s所有出现的位置（尾字母下标）集合。SAM中的每个状态都一一对应一个endpos的等价类。

endpos的性质：

(1) 令 s1,s2 为 S 的两个子串 ，不妨设 |s1|≤|s2| （我们用 |s| 表示 s 的长度 ，此处等价于 s1 不长于s2）。则s1 是 s2 的后缀当且仅当 endpos(s1)⊇endpos(s2) ，s1 不是 s2 的后缀当且仅当 endpos(s1)∩endpos(s2)=∅　。
(2) 两个不同子串的endpos，要么有包含关系，要么没有交集。
(3) 两个子串的endpos相同，那么短串为长串的后缀。
(4) 对于一个状态 st ，以及任意的 longest(st) 的后缀 s ，如果 s的长度满足：|shortest(st)|≤|s|≤|longsest(st)| ，那么 s∈substrings(st) 。



SAM结点的具体信息

![后缀自动机1.jpg](https://cdn.acwing.com/media/article/image/2021/07/28/93600_88df7fd2ef-%E5%90%8E%E7%BC%80%E8%87%AA%E5%8A%A8%E6%9C%BA1.jpg)

SAM图的特点

```
SAM图的特点
```

![后缀自动机2.jpg](https://cdn.acwing.com/media/article/image/2021/07/28/93600_8f78490cef-%E5%90%8E%E7%BC%80%E8%87%AA%E5%8A%A8%E6%9C%BA2.jpg)



```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 2000010;
int tot = 1, last = 1;
struct Node {
    int len, fa;  // len表示endp集合中最长子串的长度。fa表示最短子串再去一个首字母到达的endp状态
    int pos;      // pos表示endp集合里所有子串的结束点。有多个结束点取最前。比如xyzxyz,下标从1开始,pos("xyz") = pos("yz") = 3
    int ch[26];
    void init() {
        len = fa = pos = 0;
        memset(ch, 0, sizeof ch);
    }
} node[N];

i64 f[N];                        // f[u]表示节点u的结束点个数，亦即endp集合里所有子串分别出现的次数
int h[N], e[N], ne[N], idx = 0;  //后缀指针的反向边，以1为根节点的树
void init() {                    //注意初始化
    while (tot >= 1) {
        h[tot] = -1;
        f[tot] = 0;
        node[tot--].init();
    }
    tot = last = 1;
    idx = 0;
}
void extend(int c, int i) {
    int p = last, np = last = ++tot;
    f[tot] = 1;
    node[np].len = node[p].len + 1, node[np].pos = i;
    for (; p && !node[p].ch[c]; p = node[p].fa)
        node[p].ch[c] = np;
    if (!p)
        node[np].fa = 1;
    else {
        int q = node[p].ch[c];
        if (node[q].len == node[p].len + 1)
            node[np].fa = q;
        else {
            int nq = ++tot;
            node[nq] = node[q], node[nq].len = node[p].len + 1;
            node[q].fa = node[np].fa = nq;
            for (; p && node[p].ch[c] == q; p = node[p].fa)
                node[p].ch[c] = nq;
        }
    }
}

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u) {  //后缀指针构建的树。u的endp由儿子的并+当前节点是否是原串的前缀
    for (int i = h[u]; ~i; i = ne[i]) {
        dfs(e[i]);
        f[u] += f[e[i]];
    }
}
```

