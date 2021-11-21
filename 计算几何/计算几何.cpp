#include <bits/stdc++.h>
using namespace std;

using f64 = double;
const f64 PI = acos(-1.0), eps = 1e-7;

int sign(double x) {
    return x < -eps ? -1 : x > eps;
}

int cmp(double x, double y) {
    return sign(x - y);
}

bool isMiddle(f64 a, f64 m, f64 b) {  //点是否在一维线段上
    return sign(a - m) == 0 || sign(b - m) == 0 || (a < m != b < m);
}

bool intersect(f64 l1, f64 r1, f64 l2, f64 r2) {  //两一维线段是否相交
    if (l1 > r1) {
        swap(l1, r1);
    }
    if (l2 > r2) {
        swap(l2, r2);
    }
    return !(cmp(r1, l2) == -1 || cmp(r2, l1) == -1);
}

struct Point {
    f64 x, y;
    f64 dot(Point p) { return x * p.x + y * p.y; }  //点积
    f64 det(Point p) { return x * p.y - y * p.x; }  //叉积
    bool same(Point p) {
        return sign(p.x - x) == 0 && sign(p.y - y) == 0;
    }  //相同的点
    Point operator+(Point p) { return {x + p.x, y + p.y}; }
    Point operator-(Point p) { return {x - p.x, y - p.y}; }
    Point operator*(f64 d) { return {x * d, y * d}; }
    Point operator/(f64 d) { return {x / d, y / d}; }
    f64 abs() { return sqrt(abs2()); }  //向量模
    f64 abs2() { return x * x + y * y; }
    f64 distTo(Point p) { return (*this - p).abs(); }  //两点距离
    Point rot90() { return Point(-y, x); }             //逆时旋转90
    Point unit() { return *this / abs(); }             //返回单位向量
    int quad() const {
        return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0);
    }  //判定是否在[0,\pi)间
    Point rot(f64 an) {
        return {x * cos(an) - y * sin(an), x * sin(an) + y * cos(an)};
    }  //逆时旋转an
};

f64 cross(Point p1, Point p2, Point p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}  //构建向量P_1P_2 与 P_1P_3 叉乘，即P_1P_2 \times P_1P_3
int crossOp(Point p1, Point p2, Point p3) {
    return sign(cross(p1, p2, p3));  //叉乘的符号
}

struct Line {
    vector<Point> ps;
    Point& operator[](int i) { return ps[i]; }
    Point dir() { return ps[1] - ps[0]; }
    Line(Point a, Point b) {
        ps = vector<Point>(2);
        ps[0] = a;
        ps[1] = b;
        // if (ps[1].y < ps[0].y || (cmp(ps[1].y, ps[0].y) == 0 && ps[1].x < ps[0].x)) {
        //     swap(ps[0], ps[1]);
        // }  //保持直线向量的弧度[0,\pi)
        //半平面交不能交换两点
    }
    bool include(Point p) {
        return sign(dir().det(p - ps[0])) > 0;
    }              //判断点是否在直线左侧
    Line push() {  // push eps outward修正精度
        const double eps = 1e-8;
        Point delta = (ps[1] - ps[0]).rot90().unit() * eps;
        return {ps[0] + delta, ps[1] + delta};
    }
    bool isMiddle(Point b) {  //点在线段代表的矩阵内
        return ::isMiddle(ps[0].x, b.x, ps[1].x) &&
               ::isMiddle(ps[0].y, b.y, ps[1].y);
    }
    bool onSeg(Point q) {  //判断点是否在线段上（包括两个端点）
        return dir().det(q) == 0 && isMiddle(q);
    }
    bool onSeg_strict(Point q) {  //判断点是否在线段上（不包括两个端点）
        return dir().det(q) == 0 && !ps[0].same(q) && !ps[1].same(q);
    }
    bool intersect(Line q) {  //快速排斥实验
        return ::intersect(ps[0].x, ps[1].x, q[0].x, q[1].x) &&
               ::intersect(ps[0].y, ps[1].y, q[0].y, q[1].y);
    }
    bool isSS(Line q) {
        return intersect(q) &&
               crossOp(ps[0], ps[1], q[0]) * crossOp(ps[0], ps[1], q[1]) <= 0 &&
               crossOp(q[0], q[1], ps[0]) * crossOp(q[0], q[1], ps[1]) <= 0;
    }
    bool isSS_strict(Line q) {
        return crossOp(ps[0], ps[1], q[0]) * crossOp(ps[0], ps[1], q[1]) < 0 &&
               crossOp(q[0], q[1], ps[0]) * crossOp(q[0], q[1], ps[1]) < 0;
    }
    Point proj(Point q) {  //求 q 在线段上的投影
        Point dirr = dir();
        return ps[0] + dirr * (dirr.dot(q - ps[0]) / dirr.abs2());
    }
    Point reflect(Point q) { return proj(q) * 2 - q; }  //求 q 在直线的镜像点
    f64 nearest(Point q) {                              //求点到线段最短距离
        Point h = proj(q);
        if (isMiddle(h))
            return q.distTo(h);
        return min(ps[0].distTo(q), ps[1].distTo(q));
    }

    f64 disSS(Line& q) {  //求两线段上两点的最短距离
        if (isSS(q))
            return 0;
        return min(min(nearest(q[0]), nearest(q[1])),
                   min(q.nearest(ps[0]), q.nearest(ps[1])));
    }
    bool chkLL(Point p1, Point p2, Point q1, Point q2) {  //判断两个直线是否平行
        f64 a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
        return sign(a1 + a2) != 0;  //平行时，自己画这个向量的叉积，都是相同的
    }

    Point isLL(Line& q) {  //考虑a1,b1的实际含义（平行四边形的面积），则相同底边，面积比等于长度比。
        f64 a1 = cross(q[0], q[1], ps[0]), a2 = -cross(q[0], q[1], ps[1]);
        return (ps[0] * a2 + ps[1] * a1) / (a1 + a2);
    }
};

struct point3D {
    f64 x, y, z;
    point3D() {}
    point3D(f64 a, f64 b, f64 c) {
        x = a;
        y = b;
        z = c;
    }
    point3D operator-(const point3D& b) const {  //返回减去后的新点
        return point3D(x - b.x, y - b.y, z - b.z);
    }
    point3D operator+(const point3D& b) const {  //返回加上后的新点
        return point3D(x + b.x, y + b.y, z + b.z);
    }
    //数乘计算
    point3D operator*(const f64& k) const {  //返回相乘后的新点
        return point3D(x * k, y * k, z * k);
    }
    point3D operator/(const f64& k) const {  //返回相除后的新点
        return point3D(x / k, y / k, z / k);
    }
    f64 operator*(const point3D& b) const {  //点乘
        return x * b.x + y * b.y + z * b.z;
    }
};

f64 dist(point3D p1, point3D p2) {  //返回平面上两点距离
    return sqrt((p1 - p2) * (p1 - p2));
}

struct sphere {  //球
    f64 r;
    point3D centre;
};

void SphereInterVS(sphere a, sphere b, f64& v, f64& s) {  // v是体积交，s是两个球缺
    f64 d = dist(a.centre, b.centre);                     //球心距
    f64 t = (d * d + a.r * a.r - b.r * b.r) / (2.0 * d);
    f64 h = sqrt((a.r * a.r) - (t * t)) * 2;                                    // h1=h2，球冠的高
    f64 angle_a = 2 * acos((a.r * a.r + d * d - b.r * b.r) / (2.0 * a.r * d));  //余弦公式计算r1对应圆心角，弧度
    f64 angle_b = 2 * acos((b.r * b.r + d * d - a.r * a.r) / (2.0 * b.r * d));  //余弦公式计算r2对应圆心角，弧度
    f64 l1 = ((a.r * a.r - b.r * b.r) / d + d) / 2;
    f64 l2 = d - l1;
    f64 x1 = a.r - l1, x2 = b.r - l2;        //分别为两个球缺的高度
    f64 v1 = PI * x1 * x1 * (a.r - x1 / 3);  //相交部分r1圆所对应的球缺部分体积
    f64 v2 = PI * x2 * x2 * (b.r - x2 / 3);  //相交部分r2圆所对应的球缺部分体积
    v = v1 + v2;                             //相交部分体积
    s = 2 * PI * (a.r * x1 + b.r * x2);      //球缺的面积
}

struct Polygon {
    vector<Point> ps;
    Polygon() {
        ps = vector<Point>();
    }
    Polygon(vector<Point> ps_)  //p_i <-> p_{i+1}
        : ps(ps_) {
    }
    int contain(Point p) {  //On判点在多边形内还是外。2:inside,1:on_seg,0:outside
        int n = ps.size(), ret = 0;
        for (int i = 0; i < n; i++) {
            Point u = ps[i], v = ps[(i + 1) % n];
            if (Line(u, v).onSeg(p))
                return 1;
            if (cmp(u.y, v.y) <= 0)
                swap(u, v);
            if (cmp(p.y, u.y) > 0 || cmp(p.y, v.y) <= 0)
                continue;                 //仅考虑会相交的边
            ret ^= crossOp(p, u, v) > 0;  //保证u在上后，可以发现（当点在多边形内）只有左侧的边会统计到
        }
        return ret * 2;
    }
    bool contain_fast(Point p0)  //Ologn判凸多边形线内还是线外。
    {
        int n = ps.size();
        if (crossOp(ps[0], ps[1], p0) < 0 || crossOp(ps[0], ps[n - 1], p0) > 0)
            return 0;
        pair<int, int> q;
        int id = 0;
        {
            int l = 0, r = n - 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (crossOp(ps[0], ps[mid], p0)) {
                    id = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
        }
        return crossOp(ps[id], ps[(id + 1) % n], p0) >= 0;
    }
    f64 area() {  //求多边形的面积
        f64 ret = 0;
        int n = ps.size();
        for (int i = 0; i < n; i++) {
            ret += ps[i].det(ps[(i + 1) % ps.size()]);
        }
        return ret / 2;
    }
};

Polygon convexHull(vector<Point> ps) {  //求点集的严格凸包
    int n = ps.size();
    if (n <= 1)
        return ps;
    sort(ps.begin(), ps.end(), [](Point p1, Point p2) {
        if (p1.x != p2.x) {
            return p1.x < p2.x;
        }
        return p1.y < p2.y;
    });
    vector<Point> qs(n * 2);
    int k = 0;
    for (int i = 0; i < n; qs[k++] = ps[i++])
        while (k > 1 && crossOp(qs[k - 2], qs[k - 1], ps[i]) <= 0)
            --k;
    for (int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
        while (k > t && crossOp(qs[k - 2], qs[k - 1], ps[i]) <= 0)
            --k;
    qs.resize(k - 1);
    return Polygon(qs);
}

Polygon convexHullNonStrict(vector<Point> ps) {  //求点集的非严格凸包（点可以在凸包线上）
    //caution: need to unique the Ps first
    int n = ps.size();
    if (n <= 1)
        return ps;
    sort(ps.begin(), ps.end());
    vector<Point> qs(n * 2);
    int k = 0;
    for (int i = 0; i < n; qs[k++] = ps[i++])
        while (k > 1 && crossOp(qs[k - 2], qs[k - 1], ps[i]) < 0)
            --k;
    for (int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
        while (k > t && crossOp(qs[k - 2], qs[k - 1], ps[i]) < 0)
            --k;
    qs.resize(k - 1);
    return Polygon(qs);
}

vector<Point> halfPlaneIS(vector<Line>& l) {
    auto parallel = [&](Line l0, Line l1) {
        return sign(l0.dir().det(l1.dir())) == 0;
    };
    auto sameDir = [&](Line l0, Line l1) {
        return parallel(l0, l1) && sign(l0.dir().dot(l1.dir())) == 1;
    };
    auto check = [](Line u, Line v, Line w) {
        return w.include(u.isLL(v));
    };
    sort(l.begin(), l.end(), [&](Line l0, Line l1) {
        auto cmp = [](Point a, Point b) {
            if (a.quad() != b.quad()) {
                return a.quad() < b.quad();
            } else {
                return sign(a.det(b)) > 0;
            }
        };
        if (sameDir(l0, l1)) {
            return l1.include(l0[0]);
        } else {
            return cmp(l0.dir(), l1.dir());
        }
    });
    deque<Line> q;
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
    vector<Point> ret;
    for (int i = 0; i < (int)q.size(); ++i)
        ret.push_back(q[i].isLL(q[(i + 1) % q.size()]));
    return ret;
}

Point gravity(Point a, Point b, Point c) {  // 重心
    double x = (a.x + b.x + c.x) / 3;
    double y = (a.y + b.y + c.y) / 3;
    return Point(x, y);
}

Point Incenter(Point a, Point b, Point c) {  //三角形内心
    double A = b.distTo(c);
    double B = a.distTo(c);
    double C = a.distTo(b);
    double S = A + B + C;
    double x = (A * a.x + B * b.x + C * c.x) / S;
    double y = (A * a.y + B * b.y + C * c.y) / S;
    return Point(x, y);
}

Point Circum(Point a, Point b, Point c) {  //三角形外心
    double x1 = a.x, y1 = a.y;
    double x2 = b.x, y2 = b.y;
    double x3 = c.x, y3 = c.y;

    double a1 = 2 * (x2 - x1);
    double b1 = 2 * (y2 - y1);
    double c1 = x2 * x2 + y2 * y2 - x1 * x1 - y1 * y1;

    double a2 = 2 * (x3 - x2);
    double b2 = 2 * (y3 - y2);
    double c2 = x3 * x3 + y3 * y3 - x2 * x2 - y2 * y2;

    double x = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
    double y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);

    return Point(x, y);
}
Point ortho(Point a, Point b, Point c) {  //垂心
    double A1 = b.x - c.x;
    double B1 = b.y - c.y;
    double C1 = A1 * a.y - B1 * a.x;

    double A2 = a.x - c.x;
    double B2 = a.y - c.y;
    double C2 = A2 * b.y - B2 * b.x;

    double x = (A1 * C2 - A2 * C1) / (A2 * B1 - A1 * B2);
    double y = (B1 * C2 - B2 * C1) / (A2 * B1 - A1 * B2);

    return Point(x, y);
}

vector<Point> Minkowski(vector<Point> C1, vector<Point> C2) {
    int n = C1.size(), m = C2.size();
    vector<Point> s1(n), s2(m), A;
    for (int i = 0; i < n; i++)
        s1[i] = C1[(i + 1) % n] - C1[i];
    for (int i = 0; i < m; i++)
        s2[i] = C2[(i + 1) % m] - C2[i];
    A.emplace_back(C1[0] + C2[0]);
    int p1 = 0, p2 = 0;
    while (p1 < n && p2 < m)
        A.emplace_back(A.back() + (s1[p1].det(s2[p2]) >= 0 ? s1[p1++] : s2[p2++]));
    while (p1 < n)
        A.emplace_back(A.back() + s1[p1++]);
    while (p2 < m)
        A.emplace_back(A.back() + s2[p2++]);
    return A;
}

int main() {
    return 0;
}