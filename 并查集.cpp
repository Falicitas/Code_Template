struct unionSet
{
    int fa[maxn],size[maxn];
    void init(){REP(i,1,n) fa[i] = i,size[i] = 1;}
    void find(int x) {return x == fa[x] ? x : find(fa[x]);}//一般启发式合并就不需要加路径压缩、、
    void comb(int x, int y)
    {
        int xx = find(x), yy = find(y);
        if (xx == yy) return;
        if (size[xx] > size[yy]) swap(xx, yy);
        fa[xx] = yy;
        size[yy] += size[xx];
    }
};
