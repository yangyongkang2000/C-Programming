# 并行斐波那契数列计算
## 前言 
> 为充分发挥CPU多核的性能,写了并发版本。
##  介绍
+ 如何写测试程序
> 源文件开头用宏指定运行核数，比如
```C++
#define Kernel 4
```
> 可以指定核数为2,4,6,8。当指定其他数值,则用默认方式运行。

> 完整测试程序(样例)
```C++
#define Kernel 4
#include<iostream>
#include <vector>
#include<algorithm>
#include<future>
#include<cmath>
#include<chrono>
#include"FibonacciSequence_Parallel.hpp"
template<typename T>
std::ostream& print(std::ostream &os,const T&v)
{
    std::for_each(v.rbegin(), v.rend(), [&](auto &n){os<<n;});
    return os<<std::endl;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace std;
    using namespace FibonacciSequence;
    using namespace std::chrono;
    auto t0=high_resolution_clock::now();
    fibonacci<1,vector,vector>(1000000);
    auto t1=high_resolution_clock::now();
    std::cout<<duration_cast<milliseconds>(t1-t0).count()<<"ms\n";
    return 0;
}

```