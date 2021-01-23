//
//  main.cpp
//  SpeedTest_Project
//
//  Created by 杨永康 on 2021/1/21.
//
#include<iostream>
#include <vector>
#include<algorithm>
#include"FibonacciSequence.hpp"
template<typename T>
std::ostream& operator<<(std::ostream &os,const T&v)
{
    std::for_each(v.rbegin(), v.rend(), [&](auto &n){os<<n;});
    return os<<std::endl;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace std;
    using namespace FibonacciSequence;
    cout<<fibonacci<1,vector,vector>(1000000);
    return 0;
}
