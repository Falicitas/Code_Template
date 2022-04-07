#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
template <class Info, class Merge = std::plus<Info>>
struct SegmentTree {
    const int n;
    const Merge merge;
    std::vector<Info> info;
    SegmentTree(int n)
        : n(n), merge(Merge()), info(4 << std::__lg(n)) {}
    SegmentTree(std::vector<Info> init)
        : SegmentTree(init.size()) {
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            cout << p << ":" << l << "," << r << "\n";
            if (r - l == 1) {
                info[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) { info[p] = merge(info[2 * p], info[2 * p + 1]); }
    void modify(int p, int l, int r, int x, const Info& v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info& v) {  //这里的p是单点位置
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
    }
    Info rangeQuery(int l, int r) {  //区间查询[l,r)
        return rangeQuery(1, 0, n, l, r);
    }
};

struct Info {
    /*
    示例：这里Info维护区间中连续子段的个数，s维护该段连续的子段的个数。x=(i!=n-1 && a[i]<=a[i+1])
    这里说下 s(x+1) 的问题。由于最长连续段 [x,y) 的尾的 x=0 ，故初始化先统计
    [x,y),[x+1,y),[x+2,y) 的子段 （包括 [x,x+1),[x+1,x+2),... ，故 s = x+1）
    对于查询 [l,r] 连续子段的个数，仅查 [l,r) 即可，最后少了个 [r,r+1)
    ，所以结果为 rangeQuery(l,r) + 1。 还有注意下标从 0 开始。
    */
    int l, r;
    int len;
    i64 s;
    Info()
        : l(0), r(0), len(0), s(0) {}
    Info(int x)
        : l(x), r(x), len(1), s(x + 1) {}
};

Info operator+(const Info& a, const Info& b) {
    Info c;
    c.l = a.l == a.len ? a.len + b.l : a.l;  //示例：证明返回Info(),l,r维护正常：Info()时，l = len = 0，所以会触发a.len+b.l
    c.r = b.r == b.len ? a.r + b.len : b.r;
    c.len = a.len + b.len;
    c.s = a.s + b.s + 1LL * a.r * b.l;
    return c;
}
