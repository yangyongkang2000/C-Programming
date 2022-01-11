//
//  merge_sort.hpp
//  merge_sort
//
//  Created by 杨永康 on 2021/5/4.
//

#ifndef merge_sort_h
#define merge_sort_h
#include<algorithm>
#include<memory>
#include<type_traits>
namespace yyk_demo {
template<typename Compare,typename InputIt>
inline constexpr void insertion_sort(InputIt beg,InputIt end,Compare cmp)
{
    using value_type=typename iterator_traits<InputIt>::value_type;
    if(beg!=end)
    {
        InputIt i=beg;
        for(++i;i!=end;++i)
        {
            InputIt j=i;
            value_type t(std::move(j));
            for(auto k=i;k!=beg&&cmp(*t,*--k);--j)
                *j=std::move(*k);
            *j=std::move(t);
        }
    }
}
template<class InputIt, class OutputIt>
OutputIt move_copy(InputIt first, InputIt last,
              OutputIt d_first)
{
    while (first != last) {
        *d_first++ = std::move(*first++);
    }
    return d_first;
}
template<typename InputIt,typename InputIt1,typename Compare>
inline constexpr void yyk_merge(InputIt beg,InputIt mid,InputIt end,InputIt1 beg1,Compare cmp) noexcept
{
    auto l=beg,r=mid;
    while(l!=mid&&r!=end)
        if(cmp(*l,*r))
            *beg1++=std::move(*l++);
        else *beg1++=std::move(*r++);
    while(l!=mid)
        *beg1++=std::move(*l++);
    while(r!=end)
        *beg1++=std::move(*r++);
    auto len=end-beg;
    move_copy(beg1-len, beg1, beg);
}
template<typename InputIt,typename InputIt1,typename Compare>
inline constexpr void msort(InputIt beg,InputIt end,InputIt1 beg1,Compare cmp) noexcept
{
    auto len=end-beg;
    if(len>=2)
    {
        auto mid=beg+len/2;
        msort(beg, mid, beg1,cmp);
        msort(mid,end, beg1, cmp);
        yyk_merge(beg, mid, end, beg1, cmp);
    }
}
template<typename InputIt,typename Compare>
inline constexpr void merge_sort(InputIt beg,InputIt end,Compare cmp) noexcept
{
    auto len=end-beg;
    using P=typename std::iterator_traits<InputIt>::value_type;
    if(len>=2)
    {
        std::unique_ptr<P[]> unp{new P[len]};
        msort(beg, end, unp.get(), cmp);
    }
}
template<typename  InputIt>
inline constexpr void merge_sort(InputIt beg,InputIt end)
{
    return merge_sort(beg, end, std::less_equal<typename std::iterator_traits<InputIt>::value_type>());
}
}

#endif /* merge_sort_h */
