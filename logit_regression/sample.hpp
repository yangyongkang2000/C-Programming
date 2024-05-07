//
//  sample.hpp
//  logit_regression
//
//  Created by 杨永康 on 2023/4/29.
//

#ifndef sample_h
#define sample_h

class simple_rand {
    unsigned int g_seed;
public:
    simple_rand(unsigned int _):g_seed(_) {}
    int operator()() noexcept {
        g_seed = (214013*g_seed+2531011);
        return (g_seed>>16)&0x7FFF;
    }
};


template<typename T,typename Out,typename G>
inline auto Sample(T l,T r,T n,Out o,G &&g) noexcept {
    T s=r-l;
    for(;n!=0;++l){
        auto r(static_cast<T>(g())%s);
        --s;
        if(r<n) {
            *o++=l;
            --n;
        }
    }
    return o;
}
#endif /* sample_h */
