
#include <iostream>
#include<future>
#include<chrono>
#include<array>
#include<cstdio>
#include "memory_simulator.hpp"
#include"memory_generate.hpp"
template<uint32_t N,int M>
inline auto test() {
    using namespace memory_simulator;
    using namespace std::chrono;
    constexpr uint32_t S=10;
    constexpr uint32_t L=N/S;
    test_memory<L> m;
    std::array<uint32_t, S> fault_num;
    std::conditional_t<M==1, FIFO_model, std::conditional_t<M==2, LRU_model, LFU_model>> f {};
        init<M>(f);
        for(uint32_t i=0;i<S;i++){
            if constexpr(M==1) FIFO(f, m);
            if constexpr(M==2) LRU(f, m);
            if constexpr(M==3) LFU(f, m);
            fault_num[i]=m.result();
            m.reset();
        }
    return fault_num;
}
int main()
{
    using namespace std::chrono;
    constexpr uint32_t N=0x989680;
    auto t0=high_resolution_clock::now();
    auto f1=std::async(std::launch::async, test<N,2>);
    auto f2=std::async(std::launch::async, test<N,3>);
    auto p0=test<N, 1>();
    auto p1=f1.get();
    auto p2=f2.get();
    auto t1=high_resolution_clock::now();
    for(uint32_t i=0;i<10;i++)
        printf("Run_Loops:%u\tFIFO_fault_num:%u\tLRU_fault_num:%u\tLFU_fault_num:%u\n",(i+1)*0xf4240,p0[i],p1[i],p2[i]);
    std::cout<<"Run time:"<<duration_cast<milliseconds>(t1-t0).count()<<"ms\n";
}


