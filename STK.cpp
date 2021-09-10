template<typename T>
struct STK{
    int top;
    T s[maxn];
    void Reset(){top=0;}
    void Push(T i){
        s[++top]=i;
    }
    void pop()
    {
        if(top>0) top--;
    }
    T top()
    {
        return s[top];
    }
}S;
