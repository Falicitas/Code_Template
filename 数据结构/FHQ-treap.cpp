#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
//放一些基本的函数
int rnd() {
    static int seed = 233;
    return seed = (int)seed * 482711LL % 2147483647;
}

constexpr int N = 1e6 + 5;
int root, pool[N], eid, r1, r2, r3;  // ri是待用的分裂根节点

struct node {
    int fa, ch[2], siz, key;
    i64 val, tag;
    void clear() {
        fa = ch[0] = ch[1] = siz = val = key = tag = 0;
    }
} T[N];

void del(int x) {
    if (!x)
        return;
    T[x].clear(), pool[--eid] = x;
}
int nw() {
    return pool[eid++];
}

void init() {  //记得初始化
    for (int i = 1; i < N; i++)
        pool[i] = i;
    eid = 1;
}

void up(int now) {
    if (!now)
        return;
    T[now].siz = 1;
    if (T[now].fa && T[T[now].fa].ch[0] != now && T[T[now].fa].ch[1] != now)
        T[now].fa = 0;  //在split时可能now节点会作为根节点
    if (T[now].ch[0])
        T[now].siz += T[T[now].ch[0]].siz, T[T[now].ch[0]].fa = now;
    if (T[now].ch[1])
        T[now].siz += T[T[now].ch[1]].siz, T[T[now].ch[1]].fa = now;
}

void do_sth(int now, int tag) {
    if (!now)
        return;
    //对于当前点now的维护值改变
    // now的懒标记进行修改
    //有必要时清空当前点的其它懒标记
}

void down(int now) {
    if (!now)
        return;
    if (T[now].tag) {
        if (T[now].ch[0])
            do_sth(T[now].ch[0], T[now].tag);  //各种操作
        if (T[now].ch[1])
            do_sth(T[now].ch[1], T[now].tag);  //各种操作
        T[now].tag = 0;                        //懒标记已下传
    }
}

int newnode(int x) {
    int u = nw();
    T[u].val = x, T[u].key = rnd(), T[u].siz = 1;
    return u;
}

void split(int now, int k, int& x, int& y)  //按排名分裂
{
    if (!now)
        return (void)(x = y = 0);
    down(now);
    if (T[T[now].ch[0]].siz >= k)
        y = now, split(T[now].ch[0], k, x, T[now].ch[0]);
    else
        x = now, split(T[now].ch[1], k - T[T[now].ch[0]].siz - 1, T[now].ch[1], y);
    up(now);
}

void split(int now, int k, int& x, int& y)  //按值分裂 [-inf,k],[k+1,inf]
{
    if (!now)
        return (void)(x = y = 0);
    down(now);
    if (T[now].val <= k)
        x = now, split(T[now].ch[1], k, T[now].ch[1], y);
    else
        y = now, split(T[now].ch[0], k, x, T[now].ch[0]);
    up(now);
}

int merge(int u, int v)  // u左区间树，v右区间树。调用merge记得给root赋值
{
    if (!u || !v)
        return u | v;
    if (T[u].key < T[v].key) {
        down(u);
        T[u].ch[1] = merge(T[u].ch[1], v);
        up(u);
        return u;
    } else {
        down(v);
        T[v].ch[0] = merge(u, T[v].ch[0]);
        up(v);
        return v;
    }
}

void myclear(int now) {  //在findsiz函数中最先调用
    if (now != root)
        myclear(T[now].fa);  //先回溯父亲节点
    down(now);               //再下传标记
}

int findsiz(int now)  //按排名分裂，回溯找某个节点的排名。有懒标记操作前记得myclear从上至下down
{
    if (!root)
        return 0;
    int res = T[now].siz - T[T[now].ch[1]].siz;
    while (now != root) {
        if (now == T[T[now].fa].ch[1])
            res += T[T[now].fa].siz - T[now].siz;
        now = T[now].fa;
    }
    return res;
}

int kth(int k)  //排名第k小的节点，从1开始。返回节点编号
{
    int now = root;
    while (true) {
        down(now);
        if (T[T[now].ch[0]].siz >= k)
            now = T[now].ch[0];
        else if (k == T[T[now].ch[0]].siz + 1)
            return now;
        else
            k -= T[T[now].ch[0]].siz + 1, now = T[now].ch[1];
    }
}

void insert(int x) {
    split(root, x, r1, r2);
    root = merge(merge(r1, newnode(x)), r2);
}

void erase(int x)  //删一个
{
    split(root, x, r1, r3);
    split(r1, x - 1, r1, r2);
    down(r2);
    root = merge(merge(r1, merge(T[r2].ch[0], T[r2].ch[1])), r3);
    del(r2);
}
