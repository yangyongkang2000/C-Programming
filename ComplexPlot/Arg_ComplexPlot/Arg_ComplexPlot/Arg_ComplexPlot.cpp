//
//  Arg_ComplexPlot.cpp
//  Arg_ComplexPlot
//
//  Created by 杨永康 on 2021/1/24.
//


#include<complex>
#include<WolframImageLibrary.h>
#include"Arg_ComplexPlot.hpp"
template<typename T=double>
std::complex<T> complex_func(const std::complex<T> &z)
{
    using namespace std::complex_literals;
    return (z-14.+4.6i)*(z-12.+5.i)*(z+7.+14.i)/std::pow(z-15.i,3.);
}
template<typename data_pointer,typename T=double>
void color_func(const data_pointer&data_out,const std::complex<T>&x)
{
    T p[3]={0.5*(std::arg(x)/M_PI+1),1,1.};
    std::copy(p, p+3, data_out);
}

EXTERN_C DLLEXPORT int arg_plot(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    
    double * range=libData->MTensor_getRealData(MArgument_getMTensor(Args[0]));
    mint * wh=libData->MTensor_getIntegerData(MArgument_getMTensor(Args[1]));
    ImageInfo<double,mint> im(range[0],range[1],range[2],range[3],wh[0],wh[1],3);
    auto imageFuns=libData->imageLibraryFunctions;
    MImage image_out;
    imageFuns->MImage_new2D(wh[0],wh[1],3,MImage_Type_Real,MImage_CS_HSB,True,&image_out);
    auto out=imageFuns->MImage_getRealData(image_out);
    Arg_Complexplot(out, complex_func<>, im, color_func<decltype(out)>);
    MArgument_setMImage(Res, image_out);
    return LIBRARY_NO_ERROR;
}
