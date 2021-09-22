#include <bits/stdc++.h>
using namespace std;
constexpr int P = 1000000007;
using i64 = long long;
// assume -P <= x < 2P
int norm(int x) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}
template <class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0)
        : x(norm(x)) {}
    int val() const { return x; }
    Z operator-() const { return Z(norm(P - x)); }
    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z& operator*=(const Z& rhs) {
        x = i64(x) * rhs.x % P;
        return *this;
    }
    Z& operator+=(const Z& rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z& operator-=(const Z& rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z& operator/=(const Z& rhs) { return *this *= rhs.inv(); }
    friend Z operator*(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
};
struct mat {
    int n, m;
    vector<vector<Z>> c;
    mat(int a, int b)
        : n(a), m(b) {
        c = vector<vector<Z>>(n, vector<Z>(m));
    }
    void clear() {
        c = vector<vector<Z>>(n, vector<Z>(m));
    }
    mat operator*(const mat& temp) {
        mat ans(n, temp.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < temp.m; j++) {
                for (int k = 0; k < m; k++) {
                    ans.c[i][j] += c[i][k] * temp.c[k][j];
                }
            }
        }
        return ans;
    }
    friend mat operator^(mat M, i64 n) {
        mat ans(M.n, M.n);
        for (int i = 0; i < M.n; i++) {
            ans.c[i][i] = 1;
        }
        while (n > 0) {
            if (n & 1) {
                ans = ans * M;
            }
            M = M * M;
            n >>= 1;
        }
        return ans;
    }
};
