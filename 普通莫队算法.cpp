void add(int x)
{
    cnt[x]++;
    if(cnt[x]==1)ans++;
}

void del(int x)
{

    cnt[x]--;
    if(cnt[x]==0)ans--;
}

struct node
{
    int l,r,id;
    bool operator<(const node&rhs) const
    {
        return (l / S) == (rhs.l / S) ? (((l / S) & 1) ? r < rhs.r : r > rhs.r) : ((l / S) < (rhs.l / S));
    }
}q[maxn];


//在获取答案时：一般init l = 1,r = 0。cnt初始视情况而定
while(l>q[i].l) add(a[--l]);
while(r<q[i].r) add(a[++r]);
while(l<q[i].l) del(a[l++]);
while(r>q[i].r) del(a[r--]);

S = ceil(n / sqrt(2.0 * m / 3));
