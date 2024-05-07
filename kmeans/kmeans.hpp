//
//  kmeans.hpp
//  kmeans
//
//  Created by 杨永康 on 2023/4/16.
//

#ifndef kmeans_h
#define kmeans_h
#include<array>
#include<numeric>
#include<iterator>
#include<random>
#include<ranges>
#include<memory>
#include<type_traits>
#include<cmath>
#include<algorithm>
#include<utility>
#include"avx_vector.hpp"

template<int N,int K,int I=0,typename T>
inline void expand_calc(T *v,T *c,avx_vector<T> *s) noexcept {
    if constexpr(I<N) {
        avx_vector<T> y(vector_load<true>(c));
        if constexpr(std::is_same_v<T, float>){
            avx_vector<T> x(_mm256_set1_ps(v[I]));
            s[I]=(x-y)*(x-y);
        }else{
            avx_vector<T> x(_mm256_set1_pd(v[I]));
            s[I]=(x-y)*(x-y);
        }
        expand_calc<N, K,I+1>(v, c+K, s);
    }
}

template<int N,int K,typename T>
inline auto nearst(T *v,T *c) noexcept {
    alignas(64) T tmp[K];
    constexpr int Q=std::is_same_v<T, float>?8:4;
    constexpr int M=K/Q;
    for(int k=0;k<M;k++)
    {
        avx_vector<T> s[N];
        expand_calc<N,K>(v,c+k*Q,s);
        std::accumulate(s+1,s+N ,*s).store(tmp+Q*k);
    }
    return std::min_element(tmp,tmp+K)-tmp;
}

template<int N,int K,int Max,typename InputIt,typename G>
inline auto kmeans(InputIt beg,InputIt end,G groups) noexcept {
    using V=typename std::iterator_traits<InputIt>::value_type;
    using T=typename V::value_type;
    using diff=  typename std::iterator_traits<InputIt>::difference_type;
    static_assert(std::is_same_v<V,std::array<T,N>>, "type is error");
    static_assert(K%(32/sizeof(T))==0, "K%(32/sizeof(T))==0");
    constexpr T delta=1e-6;
    alignas(64) T mean[K*N];
    alignas(64) T tmp[K*N];
    alignas(64) diff index[K];
    auto len=end-beg;
    std::array<std::array<T,N>,K> center;
    std::default_random_engine gen;
    std::ranges::sample(std::views::iota(0,len),index,K,gen);
    for(int i=0;i<K;i++)
        for(int j=0;j<N;j++)
            mean[j*K+i]=beg[index[i]][j];
    for(int _=0;_<Max;_++) {
        std::transform(beg, end, groups, [&](auto &p){
            return nearst<N, K>(p.data(), mean);
        });
        std::fill_n(index,K,diff(0));
        std::fill_n(tmp,K*N,T(0));
        for(diff i=0;i<len;i++) {
            index[groups[i]]++;
            for(int j=0;j<N;j++)
                tmp[j*K+groups[i]]+=beg[i][j];
        }
        for(int i=0;i<N;i++)
            for(int j=0;j<K;j++)
                tmp[i*K+j]/=T(index[j]);
        if(std::equal(mean,mean+K*N,tmp,[](auto x,auto y){
            return std::abs(x-y)<delta;
        }))
            break;
        std::copy_n(tmp,K*N,mean);
    }
    for(int i=0;i<K;i++)
        for(int j=0;j<N;j++)
            center[i][j]=mean[j*K+i];
    return center;
}

#endif /* kmeans_h */
