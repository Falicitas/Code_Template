ull mi[200];
void bit_init(){REP(i,0,63) mi[i] = 1llu << i;}
struct Bit {
	ull bit[15626]; int len = 15626;
	void reset() {memset(bit, 0, sizeof(bit));}
	Bit() {memset(bit, 0, sizeof(bit));}
	void set1(int x) { bit[x>>6] |= mi[x&63];}
	void set0(int x) { bit[x>>6] &= ~mi[x&63];}
	void flip(int x) { bit[x>>6] ^= mi[x&63];}
	bool operator [](int x) {return (bit[x>>6] >> (x&63)) & 1;}
	Bit operator ~(void){Bit res;REP(i,0,len-1) res.bit[i] = ~bit[i];return res;}
	Bit operator &(const Bit &b){Bit res;REP(i,0,len-1) res.bit[i] = bit[i] & b.bit[i];return res;}
	Bit operator |(const Bit &b){Bit res;REP(i,0,len-1) res.bit[i] = bit[i] | b.bit[i];return res;}
    Bit operator ^(const Bit &b){Bit res;REP(i,0,len-1) res.bit[i] = bit[i] ^ b.bit[i];return res;}
    Bit operator &=(const Bit &b){REP(i,0,len-1) bit[i] &= b.bit[i];return *this;}
    Bit operator |=(const Bit &b){REP(i,0,len-1) bit[i] |= b.bit[i];return *this;}
	Bit operator ^=(const Bit &b){REP(i,0,len-1) bit[i] ^= b.bit[i];return *this;}
	Bit operator << (const int t)
	{
		Bit res; int high = t >> 6, low = t & 63;
		ull last = 0;
		for (int i = 0;i + high < len; i++) {res.bit[i + high] = (last | (bit[i] << low));if (low) last = (bit[i] >> (64 - low));}
		return res;
	}
    Bit operator >> (const int t)
    {
		Bit res; int high = t >> 6, low = t & 63;
		ull last = 0;
		for (int i = len - 1;i >= high; i--) {res.bit[i - high] = last | (bit[i] >> low);if (low) last = bit[i] << (64 - low);}
		return res;
	}
};

//__builtin_popcountll(n)
