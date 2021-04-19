//
// Created by 杨永康 on 2021/4/16.
//

#ifndef INTERSECT_COUNT_INTERSECT_COUNT_H
#define INTERSECT_COUNT_INTERSECT_COUNT_H
template<typename T,typename Iterator>
inline bool is_intersect(Iterator l,Iterator r)
{
    static_assert(std::is_same<std::pair<std::pair<T,T>,T>,typename std::iterator_traits<Iterator>::value_type>::value,
                  "type isn't match");
    auto d=l->second+r->second;
    auto x=std::abs(l->first.first-r->first.first);
    if(x>d) return false;
    auto y=std::abs(l->first.second-r->first.second);
    if(y>d) return false;
    return x*x<(d-y)*(d+y);
}
template<typename T,typename T1,typename Iterator>
inline T part_count(Iterator it,Iterator beg,Iterator end)
{
    T _count=0;
    while(beg!=end)
        if (is_intersect<T1>(it,beg++))
            _count++;
        return  _count;
}
template<bool B,bool C,typename T,typename T1,typename Iterator>
struct single_count {
    typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
    Iterator beg, end;
    difference_type len;

    single_count(Iterator b, Iterator e, difference_type l) : beg(b), end(e), len(l) {}

    inline T operator()(Iterator it) {
        auto l = end - it;
        if constexpr(B) {
            if constexpr(C)
                return part_count<T, T1, Iterator>(it, it+1, it + len+1);
            else
                return part_count<T, T1, Iterator>(it, it+1,  end) +
                       part_count<T, T1, Iterator>(it, beg, beg + (len - l+1));
        } else {
            if constexpr (C)
                return part_count<T,T1,Iterator>(it,it+1,it+len+1);
            else return part_count<T,T1,Iterator>(it,beg,it-len)+part_count<T,T1,Iterator>(it,it+1,it+(2*len-(it-beg)+1));
        }
    }
};
template<class T,class InputIt, class Op>
constexpr
inline T yyk_accumulate(InputIt first, InputIt last,
             Op op)
{
    T init=0;
    for (; first != last; ++first) {
        init +=op(first);
    }
    return init;
}
template<class T,class InputIt,class Op>
constexpr
inline T yyk_parallel_accumulate(InputIt first,InputIt last,Op op)
{
    auto len=last-first;
    if(len<45)
        return yyk_accumulate<T>(first,last,op);
    InputIt mid=first+len/2;
    auto handle=std::async(std::launch::async,yyk_parallel_accumulate<T,InputIt,Op>,mid,last,op);
    T sum= yyk_parallel_accumulate<T>(first,mid,op);
    return sum+handle.get();
}

template<typename T,typename Iterator>
inline T parallel_intersect_count(Iterator beg,Iterator end)
{
    typedef typename std::iterator_traits<Iterator>::value_type::second_type T1;
    auto size=end-beg;
    auto len=(size-1)/2;
    if(size>1)
    {
        if(size&1)
        {
            auto l1=yyk_parallel_accumulate<T>(beg,end-len,single_count<true,true,T,T1,Iterator>(beg,end,len));
            auto l2=yyk_parallel_accumulate<T>(end-len,end,single_count<true,false,T,T1,Iterator>(beg,end,len));
            return l1+l2;
        }
        else {
            auto l1=yyk_parallel_accumulate<T>(beg,beg+len+1,single_count<false,true,T,T1,Iterator>(beg,end,len));
            auto l2=yyk_parallel_accumulate<T>(beg+len+1,end-1,single_count<false,false,T,T1,Iterator>(beg,end,len));
            auto l3=part_count<T,T1,Iterator>(end-1,beg,end-1);
            return l1+l2+l3;
        }
    }else return T{0};
}
template<typename T,typename Iterator>
inline T intersect_count(Iterator beg,Iterator end)
{
    typedef typename std::iterator_traits<Iterator>::value_type::second_type T1;
    T init=0;
   while(++beg!=end)
       init+=part_count<T,T1>(beg-1,beg,end);
   return init;
}
#endif //INTERSECT_COUNT_INTERSECT_COUNT_H
