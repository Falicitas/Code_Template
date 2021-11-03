# Algorithm & numeric & functional 库实用函数

## nth_element

```cpp
std::nth_element(std::begin(numbers), std::begin(numbers) + k, std::end(numbers));
```

找一个左闭右开区间的第 k 小元素。

第一个参数是开始位置，第三个参数是结束位置，第二个参数是 **这个区间的某个位置**，代表实现完全排序后，这个位置该是什么元素。

调用完函数，此时第二个参数的位置的左侧比该位置小（但不一定有序），右侧比该位置大（但不一定有序）。类似于快排找第 k 小。

这里从第 0 小开始算起。

## partition

```cpp
ForwardIterator partition (ForwardIterator first,//ForwardIterator指正向迭代器iterator
                           ForwardIterator last,
                           UnaryPredicate pred);
```

用于将数组的元素分为两组，第一组满足 pred 指定的性质，作为新数组的前缀，第二组不满足 pred 指定的性质，作为新数组的后缀。最后会返回第二组第一个元素的迭代器。

partition 的缺点在于不保证组内元素的相对位置。而 stable_partition 则满足这个条件。

```cpp
BidirectionalIterator stable_partition (BidirectionalIterator first,
                                        BidirectionalIterator last,
                                        UnaryPredicate pred);
```

实例：

```cpp
vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto bound = std::partition(vec.begin(), vec.end(), [&](int i) {
        return i % 2 == 1;
    });
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
//1 3 5 7 9 2 4 6 8
```

## iota

```cpp
iota(iterator first,iterator last,T ini);
```

这个函数从迭代器的初始位置赋值 ini ，之后每遍历一个位置，都会在上个位置的基础上调用 ini++ （即泛型 T 需要支持 ++ 运算）。

例如：

```cpp
vector<int> vec(n);
int a = 0;
iota(vec.begin(),vec.end(),a);
//vec = {0,1,2,...,n-1}
```

## accumulate

```cpp
accumulate(iterator first,iterator last,T ini,[BinaryOperation binary_op])
```

第四个参数用于重载对于 a 的运算，比如可以调用 `minus<T>()` 来实现 a 减去所有迭代器元素的值。亦可以自己写重载：

```cpp
vector<int> vec{10, 20, 30};  //10,20,30
int a = 0;
int b = accumulate(vec.begin(), vec.end(), a, [](int x, int y) {
    return x - 2 * y;
});
cout << b << "\n";
//b = -120
```

## function

```cpp
function<int(char,double,string)>
```

用其来声明一个函数。可以使用 lambda 表达式给 function 对象赋值：

```cpp
std::function<int(int,int,int)> solve = [&](int d,int l,int r){
	
};

auto solve = [&](int d,int l,int r){
  	//使用 auto 时，solve 不能递归；return 某值时需要显式返回参数类型，比如 0LL.  
};
```

其中 `[&]` 表示，若使用到 lambda 外的外部变量，则按引用捕获。
