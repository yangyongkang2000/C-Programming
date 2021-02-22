//
//  main.cpp
//  SpeedTest_Project
//
//  Created by 杨永康 on 2021/1/21.
//
#define Kernel 8
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
    fibonacci<1000001,1,vector,ULL>(1000000);
    auto t1=high_resolution_clock::now();
    std::cout<<duration_cast<milliseconds>(t1-t0).count()<<"ms\n";
    return 0;
}
