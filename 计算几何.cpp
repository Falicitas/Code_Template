#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
typedef unsigned long long ll;
struct point3D {
    double x, y, z;
    point3D() {
    }
    point3D(double a, double b, double c) {
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
    point3D operator*(const double& k) const {  //返回相乘后的新点
        return point3D(x * k, y * k, z * k);
    }
    point3D operator/(const double& k) const {  //返回相除后的新点
        return point3D(x / k, y / k, z / k);
    }
    double operator*(const point3D& b) const {  //点乘
        return x * b.x + y * b.y + z * b.z;
    }
};

double dist(point3D p1, point3D p2) {  //返回平面上两点距离
    return sqrt((p1 - p2) * (p1 - p2));
}

struct sphere {  //球
    double r;
    point3D centre;
};

namespace Geometry {
void SphereInterVS(sphere a, sphere b, double& v, double& s) {  //v是体积交，s是两个球缺
    double d = dist(a.centre, b.centre);                        //球心距
    double t = (d * d + a.r * a.r - b.r * b.r) / (2.0 * d);
    double h = sqrt((a.r * a.r) - (t * t)) * 2;                                    //h1=h2，球冠的高
    double angle_a = 2 * acos((a.r * a.r + d * d - b.r * b.r) / (2.0 * a.r * d));  //余弦公式计算r1对应圆心角，弧度
    double angle_b = 2 * acos((b.r * b.r + d * d - a.r * a.r) / (2.0 * b.r * d));  //余弦公式计算r2对应圆心角，弧度
    double l1 = ((a.r * a.r - b.r * b.r) / d + d) / 2;
    double l2 = d - l1;
    double x1 = a.r - l1, x2 = b.r - l2;        //分别为两个球缺的高度
    double v1 = PI * x1 * x1 * (a.r - x1 / 3);  //相交部分r1圆所对应的球缺部分体积
    double v2 = PI * x2 * x2 * (b.r - x2 / 3);  //相交部分r2圆所对应的球缺部分体积
    v = v1 + v2;                                //相交部分体积
    s = 2 * PI * (a.r * x1 + b.r * x2);         //球缺的面积
}
}  // namespace Geometry