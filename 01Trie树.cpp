namespace trie//01Trie树维护异或和
{
    const int MAXH = 21;//2^20 = 1e6
    const int MAXN = 1e5 + 5;//修改次数
    int ch[MAXN * (MAXH + 1)][2], w[MAXN * (MAXH + 1)], xorv[MAXN * (MAXH + 1)];
    int tot = 0;
    int mknode()
    {
        ++tot;
        ch[tot][1] = ch[tot][0] = w[tot] = xorv[tot] = 0;
        return tot;
    }
    void maintain(int p)
    {
        w[p] = xorv[p] = 0;
        if (ch[p][0]) {
            w[p] += w[ch[p][0]];
            xorv[p] ^= xorv[ch[p][0]] << 1;
        }
        if (ch[p][1]) {
            w[p] += w[ch[p][1]];
            xorv[p] ^= (xorv[ch[p][1]] << 1) | (w[ch[p][1]] & 1);
        }
        //w[p] = w[p] & 1;其实不需要，强调01Trie树对存了什么数不在乎
    }
    void insert(int &p, int x, int dep)
    {
        if (!p) p = mknode();
        if (dep > MAXH) return (void)(w[p]++);
        insert(ch[p][x & 1], x >> 1, dep + 1);
        maintain(p);
    }
    void erase(int p, int x, int dep)
    {
        if (dep > MAXH) return (void)(w[p]--);
        erase(ch[p][x & 1], x >> 1, dep + 1);
        maintain(p);
    }
    void addall(int p)//全体加1
    {
        swap(ch[p][0], ch[p][1]);
        if (ch[p][0]) addall(ch[p][0]);
        maintain(p);
    }
}
//单独有个Trie树合并的模板、、
