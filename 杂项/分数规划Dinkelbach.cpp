namespace Dinkelbach {
int n;
double r0, k, f;
struct node {
    double a, b;
    bool operator<(const node& rhs) const {
        return a - r0 * b > rhs.a - r0 * rhs.b;
    }
} e[maxn];
int op(double x) {
    return fabs(x) < eps ? 0 : (x > 0 ? 1 : -1);
}
double get_max() {
    r0 = 0;
    while (1) {
        k = f = 0;
        sort(e + 1, e + n + 1);
        REP(i, 1, n) {
            if (e[i].a - r0 * e[i].b > 0)
                k += -e[i].b, f += e[i].a - r0 * e[i].b;
            else
                break;
        }
        if (op(f) == 0)
            break;
        r0 = r0 - f / k;
    }
    return r0;
}
}  // namespace Dinkelbach
