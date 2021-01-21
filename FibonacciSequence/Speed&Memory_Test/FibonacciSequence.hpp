#ifndef FibonacciSequence_h
#define FibonacciSequence_h
namespace FibonacciSequence {
using ULL=unsigned long long int;
template<template<typename...> class U,typename T=ULL,ULL M=1000000000>
inline U<T> operator+( const U<T> &v1, const U<T> &v2)
{
    U<T> result;
    result.reserve(std::max(v1.size(),v2.size())+1);
    auto i=0,j=0;
    T _,__=0;
    auto f=[&](const T &s){__=(s-(_=s%M))/M;result.push_back(_);};
    while(i<v1.size()&&j<v2.size())  f(v1[i++]+v2[j++]+__);
    for(;j<v2.size();f(v2[j++]+__));
    for(;i<v1.size();f(v1[i++]+__));
    if(__!=0) result.push_back(__);
    return result;
}
template<template<typename...> class U,typename T=ULL,ULL M=1000000000>
inline U<T> operator*(const U<T> &v1, const U<T> &v2)
{
  U<T> result;
  result.resize(v1.size()+v2.size());
  for(auto i=0;i<v1.size();i++)
    for(auto j=0;j<v2.size();j++)
  {
      T mid=v1[i] * v2[j] + result[i + j];
      T lo = mid % M;
      T hi = mid / M;
       result[i + j] = lo;
       result[i + j + 1] += hi;
  }
  while (result.size()>1&&result.back()==0)
      result.pop_back();
  return result;
}
template<typename C>
C matrix_dot(const C &v1,const C&v2)
{
    return {v1[0] * v2[0] + v1[1] * v2[2], v1[0]*v2[1] + v1[1] *v2[3],
        v1[2] * v2[0] + v1[3]*v2[2], v1[2] *v2[1] + v1[3] *v2[3]};
}
template<typename C,typename T>
C matrix_pow(const C &v, const T& n)
{
      if(n==1)
          return v;
     if(n&1)
         return matrix_dot(matrix_pow(matrix_dot(v,v),n>>1),v);
     else   return matrix_pow(matrix_dot(v,v),n>>1);
}
template<template<typename...> class C,template<typename...> class U,typename T>
 U<ULL> fibonacci(const T& n)
{
    static C<U<ULL>> v={{1},{1},{1},{0}};
    if(n<=2) return {1};
    return matrix_pow(v,n-1)[0];
}
template<unsigned int N,template<typename...> class U,typename T>
U<ULL> fibonacci(const T&n)
{
    static U<ULL> f[N]={{0},{1},{1},{2}};
    if(f[n].size()!=0)
        return f[n];
    if(n&1)
        return f[n]=fibonacci<N,U>(n>>1)*fibonacci<N,U>(n>>1)+fibonacci<N,U>(n/2+1)*fibonacci<N,U>(n/2+1);
    else   return f[n]=fibonacci<N,U>(n>>1)*(fibonacci<N,U>(n/2+1)+fibonacci<N,U>(n/2-1));
}
}
#endif 