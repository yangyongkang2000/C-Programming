//
//  near_point.hpp
//  nearest_point
//
//  Created by 杨永康 on 2021/4/30.
//

#ifndef near_point_h
#define near_point_h
#include<type_traits>
#include<algorithm>
template<typename P>
inline constexpr P min_result(P const &p1,P const & p2) noexcept
{
    return std::min(p1, p2, [](auto &p1,auto &p2){return p1.second<p2.second;});
}
template<typename P,typename T=typename P::first_type>
inline constexpr T square_point_dist(P const &p1,P const &p2) noexcept
{
    static_assert(std::is_same<T,typename P::second_type>::value,"type isn't match");
    const auto & x=p1.first-p2.first;
    const auto & y=p1.second-p2.second;
    return x*x+y*y;
}
template<template<typename ...> class V,typename InputIt,typename InputIt1,typename T=typename std::iterator_traits<InputIt>::value_type::first_type,typename Result_Type=std::pair<std::pair<InputIt, InputIt>, T>>
inline constexpr Result_Type ___near_point(InputIt beg,InputIt end,InputIt1 beg1,InputIt1 end1) noexcept
{
    using P=typename std::iterator_traits<InputIt>::value_type;
    auto len=end-beg;
    if(len<=1)
        return {{end,end},std::numeric_limits<T>::max()};
    switch (len) {
        case 2:
            return {{beg,beg+1},square_point_dist(*beg, *(beg+1))};
        case 3:
        {
            auto  d1=square_point_dist(*beg, *(beg+1));
            auto  d2=square_point_dist(*beg, *(beg+2));
            auto  d3=square_point_dist(*(beg+1), *(beg+2));
            return std::min<Result_Type>({{{beg,beg+1},d1},{{beg,beg+2},d2},{{beg+1,beg+2},d3}},[](auto &p1,auto &p2){
                return p1.second<p2.second;
            });
        }
        default:
        {
            auto mid=beg+len/2;
            auto  r1=___near_point<V>(beg, mid, beg1, end1);
            auto  r2=___near_point<V>(mid,end, beg1, end1);
            auto  min_r(std::min(r1, r2,[](auto & p1,auto &p2)
                                  {
                return p1.second<p2.second;
            }));
            auto  sigma=min_r.second;
            auto  mid_x=(*mid).first;
            V<std::pair<P,InputIt>> Q;
            for(auto it=beg1;it!=end1;it++)
            {
                auto  x = it->first.first;
                if(x>=mid_x-sigma&&x<=mid_x+sigma)
                    Q.push_back(*it);
            }
            for(auto it=Q.begin();it!=Q.end();it++)
              for(auto it1=it+1;it1!=Q.end();it1++)
            {
                auto  y= it1->first.second-it->first.second;
                if(y>sigma)
                    break;
                else {
                    auto  x=it1->first.first-it->first.first;
                    auto  d=x*x+y*y;
                    if(d<sigma)
                    {
                        sigma=d;
                        min_r=std::move<Result_Type>({{it->second,it1->second},d});
                    }
                }
            }
            return min_r;
        }
    }
}
template<template<typename ...> class V,typename InputIt,typename T=typename std::iterator_traits<InputIt>::value_type::first_type,typename Result_Type=std::pair<std::pair<InputIt, InputIt>, T>>
inline constexpr Result_Type bin_near_point(InputIt beg,InputIt end)
{
    using P=typename std::iterator_traits<InputIt>::value_type;
    auto len=end-beg;
    if(len<=1)
        return {{end,end},std::numeric_limits<T>::max()};
    switch (len) {
        case 2:
            return {{beg,beg+1},square_point_dist(*beg, *(beg+1))};
        case 3:
        {
            auto  d1=square_point_dist(*beg, *(beg+1));
            auto  d2=square_point_dist(*beg, *(beg+2));
            auto  d3=square_point_dist(*(beg+1), *(beg+2));
            return std::min<Result_Type>({{{beg,beg+1},d1},{{beg,beg+2},d2},{{beg+1,beg+2},d3}},[](auto &p1,auto &p2){
                return p1.second<p2.second;
            });
        }
        default:
        {
            V<std::pair<P, InputIt>> Q;
            std::sort(beg, end, [](auto &x,auto &y){return x.first<y.first;});
            Q.reserve(len);
            for(auto it=beg;it!=end;it++)
                Q.emplace_back(std::pair<P, InputIt>{*it,it});
            std::sort(Q.begin(), Q.end(), [](auto &x,auto &y){return x.first.second<y.first.second;});
            return ___near_point<V>(beg, end, Q.begin(), Q.end());
        }
    }
    
}
#endif /* near_point_h */
