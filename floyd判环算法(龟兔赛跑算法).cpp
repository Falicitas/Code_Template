#include <bits/stdc++.h>
using namespace std;
/*
设置一个起点S，找这个起点出发的简单有向图（一个点只有一条出边or没有边）是否存在环
复杂度O(n+m)
*/

struct Floyd {
    vector<int> nex;  //没有出度的点默认-1
    int s;
    Floyd(vector<int> nex_, int s_)
        : nex(nex_), s(s_) {
        int t, h;
        t = h = s;
        do {
            t = nex[t];
            h = nex[h];
            if (h != -1) {
                h = nex[h];
            }
        } while (t != h && h != -1);
        if (h != -1) {    //有环
            int len = 0;  //环长
            do {
                t = nex[t];
                len++;
            } while (t != h);
            t = s;  //从起点s开始
            while (t != h) {
                t = nex[t];
                h = nex[h];
            }
            int P = t;  //P是环和链的交点
        }
    }
};