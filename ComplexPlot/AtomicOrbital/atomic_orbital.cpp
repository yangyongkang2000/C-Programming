#include<cmath>
#include<valarray>
#include<algorithm>
#include"special_function.hpp"
#include<WolframImageLibrary.h>
template<typename T,typename T1=int>
struct ImageInfo
{
    ImageInfo(T x_0,T x_1,T y_0,T y_1,T1 w,T1 h,T1 c):
    x0(x_0),x1(x_1),y0(y_0),y1(y_1),width(w),height(h),channels(c){
        x_delta=(x_1-x_0)/(w-1);
        y_delta=(y_0-y_1)/(h-1);
    }
    T x0,x1,y0,y1,x_delta,y_delta;
    T1 width,height,channels;
};
template<int n,typename T=double>
inline T template_pow(T x)
{
    if constexpr(n==1)
        return x;
    else return n&1?x*template_pow<n/2,T>(x*x):template_pow<n/2,T>(x*x);
}
template<int n,int l,int m,typename T=double>
inline T atomic_orbital_probability(const T x,const T y)
{
      T s=sqrt(x*x+y*y);
    return  exp(-2*s/n)*template_pow<2*l,T>(2*s/n)*composite_function<n,l,m>(y/s,2*s/n);
}
template<typename T,typename T1>
inline void color_func(T *data_out,const T1 x)
{
   data_out[0]=1-pow(x,0.25);
   data_out[1]=1.-data_out[0];
   data_out[2]=1.;
}
template<int n,int l,int m,int k,typename T=double,class I,typename D,typename R>
inline void find_condition(mint *nlm,const I&im,D out,R &result)
{
    if(nlm[0]==n&&nlm[1]==l&&nlm[2]==m)
    {
        for(auto i=0;i<im.height;i++)
           for(auto j=0;j<im.width;j++)
                result[i*im.width+j]=atomic_orbital_probability<n,l,m,T>(im.x0+(j-1)*im.x_delta,im.y1+(i-1)*im.y_delta);
    }
    if constexpr(n<k)
        find_condition<n+1,l,m,k>(nlm,im,out,result);
    if constexpr(l<n-1)
        find_condition<n,l+1,m,k>(nlm,im,out,result);
    if constexpr(m<l)
        find_condition<n,l,m+1,k>(nlm,im,out,result);
}

EXTERN_C DLLEXPORT int atomic_orbital_density_plot(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    mint * nlm=libData->MTensor_getIntegerData(MArgument_getMTensor(Args[0]));
    double * range=libData->MTensor_getRealData(MArgument_getMTensor(Args[1]));
    mint * wh=libData->MTensor_getIntegerData(MArgument_getMTensor(Args[2]));
    ImageInfo<double,mint> im(range[0],range[1],range[2],range[3],wh[0],wh[1],3);
    auto imageFuns=libData->imageLibraryFunctions;
    MImage image_out;
    imageFuns->MImage_new2D(wh[0],wh[1],3,MImage_Type_Real,MImage_CS_HSB,True,&image_out);
    auto out=imageFuns->MImage_getRealData(image_out);
    std::valarray<double> result(wh[0]*wh[1]);
    find_condition<2,1,0,10>(nlm,im,out,result);
    const auto p=std::minmax_element(std::begin(result),std::end(result));
    const auto q=*p.second-*p.first;
    for(auto i=0;i<im.height;i++)
       for(auto j=0;j<im.width;j++)
         color_func(out+im.channels*(i*im.width+j), (result[i*im.width+j]-*p.first)/q);
    MArgument_setMImage(Res, image_out);
    return LIBRARY_NO_ERROR;
}
