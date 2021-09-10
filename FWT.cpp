void OR(int *f, int opt)
{
    for (int o = 2, k = 1; o <= lim; o <<= 1, k <<= 1)
        for (int i = 0; i < lim; i += o)
            for (int j = 0; j < k; j++)
                (f[i+j+k] += 1LL * f[i+j] * opt % mod) %= mod;
}

void AND(int *f, int opt)
{
    for (int o = 2, k = 1; o <= lim; o <<= 1, k <<= 1)
        for (int i = 0; i < lim; i += o)
            for (int j = 0; j < k; j++)
                (f[i+j] += 1LL * f[i+j+k] * opt % mod) %= mod;
}

void XOR(int *f, int opt)//求逆时x = 1 / 2.不在模系时需要直接修改成 / 2
{   for (int o = 2, k = 1; o <= lim; o <<= 1, k <<= 1)
        for (int i = 0; i < lim; i += o)
            for (int j = 0; j < k; j++)
                (f[i+j] += f[i+j+k]) %= mod,
                f[i+j+k] = (1LL * f[i+j] - f[i+j+k] - f[i+j+k] + 3LL * mod) % mod,
                f[i+j] = 1LL * f[i+j] * opt % mod, f[i+j+k] = 1LL * f[i+j+k] * opt % mod;
                //f[i+j] = 1LL * f[i+j] / (opt == 1 ? 1 : 2), f[i+j+k] = 1LL * f[i+j+k] / (opt == 1 ? 1 : 2);
}
