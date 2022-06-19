#ifndef FibonacciSequence_h
#define FibonacciSequence_h
namespace FibonacciSequence {
using ULL=unsigned long long int;
using UL=unsigned long int;
constexpr ULL M[3]={0xF4240,0x989680,0x5F5E100};
constexpr UL ULL_Max[3]={0x11979AA,0x2D093,0x734};
constexpr UL S[3]={4,3,3};
template<int N,typename V>
inline void base(V & v)
{
    for(auto i=0;i+1<v.size();i++)
    {
        v[i+1]+=(v[i]/M[N]);
        v[i]%=M[N];
    }
    while (v.size()>1&&v.back()==0)
        v.pop_back();
}
template<int N,template<typename...> class U,typename T=ULL>
inline U<T> plus( const U<T> &v1, const U<T> &v2)
{
    U<T> result;
    result.resize(std::max(v1.size(),v2.size())+1);
     auto n=std::min(v1.size(),v2.size());
    for(auto i=0;i<n;i++) result[i]=v1[i]+v2[i];
    for(auto i=n;i<v1.size();i++) result[i]=v1[i];
    for(auto i=n;i<v2.size();i++) result[i]=v2[i];
    base<N>(result);
    return result;
}
template<int N,template<typename...> class U,typename T=ULL>
inline U<T> dot(const U<T> &v1, const U<T> &v2)
{
    U<T> result;
    result.resize(v1.size()+v2.size());
    const auto n=v1.size()>=ULL_Max[N]?ULL_Max[N]:v1.size();
    const auto m=std::min(n+v2.size()+S[N],result.size());
    for(auto i=0;i<n;i++)
      for(auto j=0;j<v2.size();j++)
        result[i+j]+=v1[i]*v2[j];
    for(auto i=0;i+1<m;i++)
    {
        result[i+1]+=(result[i]/M[N]);
        result[i]%=M[N];
    }
    for(auto i=n;i<v1.size();i++)
    for(auto j=0;j<v2.size();j++)
    {
        T mid=v1[i] * v2[j] + result[i + j];
         result[i + j] = mid%M[N];
         result[i + j + 1] += mid/M[N];
    }
    while (result.size()>1&&result.back()==0)
        result.pop_back();
    return result;
}
template<int N,typename C>
C matrix_dot(const C &v1,const C&v2)
{
    return {plus<N>(dot<N>(v1[0],v2[1]),dot<N>(plus<N>(v1[0],v1[1]),v2[0])),
        plus<N>(dot<N>(v1[0],v2[0]),dot<N>(v1[1],v2[1]))
    };
}
template<int N,typename C,typename T>
C matrix_pow(const C &v, const T& n)
{
      if(n==1)
          return v;
     if(n&1)
         return matrix_dot<N>(matrix_pow<N>(matrix_dot<N>(v,v),n>>1),v);
     else   return matrix_pow<N>(matrix_dot<N>(v,v),n>>1);
}
template<int N,template<typename...> class C,template<typename...> class U,typename T>
 U<ULL> fibonacci(const T& n)
{
    static C<U<ULL>> v={{1},{0}};
    if(n<=2) return {1};
    return matrix_pow<N>(v,n)[0];
}
template<unsigned int N,int I,template<typename...> class U,typename T>
U<ULL> fibonacci(const T&n)
{
    static U<ULL> f[N]={{0},{1},{1},{2}};
    if(f[n].size()!=0)
        return f[n];
    if(n&1)
        return f[n]=
        plus<I>(dot<I>(fibonacci<N,I,U>(n>>1),fibonacci<N,I,U>(n>>1)),dot<I>(fibonacci<N,I,U>(n/2+1),fibonacci<N,I,U>(n/2+1)));
    else   return f[n]=
        dot<I>(fibonacci<N,I,U>(n>>1),plus<I>(fibonacci<N,I,U>(n/2+1),fibonacci<N,I,U>(n/2-1)));
}
}
#endif 
