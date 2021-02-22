## 多线程计算素数
## 前言
> 利用并发操作充分利用CPU性能，写了并发计算版本
## 编译环境
> 编译器支持C++17以上标准库。
## 测试样例
```C++
#include <iostream>
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
}
```
## 更多关于并发计算例子
 + [参考](https://github.com/yangyongkang2000/C-Programming/tree/master/FibonacciSequence/FibonacciSequence_Parallel)