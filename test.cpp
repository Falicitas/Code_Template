#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    vector<int> vec{10, 20, 30};  //10,20,30
    int a = 0;
    int b = accumulate(vec.begin(), vec.end(), a, [](int x, int y) {
        cout << x << " " << y << "\n";
        return x - 2 * y;
    });
    cout << b << "\n";
    //b = -120
    double x = 1.2345;
    cout << fixed << setprecision(10) << x << "\n";
    return 0;
}