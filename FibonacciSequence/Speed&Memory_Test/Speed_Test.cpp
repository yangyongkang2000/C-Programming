//
//  main.cpp
//  SpeedTest_Project
//
//  Created by 杨永康 on 2021/1/21.
//
#include<iostream>
#include <vector>
#include<cstdlib>
#include<algorithm>
template<typename T>
std::ostream& operator<<(std::ostream &os,const T&v)
{
    std::for_each(v.rbegin(), v.rend(), [&](auto &n){os<<n;});
    return os<<std::endl;
}
#include"FibonacciSequence.hpp"
int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace std;
    using namespace FibonacciSequence;
    int n;
    if(argc!=2||(n=atoi(argv[1]))<1)
        return 1;
    cout<<fibonacci<vector, vector>(n);
    return 0;
}
