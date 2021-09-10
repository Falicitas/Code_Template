#include <bits/stdc++.h>
using namespace std;

void GetNext(char T[], int m, int next[])
{
    int a = 0, p = 0;
    next[0] = m;

    for (int i = 1; i < m; i++){
        if (i >= p || i + next[i - a] >= p){
            if (i >= p)
                p = i;

            while (p < m && T[p] == T[p - i])
                p++;

            next[i] = p - i;
            a = i;
        }
        else
            next[i] = next[i - a];
    }
}

/* ��� extend[] */
void GetExtend(char S[], int n, char T[], int m, int extend[], int next[])
{
    int a = 0, p = 0;
    GetNext(T, m, next);

    for (int i = 0; i < n; i++)
    {
        if (i >= p || i + next[i - a] >= p) // i >= p �����ã��ٸ��������ӣ�S �� T ��һ�ַ���ͬ
        {
            if (i >= p)
                p = i;

            while (p < n && p - i < m && S[p] == T[p - i])
                p++;

            extend[i] = p - i;
            a = i;
        }
        else
            extend[i] = next[i - a];
    }
}

int main()
{
    int next[100];
    int extend[100];
    char S[100], T[100];
    int n, m;

    while(scanf("%s%s",S,T)==2)
    {
        n = strlen(S);
        m = strlen(T);
        GetExtend(S, n, T, m, extend, next);

        // ��ӡ next
        cout << "next:   ";
        for (int i = 0; i < m; i++)
            cout << next[i] << " ";

        // ��ӡ extend
        cout << "\nextend: ";
        for (int i = 0; i < n; i++)
            cout << extend[i] << " ";

        cout << endl << endl;
    }
    return 0;
}
