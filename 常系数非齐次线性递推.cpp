/*
st_n = H(n) + \sum_{i=1}^{k} st_{n-i}a_i,H(x)的度数为m
参考输入
ri3(n,_Rec::m,_Rec::k);//第n项，H(x)的度数，递推系数长度
REP(i,0,_Rec::k-1) ri1(_Rec::Recurrence::st[i]);初始k个值
REP(i,1,_Rec::k) ri1(_Rec::a[i]);递推系数
REP(i,0,_Rec::m) ri1(_Rec::mul_Eva::f[i]);H(x)系数
*/
namespace _Rec {
namespace mul_Eva {
int x[maxn << 1], y[maxn << 1];
vector<int> f(maxn << 1), h(maxn << 1), g[maxn << 1], _g, g_(maxn << 1);
void Get_g(int p, int l, int r) {
    if (l == r) {
        g[p].resize(2);
        g[p][0] = 1, g[p][1] = (mod - x[l]) % mod;
        return;
    }
    int mid = l + r >> 1;
    Get_g(p << 1, l, mid), Get_g(p << 1 | 1, mid + 1, r);
    int lim = 1, deg = r - l + 2;
    while (lim < deg)
        lim <<= 1;
    g[p << 1].resize(lim), g[p << 1 | 1].resize(lim), g[p].resize(lim);
    ntt(g[p << 1], lim, 1), ntt(g[p << 1 | 1], lim, 1);
    REP(i, 0, lim - 1)
    g[p][i] = 1LL * g[p << 1][i] * g[p << 1 | 1][i] % mod;
    ntt(g[p], lim, -1);  //做完以后除了g[1]每一个g都是点值形式
    g[p].resize(deg);
}
vector<int> mulT(vector<int> a, vector<int> b, int n)  //除去idft之外的卷积转置，需要保证a和b是个数相同的点值，n是保留的项数
{
    int lim = a.size();
    for (int i = 0; i < lim; i++)
        a[i] = 1ll * a[i] * b[i] % mod;
    ntt(a, lim, 1);
    return vector<int>(&a[0], &a[n]);  //取a[0]-a[n-1]
}
void solve(int p, int l, int r, vector<int> h) {
    if (l == r) {
        y[l] = h[0];
        return;
    }  //把y作为存答案的数组
    int mid = (l + r) >> 1, lim = 1;
    while (lim < (r - l + 2))
        lim <<= 1;
    h.resize(lim);
    ntt(h, lim, -1);
    solve(p << 1, l, mid, mulT(g[p << 1 | 1], h, mid - l + 1));
    solve(p << 1 | 1, mid + 1, r, mulT(g[p << 1], h, r - mid));
}
void Get_Y(int m) {
    Get_g(1, 0, m - 1);
    _g = g[1];
    PolyInv(m, _g, g_);
    int lim = 1;
    while (lim < ((m + 2) << 1))
        lim <<= 1;
    g_.resize(lim), f.resize(lim);
    ntt(g_, lim, 1);
    ntt(f, lim, -1);
    solve(1, 0, m - 1, mulT(g_, f, m));
}
}  // namespace mul_Eva
namespace Recurrence {
vector<int> g(maxn << 1), gT(maxn << 1), _gT(maxn << 1);
void PolyModulo(int n, int m, vector<int>& f, vector<int>& R)  //特别修改的多项式取模
{
    int lim = 1, deg = 2 * n - m + 10;
    while (lim < (deg))
        lim <<= 1;
    vector<int> fT(lim), Q(lim);
    REP(i, 0, n - 1)
    fT[i] = f[n - 1 - i];
    ntt(fT, lim, 1);
    REP(i, 0, lim - 1)
    fT[i] = 1LL * fT[i] * _gT[i] % mod;
    ntt(fT, lim, -1);
    REP(i, 0, n - m)
    Q[i] = fT[i];
    reverse(Q.begin(), Q.begin() + n - m + 1);
    lim = 1, deg = n + 10;
    while (lim < (deg))
        lim <<= 1;
    vector<int> f1 = f;
    f1.resize(lim), Q.resize(lim), R.resize(lim);
    ntt(f1, lim, 1), ntt(Q, lim, 1);
    REP(i, 0, lim - 1)
    R[i] = (1LL * f1[i] + mod - 1LL * g[i] * Q[i] % mod) % mod;
    ntt(R, lim, -1);
}
void get_g(int n, int m) {
    int lim = 1, deg = 2 * n - m + 10;  //这里的长度要与mod_poly一致
    while (lim < (deg))
        lim <<= 1;
    REP(i, 0, m - 1)
    gT[i] = g[m - 1 - i];
    PolyInv(n - m + 1, gT, _gT);
    ntt(_gT, lim, 1);
    lim = 1, deg = n + 10;  //这里的长度同样要与mod_poly一致
    while (lim < (deg))
        lim <<= 1;
    ntt(g, lim, 1);
}
vector<int> f(maxn << 1);
void mul(int k) {
    int lim = 1;
    while (lim < (k << 1))
        lim <<= 1;
    ntt(f, lim, 1);
    REP(i, 0, lim - 1)
    f[i] = 1LL * f[i] * f[i] % mod;
    ntt(f, lim, -1);
    vector<int> R;
    PolyModulo(2 * k + 1, k + 1, f, R);
    REP(i, 0, k - 1)
    f[i] = R[i];
    REP(i, k, lim - 1)
    f[i] = 0;
}
void add(int k) {
    _REP(i, k, 1)
    f[i] = f[i - 1];
    f[0] = 0;
}

int st[maxn << 1];  //递推系数，初始值，长度均为k

int work(int n, int k)  //a_n = sum 1 to k
{
    get_g(2 * k + 1, k + 1);
    f[1] = 1;
    int cur = 1, lg = log2(n), ok = 0;
    _REP(i, lg - 1, 0) {
        if (k <= (cur << 1))
            ok = 1;
        if (!ok)
            f[cur << 1] = f[cur], f[cur] = 0, cur <<= 1;
        else
            mul(k);
        if (n & (1 << i)) {
            if (!ok)
                f[cur + 1] = f[cur], f[cur] = 0, cur += 1;
            else
                add(k);
        }
    }
    vector<int> R;
    PolyModulo(2 * k + 1, k + 1, f, R);
    REP(i, 0, k - 1)
    f[i] = R[i];
    int ans = 0;
    REP(i, 0, k - 1)
    (ans += 1LL * f[i] * st[i] % mod) %= mod;
    return (ans + mod) % mod;
}
}  // namespace Recurrence
vector<int> a(maxn << 1), P(maxn << 1);
int m, k;
void get_P() {
    int lim = 1;
    while (lim < (k << 1) + 2)
        lim <<= 1;
    vector<int> _A(lim), B(lim);
    REP(i, 0, k - 1)
    _A[i] = Recurrence::st[i];
    REP(i, 1, k)
    B[i] = a[i];
    ntt(_A, lim, 1), ntt(B, lim, 1);
    REP(i, 0, lim - 1)
    _A[i] = 1LL * _A[i] * B[i] % mod;
    ntt(_A, lim, -1);
    REP(i, 0, k - 1)
    P[i] = (1LL * Recurrence::st[i] - _A[i] + mod) % mod;
    REP(i, 0, m)
    mul_Eva::x[i] = k + i;
    mul_Eva::Get_Y(m + 1);
    REP(i, 0, m)
    P[k + i] = mul_Eva::y[i];
}
void get_g() {
    int op = 1, lim = 1;
    while (lim < (m + k + 3))
        lim <<= 1;
    vector<int> h1(lim), h2(lim);
    REP(i, 0, m + 1)
    h1[i] = (1LL * op * Comb::C(m + 1, i) + mod) % mod,
    op = -op;
    REP(i, 0, k - 1)
    h2[i] = a[k - i];
    h2[k] = mod - 1;
    ntt(h1, lim, 1), ntt(h2, lim, 1);
    REP(i, 0, lim - 1)
    Recurrence::g[i] = 1LL * h1[i] * h2[i] % mod;
    ntt(Recurrence::g, lim, -1);
}
void get_st() {
    int lim = 1;
    while (lim < (2 * m + 2 * k + 2))
        lim <<= 1;
    vector<int> B(lim), _f(lim);
    REP(i, 1, k)
    B[i] = (mod - a[i]) % mod;
    B[0] = 1;
    PolyInv(m + k + 1, B, _f);
    ntt(_f, lim, 1), ntt(P, lim, 1);
    REP(i, 0, lim - 1)
    P[i] = 1LL * P[i] * _f[i] % mod;
    ntt(P, lim, -1);
    REP(i, 0, m + k)
    Recurrence::st[i] = P[i];
}
int work(int n) {
    get_P();
    get_g();
    get_st();
    return Recurrence::work(n, m + k + 1);
}
}  // namespace _Rec
