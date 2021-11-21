# floyd判环算法

floyd 判环算法适用于每一个点至多有一个出点的图，此时可以求出从一个起点 S 出发找是否有环，以及环部分与非环部分的长度。

## 原理

在链表头放两个速度不同的指针，p1，p2。假设无环，快指针 p2 会先跑到链尾，否则 p2 会赶上 p1 在环上某点相遇。记相遇点离入环点为 k，链头离入环点为 m，环长为 n。对于 p1 的总路程为 $i = m + a * n + k$​，p2 的总路程为 $2i = m + b * n + k$​。两式相减，得 $i = (b - a) * n$​，即 p1 走过的路程为环长的整数倍。

之后，将快指针 p2 放回链头，速度调制 1，p1 位置速度不变。再次相遇时定在入环点（由于i是环长的整数倍，将 p1 走过的路程掰到环上就看得出了）。

要求环长，只需要在跑多一圈，p2 对于 p1 多跑了一圈。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
/*
设置一个起点S，找这个起点出发的简单有向图（一个点只有一条出边or没有边）是否存在环
复杂度O(n+m)
*/

struct Floyd {
    vector<int> nex;  //没有出度的点默认-1
    int s;
    Floyd(vector<int> nex_, int s_)
        : nex(nex_), s(s_) {
        int t, h;
        t = h = s;
        do {
            t = nex[t];
            h = nex[h];
            if (h != -1) {
                h = nex[h];
            }
        } while (t != h && h != -1);
        if (h != -1) {    //有环
            int len = 0;  //环长
            do {
                t = nex[t];
                len++;
            } while (t != h);
            t = s;  //从起点s开始
            while (t != h) {
                t = nex[t];
                h = nex[h];
            }
            int P = t;  //P是环和链的交点
        }
    }
};
```

