//
//  avx_poisson2d.hpp
//  avx_poisson2d
//
//  Created by 杨永康 on 2022/10/9.
//
#ifndef avx_poisson2d_h
#define avx_poisson2d_h
#include<algorithm>
#include <immintrin.h>
struct col_pointer {
    double *u,*l,*r,*x,*m,*o;
    col_pointer(double *_u,double *_l,double *_r,double *_x,double *_m,double *_o):u(_u),l(_l),r(_r),x(_x),m(_m),o(_o) {}
    void add() {
        u+=4;l+=4;r+=4;x+=4;m+=4;o+=4;
    }
};
template<int N>
class poisson2d_matrix {
     static_assert(N%4==0, "N%4==0");
     alignas(32)  double phi_mat[N*N] ={};
     alignas(32)  double phiprime_mat[N*N] ={};
     alignas(32)  double rhoarr_mat[N*(N-2)] ={};
     double *p1=phi_mat;
     double *p2=phiprime_mat;
public:
    auto  phi(size_t i=0,size_t j=0) noexcept {
        return p1+i*N+j;
    }
    auto phiprime(size_t i=0,size_t j=0) noexcept {
        return p2+i*N+j;
    }
    auto rhoarr(size_t i=0,size_t j=0) noexcept {
        return rhoarr_mat+i*N+j;
    }
    void swap() noexcept {
        std::swap(p1, p2);
    }
    col_pointer col(size_t i) noexcept {
        return col_pointer(phi(i-1,1),phi(i),phi(i,2),phi(i+1,1),rhoarr(i-1,0),phiprime(i,1));
    }
}
;

template<bool b>
inline auto vector_load(double *_) noexcept {
    if constexpr(b)
        return _mm256_load_pd(_);
    else return _mm256_loadu_pd(_);
}

class Vector_Double {
    __m256d m;
public:
    Vector_Double(__m256d _):m(_) {};
    Vector_Double()=default;
    friend Vector_Double operator+(Vector_Double v,const Vector_Double &r) noexcept {
        v.m=_mm256_add_pd(v.m,r.m);
        return v;
    }
    friend Vector_Double operator*(Vector_Double v,const Vector_Double &r) noexcept {
        v.m=_mm256_mul_pd(v.m,r.m);
        return v;
    }
    template<bool b=false>
    void store(double * p) noexcept {
        if constexpr(b)
            _mm256_store_pd(p,m);
        else _mm256_storeu_pd(p, m);
    }
};

template<int N,int M>
inline void avx_transform(col_pointer && cp) noexcept {
    Vector_Double a1(_mm256_set1_pd(0.25));
    for (int i = 0; i < N ; ++i)
    {
        Vector_Double u(vector_load<false>(cp.u));
        Vector_Double l(vector_load<true>(cp.l));
        Vector_Double r(vector_load<false>(cp.r));
        Vector_Double x(vector_load<false>(cp.x));
        Vector_Double m(vector_load<true>(cp.m));
        Vector_Double result((u+l+r+x)*a1+m);
        result.store(cp.o);
        cp.add();
    }
    for(int i=0;i<M-4*N;i++)
    {
        auto u=*cp.u++;
        auto l=*cp.l++;
        auto r=*cp.r++;
        auto x=*cp.x++;
        auto m=*cp.m++;
        *cp.o++=(u+l+r+x)*0.25+m;
    }
    
}
inline double rho(double x, double y) noexcept
{
    constexpr double s1 = 0.6;
    constexpr double e1 = 0.8;
    constexpr double s2 = 0.2;
    constexpr double e2 = 0.4;

    if (x > s1 && x < e1 && y > s1 && y < e1)
    {
        return 1.0;
    }
    else if (x > s2 && x < e2 && y > s2 && y < e2)
    {
        return -1.0;
    }
    else
    {
        return 0.0;
    }
}
inline void poisson2d(int &iteration) noexcept
{
    constexpr int M = 100;
    constexpr double target = 1.0e-12;
    constexpr double epsilon0 = 8.85e-12;
    constexpr double a = 0.01;
    constexpr double k=0.25*a*a/epsilon0;
    poisson2d_matrix<M> p;
    for (int i = 0; i < M-2; ++i)
        for (int j = 0; j < M-2; ++j)
           *p.rhoarr(i,j) = k*rho((i+1) * 0.01, (j+1) * 0.01);
    int iter=0;
loop:
    {
        iter+=1;
        for (int i = 1; i < M - 1; ++i)
            avx_transform<(M-2)/4,M-2>(p.col(i));
        auto b=std::mismatch(p.phi(),p.phi(M,M),p.phiprime(),[](auto l,auto r){return (l-r)*(l-r)<target;}).first!=p.phi(M,M);
        if(b){
                p.swap();
                goto loop;
            }
    }
    iteration = iter;
}
#endif /* avx_poisson2d_h */
