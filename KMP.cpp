#include <bits/stdc++.h>
using namespace std;

/*
pi(i)表示[0,i]中最长的真前缀相同真后缀（即不含原串）
*/

vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    string s;
    cin >> s;
    prefix_function(s);
    return 0;
}
