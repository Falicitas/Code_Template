# wqs 二分

这里抽象地给出 wqs 二分适用的题目类型：

> 给定 $n$ 个物品，我们需要在其中**恰好**选择 $k$ 个（或至多 k 个，至少可能能做，但没遇到），并且需要最大化收益。设对应的收益为 $g_k$，那么需要满足**在最大化收益的前提下，每多选择一个物品，额外产生的收益是单调递减的**，也就是 $g_{k+1}-g_k\le g_k - g_{k-1}$。同时，如果我们**对物品的选择数量没有限制**，即 $k$ 不存在，那么我们应当能够快速地计算出最大的收益，以及达到最大的收益需要选择的物品数量。

------

设**恰好完成** ![[公式]](https://www.zhihu.com/equation?tex=k) **笔交易时**，能够获取的最大收益为 ![[公式]](https://www.zhihu.com/equation?tex=g_k) ，那么

![[公式]](https://www.zhihu.com/equation?tex=g_%7Bk%2B1%7D-g_k+%5Cleq+g_k-g_%7Bk-1%7D%5C%5C)

是成立的。

可以这样想：每额外增加一笔交易 ![[公式]](https://www.zhihu.com/equation?tex=g_k+%5Cto+g_%7Bk%2B1%7D)，那么这一笔交易一定不会比上一笔交易 ![[公式]](https://www.zhihu.com/equation?tex=g_%7Bk-1%7D+%5Cto+g_k) 产生的收益高，否则就可以交换这两笔交易，使得 ![[公式]](https://www.zhihu.com/equation?tex=g_k) 更大，那么就与 ![[公式]](https://www.zhihu.com/equation?tex=g_k) 是恰好完成 ![[公式]](https://www.zhihu.com/equation?tex=k) 笔交易时的最大收益这个事实相矛盾了。

如果把 ![[公式]](https://www.zhihu.com/equation?tex=%28k%2C+g_k%29) 看成平面直角坐标系上的点，那么这些点就组成了一个上凸壳，如下图所示：

![img](https://pic4.zhimg.com/80/v2-e7e48ac8851067558cb10101b9b388cf_720w.jpg)

虽然并不知道 ![[公式]](https://www.zhihu.com/equation?tex=g_k) 的值到底是多少（否则就可以直接返回正确答案了）。但是感性知道 ![[公式]](https://www.zhihu.com/equation?tex=%28k%2C+g_k%29) 对应的图像的形状。wqs 二分的妙处就在于此，通过对**斜率进行二分**，求出 ![[公式]](https://www.zhihu.com/equation?tex=g_k) 的值（往左斜率增大)。

![img](https://pic4.zhimg.com/80/v2-bed3693e16a117a5ffa4f7b1e924e363_720w.jpg)

假设枚举了某斜率 ![[公式]](https://www.zhihu.com/equation?tex=c) ，如上图所示，画出所有经过 ![[公式]](https://www.zhihu.com/equation?tex=%28k%2C+g_k%29) 并且斜率为 ![[公式]](https://www.zhihu.com/equation?tex=c) 的直线。斜率为 ![[公式]](https://www.zhihu.com/equation?tex=c) 的直线与上凸壳相切在了 ![[公式]](https://www.zhihu.com/equation?tex=k%27%3D4) 的绿色点位置，根据上凸壳的性质，经过绿色点的这条直线与 ![[公式]](https://www.zhihu.com/equation?tex=y) 轴的截距也是所有斜率为 ![[公式]](https://www.zhihu.com/equation?tex=c) 的直线中最大的。

那么这个「截距」代表了什么？对于经过 ![[公式]](https://www.zhihu.com/equation?tex=%28k%2C+g_k%29) 而言，经过它并且斜率为 ![[公式]](https://www.zhihu.com/equation?tex=c) 的直线在 ![[公式]](https://www.zhihu.com/equation?tex=y) 轴上的截距是

![[公式]](https://www.zhihu.com/equation?tex=g_k+-+k+%5Ccdot+c%5C%5C)

而 ![[公式]](https://www.zhihu.com/equation?tex=g_k) 恰好包含了恰好 ![[公式]](https://www.zhihu.com/equation?tex=k) 笔交易带来的收益，如果将这个收益减去 ![[公式]](https://www.zhihu.com/equation?tex=k+%5Ccdot+c) ，那么就可以看做是**每一笔交易都包含了 ![[公式]](https://www.zhihu.com/equation?tex=c) 的手续费**。当每一笔交易都包含了 ![[公式]](https://www.zhihu.com/equation?tex=c) 的手续费时，如果规定了恰好进行 ![[公式]](https://www.zhihu.com/equation?tex=k) 笔交易，那么最大的收益就是经过 ![[公式]](https://www.zhihu.com/equation?tex=%28k%2C+g_k%29) 并且斜率为 ![[公式]](https://www.zhihu.com/equation?tex=c) 的直线在 ![[公式]](https://www.zhihu.com/equation?tex=y) 轴上的截距。此时，![[公式]](https://www.zhihu.com/equation?tex=%28k%27%2C+g_k%27%29) 对应的截距是大，因此**如果我们不限制进行的交易次数，那么最终得到的最大收益就是** ![[公式]](https://www.zhihu.com/equation?tex=g_k%27-k%27+%5Ccdot+c) 。

因此，**如果选择了一个合适的斜率** ![[公式]](https://www.zhihu.com/equation?tex=c%27) **，使得其与上凸壳相切在了某一个我们需要的** ![[公式]](https://www.zhihu.com/equation?tex=%28k%2C+g_k%29) **的位置（例如本题中给出的参数** ![[公式]](https://www.zhihu.com/equation?tex=k) **），这样我们就可以在** ![[公式]](https://www.zhihu.com/equation?tex=O%28n%29) **的时间内直接求出不限制交易次数的最大收益，并且我们知道它实际上就是交易了** ![[公式]](https://www.zhihu.com/equation?tex=k) **次**。

## 至多 k 次交易

照此方法确实能通过二分来求出满足恰好为 $k$ 的约束的 $g_k$。而若限制的是最多进行 ![[公式]](https://www.zhihu.com/equation?tex=k) 次交易，而不是恰好进行 ![[公式]](https://www.zhihu.com/equation?tex=k) 次交易，那么上面的方法还适用吗？

对于最多 $k$ 次交易，分两种情况进行讨论：

- 如果 ![[公式]](https://www.zhihu.com/equation?tex=%28k%2C+g_k%29) 所在的位置是上凸壳的左半部分（即斜率大于 ![[公式]](https://www.zhihu.com/equation?tex=0) 的部分），那么我们就可以使用上面的方法得到答案，这是因为最优的答案一定是进行 ![[公式]](https://www.zhihu.com/equation?tex=k) 次交易的；
- 如果 ![[公式]](https://www.zhihu.com/equation?tex=%28k%2C+g_k%29) 所在的位置是上凸壳的右半部分（即斜率小于等于 ![[公式]](https://www.zhihu.com/equation?tex=0) 的部分），那么我们通过二分是没有办法找到斜率 ![[公式]](https://www.zhihu.com/equation?tex=c) 并且计算出对应的 ![[公式]](https://www.zhihu.com/equation?tex=%28k%2C+g_k%29) 的（因为对于至多选 $k$ 的问题，若 $k$ 取上凸壳的右半部分，显然比选上凸壳的极点要劣。故二分的斜率的下界正的开始)。

我们规定手续费二分查找的下界为 1（可能有疑问为什么不选0.00001，由于一般问题的权值为整数，对于原本正整数-0.00001还是正整数可以选，所以选最小正整数 1。另外整数价值有个性质，即一个物品的价值 >=1 才选，那么 i 到 i + 1 的斜率至少为 1），这样当 ![[公式]](https://www.zhihu.com/equation?tex=%28k%2C+g_k%29) 所在的位置是上凸壳的右半部分时，二分查找就会失败。二分查找的上界可以设定得宽松一些，由于每一条线段的斜率都不会超过数组 ![[公式]](https://www.zhihu.com/equation?tex=%5Ctextit%7Bprices%7D) 中给定价格的最大值，因此可以将上界设定为这个最大值。如果二分查找失败，那么说明最大收益对应的交易次数是严格小于题目中给定的 ![[公式]](https://www.zhihu.com/equation?tex=k) 的，这就说明**交易次数的限制并不是瓶颈**，因此可以直接令手续费为 0，求一次结果。

## 价值为 0 的商品

不过可能会有另外一种情况导致二分查找失败，即如果上凸壳上有若干连续的且斜率相等的线段，例如下图所示，那么在查找到该斜率 ![[公式]](https://www.zhihu.com/equation?tex=c) 时，我们只会计算出一个对应的 ![[公式]](https://www.zhihu.com/equation?tex=k) 值（例如图中绿色的点），然而实际上是有不止一个 ![[公式]](https://www.zhihu.com/equation?tex=k) 值是满足要求的 （例如图中红色的点），这些点对应的截距都是最大值，那么如果题目中给定的 ![[公式]](https://www.zhihu.com/equation?tex=k) 对应的是红色的点，那么二分查找就会失败。

![img](https://pic4.zhimg.com/80/v2-7e12615d7369f49c66b4c0dbd3b29e4f_720w.jpg)

对于这种情况，我们可以在求解子问题时，尽可能地多进行交易，求解出最大的那个 ![[公式]](https://www.zhihu.com/equation?tex=k) 值（对于恰好为 k 和至多为 k 的问题都适用，对于恰好为 k 的，当选的物品 >= k 了就更新，因为一旦 >= k，那么肯定可以增大斜率枚举到恰好为 k）。从本质上来说，红色的点与绿色的点之间实际上只是相差了若干笔收益为 0 的交易而已（即取决于多选了几个减去手续费后价值为 0 的商品)，因此它们之间都是可以互相转换的。

最后需要注意的是：我们求解子问题时得到的收益是 ![[公式]](https://www.zhihu.com/equation?tex=g_k+-+k+%5Ccdot+c)，所以别忘了将这个收益加上 ![[公式]](https://www.zhihu.com/equation?tex=k+%5Ccdot+c) 才会得到最终的答案。

## 恰好为 k 的下界

下界的斜率可能非常之小。可以在总价值不爆 i64 前提下让下界尽可能的小。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct wqs {
    wqs() {
        int n, k;
        cin >> n >> k;
        vector<int> a(n + 1);  // profit
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        auto check = [&](int c) {  // cost for each deal
            i64 val = 0;           // total_val
            int cnt = 0;           // total_deal_count
            //...
            return make_pair(val, cnt);
        };
        int l = 1,
            r = *max_element(a.begin() + 1, a.end());
        long long ans = -1;
        while (l <= r) {
            int c = (l + r) / 2;
            if (auto [val, cnt] = check(c); cnt >= k) {
                ans = val + (long long)c * k;  // note: c * k but not c * cnt. Right result in exactly or at most k problem.
                l = c + 1;
            } else {
                r = c - 1;
            }
        }

        if (ans == -1) {
            ans = check(0).first;
        }
    }
};
```

