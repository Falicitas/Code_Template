#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct wqs {
    wqs() {
        int n, k;
        cin >> n >> k;
        vector<int> a(n + 1);  // profit
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        auto check = [&](int c) {  // cost for each deal
            i64 val = 0;           // total_val
            int cnt = 0;           // total_deal_count
            //...
            return make_pair(val, cnt);
        };
        int l = 1,
            r = *max_element(a.begin() + 1, a.end());  // for exactly k, l should be changed due to enumerate all possible k.
        long long ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (auto [val, cnt] = check(mid); cnt >= k) {
                ans = val + (long long)mid * k;  // note: c * k but not c * cnt. Right result in exactly or at most k problem.
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        if (ans == -1) {
            ans = check(0).first;
        }
    }
};