[toc]

# 计算几何

叉积：$a \times b$​，大小为 $|a||b|\sin\theta = \det|将向量展开后的矩阵| = x_1y_2 - x_2y_1$​（二维平面向量）。是矢量，遵循右手定则。

点积：$a\cdot b$​，大小为 $|a||b|\cos\theta = x_1y_1 + x_2y_2$​（二维平面向量）。是标量。

正弦定理：角 A 对着的边为 a，$\frac{a}{\sin A} = \frac{b}{\sin B} = \frac{c}{\sin C} = 2R$​​​，R 为外接圆半径。

余弦定理：$a^2 = b^2 + c^2 -2bc\cos A$​​​，其余 2 个边同理。

线的方向：一般指向 y 大的值（y 相同则指向 x 大的）。

快速排斥实验：

两个线段分别对应两个矩形。未通过快速排斥实验指存在 x 或 y 使得两个线段在对应维度的投射没有交集。反之则通过快速排斥实验。未通过快速排斥实验是线段不相交充分不必要条件。

跨立实验：

做两组实验：对于线段 L1 ，是否 L2 的两点处在 L1 代表直线的两端（即叉积乘为负）；对于线段 L2 ，是否 L1 的两点处在L2代表直线的两端（即叉积乘为负）

非严格的线段判交：非严格指一条线段的端点可以在另一条线段上。需要同时使用两个实验进行判定（对于线段共线的情况，跨立实验会通过二不一定相交）

严格的线段判交：严格即两线段仅交于非端点处或不交。

求投影点：求 (p1,p) 在 (p1,p2) 上的投影，等于从 p1 点往 (p1,p2) 的方向位移 $|(p1,p)\cos\theta|$ 的距离。

求一点相对直线的镜像点：求出投影点后，投影点则作为镜像点的中点，根据中点公式求出镜像点。

求点、线段到线段的最短距离：点到线段最短距离：若点在线段的投影在线段上，则最短距离是投影点到点的距离（垂直），否则是线段两个端点到点的最短距离。

求两个直线的交点：利用了相似图形（相似图形，对应边成比例）的原理。建议手动画图。

一维数轴上，$b > a$​，现已知 $[a,b]$​ 中有一点 c，且 $[a,c]:[c,d] = e:f$​，则 $c = \frac{a*f+b*e}{e+f}$​。

极角排序：选取点集中 y 值最小的点（y 值相同则 x 值最小）作为排序点，此时所有的向量都在 y 非负半轴上，直接使用 atan2 或者叉积排序。

Jordan curve theorem：在欧式平面，一个闭曲线 J 将平面划分成两个部分。相同部分里的点对可以画一个弧且弧与 J 相交偶数次（可以不相交）。而不同部分的点画弧必与 J 相交奇数次 。

判断点在多边形内还是外：由上面的定理，选择一个点做射线。一般选择与 x 轴平行指向负无穷的射线。若统计到的为奇数，在多边形内，否则在多边形外。

求任意多边形周长和面积：考虑叉积模的实际含义。将多边形按顺序标为 $p_0,p_1,\dots$​，任选一个辅助点 $O$​（可以试着画在多边形外侧），令 $v_i = p_i - O$​，则 $S = |\sum\limits_{i=0}^{n-1}\frac{1}{2}v_i\times v_{i+1 \bmod n} |$​

求凸包：能把所有点包含进去的，面积最小的闭曲线。把点按 x 为第一关键字，y 为第二关键字，排序。

可以发现凸包上的点的向量按逆时针旋转。

那么从 0 到 n-1 遍历，维护下凸壳是比较容易的。具体的，将点扔入栈内，使用叉积判断三个点的位置关系以维护一个凸壳。

再倒序遍历一次，维护上凸壳。由于最左的点在凸包里（是正确的，感性证明就行），最右的点参与叉积判断，所以上下凸壳能围成封闭图形。

非严格的凸包，点可以在凸包边上。弹栈的条件降低。

判点是否在凸多边形内 $O(\log n)$：

首先判断点与凸多边形的极角关系。若点不在射线 $(p_0,p_1)->(p_0,p_{n-1})$ ，则必不在凸多边形内。

否则在这个射线框出来的区间内进行极角二分，找到对应区间内，再叉积一次判断在凸多边形内还是凸边形外。

求半平面交：对于一条直线 $Ax+By+C\geq 0$​​，即为该直线对应的半平面。默认向量的左侧为该向量对应的半平面。那么半平面交就是所有向量对应的半平面的交，类似于线性规划。

半平面交若存在，一定为凸多边形（画图易证）。于是按极角给线对应的向量排序。

由于半平面靠左，对于同方向的向量，优先让左边的向量靠前，另外的可以直接舍弃（不影响答案）。

先判断队尾的两向量交点，交点在当前向量右侧则弹队尾；再判断队首。

最后让队首的元素检测队尾。

两凸包闵科夫斯基和 $O(n+m)$：定义为图形 A，图形 B，闵可夫斯基和得到的图形 C 满足，$C = \{c|(a+b),a\in A,b\in B\}$。

两凸包的闵可夫斯基和的边恰为两图形的边之和。故使用双指针（凸包的边已按照极角排好序，其中 A[0],B[0] 是最低点），来 $O(n+m)$​ 求闵科夫斯基和。

凸壳也可视作满足性质的凸包（将首尾点相连），比如可以 $O(n+m)$ 合并两下凸壳。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using f64 = long double;
const f64 PI = acosl(-1.0), eps = 1e-11;

inline int sign(f64 a) {
    return a < -eps ? -1 : a > eps;
}

inline int cmp(f64 a, f64 b) {  //精度比较函数
    return sign(a - b);
}

struct P {  //点
    f64 x, y;
    P() {}
    P(f64 _x, f64 _y)
        : x(_x), y(_y) {}
    P operator+(P p) { return P(x + p.x, y + p.y); }
    P operator-(P p) { return P(x - p.x, y - p.y); }
    P operator*(f64 d) { return P(x * d, y * d); }
    P operator/(f64 d) { return P(x / d, y / d); }
    bool operator<(P p) const {
        int c = cmp(x, p.x);
        if (c)
            return c == -1;
        return cmp(y, p.y) == -1;
    }
    bool same(P p) { return sign(x - p.x) == 0 && sign(y - p.y) == 0; }  //判断两点相等
    f64 dot(P p) { return x * p.x + y * p.y; }                           //点积
    f64 det(P p) { return x * p.y - y * p.x; }                           //叉积
    f64 distTo(P p) { return (*this - p).abs(); }                        //距离
    f64 alpha() { return atan2l(y, x); }                                 //求极角
    void read() { cin >> x >> y; }
    f64 abs() { return sqrtl(abs2()); }                                          //长度
    f64 abs2() { return x * x + y * y; }                                         //长度的平方
    P rot90() { return P(-y, x); }                                               //逆时针旋转90度
    P unit() { return *this / abs(); }                                           //单位化
    int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }  //极角是否在[0,180)之间
    P rot(f64 an) {
        return {x * cosl(an) - y * sinl(an), x * sinl(an) + y * cosl(an)};
    }  //逆时旋转an
};

struct L {  // ps[0] -> ps[1]
    P ps[2];
    L(P x, P y) {
        ps[0] = x, ps[1] = y;
    }
    P& operator[](int i) { return ps[i]; }
    P dir() { return ps[1] - ps[0]; }                                       //直线的方向向量
    bool include(P p) { return sign((ps[1] - ps[0]).det(p - ps[0])) > 0; }  //是否在左边（半平面交的时候有用）
    L push() {                                                              // push eps outward
        const double eps = 1e-6;
        P delta = (ps[1] - ps[0]).rot90().unit() * eps;
        return {ps[0] - delta, ps[1] - delta};
    }
};

#define cross(p1, p2, p3) ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y))
#define crossOp(p1, p2, p3) sign(cross(p1, p2, p3))

P isLL(P p1, P p2, P q1, P q2) {  //求两直线交点
    f64 a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}

P isLL(L l1, L l2) {
    return isLL(l1[0], l1[1], l2[0], l2[1]);
}  //求两直线交点

bool intersect(f64 l1, f64 r1, f64 l2, f64 r2) {
    if (l1 > r1)
        swap(l1, r1);
    if (l2 > r2)
        swap(l2, r2);
    return !(cmp(r1, l2) == -1 || cmp(r2, l1) == -1);
}

bool isSS(P p1, P p2, P q1, P q2) {
    return intersect(p1.x, p2.x, q1.x, q2.x) && intersect(p1.y, p2.y, q1.y, q2.y) &&
           crossOp(p1, p2, q1) * crossOp(p1, p2, q2) <= 0 && crossOp(q1, q2, p1) * crossOp(q1, q2, p2) <= 0;
}

bool isMiddle(f64 a, f64 m, f64 b) {  //判断m是否在a,b之间
    return sign(a - m) == 0 || sign(b - m) == 0 || (a < m != b < m);
}

bool isMiddle(P a, P m, P b) {  //判断点m的坐标是否在a,b之间
    return isMiddle(a.x, m.x, b.x) && isMiddle(a.y, m.y, b.y);
}

bool onSeg(P p1, P p2, P q) {  //判断点是否在直线上
    return crossOp(p1, p2, q) == 0 && isMiddle(p1, q, p2);
}

P proj(P p1, P p2, P q) {  //关于直线的投影
    P dir = p2 - p1;
    return p1 + dir * (dir.dot(q - p1) / dir.abs2());
}

P reflect(P p1, P p2, P q) {  //关于直线的对称
    return proj(p1, p2, q) * 2 - q;
}

f64 nearest(P p1, P p2, P q) {  //线段p1p2到q的最近距离
    P h = proj(p1, p2, q);
    if (isMiddle(p1, h, p2))
        return q.distTo(h);
    return min(p1.distTo(q), p2.distTo(q));
}

f64 disSS(P p1, P p2, P q1, P q2) {  //线段和线段的距离
    if (isSS(p1, p2, q1, q2))
        return 0;
    return min(min(nearest(p1, p2, q1), nearest(p1, p2, q2)), min(nearest(q1, q2, p1), nearest(q1, q2, p2)));
}

f64 disSS(L l1, L l2) {  //线段和线段距离
    return disSS(l1[0], l1[1], l2[0], l2[1]);
}

f64 rad(P p1, P p2) {  // 返回p1p2关于原点的弧度
    return atan2l(p1.det(p2), p1.dot(p2));
}

f64 incircle(P p1, P p2, P p3) {  //
    f64 A = p1.distTo(p2);
    f64 B = p2.distTo(p3);
    f64 C = p3.distTo(p1);
    return sqrtl(A * B * C / (A + B + C));
}

// polygon

f64 area(vector<P> ps) {
    f64 ret = 0;
    for (int i = 0; i < ps.size(); i++)
        ret += ps[i].det(ps[(i + 1) % ps.size()]);
    return abs(ret / 2);
}
//引向右的虚线判断是否在多边形内
int contain(vector<P> ps, P p) {  // 2:inside,1:on_seg,0:outside
    int n = ps.size(), ret = 0;
    for (int i = 0; i < n; i++) {
        P u = ps[i], v = ps[(i + 1) % n];
        if (onSeg(u, v, p))
            return 1;
        if (cmp(u.y, v.y) <= 0)
            swap(u, v);
        if (cmp(p.y, u.y) > 0 || cmp(p.y, v.y) <= 0)
            continue;
        ret ^= crossOp(p, u, v) > 0;
    }
    return ret * 2;
}

vector<P> convexHull(vector<P> ps) {  // 凸包
    int n = ps.size();
    if (n <= 1)
        return ps;
    sort(ps.begin(), ps.end());
    vector<P> qs(n * 2);
    int k = 0;
    for (int i = 0; i < n; qs[k++] = ps[i++])
        while (k > 1 && crossOp(qs[k - 2], qs[k - 1], ps[i]) <= 0)
            --k;
    for (int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
        while (k > t && crossOp(qs[k - 2], qs[k - 1], ps[i]) <= 0)
            --k;
    qs.resize(k - 1);
    return qs;
}

vector<P> convexHullNonStrict(vector<P> ps) {  //非严格凸多边形
    // caution: need to unique the Ps first
    int n = ps.size();
    if (n <= 1)
        return ps;
    sort(ps.begin(), ps.end());
    vector<P> qs(n * 2);
    int k = 0;
    for (int i = 0; i < n; qs[k++] = ps[i++])
        while (k > 1 && crossOp(qs[k - 2], qs[k - 1], ps[i]) < 0)
            --k;
    for (int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
        while (k > t && crossOp(qs[k - 2], qs[k - 1], ps[i]) < 0)
            --k;
    qs.resize(k - 1);
    return qs;
}

f64 convexDiameter(vector<P> ps) {  //旋转卡壳求凸多边形直径
    int n = ps.size();
    if (n <= 1)
        return 0;
    int is = 0, js = 0;
    for (int k = 1; k < n; k++)
        is = ps[k] < ps[is] ? k : is, js = ps[js] < ps[k] ? k : js;
    int i = is, j = js;
    f64 ret = ps[i].distTo(ps[j]);
    do {
        if ((ps[(i + 1) % n] - ps[i]).det(ps[(j + 1) % n] - ps[j]) >= 0)
            (++j) %= n;
        else
            (++i) %= n;
        ret = max(ret, ps[i].distTo(ps[j]));
    } while (i != is || j != js);
    return ret;
}

vector<P> convexCut(const vector<P>& ps, P q1, P q2) {
    vector<P> qs;
    int n = ps.size();
    for (int i = 0; i < n; i++) {
        P p1 = ps[i], p2 = ps[(i + 1) % n];
        int d1 = crossOp(q1, q2, p1), d2 = crossOp(q1, q2, p2);
        if (d1 >= 0)
            qs.emplace_back(p1);
        if (d1 * d2 < 0)
            qs.emplace_back(isLL(p1, p2, q1, q2));
    }
    return qs;
}

// min_dist

f64 min_dist(vector<P>& ps, int l, int r) {
    if (r - l <= 5) {
        f64 ret = 1e100;
        for (int i = l; i < r; i++)
            for (int j = l; j < i; j++)
                ret = min(ret, ps[i].distTo(ps[j]));
        return ret;
    }
    int m = (l + r) >> 1;
    f64 ret = min(min_dist(ps, l, m), min_dist(ps, m, r));
    vector<P> qs;
    for (int i = l; i < r; i++)
        if (abs(ps[i].x - ps[m].x) <= ret)
            qs.emplace_back(ps[i]);
    sort(qs.begin(), qs.end(), [](P a, P b) -> bool { return a.y < b.y; });
    for (int i = 1; i < qs.size(); i++)
        for (int j = i - 1; j >= 0 && qs[j].y >= qs[i].y - ret; --j)
            ret = min(ret, qs[i].distTo(qs[j]));
    return ret;
}

int type(P o1, f64 r1, P o2, f64 r2) {
    f64 d = o1.distTo(o2);
    if (cmp(d, r1 + r2) == 1)
        return 4;  //不交
    if (cmp(d, r1 + r2) == 0)
        return 3;  //外切
    if (cmp(d, abs(r1 - r2)) == 1)
        return 2;  //相交
    if (cmp(d, abs(r1 - r2)) == 0)
        return 1;  //内切
    return 0;      //内含
}

vector<P> isCL(P o, f64 r, P p1, P p2) {
    f64 x = (p1 - o).dot(p2 - p1), y = (p2 - p1).abs2(), d = x * x - y * ((p1 - o).abs2() - r * r);
    if (sign(d) < 0)
        return {};
    d = max(d, (long double)0.0);
    P m = p1 - (p2 - p1) * (x / y), dr = (p2 - p1) * (sqrtl(d) / y);
    return {m - dr, m + dr};  // along dir: p1->p2
}

vector<P> isCC(P o1, f64 r1, P o2, f64 r2) {  // need to check whether two circles are the same
    f64 d = o1.distTo(o2);
    if (cmp(d, r1 + r2) == 1)
        return {};
    d = min(d, r1 + r2);
    f64 y = (r1 * r1 + d * d - r2 * r2) / (2 * d), x = sqrtl(r1 * r1 - y * y);
    P dr = (o2 - o1).unit();
    P q1 = o1 + dr * y, q2 = dr.rot90() * x;
    return {q1 - q2, q1 + q2};  // along circle 1
}

vector<P> tanCP(P o, f64 r, P p) {  //点到圆的两个切点
    f64 x = (p - o).abs2(), d = x - r * r;
    if (sign(d) <= 0)
        return {};  // on circle => no tangent
    P q1 = o + (p - o) * (r * r / x);
    P q2 = (p - o).rot90() * (r * sqrtl(d) / x);
    return {q1 - q2, q1 + q2};  // counter clock-wise
}

vector<L> extanCC(P o1, f64 r1, P o2, f64 r2) {
    vector<L> ret;
    if (cmp(r1, r2) == 0) {
        P dr = (o2 - o1).unit().rot90() * r1;
        ret.emplace_back(o1 + dr, o2 + dr), ret.emplace_back(o1 - dr, o2 - dr);
    } else {
        P p = (o2 * r1 - o1 * r2) / (r1 - r2);
        vector<P> ps = tanCP(o1, r1, p), qs = tanCP(o2, r2, p);
        for (int i = 0; i < min(ps.size(), qs.size()); i++)
            ret.emplace_back(ps[i], qs[i]);  // c1 counter-clock wise
    }
    return ret;
}

vector<L> intanCC(P o1, f64 r1, P o2, f64 r2) {
    vector<L> ret;
    P p = (o1 * r2 + o2 * r1) / (r1 + r2);
    vector<P> ps = tanCP(o1, r1, p), qs = tanCP(o2, r2, p);
    for (int i = 0; i < min(ps.size(), qs.size()); i++)
        ret.emplace_back(ps[i], qs[i]);  // c1 counter-clock wise
    return ret;
}

f64 areaCT(f64 r, P p1, P p2) {
    vector<P> is = isCL(P(0, 0), r, p1, p2);
    if (is.empty())
        return r * r * rad(p1, p2) / 2;
    bool b1 = cmp(p1.abs2(), r * r) == 1, b2 = cmp(p2.abs2(), r * r) == 1;
    if (b1 && b2) {
        if (sign((p1 - is[0]).dot(p2 - is[0])) <= 0 &&
            sign((p1 - is[0]).dot(p2 - is[0])) <= 0)
            return r * r * (rad(p1, is[0]) + rad(is[1], p2)) / 2 + is[0].det(is[1]) / 2;
        else
            return r * r * rad(p1, p2) / 2;
    }
    if (b1)
        return (r * r * rad(p1, is[0]) + is[0].det(p2)) / 2;
    if (b2)
        return (p1.det(is[1]) + r * r * rad(is[1], p2)) / 2;
    return p1.det(p2) / 2;
}

bool parallel(L l0, L l1) {
    return sign(l0.dir().det(l1.dir())) == 0;
}  //判断两直线是否平行

bool sameDir(L l0, L l1) {
    return parallel(l0, l1) && sign(l0.dir().dot(l1.dir())) == 1;
}  //判断两射线是否同向

bool cmp(P a, P b) {
    if (a.quad() != b.quad()) {
        return a.quad() < b.quad();
    } else {
        return sign(a.det(b)) > 0;
    }
}

bool operator<(L l0, L l1) {
    if (sameDir(l0, l1)) {
        return l1.include(l0[0]);
    } else {
        return cmp(l0.dir(), l1.dir());
    }
}

bool check(L u, L v, L w) {
    return w.include(isLL(u, v));
}

vector<P> halfPlaneIS(vector<L>& l) {  //求半平面交
    sort(l.begin(), l.end());
    deque<L> q;
    for (int i = 0; i < (int)l.size(); ++i) {
        if (i && sameDir(l[i], l[i - 1]))
            continue;
        while (q.size() > 1 && !check(q[q.size() - 2], q[q.size() - 1], l[i]))
            q.pop_back();
        while (q.size() > 1 && !check(q[1], q[0], l[i]))
            q.pop_front();
        q.push_back(l[i]);
    }
    while (q.size() > 2 && !check(q[q.size() - 2], q[q.size() - 1], q[0]))
        q.pop_back();
    while (q.size() > 2 && !check(q[1], q[0], q[q.size() - 1]))
        q.pop_front();
    vector<P> ret;
    for (int i = 0; i < (int)q.size(); ++i)
        ret.push_back(isLL(q[i], q[(i + 1) % q.size()]));
    return ret;
}

struct point3D {
    f64 x, y, z;
    point3D() { x = 0, y = 0, z = 0; }
    point3D(f64 a, f64 b, f64 c) {
        x = a, y = b, z = c;
    }
    point3D det(point3D p) {
        return point3D(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }
    f64 dot(point3D p) {
        return x * p.x + y * p.y + z * p.z;
    }
    point3D operator-(const point3D& b) const {
        return point3D(x - b.x, y - b.y, z - b.z);
    }
    point3D operator+(const point3D& b) const {
        return point3D(x + b.x, y + b.y, z + b.z);
    }
    point3D operator*(const f64 k) const {
        return point3D(x * k, y * k, z * k);
    }
    point3D operator/(const f64 k) const {
        return point3D(x / k, y / k, z / k);
    }
    f64 operator*(const point3D& b) const {
        return x * b.x + y * b.y + z * b.z;
    }
    f64 abs() { return sqrtl(abs2()); }  //向量模
    f64 abs2() { return x * x + y * y + z * z; }
    f64 distTo(point3D p) { return (*this - p).abs(); }  //两点距离
    point3D unit() { return *this / abs(); }             //返回单位向量
    friend ostream& operator<<(ostream& os, point3D& cc) {
        os << cc.x << " " << cc.y << " " << cc.z;
        return os;
    }
};

point3D eval(point3D U, point3D V, f64 r) {  //罗德里格斯公式，按右手法则任意向量V绕单位向量U旋转弧度r
    return V * cos(r) + U * U.dot(V) * (1 - cos(r)) + U.det(V) * sin(r);
}

int main() {
    return 0;
}
```

# 曼哈顿距离和切比雪夫距离

- 曼哈顿坐标系是通过切比雪夫坐标系旋转 $45^\circ$ 后，再缩小到原来的一半得到的。
- 将一个点 $(x,y)$ 的坐标变为 $(x + y, x - y)$ 后，原坐标系中的曼哈顿距离等于新坐标系中的切比雪夫距离。
- 将一个点 $(x,y)$ 的坐标变为 $(\dfrac{x + y}{2},\dfrac{x - y}{2})$ 后，原坐标系中的切比雪夫距离等于新坐标系中的曼哈顿距离。



# 最小球覆盖

```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;

struct point {
    double x;
    double y;
    double z;
} p[313];
int N;
double dist(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
double solve() {
    const double eps = 1e-3;      //精度
    const double start_T = 1000;  //初始温度
    const double rate = 0.98;     //温度下降速率
    const double eps = 1e-3;      //精度
    const double start_T = 1000;  //初始温度
    const double rate = 0.98;     //温度下降速率
    double T = start_T;
    point ans_p = {0, 0, 0};  //初始点
    double ans = 1e99;        //预设一个较大值
    while (T > eps) {
        point maxd_p = p[1];
        for (int i = 2; i <= N; i++) {
            if (dist(ans_p, p[i]) > dist(ans_p, maxd_p))
                maxd_p = p[i];
        }
        //找到距离ans_p最远的点,maxd_p
        ans = min(ans, dist(ans_p, maxd_p));
        ans_p.x += (maxd_p.x - ans_p.x) * (T / start_T);  //以一定概率靠近maxd_p
        ans_p.y += (maxd_p.y - ans_p.y) * (T / start_T);
        ans_p.z += (maxd_p.z - ans_p.z) * (T / start_T);
        T *= rate;
    }
    return ans;
}
int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].z);
    printf("%.8lf", solve());
    return 0;
}

```

