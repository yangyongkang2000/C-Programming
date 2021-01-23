//
//  main.cpp
//  Memory_Test_Project
//
//  Created by 杨永康 on 2021/1/21.
//

#include<iostream>
#include <vector>
#include<cstdlib>
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
    int n;
    if(argc!=2||(n=atoi(argv[1]))<1||n>100000000)
        return 1;
    if(n<0x186A0)
    {
        cout<<fibonacci<100000001, 2,vector>(n);
    }else if(n<0x4C4B40)
        cout<<fibonacci<100000001, 1,vector>(n);
    else cout<<fibonacci<100000001, 0,vector>(n);
    return 0;
}
