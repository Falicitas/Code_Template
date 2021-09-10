int lower_bound(int *a,int l,int r,int v)
{
    int m;
    while(l<r){
        m = x + (y - x) / 2;
        if(a[m]>=v) r = m;
        else l = m + 1;
    }
    return l;
}

int upper_bound(int *a,int l,int r,int v)
{
    int m;
    while(l<r){
        m = x + (y - x) / 2;
        if(a[m]<=v) l = m+1;
        else r = m;
    }
    return l;
}
//递减有异曲同工之妙
int lower_bound(int *a,int l,int r,int v)//小于等于v的第一个a[i]
{
    int m;
    while(l<r){
        m = x + (y - x) / 2;
        if(a[m]<=v) r = m;
        else l = m + 1;
    }
    return l;
}

int upper_bound(int *a,int l,int r,int v)
{
    int m;
    while(l<r){
        m = x + (y - x) / 2;
        if(a[m]>=v) l = m + 1;
        else r = m;
    }
    return l;
}
