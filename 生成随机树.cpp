#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("out.txt", "w", stdout);
    srand(time(0));
    int n = 100;
    cout << n << endl;
    for (int i = 2; i <= n; i++) {
        int x = rand() % (i - 1) + 1;
        cout << x << " " << i << "\n";
    }
}
