//
//  Arg_ComplexPlot.hpp
//  Arg_ComplexPlot
//
//  Created by 杨永康 on 2021/1/24.
//

#ifndef Arg_ComplexPlot_
#define Arg_ComplexPlot_
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
template<typename C,typename data_pointer,typename F,typename Image>
void Arg_Complexplot(const data_pointer &data_out,const C &cf,const Image&im,const F&f)
{
    for(auto i=0;i<im.height;i++)
    for(auto j=0;j<im.width;j++)
    f(data_out+im.channels*(i*im.width+j),cf({im.x0+(j-1)*im.x_delta,im.y1+(i-1)*im.y_delta}));
}

#endif
