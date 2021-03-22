//
//  read_write_vector_file.hpp
//  integer_vector_to_file
//
//  Created by 杨永康 on 2021/3/22.
//

#ifndef read_write_vector_file_h
#define read_write_vector_file_h
#include<array>
#include<cstdio>
#include<charconv>
#include<future>
#include<filesystem>
#define Parallel_Expand(ll) auto t##ll=std::async(std::launch::async, f,m[ll],m[ll+1],i*N);
template<size_t N,size_t M,bool parallel=true,char Ch='\n',typename Input_It>
inline void vector_to_file(Input_It it,size_t len,char *file_out) noexcept
{
    static std::array<char,N*M> mem;
    FILE *file=fopen(file_out, "wb");
    mem.fill(0);
    auto f=[&](size_t l,size_t r,size_t t)
    {
        for(size_t i=l;i<r;i++)
        {
            std::to_chars(mem.data()+i*M, mem.data()+(i+1)*M, it[i+t]);
            mem[(i+1)*M-1]=Ch;
        }
    };
    if(N>=len)
    {
        f(0,len,0);
        fwrite(mem.data(), sizeof(char), len*M, file);
    }
    else   {
        auto j=len/N;
        constexpr auto x=N/16;
        constexpr size_t m[17]={0, x, 2* x, 3 *x, 4 *x, 5 *x, 6 *x, 7* x, 8 *x, 9 *x, 10* x, 11 *x, 12* x, 13* x,
            14 *x, 15* x,N};
        for(size_t i=0;i<j;i++)
        {
            if constexpr(parallel)
            {
                Parallel_Expand(0)
                Parallel_Expand(1)
                Parallel_Expand(2)
                Parallel_Expand(3)
                Parallel_Expand(4)
                Parallel_Expand(5)
                Parallel_Expand(6)
                Parallel_Expand(7)
                Parallel_Expand(8)
                Parallel_Expand(9)
                Parallel_Expand(10)
                Parallel_Expand(11)
                Parallel_Expand(12)
                Parallel_Expand(13)
                Parallel_Expand(14)
                Parallel_Expand(15)
                t0.get();
                t1.get();
                t2.get();
                t3.get();
                t4.get();
                t5.get();
                t6.get();
                t7.get();
                t8.get();
                t9.get();
                t10.get();
                t11.get();
                t12.get();
                t13.get();
                t14.get();
                t15.get();
            }
            else f(0,N,i*N);
            fwrite(mem.data(), sizeof(char), N*M, file);
            mem.fill(0);
        }
        f(0,len-j*N,j*N);
        fwrite(mem.data(), sizeof(char), (len-j*N)*M, file);
    }
    fclose(file);
}
template<size_t N,size_t M,bool parallel=true,typename OutPut_It>
void file_to_vector(char *file_in,OutPut_It result) noexcept
{
    static std::array<char,N*M> mem;
    auto size=std::filesystem::file_size(std::filesystem::path(file_in))/M;
    FILE *file=fopen(file_in, "rb");
    auto f=[&](size_t l,size_t r,size_t t)
    {
        for(size_t i=l;i<r;i++)
        std::from_chars(mem.data()+i*M, mem.data()+(i+1)*M, result[i+t]);
    };
    if(size<=N)
    {
        fread(mem.data(), sizeof(char), size*M, file);
        f(0,size,0);
    }
    else {
        auto j=size/N;
        constexpr auto x=N/16;
        constexpr size_t m[17]={0, x, 2* x, 3 *x, 4 *x, 5 *x, 6 *x, 7* x, 8 *x, 9 *x, 10* x, 11 *x, 12* x, 13* x,
            14 *x, 15* x,N};
        for(size_t i=0;i<j;i++)
        {
            fread(mem.data(), sizeof(char), N*M, file);
            if constexpr(parallel)
            {
                Parallel_Expand(0)
                Parallel_Expand(1)
                Parallel_Expand(2)
                Parallel_Expand(3)
                Parallel_Expand(4)
                Parallel_Expand(5)
                Parallel_Expand(6)
                Parallel_Expand(7)
                Parallel_Expand(8)
                Parallel_Expand(9)
                Parallel_Expand(10)
                Parallel_Expand(11)
                Parallel_Expand(12)
                Parallel_Expand(13)
                Parallel_Expand(14)
                Parallel_Expand(15)
                t0.get();
                t1.get();
                t2.get();
                t3.get();
                t4.get();
                t5.get();
                t6.get();
                t7.get();
                t8.get();
                t9.get();
                t10.get();
                t11.get();
                t12.get();
                t13.get();
                t14.get();
                t15.get();
            }
            else
                f(0,N,i*N);
        }
        fread(mem.data(),sizeof(char),(size-j*N)*M,file);
        f(0,size-j*N,j*N);
    }
}
#endif /* read_write_vector_file_h */
