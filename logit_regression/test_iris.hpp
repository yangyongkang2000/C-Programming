//
//  test.hpp
//  logit_regression
//
//  Created by 杨永康 on 2023/4/27.
//

#ifndef test_h
#define test_h
#include<fstream>
#include<array>
#include<chrono>
#include"logic_regression.hpp"
template<int N,int M,typename T,typename S>
inline auto read_iris_data(const S &file_name) noexcept {
    std::ifstream is(file_name);
    std::array<std::array<T,N>,M> data;
    for(int i=0;i<M;i++)
        for(int j=0;j<N-1;j++)
            is>>data[i][j];
    return data;
}

template<int O,std::size_t N,std::size_t M,typename T>
auto test_accuracy(const std::array<std::array<T,N>,M> &data,const std::array<std::array<T,N>,O> &theta) {
    T acc=0;
    std::array<T,O> tmp;
    for(auto &x:data) {
        std::transform(theta.begin(), theta.end(),tmp.begin(), [&](auto &p){
            return std::inner_product(x.begin(), x.begin()+N-1, p.begin(), T(0))+p[N-1];
        });
        if(T(std::max_element(tmp.begin(), tmp.end())-tmp.begin())==x[N-1])
            acc++;
    }
    return acc/M;
}

template<int Method,int O,int Max=1000,bool B=false,std::size_t N,std::size_t M,typename T,typename S>
inline auto OvR(std::array<std::array<T,N>,M> &data,const S &file_name) noexcept {
    if constexpr(B)
    std::ofstream  os(file_name);
    std::array<std::array<T,N>,O> theta {};
    constexpr int P=M/O;
    auto t0=std::chrono::high_resolution_clock::now();
    for(int i=0;i<O;i++) {
        for(int j=0;j<i*P;j++) data[j].back()=0;
        for(int j=i*P;j<(i+1)*P;j++) data[j].back()=1;
        for(int j=(i+1)*P;j<int(M);j++) data[j].back()=0;
        logic_regression<Method, N,Max,B>(data.begin(), data.end(), theta[i].begin());
        if constexpr(B) {
            std::ofstream  os(file_name,std::ios::ate|std::ios::in);
            if constexpr(Method==1)
                for(auto x:gd_convergence_curve<T,Max>) os<<x<<'\n';
            if constexpr(Method==2)
                for(auto x:sgd_convergence_curve<T,Max>) os<<x<<'\n';
            if constexpr(Method==3)
                for(auto x:adam_convergence_curve<T,Max>) os<<x<<'\n';
        }
    }
    auto t1=std::chrono::high_resolution_clock::now();
    if constexpr(!B) {
        for(int i=0;i<O;i++)
            for(int j=i*P;j<(i+1)*P;j++) data[j].back()=i;
        return std::make_pair(test_accuracy<O>(data, theta),std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count());
    }else{
        return std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
    }
}
#endif /* test_h */
