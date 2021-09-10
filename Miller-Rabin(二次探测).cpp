typedef long long ll;

mt19937_64 rnd(233);

ll qp(ll base,ll n,ll mod)
{
    ll res = 1;
    while(n){
        if(n&1) res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}

const int maxnS = 20;
bool miller_rabin(ll n)
{
    if(n == 2 || n == 3 || n == 5 || n == 7 || n == 11)    return true;
    if(n == 1 || !(n%2) || !(n%3) || !(n%5) || !(n%7) || !(n%11))    return false;

    ll x, pre, u;
    int i, j, k = 0;
    u = n - 1;    //要求x^u % n

    while(!(u&1)) {    //如果u为偶数则u右移，用k记录移位数
        k++; u >>= 1;
    }

    for(i = 0; i < maxnS; ++i) {    //进行S次测试
        x = rnd()%(n-2) + 2;    //在[2, n)中取随机数
        if((x%n) == 0)    continue;

        x = qp(x, u, n);    //先计算(x^u) % n，
        pre = x;
        for(j = 0; j < k; ++j) {    //把移位减掉的量补上，并在这地方加上二次探测
            x = x * x % n;
            if(x == 1 && pre != 1 && pre != n-1)    return false;    //二次探测定理，这里如果x = 1则pre 必须等于 1，或则 n-1否则可以判断不是素数
            pre = x;
        }
        if(x != 1)    return false;    //费马小定理
    }
    return true;
}
