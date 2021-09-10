//带高精度玩、、
namespace Ex_Euler
{
    using namespace BigInt;
    int Phi[maxl];

    int euler_phi(int n) {
        int m = int(sqrt(n + 0.5));
        int ans = n;
        for (int i = 2; i <= m; i++)
            if (n % i == 0) {
                ans = ans / i * (i - 1);
            while (n % i == 0) n /= i;
        }
        if (n > 1) ans = ans / n * (n - 1);
        return ans;
    }

    int qp(ll base,ll n,int mod)
    {
        ll res = 1;
        while(n){
            if(n&1) (res *= base) %= mod;
            (base *= base) %= mod;
            n>>=1;
        }
        return (int) res;
    }
    int buffer[maxl];
    int Ex(int base[],int n[],int mod)
    {
        int phi = euler_phi(mod);
        int Base = div0(base,mod,buffer),N;//只要取模的余数，不改变被除数
        get_x(Phi,phi);
        if(cmp(n,Phi)>=0) N = div0(n,phi,buffer) + phi;
        else N = get_num(n);
        return qp(Base,N,mod);
    }
}
