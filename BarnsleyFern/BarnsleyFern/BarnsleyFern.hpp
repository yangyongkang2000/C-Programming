//
//  BarnsleyFern.hpp
//  BarnsleyFern
//
//  Created by 杨永康 on 2021/1/17.
//

#ifndef BarnsleyFern_
#define BarnsleyFern_
template<template<typename...>class C,typename T,typename D=double>
class ImageInfo{
public:
    ImageInfo(const T&w,const T&h, const C<D>&r):height(h),width(w),range(r),
    delta({(r[1]-r[0])/(w-1.),(r[2]-r[3])/(h-1.)}){}
    T width,height;
    C<D> range,delta;
};
template<template<typename...>class C,typename T,typename D=double>
class BarnsleyFern:public ImageInfo<C,T,D>
{
public:
    using Y=ImageInfo<C,T,D>;
    BarnsleyFern( C<D>&&m, C<D>&& ps,const T&w,const T&h, const C<D>&r):matrix(m),position(ps),
    ImageInfo<C,T,D>(w,h,r){}
    C<D> matrix,position;
    template<typename data_type,typename Random,typename G,typename function_type>
    void Plot(data_type *data_out,Random &d, G&gen,const function_type &func,const uint64_t &iteration)
    {
        for(auto i=0;i<iteration;i++)
        {
            _(d(gen));
            func(data_out,row,col);
        }
    }
private:
    T row,col;
    template<typename Index>
    inline void _(const Index&i) {
        D p1=matrix[6*i]*position[0]+matrix[6*i+1]*position[1]+matrix[6*i+2];
        D p2=matrix[6*i+3]*position[0]+matrix[6*i+4]*position[1]+matrix[6*i+5];
        position[0]=p1;
        position[1]=p2;
        __();
    }
    inline void __(){
        row=lround((position[0]-Y::range[0])/Y::delta[0]);
        col=lround((position[1]-Y::range[3])/Y::delta[1]);
    }
};
#endif
