struct Link
{
    struct E
    {
        int v,next,w;
    }edge[M];
    int p[N],eid;
    void init_E(){memset(p,-1,sizeof p),eid = 0;}
    void link1(int u,int v,int w){edge[eid].v = v,edge[eid].w = w,edge[eid].next = p[u],p[u] = eid++;}
    void link2(int u,int v,int w){link1(u,v,w),link1(v,u,w);}
};

struct E
{
    int v,next,w;
}edge[M];
int p[N],eid;
void init_E(){memset(p,-1,sizeof p),eid = 0;}
void link1(int u,int v,int w){edge[eid].v = v,edge[eid].w = w,edge[eid].next = p[u],p[u] = eid++;}
void link2(int u,int v,int w){link1(u,v,w),link1(v,u,w);}
