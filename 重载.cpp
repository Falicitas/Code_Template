#include <bits/stdc++.h>
using namespace std;

/*任何的重载方式，都优先推荐lambda重载。只有在简单的环境下才使用如下的非成员函数重载*/

auto cmp = [&](const pair<int, int>& x, const pair<int, int>& y) {
    return x.second < y.second;
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

/*自定义类有两种重载方式：一个是成员函数重载；一个是非成员函数重载*/

//成员函数重载

struct node {
    int len, u;
    bool operator<(const node& rhs) {
        return len < rhs.len;
    }
};

//非成员函数重载

bool operator<(const node& x, const node& y) {
    return x.len < y.len;
}

/*非自定义类仅有一种重载方式：非成员函数重载*/

bool operator<(const pair<int, int>& x, const pair<int, int>& y) {
    return x.first < y.first;
}
