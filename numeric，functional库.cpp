#include <bits/stdc++.h>
using namespace std;

iota(iterator first, iterator last, T ini);  //函数：这个函数从迭代器的初始位置赋值 ini ，之后每遍历一个位置，都会在上个位置的基础上调用 ini++ （即泛型 T 需要支持++ 运算）。
{                                            //实例
    vector<int> vec(n);
    int a = 0;
    iota(vec.begin(), vec.end(), a);
}

accumulate(iterator first, iterator last, T ini, [BinaryOperation binary_op]);  //函数：这个函数用于将迭代器里的元素都加到 ini 中，比如
{                                                                               //实例
    vector<int> vec(n);                                                         //10,20,30
    int a = 0;
    accumulate(vec.begin(), vec.end(), a);
}  //a = 60
//第四个参数用于重载对于 a 的运算，比如可以调用 `minus<T>()` 来实现 a 减去所有迭代器元素的值。亦可以自己写：
{                        //实例
    vector<int> vec(n);  //10,20,30
    int a = 0;
    accumulate(vec.begin(), vec.end(), a, [](int x, int y) {
        return x + 3 * y;
    });
}  //a = 180