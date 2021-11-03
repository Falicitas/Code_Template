# tie & tuple

tuple 元组，可以包含任意个数的参数。

tie 一次返回变量的引用。

可以通过以下方式来赋值：

```cpp
string s;
int x, y, z;
tie(x, y, z, s) = make_tuple(1, 2, 3, "xyz");
```

