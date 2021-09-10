static char buf[100000],*h=buf,*d=buf;//缓存开大可减少读入时间、、看题目给的空间
#define gc h==d&&(d=(h=buf)+fread(buf,1,100000,stdin),h==d)?EOF:*h++//不能用fread则换成getchar
template<typename T>
inline void read(T&x)
{
    int f = 1;x = 0;
    register char c(gc);
    while(c>'9'||c<'0'){
        if(c == '-') f = -1;
        c=gc;
    }
    while(c<='9'&&c>='0')x=(x<<1)+(x<<3)+(c^48),c=gc;
    x *= f;
}
template<typename T>
void output(T x)
{
    if(x<0){putchar('-');x=~(x-1);}
    static int s[20],top=0;
    while(x){s[++top]=x%10;x/=10;}
    if(!top)s[++top]=0;
    while(top)putchar(s[top--]+'0');
}
//上面的，不建议使用
