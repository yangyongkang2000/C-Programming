//
//  mandelbrot_simd.hpp
//  mandelbrot
//
//  Created by 杨永康 on 2023/2/5.
//

#ifndef mandelbrot_simd_h
#define mandelbrot_simd_h
#include<simd/simd.h>
#include <cstring>
template<int W,int H,int N>
inline void mandelbrot_simd(float x1,float x2,float y1,float y2,unsigned char *r,unsigned char *g,unsigned char *b) noexcept {
    static_assert(W%8==0, "W%8==0");
    float dx=(x2-x1)/W;
    float dy=(y2-y1)/H;
    for(int i=0;i<H;i++)
        for(int j=0;j<W;j+=8)
        {
            simd_float8 X0{x1+j*dx,x1+(j+1)*dx,x1+(j+2)*dx,x1+(j+3)*dx,x1+(j+4)*dx,x1+(j+5)*dx,x1+(j+6)*dx,x1+(j+7)*dx};
            simd_float8 Y0{y1+i*dy,y1+i*dy,y1+i*dy,y1+i*dy,y1+i*dy,y1+i*dy,y1+i*dy,y1+i*dy};
            auto X=X0;
            auto Y=Y0;
            simd_int8 K{1,1,1,1,1,1,1,1};
            for(int k=1;k<N;k++)
            {
                auto X2(X*X);
                auto Y2(Y*Y);
                auto R(X2+Y2);
                auto XY((X+X)*Y);
                X=X2-Y2+X0;
                Y=XY+Y0;
                auto mask=(R<4.0f);
                K+=mask&1;
                if(!simd_any(mask))
                    break;
            }
            constexpr float m=float(1)/float(N);
            auto T=simd_float(K)*m;
            auto R(simd_uchar(2427.26f*T*T*T*(1-T)));
            auto G(simd_uchar(4096.0f*T*T*(1-T)*(1-T)));
            auto B(simd_uchar(2427.26f*T*(1-T)*(1-T)*(1-T)));
            r=(unsigned char *)std::memcpy(r, &R, 8)+8;
            g=(unsigned char *)std::memcpy(g, &G, 8)+8;
            b=(unsigned char *)std::memcpy(b, &B, 8)+8;
        }
}
template<int width, int height, int maxIters>
inline void mandelbrot(float x1, float x2, float y1, float y2,  unsigned char *r,unsigned char *g,unsigned char *b) noexcept
{
    float dx = (x2-x1)/width, dy = (y2-y1)/height;
    for (int j = 0; j < height; ++j)
        for (int i = 0; i < width; ++i)
        {
            float cx = x1+dx*i, cy = y1+dy*j;
            float x = cx, y = cy;
            int count=0;
            for (count = 1; count < maxIters; ++count)
            {
                float x2 = x * x, y2 = y * y;
                float xy = (x+x)*y;
                x = x2 - y2 + cx;
                y = xy + cy;
                if (x2 + y2 >= 4)
                    break;
            }
            constexpr float m=float(1)/float(maxIters);
            auto t=m*float(count);
            *r++=2427.26f*t*t*t*(1-t);
            *g++=4096.0f*t*t*(1-t)*(1-t);
            *b++=2427.26f*t*(1-t)*(1-t)*(1-t);
        }
}

#endif /* mandelbrot_simd_h */
