# Q-模拟 & 高斯二项式

经典的Q-理论来自于对于非负整数的Q-模拟：

对于$n\in N$，$\lim\limits_{q\rightarrow 1}\frac{1-q^n}{1-q} = n$

定义$n$的Q-模拟为：

$[n]_q = 1 + q + q^2 + \dots +q^{n-1}$

由此可以推出阶乘的Q-模拟定义，组合数的Q-模拟定义（亦称高斯二项式系数）。

下次可以这样装b：$\sum\limits_{i=0}^n q^i = [n+1]_q$，表示对$n+1$的q-模拟（q-analog）（qwq）

## Q-模拟

由$[n]_q = 1 + q + q^2 + \dots +q^{n-1}$

可以推得Q-模拟阶乘的定义：

$[n]_q! = [1]_q [2]_q\dots [n]_q = (1)(1+q)(1+q+q^2)\dots(1+q+q^2\dots+q^{n-1})$

于是可以定义组合数：

$\dbinom{n}{m}_q = \frac{[n]_q!}{[m]_q![n-m]_q!}$，此式称作高斯二项式系数。高斯二项式系数计算一个有限维[向量空间](https://zh.wikipedia.org/wiki/向量空间)的子空间数。令*q*表示一个[有限域](https://zh.wikipedia.org/wiki/有限域)里的元素数目，则在*q*元有限域上*n*维向量空间的*k*维子空间数等于$\dbinom{n}{m}_q $。（虽然我也不知道是啥玩意QAQ）$q=1$时就是普通的二项式系数了。