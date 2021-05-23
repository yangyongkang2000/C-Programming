//
//  tmp.hpp
//  TMA
//
//  Created by 杨永康 on 2021/5/21.
//

#ifndef tmp_h
#define tmp_h
#include<future>
template<typename T>
inline constexpr T _sq(T const & x) noexcept
{
    return x*x;
}
template<bool parallel,int M=2,int K=0,typename R,typename G,typename B,typename D,typename I>
inline constexpr void tmp_plot(R r,G g,B b,D d,I h1,I h2,I w) noexcept
{
    if constexpr(parallel)
    {
        auto len=h2-h1;
        if(len*w<1000)
            return tmp_plot<false>(r,g,b,d,h1,h2,w);
        else {
            if constexpr(K<M)
            {
                auto m=h1+len/2;
                auto handle=std::async(std::launch::async,tmp_plot<true,M,K+1,R,G,B,D,I>,r,g,b,d,h1,m,w);
                tmp_plot<true,M,K+1>(r,g,b,d+(m-h1)*w*3,m,h2,w);
                handle.get();
            }else
                return tmp_plot<false>(r,g,b,d,h1,h2,w);
        }
    }else
        for(I i=h1;i<h2;i++)
            for(I j=0;j<w;j++)
            {
                d[0]=r(i,j);
                d[1]=g(i,j);
                d[2]=b(i,j);
                d+=3;
            }
}

#endif /* tmp_h */
