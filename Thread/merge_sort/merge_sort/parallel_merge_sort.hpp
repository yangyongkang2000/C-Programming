//
//  parallel_merge_sort.hpp
//  merge_sort
//
//  Created by 杨永康 on 2021/5/4.
//

#ifndef parallel_merge_sort_h
#define parallel_merge_sort_h
#include<iterator>
#include<algorithm>
#include<cmath>
#include<future>
namespace yyk_demo {
template<typename InputIt>
InputIt trn=static_cast<InputIt>(nullptr);
template <class T,class T1=T> struct yyk_less {
  bool operator()  (const T& x, const T1& y)  const noexcept {
      return x<static_cast<T>(y);}
  typedef T first_argument_type;
  typedef T1 second_argument_type;
  typedef bool result_type;
};
template<typename Compare,typename InputIt,typename T>
inline constexpr InputIt yyk__lower_bound(InputIt first,InputIt last,T const & val,Compare cmp) noexcept
{
    using difference_type=typename std::iterator_traits<InputIt>::difference_type;
    difference_type len=std::distance(first, last);
    while(len!=0)
    {
        difference_type l=len>>1;
        InputIt m=first;
        std::advance(m, l);
        if(cmp(*m,val))
        {
            first=m+1;
            len-=l+1;
        }else
            len=l;
    }
    return first;
}
template<typename Compare,typename InputIt,typename T>
inline constexpr InputIt yyk_lower_bound(InputIt first,InputIt last,T const & val,Compare cmp) noexcept
{
    return yyk__lower_bound(first, last, val, cmp);
}
template<typename InputIt,typename T>
inline constexpr InputIt yyk_lower_bound(InputIt first,InputIt last,T const & val) noexcept
{
    return yyk__lower_bound(first, last, val, yyk_less<typename std::iterator_traits<InputIt>::value_type,T>());
}
template<typename Compare,typename InputIt,typename InputIt1,typename T=typename std::iterator_traits<InputIt>::difference_type>
inline  std::pair<InputIt, InputIt1> yyk_kth_element(InputIt beg,InputIt end,InputIt1 beg1,InputIt1 end1,T k,Compare cmp) noexcept
{
    auto len=std::distance(beg, end);
    auto len1=std::distance(beg1,end1);
    if(len+len1<k)
        return {trn<InputIt>,trn<InputIt1>};
    if(len==0)
        return {trn<InputIt>,beg1+k};
    if(len1==0)
        return {beg+k,trn<InputIt1>};
    while(len>1&&len1>1)
    {
        auto l=len/2;
        auto mid=beg;
        std::advance(mid, l);
        auto l1=len1/2;
        auto mid1=beg1;
        std::advance(mid1, l1);
        if(cmp(*mid,*mid1))
        {
            if(k<l+l1+1)
                end1=mid1;
            else {
                beg=mid;
                k-=l;
            }
        }else {
            if(k<l+l1)
                end=mid;
            else{
                beg1=mid1;
                k-=l1;
            }
        }
        len=std::distance(beg, end);
        len1=std::distance(beg1, end1);
    }
    if(len==1)
    {
        auto first=yyk_lower_bound(beg1, end1, *beg, cmp);
        auto l=std::distance(beg1, first);
        if(l==k)
            return {beg,trn<InputIt1>};
        if(l>k)
            return {trn<InputIt>,std::next(beg1,k)};
        return {trn<InputIt>,std::next(beg1,k-1)};
    }
    auto first=yyk_lower_bound(beg, end, *beg1, cmp);
    auto l=first-beg;
    if(l==k)
        return {trn<InputIt>,beg1};
    if(l>k)
        return {std::next(beg,k),trn<InputIt1>};
    return {std::next(beg,k-1),trn<InputIt1>};
}
template<typename InputIt,typename InputIt1,typename T=typename std::iterator_traits<InputIt>::difference_type>
inline  std::pair<InputIt, InputIt1> yyk_kth_element(InputIt beg,InputIt end,InputIt1 beg1,InputIt1 end1,T k) noexcept
{
    return yyk_kth_element(beg, end, beg1, end1, k, yyk_less<typename std::iterator_traits<InputIt>::value_type,T>());
}
template<typename T>
inline constexpr auto return_result(T  const & r) noexcept
{
    if(r.first==trn<decltype(r.first)>)
    {
        if(r.second!=trn<decltype(r.second)>)
             return *(r.second);
        else return std::numeric_limits<typename std::remove_reference<decltype(*(r.first))>::type>::max();
    }
    else
            return *(r.first);
}
template<typename Compare,typename InputIt>
inline constexpr void insertion_sort(InputIt beg,InputIt end,Compare cmp) noexcept
{
    using value_type=typename std::iterator_traits<InputIt>::value_type;
    if(beg!=end)
    {
        InputIt i=beg;
        for(++i;i!=end;++i)
        {
            InputIt j=i;
            value_type t(std::move(*j));
            for(auto k=i;k!=beg&&cmp(t,*--k);--j)
                *j=std::move(*k);
            *j=std::move(t);
        }
    }
}
/*
template<class InputIt, class OutputIt>
inline constexpr OutputIt move_copy(InputIt first, InputIt last,
              OutputIt d_first) noexcept
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
template<typename InputIt,typename InputIt1 ,typename Compare,typename T=typename std::iterator_traits<InputIt>::difference_type>
inline constexpr void yyk_merge(InputIt beg,T l,T m,T r,InputIt1 beg1,Compare cmp) noexcept
{
    return yyk_merge(beg+l, beg+m, beg+r, beg1+l, cmp);
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
 */
template<bool parallel,int M=2,int K=0,typename InputIt,typename Compare>
inline constexpr void msort(InputIt beg,InputIt end,Compare cmp) noexcept
{
    auto len=end-beg;
    if(len<60)
        insertion_sort(beg, end, cmp);
    else {
        auto mid=beg+len/2;
        if constexpr(parallel)
        {
            if(len<2000)
                return msort<false>(beg, end, cmp);
            else {
                if constexpr(K<M)
                {
                auto handle=std::async(std::launch::async,msort<true,M,K+1,InputIt,Compare>,beg, mid, cmp);
                msort<true,M,K+1>(mid,end, cmp);
                handle.get();
                std::inplace_merge(beg, mid, end, cmp);
                }else
                    return msort<false>(beg, end, cmp);
            }
        }
        else
        {
            msort<false>(beg, mid, cmp);
            msort<false>(mid, end, cmp);
            std::inplace_merge(beg, mid, end, cmp);
        }
    }
}
/*template<bool parallel,int M=2,int K=0,typename InputIt,typename InputIt1 ,typename Compare,typename T=typename std::iterator_traits<InputIt>::difference_type>
inline constexpr void parallel_msort(InputIt beg,T l,T r,InputIt1 beg1,Compare cmp) noexcept
{
    auto len=r-l;
    if(len>=2)
    {
        auto m=(l+r)/2;
        if constexpr(parallel)
        {
            if(len<2000)
            {
                parallel_msort<false>(beg, l, m, beg1, cmp);
                parallel_msort<false>(beg, m, r, beg1, cmp);
                yyk_merge(beg, l, m, r, beg1, cmp);
            }else {
                if constexpr(K<M)
                {
                auto handle=std::async(std::launch::async,parallel_msort<true,M,K+1,InputIt,InputIt1,Compare,T>,beg, l, m, beg1, cmp);
                parallel_msort<true,M,K+1>(beg, m, r, beg1, cmp);
                handle.get();
                yyk_merge(beg, l, m, r, beg1,cmp);
                }else {
                    parallel_msort<false>(beg, l, m, beg1, cmp);
                    parallel_msort<false>(beg, m, r, beg1, cmp);
                    yyk_merge(beg, l, m, r, beg1, cmp);
                }
            }
        }else {
            parallel_msort<false>(beg, l, m, beg1, cmp);
            parallel_msort<false>(beg, m, r, beg1, cmp);
            yyk_merge(beg, l, m, r, beg1, cmp);
        }
    }
}
 */
/*template<bool parallel,typename InputIt,typename Compare>
inline constexpr void merge_sort(InputIt beg,InputIt end,Compare cmp) noexcept
{
    auto len=end-beg;
    using P=typename std::iterator_traits<InputIt>::value_type;
    if(len>=2)
    {
        std::unique_ptr<P[]> unp{new P[len]};
        if constexpr(parallel)
            parallel_msort<true>(beg, decltype(len)(0), len, unp.get(), cmp);
        else
        msort(beg, end, unp.get(), cmp);
    }
}*/
/*template<bool parallel,typename  InputIt>
inline constexpr void merge_sort(InputIt beg,InputIt end) noexcept
{
    return merge_sort<parallel>(beg, end, std::less_equal<typename std::iterator_traits<InputIt>::value_type>());
}
}
*/
template<bool parallel,int M=2,int K=0,typename InputIt>
inline constexpr void msort(InputIt beg,InputIt end) noexcept
{
    return msort<parallel>(beg, end, std::less_equal<typename std::iterator_traits<InputIt>::value_type>());
}

}
#endif /* parallel_merge_sort_h */
