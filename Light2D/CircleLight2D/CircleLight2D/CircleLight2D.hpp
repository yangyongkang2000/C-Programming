//
//  CircleLight2D.hpp
//  CircleLight2D
//
//  Created by 杨永康 on 2021/1/25.
//

#ifndef CircleLight2D_
#define CircleLight2D_
#include"Light2D.hpp"
namespace CircleLight2D {
static double MAX_DISTANCE,EPSILON,k;
static long long MAX_STEP,n;
static bool _b;
template<typename T=double>
struct Circle2D
{
    Circle2D(T x,T y,T _,T e):ox(x),oy(y),r(_),emissive(e){};
    T ox,oy,r,emissive;
};
template<typename T>
inline T shape_sdf(const point2d<T> &p,const Circle2D<T>&shape)
{
   return sqrt(pow(p.x-shape.ox,2)+pow(p.y-shape.oy, 2))-shape.r;
}
template<class ForwardIt,typename T>
ForwardIt shape_max_element(const point2d<T> &p,ForwardIt first, ForwardIt last)
{
    if (first == last) {
        return last;
    }
    ForwardIt largest = first;
    ++first;
    for (; first != last; ++first) {
        if (shape_sdf(p,*largest) <shape_sdf(p, *first)) {
            largest = first;
        }
    }
    return largest;
}
template<class ForwardIt,typename T>
inline ForwardIt shape_min_element(const point2d<T> &p,ForwardIt first, ForwardIt last)
{
    if (first == last) return last;
 
    ForwardIt smallest = first;
    ++first;
    for (; first != last; ++first) {
        if (shape_sdf(p,*first) < shape_sdf(p,*smallest)) {
            smallest = first;
        }
    }
    return smallest;
}
template<template<typename...> class C,typename T=double>
inline auto scene(const point2d<T> &p,const C<Circle2D<T>> &shape)
{
       if(_b)
           return shape_min_element(p,shape.begin(), shape.end());
    return shape_max_element(p,shape.begin(), shape.end());
}
template<template<typename...> class C,typename T=double>
inline T trace(const point2d<T> &p,const direction2d<T> &d,const C<Circle2D<T>> &shape)
{
    T t=0.001;
    for(auto i=0;i<MAX_STEP&&t<MAX_DISTANCE;i++)
    {
        auto  it=scene({p.x+t*d.dx,p.y+t*d.dy}, shape);
        T r=shape_sdf({p.x+t*d.dx,p.y+t*d.dy}, *it);
        if(r<EPSILON)
            return it->emissive;
        t+=r;
    }
    return 0;
}
template<template<typename...> class C,typename T=double>
inline T sample(const point2d<T>&p,const  C<Circle2D<T>>&shape)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<T> dis(0,1);
    T sum=0;
    for(auto i=0;i<n;i++)
        sum+=trace(p, {k*(i+dis(gen))}, shape);
    return sum/n;
}
template<typename data_pointer,typename T=double>
inline void color_func(const data_pointer&data_out,const T&f)
{
    using ch=typename std::pointer_traits<data_pointer>::element_type;
    std::fill_n(data_out, 3, static_cast<ch>(f>1.0?255:255*f));
}
template<int channels,typename data_pointer,template<typename ...> class C,typename T=double,typename I=int>
inline void Circle_Light2D(const data_pointer &data_out,const ImageInfo<T,I>&im,const C<Circle2D<T>> &shape)
{
    for(auto i=0;i<im.height;i++)
    for(auto j=0;j<im.width;j++)
       color_func(data_out+channels*(i*im.width+j),sample({im.x0+(j-1)*im.x_delta,im.y1+(i-1)*im.y_delta},shape));
}
}
#endif
