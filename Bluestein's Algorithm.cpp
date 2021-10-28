void bluestein(Complex* x, int n, int opt)  //fft版本
{
    static Complex f[maxn << 2], g[maxn << 2];
    int lim = 1;
    while (lim < (3 * n))
        lim <<= 1;
    REP(i, 0, lim - 1)
    f[i] = g[i] = 0;
    REP(i, 0, n - 1)
    f[i] = x[i] * (opt == 1 ? w[(n - 1LL * i * (i - 1) / 2 % n) % n] : w[1LL * i * (i - 1) / 2 % n]);
    reverse(f, f + n);
    REP(i, 0, 2 * n - 1)
    g[i] = (opt == -1 ? w[(n - 1LL * i * (i - 1) / 2 % n) % n] : w[1LL * i * (i - 1) / 2 % n]);
    fft(g, lim, 1), fft(f, lim, 1);
    REP(i, 0, lim - 1)
    f[i] = f[i] * g[i];
    fft(f, lim, -1);
    REP(i, 0, n - 1)
    x[i] = (opt == 1 ? w[(n - 1LL * i * (i - 1) / 2 % n) % n] : w[1LL * i * (i - 1) / 2 % n]) * f[n - 1 + i];
    if (opt == -1)
        REP(i, 0, n - 1)
        x[i] = x[i] / n;
}
