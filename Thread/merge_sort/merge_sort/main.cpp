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

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0,100);
constexpr auto i=10000000;
std::vector<double> v(i);

#include"parallel_merge_sort.hpp"
namespace  test {
using namespace std::chrono;
template<bool parallel,bool s=false>
 int main()
{
     for(int j=0;j<i;j++)
         v[j]=dis(gen);
     auto t0=high_resolution_clock::now();
     if constexpr(s)
         std::sort(v.begin(), v.end());
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
    int p[]={3};
    int q[]={-2,-1};
    /*for(int i=0;i<13;i++)
    {
        std::cout<<yyk_demo::yyk_kth_element(p, p+7, q, q+6, i);
        std::cout<<std::endl;
    }*/
    std::cout<<yyk_demo::return_result(yyk_demo::yyk_kth_element(p, p+1, q, q+2, 1));
    std::cout<<std::endl;
    return 0;
}
