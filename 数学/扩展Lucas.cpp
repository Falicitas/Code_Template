namespace _CRT {
const int maxp = 20 + 5;
ll a[maxp], m[maxp], n;
ll ex_gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = ex_gcd(b, a % b, x, y);
    ll temp = x;
    x = y;
    y = temp - a / b * y;
    return d;
}
ll CRT() {
    ll M = 1;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        M *= m[i];
    }
    for (int i = 1; i <= n; i++) {
        ll x, y;
        ll Mi = M / m[i];
        ex_gcd(Mi, m[i], x, y);  //求逆元
        (ans += Mi * x * a[i]) % M;
    }
    ans = (ans % M + M) % M;
    return ans;
}
}  // namespace _CRT

namespace Ex_LC {
struct node {
    int base, k;
    node(int a = 0, int b = 0)
        : base(a), k(b) {}
};
vector<node> fac;
int tnt[10][1 << 20], bit[10][65];  //2^20 > 1e6
void init(int P) {
    fac.clear();
    for (int i = 2; i * i <= P; i++) {
        if (P % i == 0) {
            node q(i, 0);
            while (P % i == 0)
                P /= i, q.k++;
            fac.push_back(q);
            //printf("%d %d\n",q.base,q.k);
        }
    }
    if (P > 1)
        fac.push_back(node(P, 1));
    for (int i = 0; i < fac.size(); i++) {
        bit[i][0] = 1;
        for (int j = 1; j <= fac[i].k; j++)
            bit[i][j] = bit[i][j - 1] * fac[i].base;  //1e6
    }
    for (int i = 0; i < fac.size(); i++) {
        int p_k = bit[i][fac[i].k];
        tnt[i][0] = 1;
        for (int j = 1; j < p_k; j++) {
            tnt[i][j] = tnt[i][j - 1];
            if (j % fac[i].base != 0)
                tnt[i][j] = 1LL * tnt[i][j] * j % p_k;
        }
    }
    _CRT::n = fac.size();
    REP(i, 1, _CRT::n)
    _CRT::m[i] = bit[i - 1][fac[i - 1].k];
}
pair<int, ll> cal(ll n, int i) {
    if (!n)
        return mp(1, 0);
    pair<int, ll> Q = cal(n / fac[i].base, i);
    int p_k = bit[i][fac[i].k], val = (1LL * ((n / p_k) % 2 == 0 ? 1 : -1) * tnt[i][n % p_k] % p_k * x(Q) % p_k + p_k) % p_k;
    return mp(val, n / fac[i].base + y(Q));
}
ll inv(ll a, ll P) {
    ll x, y;
    _CRT::ex_gcd(a, P, x, y);
    return x;
}
ll Ex_lucas(ll m, ll n, int P)  //使用前记得初始化、、
{
    for (int i = 0; i < fac.size(); i++) {
        pair<int, ll> q_m = cal(m, i), q_n = cal(n, i), q_nm = cal(n - m, i);
        ll del = y(q_n) - y(q_m) - y(q_nm);
        int p_k = bit[i][fac[i].k];
        if (del >= fac[i].k)
            _CRT::a[i + 1] = 0;
        else
            _CRT::a[i + 1] = 1LL * bit[i][del] * x(q_n) % p_k * inv(x(q_m), p_k) % p_k * inv(x(q_nm), p_k) % p_k;
    }
    return _CRT::CRT();
}
}  // namespace Ex_LC
