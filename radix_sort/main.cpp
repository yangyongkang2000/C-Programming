#include <iostream>
#include"radix_sort.h"
#include<random>
#include<chrono>
#include<limits>
int main() {
    using namespace std::chrono;
    std::random_device rd;
    std::mt19937 gen(rd());
    using T=unsigned int;
    std::uniform_int_distribution<T> dis(0,std::numeric_limits<T>::max());
    std::vector<T> p(50000000);
    for(auto &c:p) c=dis(gen);
    std::vector<T> q(p);
    auto t0=high_resolution_clock::now();
    radix_sort<true,true>(std::begin(p),std::end(p));
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
