//
//  main.cpp
//  prime
//
//  Created by 杨永康 on 2021/2/21.
//
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
