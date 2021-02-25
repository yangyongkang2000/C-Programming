## 多线程计算素数
## 前言
> 利用并发操作充分利用CPU性能，写了并发计算版本。算法是分段筛法，结合Wolfram语言生成
哈希表。

> 而且我不吝啬写法，有几种效率不同的算法。
+ 第一种是namepsace prime下的
```C++
template<typename T=ULL,T n,T deep=99>
inline constexpr ULL total()
```
> 效率不高
+ 第二,三种是 namespace prime_filter下的
```C++
template<typename T=ULL,T N,T D,T M=D>
inline T total()
template<typename T=ULL,T N,T D,T M=D>
inline T total_64()
```
> 对应32位，64位。

+ 效率最高的
```C++
template<typename T=ULL,T N,T D,T M=D>
inline T yyk_total()
```
## 编译环境
 > 编译器支持C++17以上标准库。 

> 支持Wolfram语言
## 如何测试
> 终端下输入
```shell
make header
```
> 输入一个大数n，Wolfram语言会生成前n个素数。


> 然后输入 
```shell
make compile
```
## 测试样例
+ 我们测试效率最高的算法

~~#include <iostream>
#include<future>
#include<chrono>
#include<cmath>
#include"prime.hpp"
int main(int argc, const char * argv[]) {
    using namespace std::chrono;
    auto time_0=high_resolution_clock::now();
    std::cout<<prime::total<unsigned long long int,2021218918>()<<std::endl;
    auto time_1=high_resolution_clock::now();
    std::cout<<duration_cast<milliseconds>(time_1-time_0).count()<<"ms\n";
    return 0;
}~~
```C++
#include <iostream>
#include<future>
#include<chrono>
#include<cmath>
#include<bitset>
#include"prime_filter.hpp"
int main(int argc, const char * argv[]) {
    using namespace std::chrono;
    auto time_0=high_resolution_clock::now();
    std::cout<<prime_filter::yyk_total<unsigned long long,202102180918,500000>()<<std::endl;
    auto time_1=high_resolution_clock::now();
    std::cout<<duration_cast<milliseconds>(time_1-time_0).count()<<"ms\n";
    return 0;
}
```
## 更多关于并发计算例子
 + [参考](https://github.com/yangyongkang2000/C-Programming/tree/master/FibonacciSequence/FibonacciSequence_Parallel)