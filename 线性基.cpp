#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

struct Linear_base {
    vector<u64> lb;
    Linear_base() {
        lb = vector<u64>(64);
    }

    void insert(u64 x) {
        for (int i = 63; i >= 0; i--) {
            if (x & (1ull << i)) {
                if (!lb[i]) {
                    lb[i] = x;
                    return;
                } else {
                    x ^= lb[i];
                }
            }
        }
    }

    bool check(u64 x) {  //查看是否存在在一个子集，使异或和为x
        for (int i = 63; i >= 0; i--) {
            if (x & (1ull << i)) {
                if (!lb[i]) {
                    return false;
                } else {
                    x ^= lb[i];
                }
            }
        }
        return true;
    }
    u64 qmax() {
        u64 res = 0;
        for (int i = 63; i >= 0; i--) {
            res = max(res, res ^ lb[i]);
            return res;
        }
    }
    u64 qmin() {
        for (int i = 0; i <= 63; i++) {
            if (lb[i]) {
                return lb[i];
            }
        }
    }

    //剩个找第k大
};
