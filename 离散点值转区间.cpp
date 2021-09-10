for (int i = 1; i <= n; i++) scanf("%d%d", &seg[i].l, &seg[i].r), --seg[i].l;
sort(seg + 1, seg + n + 1, cmp);

int top = 0;
for (int i = 1; i <= n; i++)
    table[++top] = seg[i].l, table[++top] = seg[i].r;
sort(table + 1, table + top + 1);
top = unique(table + 1, table + top + 1) - table - 1;

for (int i = 1; i <= n; i++){
    seg[i].l = lower_bound(table + 1, table + top + 1, seg[i].l) - table;
    seg[i].r = lower_bound(table + 1, table + top + 1, seg[i].r) - table;
    for (int j = seg[i].l + 1; j <= seg[i].r; j++) table[j] - table[j-1];//遍历区间对应离散块
}
