int binary_search(int l,int r)//[l,r)
{
    int res=0,mid;//res初值看题目要求
    while(l<r){
        mid = l + (r - l) / 2;
        if(ok(mid)){
            res = mid;
            l = mid + 1;//也是看题目要求，如果满足条件往大的搜还是小的搜。注意[l,r)
        }
        else{
            r = m;
        }
    }
    return res;
}
