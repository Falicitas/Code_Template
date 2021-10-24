#include <bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;
struct Bit {
    vector<u64> mi, bit;
    int n, len;
    void reset() { bit = vector<u64>(len); }
    Bit(int n_) {
        n = n_;
        len = n / 64 + 1;
        mi = vector<u64>(64);
        for (int i = 0; i < 64; i++) {
            mi[i] = 1llu << i;
        };
        bit = vector<u64>(len);
    }
    void set1(int x) { bit[x >> 6] |= mi[x & 63]; }
    void set0(int x) { bit[x >> 6] &= ~mi[x & 63]; }
    void flip(int x) { bit[x >> 6] ^= mi[x & 63]; }
    bool operator[](int x) { return (bit[x >> 6] >> (x & 63)) & 1; }
    Bit operator~(void) {
        Bit res(n);
        for (int i = 0; i < len; i++)
            res.bit[i] = ~bit[i];
        return res;
    }
    Bit operator&(const Bit& b) {
        Bit res(n);
        for (int i = 0; i < len; i++)
            res.bit[i] = bit[i] & b.bit[i];
        return res;
    }
    Bit operator|(const Bit& b) {
        Bit res(n);
        for (int i = 0; i < len; i++)
            res.bit[i] = bit[i] | b.bit[i];
        return res;
    }
    Bit operator^(const Bit& b) {
        Bit res(n);
        for (int i = 0; i < len; i++)
            res.bit[i] = bit[i] ^ b.bit[i];
        return res;
    }
    Bit operator&=(const Bit& b) {
        for (int i = 0; i < len; i++)
            bit[i] &= b.bit[i];
        return *this;
    }
    Bit operator|=(const Bit& b) {
        for (int i = 0; i < len; i++)
            bit[i] |= b.bit[i];
        return *this;
    }
    Bit operator^=(const Bit& b) {
        for (int i = 0; i < len; i++)
            bit[i] ^= b.bit[i];
        return *this;
    }
    Bit operator<<(const int t) {
        Bit res(n);
        int high = t >> 6, low = t & 63;
        u64 last = 0;
        for (int i = 0; i + high < len; i++) {
            res.bit[i + high] = (last | (bit[i] << low));
            if (low)
                last = (bit[i] >> (64 - low));
        }
        return res;
    }
    Bit operator>>(const int t) {
        Bit res(n);
        int high = t >> 6, low = t & 63;
        u64 last = 0;
        for (int i = len - 1; i >= high; i--) {
            res.bit[i - high] = last | (bit[i] >> low);
            if (low)
                last = bit[i] << (64 - low);
        }
        return res;
    }
};

//__builtin_popcountll(n)
