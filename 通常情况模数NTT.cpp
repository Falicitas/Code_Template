const int N = ;  //最大运算长度。运算长度指大于最高项的2^k。1<<20 ~ 1e6，往前往后推
const int p = 998244353, g = 3;
int w[N << 2], inv[N << 2], r[N << 2], last;
ll qp(ll base, ll n) {
    base %= p;
    ll res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= p;
        (base *= base) %= p;
        n >>= 1;
    }
    return res;
}

void init() {
    int lim = N << 1;  //运算后最长数组的两倍
    inv[1] = 1;
    for (int i = 2; i <= lim; i++)
        inv[i] = (p - 1ll * (p / i) * inv[p % i] % p) % p;
    for (int i = 1; i < lim; i <<= 1) {
        int wn = qp(g, (p - 1) / (i << 1));
        for (int j = 0, ww = 1; j < i; j++, ww = 1ll * ww * wn % p)
            w[i + j] = ww;
    }
}

void ntt(vector<int>& f, int lim, int op) {
    if (last != lim) {
        for (int i = 1; i < lim; i++)
            r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
        last = lim;
    }
    for (int i = 1; i < lim; i++)
        if (i < r[i])
            swap(f[i], f[r[i]]);
    for (int i = 1; i < lim; i <<= 1)
        for (int j = 0; j < lim; j += i << 1)
            for (int k = 0; k < i; k++) {
                int x = f[j + k], y = 1ll * f[i + j + k] * w[i + k] % p;
                f[j + k] = (x + y) % p;
                f[i + j + k] = (x - y + p) % p;
            }
    if (op == -1) {
        reverse(&f[1], &f[lim]);
        for (int i = 0; i < lim; i++)
            f[i] = 1ll * f[i] * inv[lim] % p;
    }
}
