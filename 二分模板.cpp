int binary_search(int l,int r)//[l,r)
{
    int res=0,mid;//res��ֵ����ĿҪ��
    while(l<r){
        mid = l + (r - l) / 2;
        if(ok(mid)){
            res = mid;
            l = mid + 1;//Ҳ�ǿ���ĿҪ�������������������ѻ���С���ѡ�ע��[l,r)
        }
        else{
            r = m;
        }
    }
    return res;
}
