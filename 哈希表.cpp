namespace HASH
{
    const int NHASH = 100003;//1000003,10000019
    int head[NHASH],eid;
    struct node {int key,next;}N[NHASH];
    void init() {memset(head,-1,sizeof head),eid = 0;}
    int get(int num) {return (num % NHASH + NHASH) % NHASH;}
    void insert(int key)
    {
        int num = get(key);
        for(int i=head[num];i+1;i=N[i].next){
            if(N[i].key==key) return ;//这里按需求写
        }
        N[eid].key = key;
        N[eid].next = head[num];
        head[num] = eid++;
    }
    int search(int key)
    {
        int num = get(key);
        for(int i=head[num];i+1;i=N[i].next){
            if(N[i].key==key) return true;
        }
        return false;
    }
}
