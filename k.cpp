#include <bits/stdc++.h>

struct Chairman_Tree {
    struct Node {
        int v, ls, rs;
    };
    std::vector<Node> e;
    int n, cnt;
    std::vector<int> T;
    Chairman_Tree(int n)
        : n(n) {
        cnt = 0;
        e.resize(n << 5);
        T.resize(n + 5);
    }
#define v(p) e[p].v
#define ls(p) e[p].ls
#define rs(p) e[p].rs
#define mid (l + r >> 1)
    int update(int pre, int l, int r, int x, int v) {
        int p = ++cnt;
        e[p] = e[pre], v(p) += v;
        if (l < r) {
            if (x <= mid)
                ls(p) = update(ls(pre), l, mid, x, v);
            else
                rs(p) = update(rs(pre), mid + 1, r, x, v);
        }
        return p;
    }

    int query(int s, int l, int r, int k) {
        if (l >= r)
            return l;
        int x = v(ls(s));
        if (k <= x)
            return query(ls(s), l, mid, k);
        else
            return query(rs(s), mid + 1, r, k - x);
    }
} seg;

std::vector<int> a;
std::vector<std::array<int, 4>> xun;

int main() {
    int T;
    int q, opt, l, x, r;
    std::cin >> T;
    while (T--) {
        seg = Chairman_Tree(q + 1);
        a.clear();
        xun.clear();
        std::cin >> q;
        while (q--) {
            std::cin >> opt;
            if (opt == 1) {
                std::cin >> l >> x >> r;
                xun.emplace_back(1, l, x, r);
                a.emplace_back(l);
                a.emplace_back(r);
            } else {
                std::cin >> l >> x;
                xun.emplace_back(2, l, x, 0);
                a.emplace_back(l);
            }
        }
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        for (auto& i : xun) {
            if (i[0] == 1) {
                l = std::lower_bound(a.begin(), a.end(), l) - a.begin();

                xun.emplace_back(1, l, x, r);
                a.emplace_back(l);
                a.emplace_back(r);
            } else {
                std::cin >> l >> x;
                xun.emplace_back(2, l, x, 0);
                a.emplace_back(l);
            }
        }
    }
}