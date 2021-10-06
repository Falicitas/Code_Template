#include <bits/stdc++.h>
using namespace std;

/*使用标记永久化，此时sum[1]记录线段覆盖的区间长度*/
struct SegmentTree {
    int n;
    std::vector<int> tag, sum;
    std::vector<int> y;  //线段树点的实际y值
    SegmentTree(int n, vector<int> y_) : n(n), tag(4 * n), sum(4 * n), y(y_) {}
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