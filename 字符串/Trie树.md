# Trie树

用来维护一个字符串集合，所用空间 = $\text{字符集 }* \sum \text{字符串长度} $​。​​

## 01Trie树

可以将值从高位到将值分解放入 Trie 树中（可增可删）。在 Trie 树上可以 $O(32)$​​ ​找到一个已存过的值。在异或 & 贪心上是个不错的思考方向。

## 01Trie树维护异或和，全体加1

要实现全体加 1 的功能，故从低位向高位构造 Trie。

### 添加&删除

$w[p]$ 记录树上 $p$ 节点被多少个数字所覆盖，$xor[p]$ 记录当前 $p$ 的子树的异或之和。

将数 $x$​​​​ 按低位向高位分解，将 $x$​​​​ 分解完到节点 $p$​​​​，$w[p]++$​​​​，然后从高位向低位回溯（$maintain$​​​​）$x$​​​​ 代表的节点，回溯路过的节点 $w[p']++$​​​​。这样就实现了 $x$​​ ​​对于每一位覆盖的 $+1$​ ​​​贡献。对于异或和，由于下面的是高位，$xor[p] = xor[ch[p][0/1]] << 1 + [0 / 1] * (w[ch[p][0/1]] \& 1)$​​​​。记得每次都清空，由子树更新。

关于 $xor[p]\ \oplus = (xor[ch[p][0/1]] << 1) | ([0 / 1] * (w[ch[p][0/1]] \& 1))$​ 的证明可以用数学归纳法：

假设子树的计算是正确的，子树向高位进 $1$​。当 $ch[p][1]$ ​有被覆盖，且覆盖次数为奇数，则该位为 $1$。证毕。

还有并不是最高位为 $0$ ​就不更新了，用 $MAXH$​ 来限制更新深度，以保证能正常进位。

删除类似。

复杂度为 $O(32)$​。

### 全体+1

观察数 $+1$​​ 后的变化：

> 1000(10)  + 1 = 1001(11) ;
>
> 10011(19) + 1 = 10100(20) ;
>
> 11111(31) + 1 = 100000(32) ;
>
> 10101(21) + 1 = 10110(22) ;
>
> 100000000111111(16447) + 1 = 100000001000000(16448) ;

即低位向高位的第一个 $0$​​​ ​位改为 $1$​​​​，低于该位所有 $1 $​​​​ 都为 $0$​​​​。

具体在树上操作就是将子树交换，对于原来为 $1$​​，现为 $ch[p][0]$​​ 的子树来说，高位还需要修改，就一直迭代下去。

对于实际被更新的 $0$​​​​​​​ ​节点，$ch[p][0],ch[p][1]$​​​​​​​​ 仍会 $swap$​​​​​ ​​​一次，而当前节点为原来的最后一个 $ 1$​​​​ ​​​​所指，由于一直会更新到 $MAXH$​​​​​​​​，故 $ch[p][0]$​​​​​​​​ 代表的前置 $0$​​​​​​​​ 都有值，交换后相当于 $0$​ ​​​​​​​变为 $1$​​​​​​​​。

单次操作为 $O(32)$​。

### 合并Trie

将树 $B$​​ 合并到 $A$​​。对于两棵 Trie 同位置的节点 $a,b$​​：

> 若 $a$​​ 是空节点，则直接返回节点 $b$​​；
>
> 若 $b$​ ​是空节点，则直接返回节点 $a$​​；
>
> 若 $a,b$​ 均不空，合并信息，左节点为新左子树合并的返回的节点，右节点同理。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct trie01 {  //维护数的异或和，从低位往高位维护。贪心的01trie则看情况从高位往低位维护数集
    vector<vector<int>> ch;
    vector<ll> xorv, w;
    int mxH, mxN;
    int M, tot, rt;
    trie01(int mxH_, int mxN_)
        : mxH(mxH_), mxN(mxN_) {  //数的位数，比如x<=1e6,则传21。mxN是插入数的个数
        M = mxH * mxN;
        ch = vector<vector<int>>(M, vector<int>(2));
        w = vector<ll>(M), xorv = w;
        rt = tot = 1;  //初始rt为1
    }
    void maintain(int p) {
        w[p] = xorv[p] = 0;
        if (ch[p][0]) {
            w[p] += w[ch[p][0]];
            xorv[p] ^= xorv[ch[p][0]] << 1;
        }
        if (ch[p][1]) {
            w[p] += w[ch[p][1]];
            xorv[p] ^= (xorv[ch[p][1]] << 1) | (w[ch[p][1]] & 1);
        }
        //w[p] = w[p] & 1;其实不需要，强调01Trie树对存了什么数不在乎，那么w[1]就表示异或和的数有多少个
    }
    void insert(int p, int x, int dep) {
        if (dep >= mxH) {
            w[p]++;
            return;
        }
        if (!ch[p][x & 1]) {
            ch[p][x & 1] = ++tot;
        }
        insert(ch[p][x & 1], x >> 1, dep + 1);
        maintain(p);
    }
    void erase(int p, int x, int dep) {
        if (dep >= mxH) {
            w[p]--;
            return;
        }
        erase(ch[p][x & 1], x >> 1, dep + 1);
        maintain(p);
    }
    void addall(int p)  //全体加1
    {
        swap(ch[p][0], ch[p][1]);
        if (ch[p][0]) {  //原本的ch[p][1]，该进位
            addall(ch[p][0]);
        }
        maintain(p);
    }
    void minusall(int p)  //全体-1
    {
        swap(ch[p][0], ch[p][1]);
        if (ch[p][1]) {  //原本的ch[p][1]，该进位
            minusall(ch[p][1]);
        }
        maintain(p);
    }
    int merge(int a, int b)  //01Trie树的合并，其实所有Trie树均可合并
    {
        if (!a)
            return b;  // 如果 a 没有这个位置上的结点，返回 b
        if (!b)
            return a;  // 如果 b 没有这个位置上的结点，返回 a
        w[a] = w[a] + w[b];
        xorv[a] ^= xorv[b];
        ch[a][0] = merge(ch[a][0], ch[b][0]);
        ch[a][1] = merge(ch[a][1], ch[b][1]);
        return a;
    }
    //rt = merge(a,b);，其中a,b是在同个对象下的两个trie的根
};  // namespace trie01

//单独有个Trie树合并的模板、、
int main() {
    trie01 tr(21, 100000);
    tr.insert(1, 3, 0);
    return 0;
}
```

