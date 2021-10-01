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

nth_element(begin(numbers), begin(numbers) + k, end(numbers));  //函数：调用完函数，此时第二个参数的位置的左侧都比该位置小（但不一定有序），右侧都比该位置大（但不一定有序）。
{                                                               //实例
    vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    reverse(vec.begin(), vec.end());
    nth_element(vec.begin(), vec.begin() + 5, vec.end());
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";
    //5 1 2 3 4 6 7 10 8 9
}
partition(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)  //ForwardIterator指正向迭代器iterator
{                                                                            //实例
    vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto bound = std::partition(vec.begin(), vec.end(), [](int i) {
        return i % 2 == 1;
    });
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    //1 3 5 7 9 2 4 6 8 10
}
