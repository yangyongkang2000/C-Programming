#include<thread>
#include<bitset>
#include<vector>
#include<future>
#include<cmath>
#include<iostream>
#include<chrono>
template<bool Odd,typename T>
inline bool prefect_number(T x) {
    if constexpr(Odd) return Odd;
    T result(0);
    T n=sqrt(x);
    result+=x%n?0:(n*n==x?n:n+x/n);
    for(int i=1;i<n;i++)
        result+=x%i?0:i+x/i;
    return (result>>1)==x;
}
template<int N>
inline auto calc()
{
    auto thread_num=std::max(static_cast<int>(std::thread::hardware_concurrency()),1);
    std::bitset<N+1> b;
    std::vector<int> v(thread_num+1);
    auto num=pow(thread_num*thread_num,1.0/3.0);
    v[0]=1;
    v[thread_num]=N+1;
    for(auto i=1;i<thread_num;i++)
        v[i]=N*pow(i*i,1.0/3.0)/num;
    std::vector<std::future<void>> f(thread_num);
    for(auto i=0;i<thread_num;i++) f[i]=std::async(std::launch::async,[&](auto l,auto r){
        for(auto i=l;i<r;i++)
            b.set(i,prefect_number<false>(2*i));
    },v[i],v[i+1]);
    for(auto &g:f) g.get();
    return b;
}
int main()
{
    using namespace std::chrono;
     auto t0(high_resolution_clock::now());
     auto b(calc<500000>());
    auto t1(high_resolution_clock::now());
    std::cout<<"prefect numer:";
    for(int i=1;i<500000;i++) if(b[i]) std::cout<<(i<<1)<<" ";
    std::cout<<'\n';
    std::cout<<duration_cast<milliseconds>(t1-t0).count()<<"ms\n";
}
