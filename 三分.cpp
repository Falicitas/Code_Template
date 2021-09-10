int three_devide(int l,int r) //ÕÒÏÂÍ¹µã£¬Ë«±Õ
{
    while(r - l > 4)
    {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        if(f(m1) > f(m2)) l = m1;
        else r = m2;
    }
    int ans = inf;
    while(l<=r) ans = min(ans,f(l++));
    return ans;
}

double three_devide(double low,double up)
{
    double m1,m2;
    while(up-low>=eps)
    {
        m1=low+(up-low)/3;
        m2=up-(up-low)/3;
        if(f(m1)<=f(m2))
            low=m1;
        else
            up=m2;
    }
    return (m1+m2)/2;
}
