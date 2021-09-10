ll lb[64];
bool flag;//flag等于1，相当于可以选至少一个数异或使得异或结果为0
void ins(ll x){
    _REP(i,62,0) if(x&(1ll<<i))
        if(!lb[i]){lb[i]=x;return;}
        else x^=lb[i];
    flag=true;
}
bool check(ll x){
    _REP(i,62,0) if(x&(1ll<<i))
        if(!lb[i])return false;
        else x^=lb[i];
    return true;
}
ll qmax(ll res=0){
    _REP(i,62,0) res=max(res,res^lb[i]);
    return res;
}
ll qmin(){
    if(flag)return 0;
    REP(i,0,62) if(lb[i])return lb[i];
}
ll query(ll k){//第k小。实际上有0要转成第0~2^cnt-1小所以要减一
    ll res=0;int cnt=0;
    k-=flag;if(!k) return 0;
    REP(i,0,62){//简化处理
        _REP(j,i-1,0) if(lb[i]&(1ll<<j)) lb[i]^=lb[j];
        if(lb[i]) tmp[cnt++]=lb[i];
    }
    if(k>=(1ll<<cnt))return -1;
    REP(i,0,cnt-1) if(k&(1ll<<i)) res^=tmp[i];
    return res;
}
