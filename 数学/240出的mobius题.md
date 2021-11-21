# 一般笔记

求解$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\gcd(\varphi(i),\varphi(j))$。（一下简记$\lfloor \frac{n}{m}\rfloor$为$n/m$）

个人感觉$\varphi(i)$放在gcd里很难求。。故统计 $1\sim n$ 中$\varphi(i) = j$的$cnt_j$，原式转化成：

$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\gcd(i,j)cnt_icnt_j$

$= \sum\limits_{g=1}^ng\sum\limits_{i=1}^n\sum\limits_{j=1}^n[gcd(i,j)=g]cnt_icnt_j = \sum\limits_{g=1}^ng\sum\limits_{i=1}^{n/g}\sum\limits_{j=1}^{n/g}[gcd(i,j)=1]cnt_{gi}cnt_{gj}$

莫反一下，$=\sum\limits_{g=1}^ng\sum\limits_{i=1}^{n/g}\sum\limits_{j=1}^{n/g}\sum\limits_{d|gcd(i,j)}cnt_{gi}cnt_{gj}\mu(d)$，整理一下有

$\sum\limits_{g=1}^ng\sum\limits_{d=1}^n \mu(d)\sum\limits_{i=1}^{n/g}[d|i]\sum\limits_{j=1}^{n/g}[d|j]cnt_{gi}cnt_{gj} = \sum\limits_{g=1}^ng\sum\limits_{d=1}^n \mu(d)\sum\limits_{i=1}^{n/dg}\sum\limits_{j=1}^{n/dg}cnt_{dgi}cnt_{dgj} = \sum\limits_{g=1}^ng\sum\limits_{d=1}^n\mu(d)(\sum\limits_{i=1}^{n/dg}cnt_{dgi})(\sum\limits_{j=1}^{n/dg}cnt_{dgj})$

考虑$\sum\limits_{i=1}^{n/T}cnt_{Ti}$。我们记$A_1 = cnt_1 + cnt_2 + \dots + cnt_n,A_2 = cnt_2 + cnt_4 + \dots + cnt_{n/2*2},\dots,A_T = cnt_{T}+cnt_{2T}+\dots + cnt_{n/T*T}$。

，则原式为$A_T$。根据$\sum\frac{n}{i} \sim O(n\log n)$可知计算$A_i$复杂度为$O(n\log n)$。

于是原式有$\sum\limits_{g=1}^ng\sum\limits_{d=1}^n\mu(d) A_{dg}^2$，套路令$T = dg$，原式有

$= \sum\limits_{T=1}^n A_T^2\sum\limits_{d|T}\frac{T}{d}\mu(d) = \sum\limits_{T=1}^nA_T^2 (id * \mu)(T) $。

