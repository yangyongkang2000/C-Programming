//
//  naive_integral.hpp
//  naive_integral
//
//  Created by 杨永康 on 2021/4/24.
//

#ifndef naive_integral_h
#define naive_integral_h
#include<future>
#include<limits>
namespace demo {
template<int N1,int N2,typename T,typename F>
inline constexpr T sum(F f,T a,T h) noexcept
{
    T s=T{0};
    for(int k=N1;k<N2;k++)
    {
        T x=a+(k+0.5)*h;
        s+=f(x);
    }
    return s;
}
template<int N1,int N2,typename T,typename F>
inline constexpr T parallel_sum(F f,T a,T h) noexcept
{
    if constexpr((N2-N1)<1000)
        return sum<N1,N2>(f,a,h);
    else {
         constexpr int  M =(N1+N2)/2;
        auto handle=std::async(std::launch::async, parallel_sum<M,N2,T,F>, f,a,h);
        auto s=parallel_sum<N1, M>(f, a, h);
        return s+handle.get();
    }
}
template<int N=1,int K=1,typename T,typename F>
inline constexpr T expand(F f,T a,T eps,T &h,T &t,T &p) noexcept
{
    if constexpr(K<20)
    {
        if constexpr(K>5)
        if(p<eps)
            return t;
        T s=parallel_sum<0, N>(f, a, h);
        T t1=t;
        t=(t+h*s)/2.0;
        p=std::abs(t-t1);
        h=h/2.0;
        return expand<2*N,K+1>(f, a, eps, h, t, p);
    }else
        return t;
}
template<typename T,typename F>
inline constexpr T naive_integral(F f,std::pair<std::pair<T, T>,T> const & p) noexcept
{
    T fa=f(p.first.first);
    T fb=f(p.first.second);
    T h=p.first.second-p.first.first;
    T t=h*(fa+fb)/2.0;
    T d=p.second+1.;
    return expand(f, p.first.first, p.second, h, t, d);
}
}
#endif /* naive_integral_h */
