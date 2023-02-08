//
//  rgb_ppm.h
//  mandelbrot
//
//  Created by 杨永康 on 2023/2/7.
//

#ifndef rgb_ppm_h
#define rgb_ppm_h
#include<cstdio>
#include<charconv>
template<int W,int H,int M>
inline void rgb_ppm(const char *file_name,unsigned char *r,unsigned char *g,unsigned char *b ) noexcept {
    constexpr int N=W*H;
    static_assert(N%M==0,"N%M==0");
    auto file=std::fopen(file_name,"wb");
    fprintf(file, "P3\n%d %d\n%d\n", W, H, 255);
    constexpr int L=N/M;
    char buffer[M*12];
    for(int l=0;l<L;l++)
    {
        char *ptr=buffer;
        for(int i=0;i<M;i++)
        {
            ptr=std::to_chars(ptr, ptr+3, *r++).ptr;
            *ptr++=' ';
            ptr=std::to_chars(ptr, ptr+3, *g++).ptr;
            *ptr++=' ';
            ptr=std::to_chars(ptr, ptr+3, *b++).ptr;
            *ptr++='\n';
        }
        std::fwrite(buffer, sizeof(unsigned char), ptr-buffer, file);
    }
    fclose(file);
}
template<int W,int H>
inline void normal_rgb_ppm(const char *file_name,unsigned char *r,unsigned char *g,unsigned char *b ) noexcept
{
    auto file=std::fopen(file_name,"wb");
    fprintf(file, "P3\n%d %d\n%d\n", W, H, 255);
    for (int i = 0; i < W * H; i++)
        fprintf(file,"%d %d %d\n", *r++, *g++, *b++);
    fclose(file);
}
#endif /* rgb_ppm_h */
