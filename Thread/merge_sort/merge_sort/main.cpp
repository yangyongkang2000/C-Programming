//
//  main.cpp
//  merge_sort
//
//  Created by 杨永康 on 2021/5/4.
//

#include <iostream>
#include<vector>
#include<random>
#include<chrono>
#include<array>
#include<numeric>
std::random_device rd;
std::default_random_engine gen(rd());
constexpr auto i=10000000;
std::vector<double> v(i);

#include"parallel_merge_sort.hpp"
namespace  test {
using namespace std::chrono;
template<bool parallel,bool s=false>
 int main()
{
     std::iota(v.begin(),v.end(),1);
     std::shuffle(v.begin(), v.end(), gen);
     auto t0=high_resolution_clock::now();
     if constexpr(s)
         std::stable_sort(v.begin(), v.end());
     else
     yyk_demo::msort<parallel>(v.begin(),v.end());
     auto t1=high_resolution_clock::now();
     if constexpr(s)
         std::cout<<"std::sort(ms):";
     {
     if constexpr(parallel)
         std::cout<<"parallel_time(ms):";
     else  std::cout<<"single_time(ms):";
     }
     std::cout<<duration_cast<milliseconds>(t1-t0).count()<<'\n';
     std::cout<<"is_sorted(1/0):"<<std::is_sorted(v.begin(), v.end())<<'\n';
     return 0;
 }
}
template<typename OS,typename T,typename T1>
inline void operator<<(OS &os,std::pair<T, T1> r)
{
    if(r.first==nullptr)
    {
        if(r.second!=nullptr)
             std::cout<<*(r.second);
    }
    else
            std::cout<<*(r.first);
}
int main(int argc, const char * argv[]) {
    test::main<true>();
    test::main<false>();
    test::main<false,true>();
}
