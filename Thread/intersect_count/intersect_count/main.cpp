#include <iostream>
#include<iterator>
#include<type_traits>
#include<vector>
#include<future>
#include<chrono>
#include"yyk_random.hpp"
#include"intersect_count.h"
int main(int argc,const char *argv[]) {
    using namespace std::chrono;
    yyk_random::uniform_real_distribution<> dis(-10000,10000);
    yyk_random::uniform_real_distribution<> r(-100,100);
    yyk_random::initialize_seed(time(NULL));
    std::vector<std::pair<std::pair<double,double>,double>> v ;
    int n=atoi(argv[1]);
    v.reserve(n);
    for(auto i=0;i<n;i++) v.emplace_back(std::pair<std::pair<double,double>,double>{{dis(),dis()},r()});
    auto t0=high_resolution_clock::now();
    auto t=parallel_intersect_count<unsigned long long>(v.begin(),v.end());
    auto t1=high_resolution_clock::now();
    std::cout<<"parallel:"<<duration_cast<milliseconds>(t1-t0).count()<<"ms\n";
    auto t2=high_resolution_clock::now();
    auto l=intersect_count<unsigned long long>(v.begin(), v.end());
    auto t3=high_resolution_clock::now();
    std::cout<<"signal:"<<duration_cast<milliseconds>(t3-t2).count()<<"ms\n";
    std::cout << t<<","<<l<< std::endl;
    return 0;
}
