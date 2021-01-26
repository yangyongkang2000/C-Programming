//
//    Light2D.hpp
//    Light2D
//
//  Created by 杨永康 on 2021/1/25.
//

#ifndef Light2D_
#define Light2D_
template<typename T,typename T1=int>
struct ImageInfo
{
    ImageInfo()=default;
    ImageInfo(T x_0,T x_1,T y_0,T y_1,T1 w,T1 h,T1 c):
    x0(x_0),x1(x_1),y0(y_0),y1(y_1),width(w),height(h),channels(c){
        x_delta=(x_1-x_0)/(w-1);
        y_delta=(y_0-y_1)/(h-1);
    }
    T1 width,height,channels;
    T x0,x1,y0,y1,x_delta,y_delta;
};
template<typename T>
struct point2d {
    point2d()=default;
    point2d(T _,T __):x(_),y(__){};
    T x,y;
};
template<typename T>
struct direction2d {
    direction2d()=default;
    direction2d(T alpha):dx(cos(alpha)),dy(sin(alpha)){};
    T dx,dy;
};
#endif
