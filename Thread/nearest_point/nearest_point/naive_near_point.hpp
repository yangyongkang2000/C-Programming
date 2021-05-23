//
//  naive_near_point.hpp
//  nearest_point
//
//  Created by 杨永康 on 2021/4/27.
//

#ifndef naive_near_point_h
#define naive_near_point_h
#include<future>
#include"near_point.hpp"
template<typename InputIt,typename T,typename Result_Type>
inline Result_Type part_near_point(InputIt it,InputIt beg,InputIt end)
{
    Result_Type result({{end,end},std::numeric_limits<T>::max()});
    while(beg!=end)
    {
        auto d=square_point_dist(*it, *beg);
        if(d<result.second)
            result=std::move<Result_Type>({{it,beg},d});
        beg++;
    }
    return result;
}
template<bool B,bool C,typename Iterator,typename T,typename Result_Type>
struct single_near_point {
    typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
    Iterator beg, end;
    difference_type len;

    single_near_point(Iterator b, Iterator e, difference_type l) : beg(b), end(e), len(l) {}

    inline Result_Type operator()(Iterator it) {
        auto l = end - it;
        if constexpr(B) {
            if constexpr(C)
                return part_near_point<Iterator,T,Result_Type>(it, it+1, it + len+1);
            else
                return min_result(part_near_point<Iterator,T,Result_Type>(it, it+1,  end) ,
                                  part_near_point<Iterator,T,Result_Type>(it, beg, beg + (len - l+1)));
        } else {
            if constexpr (C)
                return part_near_point<Iterator,T,Result_Type>(it,it+1,it+len+1);
            else return min_result(part_near_point<Iterator,T,Result_Type>(it,beg,it-len),part_near_point<Iterator,T,Result_Type>(it,it+1,it+(2*len-(it-beg)+1)));
        }
    }
};
template<typename InputIt,typename T,typename Result_Type, class Op>
constexpr
inline Result_Type yyk_reduce(InputIt first, InputIt last,
             Op op)
{
    Result_Type result({{last,last},std::numeric_limits<T>::max()});
    for (; first != last; ++first) {
        result=std::move(min_result(result, op(first)));
    }
    return result;
}
template<typename InputIt,typename T,typename Result_Type, class Op>
constexpr
inline Result_Type yyk_parallel_reduce(InputIt first,InputIt last,Op op)
{
    auto len=last-first;
    if(len<45)
        return yyk_reduce<InputIt,T,Result_Type,Op>(first,last,op);
    InputIt mid=first+len/2;
    auto handle=std::async(std::launch::async,yyk_parallel_reduce<InputIt,T,Result_Type,Op>,mid,last,op);
    Result_Type sum(yyk_parallel_reduce<InputIt,T,Result_Type,Op>(first,mid,op));
    return min_result(sum,handle.get());
}
template<typename Iterator,typename T=typename std::iterator_traits<Iterator>::value_type::first_type,typename Result_Type=std::pair<std::pair<Iterator,Iterator>, T> >
inline auto parallel_near_point(Iterator beg,Iterator end)
{
    typedef typename std::iterator_traits<Iterator>::value_type::second_type T1;
    auto size=end-beg;
    auto len=(size-1)/2;
    if(size>1)
    {
        if(size&1)
        {
            auto l1(yyk_parallel_reduce<Iterator,T,Result_Type>(beg,end-len,single_near_point<true,true,Iterator,T,Result_Type>(beg,end,len)));
            auto l2(yyk_parallel_reduce<Iterator,T,Result_Type>(end-len,end,single_near_point<true,true,Iterator,T,Result_Type>(beg,end,len)));
            return min_result(l1, l2);
        }
        else {
            auto l1(yyk_parallel_reduce<Iterator,T,Result_Type>(beg,beg+len+1,single_near_point<true,true,Iterator,T,Result_Type>(beg,end,len)));
            auto l2(yyk_parallel_reduce<Iterator,T,Result_Type>(beg+len+1,end-1,single_near_point<true,true,Iterator,T,Result_Type>(beg,end,len)));
            auto l3(part_near_point<Iterator,T,Result_Type>(end-1,beg,end-1));
            return min_result(min_result(l1, l2), l3);
        }
    }else return Result_Type{{end,end},std::numeric_limits<T>::max()};
}
template<typename Iterator,typename T=typename std::iterator_traits<Iterator>::value_type::first_type,typename Result_Type=std::pair<std::pair<Iterator,Iterator>, T>>
inline Result_Type naive_near_point(Iterator beg,Iterator end)
{
    Result_Type result({{end,end},std::numeric_limits<T>::max()});
   while(++beg!=end)
       result=std::move(min_result(result,part_near_point<Iterator,T,Result_Type>(beg-1,beg,end)));
    return result;
}
#endif /* naive_near_point_h */
