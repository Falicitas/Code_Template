int merge(int a, int b)//01Trie树的合并，其实所有Trie树均可合并
{
    if (!a) return b;  // 如果 a 没有这个位置上的结点，返回 b
    if (!b) return a;  // 如果 b 没有这个位置上的结点，返回 a
    /*
    如果 `a`, `b` 都存在，
    那就把 `b` 的信息合并到 `a` 上。
    */
    w[a] = w[a] + w[b];
    xorv[a] ^= xorv[b];
    /* 不要使用 maintain()，
    maintain() 是合并a的两个儿子的信息
    而这里需要 a b 两个节点进行信息合并
    */
    ch[a][0] = merge(ch[a][0], ch[b][0]);
    ch[a][1] = merge(ch[a][1], ch[b][1]);
    return a;
}
