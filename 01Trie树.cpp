#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct trie01 {  //维护数的异或和，从低位往高位维护。贪心的01trie则看情况从高位往低位维护数集
    vector<vector<int>> ch;
    vector<ll> xorv, w;
    int mxH, mxN;
    int M, tot, rt;
    trie01(int mxH_, int mxN_)
        : mxH(mxH_), mxN(mxN_) {  //数的位数，比如x<=1e6,则传21。mxN是插入数的个数
        M = mxH * mxN;
        ch = vector<vector<int>>(M, vector<int>(2));
        w = vector<ll>(M), xorv = w;
        rt = tot = 1;  //初始rt为1
    }
    void maintain(int p) {
        w[p] = xorv[p] = 0;
        if (ch[p][0]) {
            w[p] += w[ch[p][0]];
            xorv[p] ^= xorv[ch[p][0]] << 1;
        }
        if (ch[p][1]) {
            w[p] += w[ch[p][1]];
            xorv[p] ^= (xorv[ch[p][1]] << 1) | (w[ch[p][1]] & 1);
        }
        //w[p] = w[p] & 1;其实不需要，强调01Trie树对存了什么数不在乎，那么w[1]就表示异或和的数有多少个
    }
    void insert(int p, int x, int dep) {
        if (dep >= mxH) {
            w[p]++;
            return;
        }
        if (!ch[p][x & 1]) {
            ch[p][x & 1] = ++tot;
        }
        insert(ch[p][x & 1], x >> 1, dep + 1);
        maintain(p);
    }
    void erase(int p, int x, int dep) {
        if (dep >= mxH) {
            w[p]--;
            return;
        }
        erase(ch[p][x & 1], x >> 1, dep + 1);
        maintain(p);
    }
    void addall(int p)  //全体加1
    {
        swap(ch[p][0], ch[p][1]);
        if (ch[p][0]) {  //原本的ch[p][1]，该进位
            addall(ch[p][0]);
        }
        maintain(p);
    }
    void minusall(int p)  //全体-1
    {
        swap(ch[p][0], ch[p][1]);
        if (ch[p][1]) {  //原本的ch[p][1]，该进位
            minusall(ch[p][1]);
        }
        maintain(p);
    }
    int merge(int a, int b)  //01Trie树的合并，其实所有Trie树均可合并
    {
        if (!a)
            return b;  // 如果 a 没有这个位置上的结点，返回 b
        if (!b)
            return a;  // 如果 b 没有这个位置上的结点，返回 a
        w[a] = w[a] + w[b];
        xorv[a] ^= xorv[b];
        ch[a][0] = merge(ch[a][0], ch[b][0]);
        ch[a][1] = merge(ch[a][1], ch[b][1]);
        return a;
    }
    //rt = merge(a,b);，其中a,b是在同个对象下的两个trie的根
};  // namespace trie01

//单独有个Trie树合并的模板、、
int main() {
    trie01 tr(21, 100000);
    tr.insert(1, 3, 0);
    return 0;
}
