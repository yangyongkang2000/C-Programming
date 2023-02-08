//
//  main.cpp
//  mandelbrot
//
//  Created by 杨永康 on 2023/2/5.
//

#include <iostream>
#include<chrono>
#include<memory>
#include"rgb_ppm.hpp"
#include"mandelbrot_simd.hpp"


template< int width, int height, int maxIters,bool Fast,int M>
void test(float x1, float y1, float x2, float y2, unsigned char * r,unsigned char * g,unsigned char * b,const char *file_name) {
    auto t0=std::chrono::high_resolution_clock::now();
    if constexpr(Fast)
    mandelbrot_simd<width,height,maxIters>(x1, x2, y1, y2, r, g, b);
    else mandelbrot<width,height,maxIters>(x1, x2, y1, y2, r, g, b);
    auto t1=std::chrono::high_resolution_clock::now();
    if constexpr(Fast)
        rgb_ppm<width, height, M>(file_name, r, g, b);
    else normal_rgb_ppm<width, height>(file_name, r, g, b);
    auto t2=std::chrono::high_resolution_clock::now();
    auto time1=std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
    auto time2=std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
    printf(Fast?"mandelbrot with simd:%lldms,fast_rgb_ppm:%lldms\n":"mandelbrot:%lldms,rgb_ppm:%lldms\n",time1,time2);
}
int main(int argc, const char * argv[]) {
    // insert code here...
    constexpr int W=1024;
    constexpr int H=1024;
    constexpr int Max=4096;
    constexpr int M=4096;
    constexpr char file_name[]="mandelbrot.ppm";
    std::unique_ptr<unsigned char[]> rgb_p {new unsigned char[3*W*H]};
    auto r=rgb_p.get();
    auto g=rgb_p.get()+W*H;
    auto b=rgb_p.get()+2*W*H;
    test<W, H, Max, false, M>(0.29768f, 0.48364f, 0.29778f, 0.48354f,r,g,b,argc>1?argv[1]:file_name);
    test<W, H, Max, true, M>(0.29768f, 0.48364f, 0.29778f, 0.48354f,r,g,b,argc>1?argv[2]:file_name);
    return 0;
}
