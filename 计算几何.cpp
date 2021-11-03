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

bool isMiddle(f64 a, f64 m, f64 b) {
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
    }
    Point operator+(Point p) { return {x + p.x, y + p.y}; }
    Point operator-(Point p) { return {x - p.x, y - p.y}; }
    Point operator*(f64 d) { return {x * d, y * d}; }
    Point operator/(f64 d) { return {x / d, y / d}; }
    f64 abs() { return sqrt(abs2()); }  //向量模
    f64 abs2() { return x * x + y * y; }
    f64 distTo(Point p) { return (*this - p).abs(); }                                     //两点距离
    Point rot90() { return Point(-y, x); }                                                //逆时旋转90
    Point unit() { return *this / abs(); }                                                //返回单位向量
    int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }           //判定是否在[0,\pi)间
    Point rot(f64 an) { return {x * cos(an) - y * sin(an), x * sin(an) + y * cos(an)}; }  //逆时旋转an
};

struct Line {
    vector<Point> ps;
    Point& operator[](int i) { return ps[i]; }
    Point dir() { return ps[1] - ps[0]; }
    Line(Point a, Point b) {
        ps = vector<Point>(2);
        ps[0] = a;
        ps[1] = b;
        if (ps[1].y < ps[0].y || (cmp(ps[1].y, ps[0].y) == 0 && ps[1].x < ps[0].x)) {
            swap(ps[0], ps[1]);
        }  //保持直线向量的弧度[0,\pi)
    }
    bool include(Point p) { return sign(dir().det(p - ps[0])) > 0; }  //判断点是否在直线左侧
    Line push() {                                                     // push eps outward修正精度
        const double eps = 1e-8;
        Point delta = (ps[1] - ps[0]).rot90().unit() * eps;
        return {ps[0] + delta, ps[1] + delta};
    }
    bool isMiddle(Point b) {  //点在线段代表的矩阵内
        return ::isMiddle(ps[0].x, b.x, ps[1].x) && ::isMiddle(ps[0].y, b.y, ps[1].y);
    }
    bool onSeg(Point q) {  //判断点是否在线段上（包括两个端点）
        return dir().det(q) == 0 && isMiddle(q);
    }
    bool onSeg_strict(Point q) {  //判断点是否在线段上（不包括两个端点）
        return dir().det(q) == 0 && !ps[0].same(q) && !ps[1].same(q);
    }
    bool intersect(Line& q) {  //快速排斥实验
        return ::intersect(ps[0].x, ps[1].x, q[0].x, q[1].x) && ::intersect(ps[0].y, ps[1].y, q[0].y, q[1].y);
    }
    bool
};

struct point3D {
    f64 x, y, z;
    point3D() {
    }
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

namespace Geometry {
void SphereInterVS(sphere a, sphere b, f64& v, f64& s) {  //v是体积交，s是两个球缺
    f64 d = dist(a.centre, b.centre);                     //球心距
    f64 t = (d * d + a.r * a.r - b.r * b.r) / (2.0 * d);
    f64 h = sqrt((a.r * a.r) - (t * t)) * 2;                                    //h1=h2，球冠的高
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
}  // namespace Geometry