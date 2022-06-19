//
//  test.cpp
//  poisson_disk_sample
//
//  Created by 杨永康 on 2022/6/19.
//

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
