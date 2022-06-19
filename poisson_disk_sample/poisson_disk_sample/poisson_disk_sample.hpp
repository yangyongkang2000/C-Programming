//
//  poisson_disk_sample.hpp
//  poisson_disk_sample
//
//  Created by 杨永康 on 2022/6/18.
//

#ifndef poisson_disk_sample_h
#define poisson_disk_sample_h
#include<numbers>
#include<algorithm>
#include<array>
#include<random>
#include<utility>
#include<cmath>
#include<iterator>
template<int N,int Max_Retry=100,typename T=double,typename InputIt>
inline InputIt poisson_disk_sample(InputIt beg,InputIt end) noexcept
{
    using P=typename std::iterator_traits<InputIt>::value_type;
    constexpr auto r=std::numbers::sqrt2_v<T>/N;
    static std::array<int, N*N> grid;
    grid.fill(-1);
    auto check=[&](auto x,auto y,auto _w,auto _h)
    {
        
        auto w0=std::max(0,_w-2);
        auto w1=std::min(N,_w+3);
        auto h0=std::max(0,_h-2);
        auto h1=std::min(N,_h+3);
        for(int h=h0;h<h1;h++)
            for(int w=w0;w<w1;w++)
                if(grid[N*h+w]!=-1){
                    auto &q=*(beg+grid[N*h+w]);
                    auto d1=(x-q[0])*(x-q[0]);
                    auto d2=(r+y-q[1])*(r+q[1]-y);
                    if(d1<d2)
                        return false;
                }
        return true;
    };
    *beg=P{0.5,0.5};
    grid[(N/2)*(N+1)]=0;
    auto head=0,tail=1;
    auto len=end-beg;
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<T> dis(0,1);
    static std::array<std::pair<T,T>,Max_Retry> r_theta;  //add
    static std::array<std::pair<T,T>,Max_Retry> xy_l;  //add
    while(head<tail)
    {
        auto & p=*(beg+head);
        head++;
        std::generate_n(r_theta.begin(), Max_Retry, [&]{return std::pair<T,T>{(dis(gen)+1)*r,dis(gen)*2*std::numbers::pi_v<T>};});
        std::transform(r_theta.begin(), r_theta.end(), xy_l.begin(), [&](auto &rt){return std::pair<T,T>{p[0]+rt.first*std::cos(rt.second),p[1]+rt.first*std::sin(rt.second)};});
        for(auto &[x,y]:xy_l)
            if(0<=x&&x<1&&0<=y&&y<1){
                auto w=static_cast<int>(x*N);
                auto h=static_cast<int>(y*N);
                if(check(x,y,w,h)){
                    *(beg+tail)={x,y};
                    grid[h*N+w]=tail++;
                    if(tail>=len) return end;
                }
            }
        /*for(int _=0;_<Max_Retry;_++)
        {
            auto theta=dis(gen)*2*std::numbers::pi_v<T>;
            auto tr=(dis(gen)+1)*r;
            auto x=p[0]+tr*std::cos(theta);
            if(x<0||x>=1) continue;
            auto y=p[1]+tr*std::sin(theta);
            if(y<0||y>=1) continue;
            auto w=static_cast<int>(x*N);
            auto h=static_cast<int>(y*N);
            if(check(x,y,w,h)){
                *(beg+tail)={x,y};
                grid[h*N+w]=tail++;
                if(tail>=len) return end;
            }
        }    */  //delete
    }
    return beg+tail;
}

#endif /* poisson_disk_sample_h */
