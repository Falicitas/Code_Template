#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using f64 = long double;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
constexpr f64 eps = 1e-9;  ///与delta X的取值直接相关

vector<i64> f, A, B, g;  //f是最终取值

struct SlopeDP {
    vector<int> stk;
    SlopeDP() {}
    i64 getans(int i, int j) {
        return f[j] - A[j] - A[j] * j + (i64)j * (j + 1) / 2 + A[j] * i -
               (i64)i * j + B[i] + A[i] + (i64)i * (i - 1) / 2;  //f[i]关于j的表达式
    }
    i64 Y(int j) { return f[j] - A[j] - A[j] * j + (i64)j * (j + 1) / 2; }
    i64 X(int j) { return A[j] - j; }
    i64 K(int i) { return -i; }  //-i表示y=kx+b的k
    f64 slope(int i, int j) { return (f64)(Y(j) - Y(i)) / (X(j) - X(i)); };
    void add(int j) {  //这里维护下凸包，opt=min。opt=max时，调转比较符
        while (stk.size() > 1) {
            int q = *prev(prev(stk.end())), p = *prev(stk.end());
            if (slope(q, p) + eps > slope(p, j)) {
                stk.pop_back();
            } else {
                break;
            }
        }
        stk.emplace_back(j);
    }
    i64 query(int i) {
        if (stk.size() == 0) {
            return inf;
        }
        int id = 0;
        int l = 0, r = (int)stk.size() - 1;
        while (l < r) {
            int m = l + r >> 1;
            if (slope(stk[m], stk[m + 1]) < K(i) + eps) {
                id = m + 1;
                l = m + 1;
            } else {
                r = m;
            }
        }
        return getans(i, stk[id]);
    }
};

struct Cdq {
    vector<int> id;
    Cdq(vector<int> id_)
        : id(id_) {
        sort(id.begin(), id.end());  //这里默认第一关键字是下标，即保证cdq之前i<j,id[i]<id[j]
    }
    function<void(int, int)> cdq = [&](int l, int r) {
        if (l < r) {
            int m = l + r >> 1;
            cdq(l, m);
            SlopeDP sdp;
            vector<int> id1, id2;
            for (int i = l; i <= m; i++) {
                id1.emplace_back(id[i]);  //这里默认左半区间的点都可以贡献给右半区间，具体需要看题目的dp结构
            }
            for (int i = m + 1; i <= r; i++) {
                id2.emplace_back(id[i]);
            }
            function<bool(int, int)> cmp = [&](int x, int y) {  //这里按照第二关键字，也就是y=kx+b的x排序
                return sdp.X(x) <= sdp.X(y);
            };
            sort(id1.begin(), id1.end(), cmp);
            sort(id2.begin(), id2.end(), cmp);
            /*下列所有注释是调试，根据需要解注释看转移过程*/
            // cout << l << " " << r << ",id1:";
            // for (auto x : id1) {
            //     cout << x << " ";
            // }
            // cout << ",id2:";
            // for (auto x : id2) {
            //     cout << x << " ";
            // }
            // cout << ".";
            // cout << l << " " << r << "\n";
            int p = 0, q = 0;
            while (q < id2.size()) {
                while (p < id1.size() &&
                       sdp.X(id[p]) <= sdp.X(id[q])) {
                    sdp.add(id1[p]);
                    p++;
                }

                int i = id2[q];
                i64 buf;  //调试用
                // cout << "[p=" << p << "],";
                f[i] = min(f[i], buf = sdp.query(i));
                // cout << "f[" << i << "]:" << buf << ",";
                q++;
                // cout << ")";
            }
            // cout << "\n";
            // cout << l << " " << r << "\n";
            cdq(m + 1, r);
        }
    };
};

int main() {
    return 0;
}