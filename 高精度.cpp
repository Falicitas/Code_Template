//x[1]是最低位，x[x[0]]是最高位
namespace BigInt
{
    const int maxl = 2e6 + 5;
    int temp[maxl];

    void get_x(int x[],int num)//低精转高精
    {
        if(!num){
            x[0] = 1;
            x[1] = 0;
            return ;
        }
        x[0] = 0;
        while(num) x[++x[0]] = num % 10,num /= 10;
    }

    void get_x(int x[],char s[])//s[0]最高位
    {
        x[0] = strlen(s);
        for(int i=x[0],j=0;i;i--,j++) x[i] = s[j] - '0';
    }

    int get_num(int x[])
    {
        int num = 0;
        for(int i=x[0];i;i--) num = num*10 + x[i];
        return num;
    }

    void mul(int x[],int y[],int z[])//高精乘，储存到z[].z[]可填x*
    {
        memset(temp,0,sizeof temp);
        for(int i=1;i<=x[0];i++){
            for(int j=1;j<=y[0];j++) temp[i+j-1]+=x[i]*y[j];
        }
        temp[0] = x[0] + y[0];
        for(int i=1;i<=temp[0];i++){
            if(temp[i]>=10){
                temp[i+1]+=temp[i]/10;
                temp[i]%=10;
            }
        }
        while(temp[0]>1&&temp[temp[0]]==0) temp[0]--;
        memcpy(z,temp,sizeof temp);
    }

    void add(int x[],int y[],int z[])
    {
        memset(temp,0,sizeof temp);
        for(int i=1;i<=x[0]&&i<=y[0];i++) temp[i] = x[i] + y[i];
        for(int i=y[0]+1;i<=x[0];i++) temp[i] = x[i];
        for(int i=x[0]+1;i<=y[0];i++) temp[i] = y[i];
        temp[0] = max(x[0],y[0])+1;
        temp[temp[0]]=0;
        for(int i=1;i<=temp[0];i++){
            if(temp[i]>=10){
                temp[i+1]++;
                temp[i]-=10;
            }
        }
        while(temp[0]>1&&temp[temp[0]]==0) temp[0]--;
        memcpy(z,temp,sizeof temp);
    }

    int div0(int x[],int y,int z[])//低精除高精
    {
        memset(temp,0,sizeof temp);
        ll r=0;
        for(int i=x[0];i>=1;i--){
            r=r*10+x[i];
            if(r>=y){
                temp[i]=r/y;
                r%=y;
            }
            else{
                temp[i]=0;
            }
        }
        temp[0]=x[0];
        while(temp[0]>1&&temp[temp[0]]==0) temp[0]--;
        memcpy(z,temp,sizeof temp);
        return r%y;
    }

    int cmp(int x[],int y[])//x>y:1 x==y:0 x<y:-1
    {
        if(x[0]!=y[0]) return x[0] > y[0] ? 1 : -1;
        else{
            for(int i=x[0];i;i--) if(x[i]!=y[i]) return x[i] > y[i] ? 1 : -1;
            return 0;
        }
    }
}
