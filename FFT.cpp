const double PI = acos(-1.0);
struct Complex
{
    double x, y;
    Complex (double _x = 0.0, double _y = 0.0) {x = _x,y = _y;}
    Complex operator-(const Complex &b) const {return Complex(x - b.x, y - b.y);}
    Complex operator+(const Complex &b) const {return Complex(x + b.x, y + b.y);}
    Complex operator*(const Complex &b) const {return Complex(x * b.x - y * b.y, x * b.y + y * b.x);}
};
void fft(Complex *a,int N,int f){
    int i,j,t,k;
    for(i=1,j=0;i<N-1;i++){
        for(t=N;j^=(t>>=1),~j&t;);
        if(i<j)
            swap(a[i],a[j]);
    }
    for(i=1;i<N;i<<=1){
        Complex wn(cos(PI/i),f*sin(PI/i));
        t=i<<1;
        for(j=0;j<N;j+=t){
            Complex w(1,0);
            for(k=0;k<i;k++,w=w*wn){
                Complex x(a[j+k]),y(w*a[j+i+k]);
                a[j+k]=x+y;
                a[j+i+k]=x-y;
            }
        }
    }
    if(f==-1){
        for(i=0;i<N;i++)
            a[i]=a[i]/N;
    }
}

//下面的fft有点问题，暂无修改


namespace FFT
{
    const double PI = acos(-1.0);
    struct Complex
    {
        double x, y;
        Complex (double _x = 0.0, double _y = 0.0) {x = _x,y = _y;}
        Complex operator-(const Complex &b) const {return Complex(x - b.x, y - b.y);}
        Complex operator+(const Complex &b) const {return Complex(x + b.x, y + b.y);}
        Complex operator*(const Complex &b) const {return Complex(x * b.x - y * b.y, x * b.y + y * b.x);}
    };
    int rev[N<<2];
    void change(vector<Complex> &x, int len)
    {
        int bit = 0;
        while((1<<bit)<len) bit++;
        REP(i,1,len-1){
            rev[i] = (rev[i>>1] >> 1) | ((i & 1) << (bit - 1));
            if (i<rev[i]) swap(x[i],x[rev[i]]);
        }
    }
    void fft(vector<Complex> &x, int lim, int opt)
    {
        change(x, lim);
        for (int h = 2; h <= lim; h <<= 1){
            Complex wn(cos(2 * PI / h), sin(opt * 2 * PI / h));
            for (int j = 0; j < lim; j += h){
                Complex w(1, 0);
                for (int k = j; k < j + h / 2; k++){
                    Complex u = x[k];
                    Complex t = w * x[k + h / 2];
                    x[k] = u + t;
                    x[k + h / 2] = u - t;
                    w = w * wn;
                }
            }
        }
        if (opt == -1){
            for (int i = 0; i < lim; i++){
                x[i].x /= lim;
            }
        }
    }
}
using FFT::fft;
using FFT::Complex;

/*

const int MAXN = 200020;
Complex x1[MAXN], x2[MAXN];
char str1[MAXN / 2], str2[MAXN / 2];
int sum[MAXN];

int main()
{
    while (scanf("%s%s", str1, str2) == 2)
    {
        int len1 = strlen(str1);
        int len2 = strlen(str2);
        int len = 1;
        while (len < len1 * 2 || len < len2 * 2) len <<= 1;
        for (int i = 0; i < len1; i++)
            x1[i] = Complex(str1[len1 - 1 - i] - '0', 0);
        for (int i = len1; i < len; i++)
            x1[i] = Complex(0, 0);
        for (int i = 0; i < len2; i++)
            x2[i] = Complex(str2[len2 - 1 - i] - '0', 0);
        for (int i = len2; i < len; i++)
            x2[i] = Complex(0, 0);
        fft(x1, len, 1);
        fft(x2, len, 1);
        for (int i = 0; i < len; i++)
            x1[i] = x1[i] * x2[i];
        fft(x1, len, -1);
        for (int i = 0; i < len; i++)
            sum[i] = int(x1[i].x + 0.5);
        for (int i = 0; i < len; i++)
        {
            sum[i + 1] += sum[i] / 10;
            sum[i] %= 10;
        }
        len = len1 + len2 - 1;
        while (sum[len] == 0 && len > 0)
            len--;
        for (int i = len; i >= 0; i--)
            printf("%c", sum[i] + '0');
        printf("\n");
    }
    return 0;
}
