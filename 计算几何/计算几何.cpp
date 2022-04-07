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