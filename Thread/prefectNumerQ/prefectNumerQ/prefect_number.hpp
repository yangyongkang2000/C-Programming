//
//  prefect_number.hpp
//  prefectNumerQ
//
//  Created by 杨永康 on 2021/11/24.
//

#ifndef prefect_number_h
#define prefect_number_h
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
template<typename T,int M>
constexpr auto Pow(const T & x)
{
    if constexpr(M!=0) {
    if constexpr(M&1)
        return x*Pow<T,M/2>(x*x);
    else return Pow<T,M/2>(x*x);
    }
    return static_cast<T>(1);
}
template<int N,int M,typename T>
inline constexpr auto Surd()
{
    T result(1);
    constexpr T T_N=static_cast<T>(N);
    constexpr T T_M=static_cast<T>(M);
    while(true)
    {
        T last=result;
        result=result+(T_N/Pow<T, M-1>(result)-result)/T_M;
        if(last==result)
            break;
    }
    return result;
}
template<int N>
auto calc()
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
    return ;
}
#endif /* prefect_number_h */
