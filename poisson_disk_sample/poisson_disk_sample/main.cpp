//
//  main.cpp
//  poisson_disk_sample
//
//  Created by 杨永康 on 2022/6/18.
//

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

