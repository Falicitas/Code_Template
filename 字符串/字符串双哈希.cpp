#include <bits/stdc++.h>
using namespace std;

struct String_Hash {
    string str;
    int n;
    int r1 = 4001, p1 = 50331653, r2 = 2333, p2 = 999999937;
    vector<int> s1, s2, pr1, pr2;
    String_Hash(string str_)
        : str(str_) {
        s1 = vector<int>(n), s2 = vector<int>(n), pr1 = vector<int>(n), pr2 = vector<int>(n);
        for (int i = 0; i < n; i++) {
            pr1[i] = r1, pr2[i] = r2;
            s1[i] = str[i];
            s2[i] = str[i];
            if (i) {
                pr1[i] = (1ll * pr1[i - 1] * r1) % p1;
                pr2[i] = (1ll * pr2[i - 1] * r2) % p2;
                (s1[i] += 1ll * s1[i - 1] * r1 % p1) %= p1;
                if (s1[i] < 0)
                    s1[i] += p1;
                (s2[i] += 1ll * s2[i - 1] * r2 % p2) %= p2;
                if (s2[i] < 0)
                    s2[i] += p2;
            }
        }
    }
    pair<int, int> get_hash(int l, int r) {
        return make_pair(s1[r] - s1[l - 1] * pr1[r - l + 1], s2[r] - s2[l - 1] * pr2[r - l + 1]);
    }
};

int main() {
    return 0;
}