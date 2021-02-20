//
// Created by 杨永康 on 2021/2/19.
//

#ifndef FibonacciSequence_h
#define FibonacciSequence_h
#define expr \
for(auto i=0;i<n;i++)\
for(auto j=0;j<v2.size();j++)\
   result[i+j]+=v1[i]*v2[j];
#define kernel_2  \
auto t1= std::async(std::launch::async,parallel,0,size);\
auto t2=std::async(std::launch::async,parallel,size,end);\
 t1.get();\
 t2.get();
#define Kernel_4 \
auto l1= static_cast<int>(std::lround(0.707107*size));\
auto r1=static_cast<int>(std::lround(0.292893*size));\
auto t1= std::async(std::launch::async,parallel,0,l1);\
auto t2= std::async(std::launch::async,parallel,l1,size);\
auto t3= std::async(std::launch::async,parallel,size,size+r1);\
auto t4= std::async(std::launch::async,parallel,size+r1,end);\
t1.get();\
t2.get();\
t3.get();\
t4.get();
#define Kernel_6 \
auto l1= static_cast<int>(std::lround(0.57735*size));\
auto l2= static_cast<int>(std::lround(0.816497*size));\
auto r1=static_cast<int>(std::lround(0.183503*size));\
auto r2=static_cast<int>(std::lround(0.42265*size));\
auto t1= std::async(std::launch::async,parallel,0,l1);\
auto t2= std::async(std::launch::async,parallel,l1,l2);\
auto t3= std::async(std::launch::async,parallel,l2,size);\
auto t4= std::async(std::launch::async,parallel,size,size+r1);\
auto t5= std::async(std::launch::async,parallel,size+r1,size+r2);\
auto t6= std::async(std::launch::async,parallel,size+r2,end);\
t1.get();\
t2.get();\
t3.get();\
t4.get();\
t5.get();\
t6.get();
#define Kernel_8 \
auto l1= static_cast<int>(std::lround(0.5*size));\
auto l2= static_cast<int>(std::lround(0.707107*size));\
auto l3= static_cast<int>(std::lround(0.866025*size));\
auto r1=static_cast<int>(std::lround(0.133975*size));\
auto r2=static_cast<int>(std::lround(0.292893*size));\
auto r3=static_cast<int>(std::lround(0.5*size));\
auto t1= std::async(std::launch::async,parallel,0,l1);\
auto t2= std::async(std::launch::async,parallel,l1,l2);\
auto t3= std::async(std::launch::async,parallel,l2,l3);\
auto t4= std::async(std::launch::async,parallel,l3,size);\
auto t5= std::async(std::launch::async,parallel,size,size+r1);\
auto t6= std::async(std::launch::async,parallel,size+r1,size+r2);\
auto t7= std::async(std::launch::async,parallel,size+r2,size+r3);\
auto t8= std::async(std::launch::async,parallel,size+r3,end);\
t1.get();\
t2.get();\
t3.get();\
t4.get();\
t5.get();\
t6.get();\
t7.get();\
t8.get();
namespace FibonacciSequence {
    using ULL=unsigned long long int;
    using UL=unsigned long int;
    constexpr ULL M[3]={0xF240,0x989680,0x5F5E100};
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
        auto parallel=[&](int l,int r){
            for(auto s=l;s<r;s++)
            {
                int ll=std::max(0,s+1-static_cast<int>(v2.size()));
                int rr=std::min(s,static_cast<int>(v1.size())-1);
                for(auto i=ll;i<=rr;i++)
                    result[s]+=v1[i]*v2[s-i];
            }
        };
        const int size=static_cast<int>(n+v2.size())/2-1;
        const int end=static_cast<int>(n+v2.size())-1;
#ifndef Kernel
               expr
#elif Kernel==2
        if(n<1000)
        {
            expr
        }else {
            kernel_2
        }
#elif  Kernel==4
        if(n<1000)
        {
            expr
        }else {
            Kernel_4
        }
#elif  Kernel==6
        if(n<1000)
        {
            expr
        }else{
            Kernel_6
        }
#elif  Kernel==8
        if(n<1000)
        {
            expr
        }else{
            Kernel_8
        }
#else
        expr
#endif
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
