[toc]

# 垂线法

定义 $a_{i, j}$ 为矩阵中是否有障碍点，若 $a_{i, j}=1$ 则有障碍点，反之则无障碍点； $u p_{i, j}$ 为点 $(i, j)$ 对应的悬线长度，初始化当点 $(i, j)$ 不是障碍点时 $u p_{i, j}=1$。

显然 $u p_{i, j}$ 很容易通过递推求出，也就是说，当点 $(i-1, j)$ 不是障碍点时， $u p_{i, j}=u p_{i-1, j}+1$ 。

关键在于如何求出 **每条悬线能够往左右扩展的最大长度** 。一条悬线往左边能扩展到的最大长度一定是它包含的所有点能往左边扩展到的最大长度的最小值，往右同理。这就是说，可以通过枚举悬线上每个点往左右扩展到的最大长度来求解一条悬线往左右扩展到的最大长度。
令 $l_{i, j}, r_{i, j}$​​ 分别为点 $(i, j)$​​ 往左/右能扩展到第几列，初始化即为当点 $(i, j)$​​ 不是障碍点时 $l_{i, j}=r_{i, j}=j$​​ 。
$l_{i, j}$​​ 需要从左到右推, 即 $j$​​ 从 2 到 $m$ ，而 $r_{i, j}$​​ 需要从右到左推, 即 $j$​​ 从 $m-1$​​ 到 $1 $​​ 。​​​​​​

证明悬线法必然访问了所有极大子矩阵：由于每个极大子矩阵必然存在一个坏点在上边（边界的子矩阵也看作坏点挡住），否则可以继续扩大。那么在该坏点便能引下一条悬线，在悬到底端前都在边缘上（显然）。故证毕。

另外有种 N,M 很大，但坏点（设 S 个）很小的极大子矩阵找法，利用极大化思想在 $O(S^2)$​​​​ 处理完。没遇到题目，故待学。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

struct suspended_line {
    vector<vector<int>> a, l, r, up;  //l_{i,j}表示往左延多远，up表示往上延多远。run时l_{i,j}表示i,j到悬线顶的悬线部分左边可以延多远
    int n, m;
    suspended_line(int n, int m, vector<vector<int>> a)  //a[i][j] = 0表示无障碍
        : n(n), m(m), a(a) {
        l = vector<vector<int>>(n, vector<int>(m));
        r = l, up = l;
    }
    void run() {  //必然访问了所有极大子矩阵
                  /*以下初始化l,r。对于l,r的初始化根据题目而定。以下为求极大子矩阵时的初始化*/
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!a[i][j]) {
                    l[i][j] = r[i][j] = j;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                if (!a[i][j] && !a[i][j - 1]) {
                    l[i][j] = l[i][j - 1];
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = m - 2; j >= 0; --j) {
                if (!a[i][j] && !a[i][j + 1]) {
                    r[i][j] = r[i][j + 1];
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!a[i][j]) {
                    up[i][j] = 1;
                    if (i && !a[i - 1][j]) {
                        up[i][j] += up[i - 1][j];
                    }
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i >= 1 && !a[i][j] && !a[i - 1][j]) {
                    l[i][j] = max(l[i][j], l[i - 1][j]);
                    r[i][j] = min(r[i][j], r[i - 1][j]);
                }
                ans = max(ans, 1ll * up[i][j] * (r[i][j] - l[i][j] + 1));  //极大子矩阵的最大面积
            }
        }
    }
};
int main() {
    return 0;
}
```


## 一些题目

## P4858 [PA2013]Karty

网格图，仅含 _ 和 X ，要求找到一个极大的子矩阵，可以覆盖完所有的 X ，子矩阵可以重复覆盖。

结论：仅需要考虑覆盖完贴边的悬线，即仅考虑所有垂下来长度为 x 的，能往左右延伸最大值的最小值，上下左右做一次即可。

证明：既然贴边线的悬线能够覆盖，那么必然能通过平移子矩阵来将非贴边线的悬线覆盖。证毕。



# 高精度

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct BigInt {  // a = 0时size = 0
    vector<int> a;
    BigInt() { a = {}; }
    BigInt(i64 a0) {
        a = vector<int>();
        while (a0) {
            a.emplace_back(a0 % 10);
            a0 /= 10;
        }
    }
    BigInt(const std::vector<int>& a1)
        : a(a1) {
        while (!a.empty() && !a.back())
            a.pop_back();
    }
    BigInt(const std::string& s0) {
        int n = s0.length();
        a = vector<int>(n);
        for (int i = n - 1; i >= 0; i--) {
            a[n - i - 1] = s0[i] - '0';
        }
        while (!a.empty() && !a.back())
            a.pop_back();
    }
    int size() const { return a.size(); }
    int operator[](int idx) const {
        if (idx < 0 || idx >= size())
            return 0;
        return a[idx];
    }
    i64 get() {  //前提是BigInt在i64范围内
        i64 num = 0;
        for (int i = (int)a.size() - 1; i >= 0; i--) {
            num = num * 10 + a[i];
        }
        return num;
    }
    friend BigInt operator+(const BigInt& a, const BigInt& b) {  //返回BigInt +
        std::vector<int> res(std::max(a.size(), b.size()) + 1);
        for (int i = 0; i < int(res.size()); ++i) {
            res[i] = a[i] + b[i];
            if (res[i] >= 10) {
                res[i + 1]++;
                res[i] -= 10;
            }
        }
        return BigInt(res);
    }
    friend BigInt operator*(const BigInt& a, const BigInt& b) {  //返回BigInt +
        std::vector<int> res(a.size() + b.size() + 1);
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < b.size(); j++) {
                res[i + j] += a[i] * b[j];
            }
        }
        for (int i = 0; i < int(res.size()); ++i) {
            if (res[i] >= 10) {
                res[i + 1] += res[i] / 10;
                res[i] %= 10;
            }
        }
        return BigInt(res);
    }
    BigInt& operator+=(BigInt b) {  // Poly +=
        return (*this) = (*this) + b;
    }

    friend BigInt operator/(const BigInt& x, int y)  //低精除，返回商
    {
        assert(y != 0);
        i64 r = 0;
        vector<int> b(x.size());
        for (int i = (int)x.a.size() - 1; i >= 0; i--) {
            r = r * 10 + x[i];
            if (r >= y) {
                b[i] = r / y;
                r %= y;
            } else {
                b[i] = 0;
            }
        }
        return BigInt(b);
    }
    friend i64 operator%(const BigInt& x, int y)  //低精除，返回余数
    {
        assert(y != 0);
        i64 r = 0;
        for (int i = (int)x.a.size() - 1; i >= 0; i--) {
            r = r * 10 + x[i];
            if (r >= y) {
                r %= y;
            }
        }
        return r;
    }
    friend bool operator<(const BigInt& x,
                          const BigInt& y)  // x>y:1 x==y:0 x<y:-1
    {
        if (x.size() != y.size()) {
            return x.size() < y.size();
        }
        for (int i = (int)x.size() - 1; i >= 0; i--) {
            if (x[i] != y[i]) {
                return x[i] < y[i];
            }
        }
        return 0;
    }
    friend ostream& operator<<(ostream& os, BigInt& cc) {
        for (int i = (int)cc.size() - 1; i >= 0; i--) {
            os << cc[i];
        }
        return os;
    }
};  // namespace BigInt

```

# 运算符优先级

![20180721141349965](https://raw.githubusercontent.com/Falicitas/Image-Hosting/main/20180721141349965.png)

# floyd判环算法

floyd 判环算法适用于每一个点至多有一个出点的图，此时可以求出从一个起点 S 出发找是否有环，以及环部分与非环部分的长度。

对于 $S_0,S_i = f(S_{i-1})$ 的找环，比用 unordered_set 判断是否出现过，时间常数更小，且空间 $O(1)$。

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

# 扫描线

```cpp
#include <bits/stdc++.h>
using namespace std;
/*使用标记永久化，此时sum[1]记录线段覆盖的区间长度*/
struct SegmentTree {
    int n;
    std::vector<int> tag, sum;
    std::vector<int> y;  //线段树点的实际y值
    SegmentTree(int n, vector<int> y_)
        : n(n), tag(4 * n), sum(4 * n), y(y_) {}
    void rangeAdd(int p, int l, int r, int x, int y, int v) {
        if (r <= x || y <= l) {
            return;
        }
        if (x <= l && r <= y) {
            add(p, l, r, v);
            return;
        }
        int m = (l + r) / 2;
        rangeAdd(2 * p, l, m, x, y, v);
        rangeAdd(2 * p + 1, m, r, x, y, v);
        pull(p, l, r);
    }
    void add(int p, int l, int r, int v) {
        tag[p] += v;
        pull(p, l, r);
    }
    void pull(int p, int l, int r) {
        if (tag[p] > 0) {
            sum[p] = y[r] - y[l];
        } else if (r - l == 1) {
            sum[p] = 0;
        } else {
            sum[p] = sum[2 * p] + sum[2 * p + 1];
        }
    }
    void rangeAdd(int l, int r, int v) { rangeAdd(1, 0, n, l, r, v); }
    int find(int p,
             int l,
             int r) {  //如果sum[1]!=n，即不覆盖所有区间，则找一个空闲的区间
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        if (sum[2 * p] < m - l) {
            return find(2 * p, l, m);
        } else {
            return find(2 * p + 1, m, r);
        }
    }
    int find() {
        if (sum[1] == n) {
            return -1;
        }
        return find(1, 0, n);
    }
};

/*求n个矩形的面积并*/
int main() {
    int n;
    cin >> n;
    // y1,y2,xi,1/-1.y离散。扫描线垂直x轴，向x正半轴移动
    using t4 = tuple<int, int, int, int>;
    vector<t4> line;
    vector<int> by;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        line.emplace_back(x1, 1, y1, y2);
        line.emplace_back(x2, -1, y1, y2);
        by.emplace_back(y1);
        by.emplace_back(y2);
    }
    sort(line.begin(), line.end());
    sort(by.begin(), by.end());  //离散的y，插入线段树中
    auto border = unique(by.begin(), by.end());

    SegmentTree tr(2 * n, vector<int>(by.begin(), border));

    using i64 = long long;
    i64 sum = 0;
    for (int i = 0; i < 2 * n - 1; i++) {
        int t1 = lower_bound(by.begin(), border, get<2>(line[i])) - by.begin();
        int t2 = lower_bound(by.begin(), border, get<3>(line[i])) - by.begin();
        tr.rangeAdd(t1, t2, get<1>(line[i]));
        sum += 1ll * tr.sum[1] * (get<0>(line[i + 1]) - get<0>(line[i]));
    }
    cout << sum << "\n";
}
```



