//
//  Vector_Double.hpp
//  intersection_point
//
//  Created by 杨永康 on 2023/1/15.
//

#ifndef Vector_Double_h
#define Vector_Double_h
#include <immintrin.h>
#include <type_traits>
template<typename T>
class avx_vector {
public:
    static_assert(std::is_floating_point_v<T>,"T isn't floating_point");
    static constexpr bool value=std::is_same_v<T, double>;
    using vector_type=std::conditional_t<value,__m256d,__m256>;
    avx_vector()=default;
    avx_vector(vector_type _):m(_) {};
    friend auto operator+(avx_vector v,const avx_vector &r) noexcept {
        if constexpr(value)
        v.m=_mm256_add_pd(v.m,r.m);
        else v.m=_mm256_add_ps(v.m,r.m);
        return v;
    }
    friend auto operator-(avx_vector v,const avx_vector &r) noexcept {
        if constexpr(value)
        v.m=_mm256_sub_pd(v.m,r.m);
        else v.m=_mm256_sub_ps(v.m,r.m);
        return v;
    }
    friend auto operator*(avx_vector v,const avx_vector &r) noexcept {
        if constexpr(avx_vector::value)
        v.m=_mm256_mul_pd(v.m,r.m);
        else v.m=_mm256_mul_ps(v.m,r.m);
        return v;
    }
    friend auto operator/(avx_vector v,const avx_vector &r) noexcept {
        if constexpr(avx_vector::value)
        v.m=_mm256_div_pd(v.m,r.m);
        else v.m=_mm256_div_ps(v.m,r.m);
        return v;
    }
    template<bool b=true>
    auto store(T * p) noexcept {
        if constexpr(b)
        {
            if constexpr(value)
            _mm256_store_pd(p,m);
            else  _mm256_store_ps(p,m);
        }
        else {
            if constexpr(value)
            _mm256_storeu_pd(p, m);
            else  _mm256_storeu_ps(p,m);
        }
        return p+32/sizeof(T);
    }
    friend auto cross_dot(avx_vector x1,const avx_vector &x2,const avx_vector &y1,const avx_vector &y2) {
        if constexpr(avx_vector::value)
        x1.m=_mm256_fmsub_pd(x1.m,y2.m,(x2*y1).m);
        else x1.m=_mm256_fmsub_ps(x1.m,y2.m,(x2*y1).m);
        return x1;
    }
private:
    vector_type m;
};
template<bool b,typename T>
inline auto vector_load(T *t) noexcept {
    constexpr bool value=sizeof(T)==8;
    if constexpr(b)
    {
        if constexpr(value)
        return _mm256_load_pd(t);
        else return _mm256_load_ps(t);
    }
    else{
        if constexpr(value)
        return _mm256_loadu_pd(t);
        else return _mm256_loadu_ps(t);
    }
    
}
#endif /* Vector_Double_h */
