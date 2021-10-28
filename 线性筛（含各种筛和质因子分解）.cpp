using i64 = long long;
bool isp[10000005];
int phi[10000005];
int prime[10000005];
int p;
void InitPhi() {  //phi(x)
    int N = 10000005;
    phi[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!isp[i])
            prime[++p] = i, phi[i] = i - 1;
        for (int j = 1; j <= p && i * prime[j] < N; j++) {
            isp[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}

int d[10000005];
int num[10000005];
void InitD() {  //求i约数个数d[i],num[i]为最小质因子个数
    int N = 10000005;
    d[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!isp[i])
            isp[i] = 1, prime[++p] = i, d[i] = 2, num[i] = 1;
        for (int j = 1; j <= p && i * prime[j] < N; ++j) {
            isp[prime[j] * i] = 1;
            if (i % prime[j] == 0) {
                num[i * prime[j]] = num[i] + 1;
                d[i * prime[j]] = d[i] / num[i * prime[j]] * (num[i * prime[j]] + 1);
                break;
            } else {
                num[i * prime[j]] = 1;
                d[i * prime[j]] = d[i] * 2;
            }
        }
    }
}

i64 g[10000005], f[10000005];

void InitF() {  //求i约数和f[i],g[i]为最小质因子p的1+p+p^2+...+p^k
    int N = 10000005;
    g[1] = f[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!isp[i])
            isp[i] = 1, prime[++p] = i, g[i] = i + 1, f[i] = i + 1;
        for (int j = 1; j <= p && i * prime[j] < N; ++j) {
            isp[prime[j] * i] = 1;
            if (i % prime[j] == 0) {
                g[i * prime[j]] = g[i] * prime[j] + 1;
                f[i * prime[j]] = f[i] / g[i] * g[i * prime[j]];
                break;
            } else {
                g[i * prime[j]] = 1 + prime[j];
                f[i * prime[j]] = f[i] * g[i * prime[j]];
            }
        }
    }
}

int mu[10000005];

void InitMu()  //求莫比乌斯函数
{
    int N = 10000005;
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!isp[i]) {
            prime[++p] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= p && i * prime[j] < N; j++) {
            isp[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                mu[i * prime[j]] = 0;
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}
