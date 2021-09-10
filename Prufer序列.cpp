vector<int> G[N];
vector<int> fa;

void dfs(int v) {
  for(int u:G[v]){
    if (u != fa[v]) fa[u] = v, dfs(u);
  }
}

vector<int> prufer_code()
{
  fa.resize(n+1),fa[n] = 0;
  dfs(n);//保证根不会被当做被删点。间接保证被删的都是除根节点以外的点
  int ptr = 0;
  vector<int> deg(n+1);
  REP(i,1,n){
    deg[i] = G[i].size();
    if(deg[i]==1&&ptr==0) ptr = i;//要跑完循环，否则deg会错
  }
  vector<int> code(n - 1);
  int leaf = ptr;
  REP(i,1,n-2){
    int nxt = fa[leaf];
    code[i] = nxt;
    if(--deg[nxt]==1&&nxt<ptr){
      leaf = nxt;
    }
    else{
      ptr++;
      while(deg[ptr]!=1) ptr++;
      leaf = ptr;
    }
  }
  return code;
}

vector<pair<int, int>> prufer_decode(vector<int> const& code)
{
  int n = code.size() + 2;
  vector<int> deg(n+1, 1);deg[0] = 0;
  for(int i:code) deg[i]++;
  int ptr = 1;
  while (deg[ptr] != 1) ptr++;
  int leaf = ptr;
  vector<pair<int, int>> edges;
  for (int v:code) {
    edges.emplace_back(leaf, v);
    if(--deg[v]==1&&v<ptr){
      leaf = v;
    }
    else{
      ptr++;
      while(deg[ptr]!=1) ptr++;
      leaf = ptr;
    }
  }
  edges.emplace_back(leaf,n);
  return edges;
}
