# Win/Linux 文件重定向

文件重定向：

```cpp
freopen("file_name.txt","r",stdin);
freopen("file_name.txt","w",stdout);
```

Windows 重定向回控制台：

```cpp
freopen("CON","r",stdin);
freopen("CON","w",stdout);
```

Linux 重定向回控制台：

```cpp
freopen("/dev/tty", "r", stdin);
freopen("/dev/tty", "w", stdout);
```

不过一个cpp文件出现两次以上的 freopen 实测有问题。所以最好使用

```cpp
ifstream cin("in.txt");
ofstream cout("out.txt");
cin >> x >> y;
cout << x + y << endl;
input.close();
cout.close();
```



