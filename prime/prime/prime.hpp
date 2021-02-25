//
//  prime.hpp
//  prime
//
//  Created by 杨永康 on 2021/2/21.
//

#ifndef prime_h
#define prime_h
namespace prime {
using ULL=unsigned long long int;
#define _Parallel_Expand_(l) auto t##l=std::async(std::launch::async, calc<T,n,m[l],m[l+1],e>);
#include"prime_constexpr.hpp"
template<typename T=ULL>
constexpr inline T qpow(T a,T n,T p)
{
    T result=1;
    while(n){
       if(n&1)
           result=result*a%p;
        a=a*a%p;
        n>>=1;
    }
    return result;
}
template<typename T,ULL index,ULL M=1>
inline constexpr bool test_prime(const T x)
{
    if constexpr(M>=index)
        return true;
    else{
    if(x%prime_list<T>[M])
        return test_prime<T,index,M+1>(x);
      return false;
    }
}
template<typename T=ULL>
inline constexpr bool test(const T x)
{
    if(x<1001) return prime_bool[x];
    if(!test_prime<T,10>(x)) return false;
    T d=x-1;
    T r=0;
    while (d%2==0)
    {
        d>>=1;
        r++;
    }
    for (auto a : {2,7,61})
        {
            T v = qpow<T>(a, d, x);
            if (v <= 1 || v == x - 1)
                continue;
            for (T i = 0; i < r; ++i)
            {
                v = v * v % x;
                if (v == x - 1 && i != r - 1)
                {
                    v = 1;
                    break;
                }
                if (v == 1)
                    return false;
            }
            if (v != 1)
                return false;
        }
    return true;
}
template<typename T=ULL>
constexpr inline T qpow_64(T a,T n,T p)
{
    T result=1;
    while(n){
       if(n&1)
           result=(__int128)result*a%p;
        a=(__int128)a*a%p;
        n>>=1;
    }
    return result;
}
template<typename T=ULL>
inline constexpr bool test_64(const T x)
{
    if(x<1001) return prime_bool[x];
    if(!test_prime<T,10>(x)) return false;
    T d=x-1;
    T r=0;
    while (d%2==0)
    {
        d>>=1;
        r++;
    }
    for (auto a : {2,13,23,1662803})
        {
            T v = qpow_64<T>(a, d, x);
            if (v <= 1 || v == x - 1)
                continue;
            for (T i = 0; i < r; ++i)
            {
                v = (__int128)v * v % x;
                if (v == x - 1 && i != r - 1)
                {
                    v = 1;
                    break;
                }
                if (v == 1)
                    return false;
            }
            if (v != 1)
                return false;
        }
    return true;
}
static constexpr auto Delta=delta<ULL>;
static constexpr auto Mod=mod<ULL>;
template<typename T=ULL,T N,T L,T r,T e>
inline ULL calc()
{
    constexpr T index=L%10;
    T i=table<T>[e][index][1];
    T l=L+table<T>[e][index][0],_count=0;
    while(l<r)
    {
        if(prime::test(l)&&prime::test(N-l))
           _count++;
        l+=Delta[e][i=i%Mod[e]];
        i++;
    }
    return _count;
}
template<typename T=ULL,T N,T n,T m=0>
inline constexpr void add(T &_count)
{
    if constexpr(m==n)
        return;
    else{
    if constexpr(test(N-prime_list<T>[m]))
        _count++;
        add<T,N, n,m+1>(_count);
    }
}
template<typename T=ULL,T n,T deep=99>
inline constexpr ULL total()
{
    if constexpr(n&1)
        return test(n-2);
    if constexpr(n<=prime_list<T>[deep]*2)
        return result<T>[n];
    T  _count=0;
    constexpr T e=(n%10)/2;
    add<T,n, deep+1>(_count);
    if(n/2-prime_list<T>[deep]<16000)
        return _count+calc<T,n,prime_list<T>[deep]+1, n/2, e>();
    constexpr T s=prime_list<T>[deep]+1;
    constexpr T a=n/2-s+1;
    constexpr T k=a/16;
    constexpr T m[17]={s, s + k, s+ 2 *k, s + 3* k, s + 4 *k, s+ 5 *k, s + 6* k, s + 7 *k,
     s + 8 *k, s + 9* k, s + 10 *k, s + 11* k, s + 12 *k, s+ 13* k, s + 14* k,
        s + 15 *k, n/2+1};
    _Parallel_Expand_(0)
    _Parallel_Expand_(1)
    _Parallel_Expand_(2)
    _Parallel_Expand_(3)
    _Parallel_Expand_(4)
    _Parallel_Expand_(5)
    _Parallel_Expand_(6)
    _Parallel_Expand_(7)
    _Parallel_Expand_(8)
    _Parallel_Expand_(9)
    _Parallel_Expand_(10)
    _Parallel_Expand_(11)
    _Parallel_Expand_(12)
    _Parallel_Expand_(13)
    _Parallel_Expand_(14)
    _Parallel_Expand_(15)
    return t0.get()+t1.get()+t2.get()+t3.get()+t4.get()+t5.get()+t6.get()+t7.\
    get()+t8.get()+t9.get()+t10.get()+t11.get()+t12.get()+t13.get()+t14.\
    get()+t15.get()+_count;
}

}

#endif /* prime_h */
