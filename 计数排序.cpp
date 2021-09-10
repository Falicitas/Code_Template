int a[maxn],cntarr[maxx-minn+1],newarr[maxn];

void count_sort()
{
    int minn = inf,maxx = -inf;
    REP(i,1,n) minn = min(minn,a[i]),maxx = max(maxx,a[i]);
    REP(i,1,n){
        cntarr[a[i]-minn]++;
    }
    REP(i,1,maxx-minn){
        cntarr[i] += cntarr[i-1];
    }
    _REP(i,n,1){
        newarr[cntarr[a[i]-minn]] = a[i];
        cntarr[a[i]-minn]--;
    }
}
