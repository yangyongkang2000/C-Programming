//
// Created by 杨永康 on 2021/9/26.
//

#ifndef RADIX_SORT_RADIX_SORT_H
#define RADIX_SORT_RADIX_SORT_H
#include<iterator>
#include<algorithm>
#include<array>
#include<future>
#include<vector>
#define P(x,y,k) auto f##k=std::async(lch,[&](){place<x,y,Bit,M>(beg,end,H);});
#define G(k) f##k.get();
template<int N,typename InputIt>
inline constexpr void single(InputIt beg,InputIt end)
{
    using T=typename std::iterator_traits<InputIt>::difference_type;
    using T1=typename std::iterator_traits<InputIt>::value_type;
    constexpr auto M=1<<N;
    constexpr auto L=M-1;
    std::array<T,M> H{};
    std::for_each(beg,end,[&](auto i){H[i&L]++;});
    for(T1 i=0;i<M;i++)
        beg= std::fill_n(beg,H[i],i);
}
template<int N,int M,int S,int L,typename InputIt,typename T=typename std::iterator_traits<InputIt>::difference_type>
inline constexpr void place(InputIt beg,InputIt end,std::array<std::array<T,(1<<S)>,L> &H)
{
    if constexpr(N<M)
    {
        constexpr auto s=N*S;
        constexpr auto b=(1<<S)-1;
        std::for_each(beg,end,[&](auto c){
            H[N][(c>>s)&b]++;
        });
        auto beg1=H[N].begin();
        auto end1=H[N].end();
        for(auto it=beg1+1;it!=end1;it++)
            (*it)+=*beg1++;
        place<N+1,M,S,L>(beg,end,H);
    }
}
template<int N,int M,int S,int L,typename InputIt,typename V,typename T=typename std::iterator_traits<InputIt>::difference_type>
        inline constexpr void _place(InputIt beg,InputIt end,V& v,std::array<std::array<T,(1<<S)>,L> &H)
        {
            if constexpr(N<M)
            {
                constexpr auto s=N*S;
                constexpr auto b=(1<<S)-1;
                std::copy(beg,end,std::begin(v));
                std::for_each(std::rbegin(v),std::rend(v),[&](auto c){
                    auto l=--H[N][(c>>s)&b];
                    *(beg+l)=c;
                });
                _place<N+1,M,S,L>(beg,end,v,H);
            }
        }
template<bool B,bool parallel,typename InputIt>
inline constexpr  void radix_sort(InputIt beg,InputIt end)
{
    using T1=typename std::iterator_traits<InputIt>::difference_type;
    using T=typename std::iterator_traits<InputIt>::value_type;
    constexpr auto Bit=B?8:16;
    constexpr auto M= (sizeof(T)<<3)/Bit;
      if constexpr(M<=1)
      {
          single<Bit>(beg,end);
      }else {
          constexpr auto lch=parallel?std::launch::async:std::launch::deferred;
          std::array<std::array<T1,(1<<Bit)>,M> H{{0}};
          std::vector<T> v(end-beg);
         if constexpr(M==2)
         {
             P(0,1,1)
             P(1,2,2)
             G(1)
             G(2)
         }
         if constexpr(M==4)
         {
              P(0,1,1)
              P(1,2,2)
              P(2,3,3)
              P(3,4,4)
              G(1)
              G(2)
              G(3)
              G(4)
         }
         if constexpr(M==8)
         {
             P(0,2,1);
             P(2,4,2)
             P(4,6,3)
             P(6,8,4)
             G(1)
             G(2)
             G(3)
             G(4)
         }
         _place<0,M,Bit,M>(beg,end,v,H);
      }
}
#endif //RADIX_SORT_RADIX_SORT_H
