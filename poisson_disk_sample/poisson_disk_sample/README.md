# Fast Poisson Disk Sampling in Arbitrary Dimensions


## 前言
 > 最近看了微信公众号的太极图形一篇文章[《如何在平面上随机均匀撒点？60 行 Python 代码实现 Poisson disk 采样，比 NumPy 快 100 倍！》](https://mp.weixin.qq.com/s/OpMTkCX-J6_SzSumHJcVJg)，根据文章上的描述，用C++对快速泊松取样进行了简单的实现（差不多是对着Python实现照葫芦画瓢）。实现的内容为在二维[0,1]*[0,1]正方形 （正方形是由N * N个同样大小的方格组成的）进行快速泊松取样。


 ## 简要介绍

> 取样函数的实现在“poisson_disk_sample.hpp”文件中。


 > 取样函数用C++20 实现（其实没必要），因为使用了
 ```C++
 #include<numbers>
 ```
> 所以需要一个支持C++20的编译器。


> 取样函数声明

```C++
template<int N,int Max_Retry=100,typename T=double,typename InputIt>
inline InputIt poisson_disk_sample(InputIt beg,InputIt end) noexcept
```

> 函数模版中的N代表单位正方形边长的分割次数，Max_Retry为在[r,2*r]扇形范围内随机选择 Max_Retry 个点，默认是100。函数输入参数为存取随机点的容器的双向迭代器指针，输出为取样结束后容器中实际的终止迭代器指针。



## 函数使用&&性能测试

+ 函数使用


```C++
std::vector<std::array<double,2>> v(1000000);
poisson_disk_sample<400>(v.begin(), v.end());
```

> 第一行代码向内存中开辟一个存取二维随机点的容器，第二行代码为取样函数，最终将取样的结果保存在容器中，并返回一个取样结果的终止位置。


+ 性能测试

>测试内容对标微信公众号的太极图形一篇文章[《如何在平面上随机均匀撒点？60 行 Python 代码实现 Poisson disk 采样，比 NumPy 快 100 倍！》](https://mp.weixin.qq.com/s/OpMTkCX-J6_SzSumHJcVJg)中的例子。


> 测试代码在main.cpp中，具体如下：
```C++
#include <iostream>
#include<chrono>
#include"poisson_disk_sample.hpp"
int main()
{
    using namespace std::chrono;
    std::vector<std::array<double,2>> v(1000000);
    auto t0(high_resolution_clock::now());
    std::cout<<poisson_disk_sample<400>(v.begin(), v.end())-v.begin()<<'\n';
    auto t1(high_resolution_clock::now());
    std::cout<<duration_cast<milliseconds>(t1-t0).count()<<"ms\n";
}
```

> 我的电脑是MacBook Pro (13-inch, 2017, Two Thunderbolt 3 ports)

> 系统：macOS Monterey 12.4

> 显卡：Intel Iris Plus Graphics 640 1536 MB


>处理器：2.3 GHz 双核Intel Core i5

> 内存：8 GB 2133 MHz LPDDR3


> 编译器：Apple clang version 13.1.6 (clang-1316.0.21.2.5)

> 编译命令：

```shell
g++ main.cpp -Ofast -march=native -std=c++20 -o main
```

> 运行结果

```shell
53768
410ms
```

> 结果意思是在400*400的单位正方形泊松取样，生成了53768个样点，用时410ms.


+ 正确性测试

> 我没有使用任何图形库，对于得到的结果，我不能进行图形上的随机化验证。但我可以进行最小距离测试，如果大于要求的最小距离就验证了结果。我使用了一年之前用C++写的二维平面点集最短距离算法，使用了二分法，复杂度为O(N*Log[N]).

> 测试代码在"test.cpp"中，具体代码如下（我就不解释了）：

```C++
#include <iostream>
#include<chrono>
#include"poisson_disk_sample.hpp"
#include"../../Thread/nearest_point/nearest_point/near_point.hpp"
#include <algorithm>
template<typename T,typename T1>
struct Pair {
    T first;
    T second;
    using first_type=T;
    using second_type=T1;
    auto operator[](int x){
        return x?second:first;
    }
};
int main()
{
    using namespace std::chrono;
    std::vector<Pair<double,double>> v(1000000);
    auto t0(high_resolution_clock::now());
    auto end=poisson_disk_sample<400>(v.begin(), v.end());
    std::cout<<"Generate Numbers:"<<end-v.begin()<<'\n';
    auto t1(high_resolution_clock::now());
    auto q=bin_near_point<std::vector>(v.begin(),end);
    printf("The near point dist is %.13f > %.13f \n",std::sqrt(q.second),std::sqrt(2.)/400.);
    std::cout<<"Time:"<<duration_cast<milliseconds>(t1-t0).count()<<"ms\n";
}

```

> 最后的测试结果验证了采样距离的正确性。

```shell
Generate Numbers:53721
The near point dist is 0.0035360612279 > 0.0035355339059 
Time:378ms
```


> 当然类Unix用户测试可以用直接我写的makefile。


## 写到最后

+ 仅仅使用了C++标准库实现了算法，没有使用图形库进行直观验证。


+ 测试方法简陋，实现算法可能存在Bug.欢迎指正。


+ 虽然是算法是串行实现，但在编程的细节上还是可以有很多的改进。比如充分利用计算机的SIMD指令集，缓存友好。实现中没有考虑到（水平有限）。


+ 是否可以进行并行计算，充分发挥多核时代CPU的性能。比如对正方形区域分四大块，在每块进行并行快速取样，然后在块与块的分界线附近对点进行筛选。

