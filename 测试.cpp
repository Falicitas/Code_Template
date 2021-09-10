#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 50000, M = N * 2 + 7;

int n, m, end_x, end_y;
int g[20][20], q[2][N], cnt[N];
int h[2][M];
LL v[2][M];

int find(int cur, int x)
{
    int t = x % M;
    while (h[cur][t] != -1 && h[cur][t] != x)
        if ( ++ t == M)
            t = 0;
    return t;
}

void insert(int cur, int state, LL w)
{
    int t = find(cur, state);
    if (h[cur][t] == -1)
    {
        h[cur][t] = state, v[cur][t] = w;
        q[cur][ ++ cnt[cur]] = t;
    }
    else v[cur][t] += w;
}

int get(int state, int k)  // 求第k个格子的状态，四进制的第k位数字
{
    return state >> k * 2 & 3;
}

int set(int k, int v)  // 构造四进制的第k位数字为v的数
{
    return v * (1 << k * 2);
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i ++ )
    {
        char str[20];
        scanf("%s", str + 1);
        for (int j = 1; j <= m; j ++ )
            if (str[j] == '.')
            {
                g[i][j] = 1;
                end_x = i, end_y = j;
            }
    }

    LL res = 0;
    memset(h, -1, sizeof h);
    int cur = 0;
    insert(cur, 0, 1);
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = 1; j <= cnt[cur]; j ++ )
            h[cur][q[cur][j]] <<= 2;
        for (int j = 1; j <= m; j ++ )
        {
            int last = cur;
            cur ^= 1, cnt[cur] = 0;
            memset(h[cur], -1, sizeof h[cur]);
            for (int k = 1; k <= cnt[last]; k ++ )
            {
                int state = h[last][q[last][k]];
                LL w = v[last][q[last][k]];
                int x = get(state, j - 1), y = get(state, j);
                if (!g[i][j])
                {
                    if (!x && !y) insert(cur, state, w);
                }
                else if (!x && !y)
                {
                    if (g[i + 1][j] && g[i][j + 1])
                        insert(cur, state + set(j - 1, 1) + set(j, 2), w);
                }
                else if (!x && y)
                {
                    if (g[i][j + 1]) insert(cur, state, w);
                    if (g[i + 1][j]) insert(cur, state + set(j - 1, y) - set(j, y), w);
                }
                else if (x && !y)
                {
                    if (g[i][j + 1]) insert(cur, state - set(j - 1, x) + set(j, x), w);
                    if (g[i + 1][j]) insert(cur, state, w);
                }
                else if (x == 1 && y == 1)
                {
                    for (int u = j + 1, s = 1;; u ++ )
                    {
                        int z = get(state, u);
                        if (z == 1) s ++ ;
                        else if (z == 2)
                        {
                            if ( -- s == 0)
                            {
                                insert(cur, state - set(j - 1, x) - set(j, y) - set(u, 1), w);
                                break;
                            }
                        }
                    }
                }
                else if (x == 2 && y == 2)
                {
                    for (int u = j - 2, s = 1;; u -- )
                    {
                        int z = get(state, u);
                        if (z == 2) s ++ ;
                        else if (z == 1)
                        {
                            if ( -- s == 0)
                            {
                                insert(cur, state - set(j - 1, x) - set(j, y) + set(u, 1), w);
                                break;
                            }
                        }
                    }
                }
                else if (x == 2 && y == 1)
                {
                    insert(cur, state - set(j - 1, x) - set(j, y), w);
                }
                else if (i == end_x && j == end_y)
                    res += w;
            }
        }
    }

    cout << res << endl;

    return 0 ;
}

作者：yxc
链接：https://www.acwing.com/activity/content/code/content/624799/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
