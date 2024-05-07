//
//  logic_regression.hpp
//  logit_regression
//
//  Created by 杨永康 on 2023/4/26.
//

#ifndef logic_regression_h
#define logic_regression_h
#include<iterator>
#include<numeric>
#include<array>
#include<valarray>
#include<random>
#include<algorithm>
#include<cmath>
#include"sample.hpp"


template<typename T,int N>
std::array<T,N> gd_convergence_curve;

template<typename T,int N>
std::array<T,N> sgd_convergence_curve;


template<typename T,int N>
std::array<T,N> adam_convergence_curve;

template<int N,typename InputIt,typename OutIt>
inline auto logic_function(InputIt beg,InputIt end,OutIt first) noexcept {
    using V=typename std::iterator_traits<InputIt>::value_type;
    using T=typename V::value_type;
    return std::accumulate(beg, end, T(0), [&](auto l,auto &x){
        auto sum=std::inner_product(x.begin(), x.end()-1, first, T(0))+first[N-1];
        return -x[N-1]*sum+std::log(1+std::exp(sum))+l;
    })/T(end-beg);
}

template<int Method,int N,int Max=1000,bool B=false,typename InputIt,typename OutIt>
inline auto logic_regression(InputIt beg,InputIt end,OutIt first) noexcept {
    using V=typename std::iterator_traits<InputIt>::value_type;
    using size_type=typename V::size_type;
    using T=typename V::value_type;
    size_type len=end-beg;
    constexpr int dim=N-1;
    if constexpr(Method==1) {
        std::array<T,N> grad ;
        std::array<T,N> val;
        constexpr  T alpha=0.1;
        constexpr   T beta=0.5;
        constexpr T start=1;
        auto fx=logic_function<N>(beg, end, first);
        for(int _=0;_<Max;_++) {
            grad.fill(T(0));
            for(size_type i=0;i<len;i++) {
                auto tmp=std::exp(*(first+dim)+std::inner_product(beg[i].begin(), beg[i].end()-1, first, T(0)));
                auto p=tmp/(1+tmp);
                auto y=beg[i][dim];
                for(int j=0;j<dim;j++)
                    grad[j]+=beg[i][j]*(y-p)/len;
                grad[dim]+= (y-p)/len;
            }
            auto dy=alpha*std::inner_product(grad.begin(), grad.end(), grad.begin(), T(0));
            T step(start);
            do {
                std::transform(first, first+N, grad.begin(), val.begin(),[=](auto x,auto dx){
                    return x+dx*step;
                });
                auto f=logic_function<N>(beg, end, val.begin());
                if(f<=(fx-dy*step)) {
                    fx=f;
                    std::copy_n(val.begin(),N,first);
                    break;
                }
                step*=beta;
            }while(true);
            if constexpr(B)
                gd_convergence_curve<T,Max>[_]=logic_function<N>(beg, end, first);
        }
    }
    if constexpr(Method==2) {
        std::array<T,N> grad ;
        constexpr size_type batch_size=50;
        std::array<T,N> val;
        constexpr  T alpha=0.1;
        constexpr   T beta=0.5;
        constexpr T start=1;
        std::array<size_type,batch_size> index;
        std::random_device rd;
        simple_rand sr(rd());
        constexpr T k=T(1)/T(batch_size);
        auto fx=logic_function<N>(beg, end, first);
        for(int _=0;_<Max;_++) {
            Sample(size_type(0), size_type(len), batch_size, index.begin(), simple_rand(sr()));
            grad.fill(T(0));
            for(auto i:index) {
                auto tmp=std::exp(first[dim]+std::inner_product(beg[i].begin(), beg[i].begin()+dim, first, T(0)));
                auto p=tmp/(1+tmp);
                auto y=beg[i][dim];
                for(int j=0;j<dim;j++)
                    grad[j]+=k*beg[i][j]*(y-p);
                grad[dim]+= k*(y-p);
            }
            auto dy=alpha*std::inner_product(grad.begin(), grad.end(), grad.begin(), T(0));
            T step(start);
            do {
                std::transform(first, first+N, grad.begin(), val.begin(),[=](auto x,auto dx){
                    return x+dx*step;
                });
                auto f=logic_function<N>(beg, end, val.begin());
                if(f<=(fx-dy*step)) {
                    fx=f;
                    std::copy_n(val.begin(),N,first);
                    break;
                }
                step*=beta;
            }while(true);
            if constexpr(B)
                sgd_convergence_curve<T,Max>[_]=logic_function<N>(beg, end, first);
        }
    }
    if constexpr(Method==3) {
        constexpr T beta1=0.9;
        constexpr T beta2=0.999;
        constexpr T eps=1e-8;
        constexpr T alpha=0.001;
        constexpr size_type batch_size=50;
        constexpr T k=T(1)/T(batch_size);
        std::array<size_type,batch_size> index;
        std::array<T,N> m {};
        std::array<T,N> v {};
        std::array<T,N> grad {};
        std::random_device rd;
        simple_rand sr(rd());
        for(int t=0;t<Max;t++) {
            Sample(size_type(0), size_type(len), batch_size, index.begin(), simple_rand(sr()));
            std::fill_n(std::begin(grad), N, 0);
            for(auto i:index) {
                auto tmp=std::exp(first[dim]+std::inner_product(beg[i].begin(), beg[i].begin()+dim, first, T(0)));
                auto p=tmp/(1+tmp);
                auto y=beg[i][dim];
                for(int j=0;j<dim;j++)
                    grad[j]+=k*beg[i][j]*(p-y);
                grad[dim]+= k*(p-y);
            }
            for(int i=0;i<N;i++)
               m[i]=beta1*m[i]+(1-beta1)*grad[i];
            for(int i=0;i<N;i++)
             v[i]=beta2*v[i]+(1-beta2)*grad[i]*grad[i];
            for(int i=0;i<N;i++)
            first[i]-=alpha*m[i]/(1-std::pow(T(beta1),T(t+1)))/(std::sqrt(v[i]/(1-std::pow(T(beta2),T(t+1))))+eps);
            if constexpr(B)
                adam_convergence_curve<T,Max>[t]=logic_function<N>(beg, end, first);
        }
    }
    return first+N;
}

#endif /* logic_regression_h */
