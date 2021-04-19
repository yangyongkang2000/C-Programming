#  Naive算法并发计算
## 前言
> 问题来源于知友在知乎提的问题，[原问题](*https://www.zhihu.com/question/454254720*) ,我对问题做了简化，几何体为二维平面的圆盘，C++ 我用 std::pair<std::pair<T,T>,T> 来表示一个圆盘。first成员代表圆盘的圆心坐标，second成员代表圆盘的半径，写出一个程序去解决各个圆盘之间相交的个数之和（几何体a与b相交就加一)。用简单的遍历算法，复杂度O(n^2).用并发去提高程序性能。
## 环境要求
> 编译器:clang gcc


> 标准: C++17以上
## 封装函数
+ 并发版本
```C++
template<typename T,typename Iterator>
inline T parallel_intersect_count(Iterator beg,Iterator end)
```
> T 需自己指定


+ 串行版本
```C++
template<typename T,typename Iterator>
inline T intersect_count(Iterator beg,Iterator end)
```

## 测试样例

```C++
#include <iostream>
#include<iterator>
#include<type_traits>
#include<vector>
#include<future>
#include<chrono>
#include"yyk_random.hpp"
#include"intersect_count.h"
int main(int argc,const char *argv[]) {
    using namespace std::chrono;
    yyk_random::uniform_real_distribution<> dis(-10000,10000);
    yyk_random::uniform_real_distribution<> r(-100,100);
    yyk_random::initialize_seed(time(NULL));
    std::vector<std::pair<std::pair<double,double>,double>> v ;
    int n=atoi(argv[1]);
    v.reserve(n);
    for(auto i=0;i<n;i++) v.emplace_back(std::pair<std::pair<double,double>,double>{{dis(),dis()},r()});
    auto t0=high_resolution_clock::now();
    auto t=parallel_intersect_count<unsigned long long>(v.begin(),v.end());
    auto t1=high_resolution_clock::now();
    std::cout<<"parallel:"<<duration_cast<milliseconds>(t1-t0).count()<<"ms\n";
    auto t2=high_resolution_clock::now();
    auto l=intersect_count<unsigned long long>(v.begin(), v.end());
    auto t3=high_resolution_clock::now();
    std::cout<<"signal:"<<duration_cast<milliseconds>(t3-t2).count()<<"ms\n";
    std::cout << t<<","<<l<< std::endl;
    return 0;
}
```
## 测试
> make


> ./test 10000
## 测试结果
> 留给读者

## 最后
> 可能有bug，或者性能问题，欢迎指正
