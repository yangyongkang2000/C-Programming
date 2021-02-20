//
//  main.cpp
//  SpeedTest_Project
//
//  Created by 杨永康 on 2021/1/21.
//
#include<iostream>
#include <vector>
#include<algorithm>
#include<future>
#include<cmath>
#define Kernel 6
#include"FibonacciSequence_Parallel.h"
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
    
    print(cout,fibonacci<1,vector,vector>(100000));
    return 0;
}
