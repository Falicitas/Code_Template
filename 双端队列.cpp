template<typename T>
struct Deque//用前clear
{
    int siz,r,f;
    T N[maxn];
    T front() {return N[f];}
    T back() {return N[r];}
    void clear() {siz = 0,r = maxn - 1,f = 0;}
    void push_back(T e) {r = (r + 1) % maxn,siz++,N[r] = e;}
    void push_front(T e) {f = (f - 1 + maxn) % maxn,siz++,N[f] = e;}
    bool pop_front()
    {
        if(siz==0) return false;
        f++,siz--;
        return true;
    }
    bool pop_back()
    {
        if(siz==0) return false;
        r--,siz--;
        return true;
    }
    int size() {return siz;}
    bool empty() {return siz==0;}
}deq;
