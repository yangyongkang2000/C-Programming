#include <iostream>
#include"radix_sort.h"
#include<random>
#include<chrono>
#include<numeric>
int main() {
    using namespace std::chrono;
    std::random_device rd;
    std::default_random_engine g(rd());
    using T= unsigned int;
    std::vector<T> p(10000000);
    
    std::vector<T> q(p);
    auto t0=high_resolution_clock::now();
    radix_sort<false,false>(std::begin(p),std::end(p));
    auto t1=high_resolution_clock::now();
    if(std::is_sorted(std::begin(p),std::end(p)))
        std::cout<<"radix_sort:"<<duration_cast<milliseconds>(t1-t0).count()<<"ms\n";
    auto t2=high_resolution_clock::now();
    std::sort(std::begin(q),std::end(q));
    auto t3=high_resolution_clock::now();
    if(std::is_sorted(std::begin(q),std::end(q)))
        std::cout<<"std::sort:"<<duration_cast<milliseconds>(t3-t2).count()<<"ms\n";
    return 0;
}
