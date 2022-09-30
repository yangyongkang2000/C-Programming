//
//  prime_filter.hpp
//  prime
//
//  Created by 杨永康 on 2021/2/23.
//

#ifndef prime_filter_h
#define prime_filter_h
#include"prime.hpp"
#include"prime_table.hpp"
namespace prime_filter {
#define Parallel_Expand(ll) auto t##ll=std::async(std::launch::async, _calc_<T,N,M,D,l>,m[ll],m[ll+1]);
#define yyk_Parallel_Expand(ll) auto t##ll=std::async(std::launch::async, yyk_calc_<T,N,M,D,l>,m[ll],m[ll+1]);
#define Parallel_Expand_64(ll) auto t##ll=std::async(std::launch::async, _calc_64<T,N,M,D,l>,m[ll],m[ll+1]);
using ULL =unsigned long long int;
template<typename T=ULL,T L,T R,T N>
inline T calc()
{
    constexpr T l=L&1?L:L+1;
    constexpr T r=R&1?R:R+1;
    constexpr T delta=r-l;
     T maxp=static_cast<T>(sqrt(r)+1);
    T _count=0;
    std::bitset<(r-l)/2> bitarray;
    for( T i=1;prime_table[i]<maxp;i++)
    {
        T offset=l%prime_table[i]?prime_table[i]-l%prime_table[i]:0;
        if(offset&1)
            offset+=prime_table[i];
        for(;offset<delta;offset+=2*prime_table[i])
                bitarray.set(offset>>1);
    }
    for(T i=0;i<bitarray.size();i++)
        if(!bitarray[i])
            if(prime::test(N-l-2*i))
                _count++;
    return _count;
}
template<typename T=ULL,T N,T M>
inline T calc(const T L,const T R)
{
    const T l=L&1?L:L+1;
    const T r=R&1?R:R+1;
    const T delta=r-l;
    const T size=(r-l)/2;
    const T maxp=static_cast<T>(sqrt(r)+1);
    T _count=0;
    std::bitset<M> bitarray;
    for( T i=1;prime_table[i]<maxp;i++)
    {
        T offset=l%prime_table[i]?prime_table[i]-l%prime_table[i]:0;
        if(offset&1)
            offset+=prime_table[i];
        for(;offset<delta;offset+=2*prime_table[i])
                bitarray.set(offset>>1);
    }
    for(T i=0;i<size;i++)
        if(!bitarray[i])
            if(prime::test(N-l-2*i))
                _count++;
    return _count;
}
template<typename T=ULL,T N,T M>
inline T yyk_calc(const T L,const T R)
{
    const T l=L&1?L:L+1;
    const T r1=N-l+2;
    const T r=R&1?R:R+1;
    const T l1=N-r+2;
    const T delta=r-l;
    const T size=(r-l)/2;
    const T maxp=static_cast<T>(sqrt(r)+1);
    const T maxp1=static_cast<T>(sqrt(r1)+1);
    T _count=0;
    std::bitset<M> bitarray;
    std::bitset<M> bitarray1;
    for( T i=1;prime_table[i]<maxp;i++)
    {
        T offset=l%prime_table[i]?prime_table[i]-l%prime_table[i]:0;
        if(offset&1)
            offset+=prime_table[i];
        for(;offset<delta;offset+=2*prime_table[i])
                bitarray.set(offset>>1);
    }
    for( T i=1;prime_table[i]<maxp1;i++)
    {
        T offset=l1%prime_table[i]?prime_table[i]-l1%prime_table[i]:0;
        if(offset&1)
            offset+=prime_table[i];
        for(;offset<delta;offset+=2*prime_table[i])
                bitarray1.set(offset>>1);
    }
    for(T i=0;i<size;i++)
       if((!bitarray[i])&&(!bitarray1[size-i-1]))
           _count++;
    return _count;
}
template<typename T=ULL,T N,T M>
inline T calc_64(const T L,const T R)
{
    const T l=L&1?L:L+1;
    const T r=R&1?R:R+1;
    const T delta=r-l;
    const T size=(r-l)/2;
    const T maxp=static_cast<T>(sqrt(r)+1);
    T _count=0;
   std::bitset<M> bitarray;
    for( T i=1;prime_table[i]<maxp;i++)
    {
        T offset=l%prime_table[i]?prime_table[i]-l%prime_table[i]:0;
        if(offset&1)
            offset+=prime_table[i];
        for(;offset<delta;offset+=2*prime_table[i])
                bitarray.set(offset>>1);
    }
    for(T i=0;i<size;i++)
        if(!bitarray[i])
            if(prime::test_64(N-l-2*i))
                _count++;
    return _count;
}
template<typename T=ULL,T L,T R,T N,T D,T U,T K=0>
inline T calc()
{
    if constexpr(K>=U-1)
        return calc<T,L+K*D,R,N>();
    else
        return calc<T,L+K*D,L+(K+1)*D,N>()+calc<T,L,R,N,D,U,K+1>();
}
template<typename T=ULL,T N,T M,T D,T U>
inline T _calc_(const T L,const T R)
{
    T _count=0;
    for(T k=0;k+1<U;k++)
    _count+=calc<T,N,M>(L+k*D, L+(k+1)*D);
    return _count+calc<T,N,M>(L+(U-1)*D, R);
}
template<typename T=ULL,T N,T M,T D,T U>
inline T yyk_calc_(const T L,const T R)
{
    T _count=0;
    for(T k=0;k+1<U;k++)
    _count+=yyk_calc<T,N,M>(L+k*D, L+(k+1)*D);
    return _count+yyk_calc<T,N,M>(L+(U-1)*D, R);
}
template<typename T=ULL,T N,T M,T D,T U>
inline T _calc_64(const T L,const T R)
{
    T _count=0;
    for(T k=0;k+1<U;k++)
    _count+=calc_64<T,N,M>(L+k*D, L+(k+1)*D);
    return _count+calc_64<T,N,M>(L+(U-1)*D, R);
}
template<typename T=ULL,T N,T D,T M=D>
inline T total()
{
    if constexpr(N&1)
        return prime::test(N-2);
    T _count=0;
    constexpr T u=std::min(N/2,static_cast<T>(65521));
    for(T i=0;prime_table[i]<=u;i++)
       if(prime::test(N-prime_table[i]))
           _count++;
    if constexpr(N<=131073)
        return _count;
    if constexpr(N<=147074)
        return calc<T,65537,N/2+1,N,21,10>()+_count;
    constexpr T x=(N/2 - 65537)/16;
    constexpr T l=x/D;
    constexpr T m[17]={65537, 65537 + x, 65537 + 2* x, 65537 + 3* x, 65537 + 4 *x, 65537 + 5 *x,
        65537 + 6* x, 65537 + 7* x, 65537 + 8 *x, 65537 + 9* x, 65537 + 10* x,
       65537 + 11 *x, 65537 + 12* x, 65537 + 13* x, 65537 + 14 *x, 65537 + 15 *x,
       N/2+1};
    Parallel_Expand(0)
    Parallel_Expand(1)
    Parallel_Expand(2)
    Parallel_Expand(3)
    Parallel_Expand(4)
    Parallel_Expand(5)
    Parallel_Expand(6)
    Parallel_Expand(7)
    Parallel_Expand(8)
    Parallel_Expand(9)
    Parallel_Expand(10)
    Parallel_Expand(11)
    Parallel_Expand(12)
    Parallel_Expand(13)
    Parallel_Expand(14)
    Parallel_Expand(15)
    return _count+t0.get()+t1.get()+t2.get()+t3.get()+t4.get()+t5.get()+t6.get()+t7.\
    get()+t8.get()+t9.get()+t10.get()+t11.get()+t12.get()+t13.get()+t14.\
    get()+t15.get();
}
template<typename T=ULL,T N,T D,T M=D>
inline T total_64()
{
    if constexpr(N&1)
        return prime::test_64(N-2);
    static_assert(N<=LimitNum, "The Num Is Larger Than Limit");
    static_assert(N>=2*NextPrime, "The Num Is Less");
    T _count=0;
    for(auto i:prime_table)
        if(prime::test_64(N-i))
            _count++;
    constexpr T x=(N/2 - NextPrime)/16;
    if constexpr(x<1000)
        return total<T,N,D,M>();
    constexpr T l=x/D;
    const T m[17]={NextPrime, NextPrime + x, NextPrime + 2 *x, NextPrime + 3* x,
     NextPrime + 4 *x, NextPrime + 5* x, NextPrime + 6* x, NextPrime + 7* x,
     NextPrime + 8* x, NextPrime + 9 *x, NextPrime + 10 *x, NextPrime + 11 *x,
      NextPrime + 12* x, NextPrime + 13* x, NextPrime + 14 *x,
        NextPrime + 15 *x, N/2+1};
    Parallel_Expand_64(0)
    Parallel_Expand_64(1)
    Parallel_Expand_64(2)
    Parallel_Expand_64(3)
    Parallel_Expand_64(4)
    Parallel_Expand_64(5)
    Parallel_Expand_64(6)
    Parallel_Expand_64(7)
    Parallel_Expand_64(8)
    Parallel_Expand_64(9)
    Parallel_Expand_64(10)
    Parallel_Expand_64(11)
    Parallel_Expand_64(12)
    Parallel_Expand_64(13)
    Parallel_Expand_64(14)
    Parallel_Expand_64(15)
    return _count+t0.get()+t1.get()+t2.get()+t3.get()+t4.get()+t5.get()+t6.get()+t7.\
    get()+t8.get()+t9.get()+t10.get()+t11.get()+t12.get()+t13.get()+t14.\
    get()+t15.get();
}
template<typename T=ULL,T N,T D,T M=D>
inline T yyk_total()
{
    if constexpr(N&1)
        return prime::test_64(N-2);
    static_assert(N<=LimitNum, "The Num Is Larger Than Limit");
    static_assert(N>=2*NextPrime, "The Num Is Less");
    T _count=0;
    for(auto i:prime_table)
        if(prime::test_64(N-i))
            _count++;
    constexpr T x=(N/2 - NextPrime)/16;
    if constexpr(x<1000)
        return total<T,N,D,M>();
    constexpr T l=x/D;
    const T m[17]={NextPrime, NextPrime + x, NextPrime + 2 *x, NextPrime + 3* x,
     NextPrime + 4 *x, NextPrime + 5* x, NextPrime + 6* x, NextPrime + 7* x,
     NextPrime + 8* x, NextPrime + 9 *x, NextPrime + 10 *x, NextPrime + 11 *x,
      NextPrime + 12* x, NextPrime + 13* x, NextPrime + 14 *x,
        NextPrime + 15 *x, N/2+1};
    yyk_Parallel_Expand(0)
    yyk_Parallel_Expand(1)
    yyk_Parallel_Expand(2)
    yyk_Parallel_Expand(3)
    yyk_Parallel_Expand(4)
    yyk_Parallel_Expand(5)
    yyk_Parallel_Expand(6)
    yyk_Parallel_Expand(7)
    yyk_Parallel_Expand(8)
    yyk_Parallel_Expand(9)
    yyk_Parallel_Expand(10)
    yyk_Parallel_Expand(11)
    yyk_Parallel_Expand(12)
    yyk_Parallel_Expand(13)
    yyk_Parallel_Expand(14)
    yyk_Parallel_Expand(15)
    return _count+t0.get()+t1.get()+t2.get()+t3.get()+t4.get()+t5.get()+t6.get()+t7.\
    get()+t8.get()+t9.get()+t10.get()+t11.get()+t12.get()+t13.get()+t14.\
    get()+t15.get();
}
}
#endif /* prime_filter_h */
