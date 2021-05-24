//
//  tmp.cpp
//  TMA
//
//  Created by 杨永康 on 2021/5/19.
//

#include <stdio.h>
#include<cmath>
#include "WolframImageLibrary.h"
#include "tmp.hpp"
namespace swirly {
template<typename I>
inline unsigned char RD(I i,I j) noexcept {
    return(sqrt(_sq(148.-i)+_sq(1000-j))+1)/(sqrt(abs(sin((sqrt(_sq(500.-i)+_sq(400-j)))/115.0)))+1);
}
template<typename I>
inline unsigned char GR(I i,I j) noexcept{
    return(sqrt(_sq(610.-i)+_sq(60-j))+1)/(sqrt(abs(sin((sqrt(_sq(864.-i)+_sq(860-j)))/115.0)))+1);
}
template<typename I>
inline unsigned char BL(I i,I j) noexcept {
    return(sqrt(_sq(180.-i)+_sq(100-j))+1)/(sqrt(abs(sin((sqrt(_sq(503.-i)+_sq(103-j)))/115.0)))+1);
}
}
namespace lyapunov {
static int _k[4];
template<typename I,typename T=float>
inline constexpr std::pair<T,T> mid_result(I i,I j) noexcept
{
    T x=0,y=0;
    for(int k=0;k++<_k[3];){
        T t=_sq(sin(x))-_sq(cos(y))+(i-512.)/512;
        y=2*sin(x)*cos(y)+(j-512.0)/512;
        x=t;}
    return {x,y};
}
template<int K,typename I,typename T=float>
inline unsigned char GR_BL(I i,I j) noexcept{
    auto r(mid_result<I,T>(i, j));
    if constexpr(K==0)
        return _k[0]*(_sq(r.first)+_sq(r.second));
    if constexpr(K==1)
        return _k[1]*fabs(r.first);
    else
        return _k[2]*fabs(r.second);
}
}
namespace spiral {
static int _kk[3];
template<typename I>
unsigned char BL(I i,I j) noexcept {
    i -= _kk[0]/ 2;
    j -= _kk[1] / 2;
    double theta = atan2(j,i);
    double prc = theta / 3.14f / 2.0f;

    I dist = sqrt(i*i + j*j);
    I makeSpiral = prc * _kk[2] / 2;
    I waves = sin(_cr(dist * dist)) * 32 + sin(theta * 10) * 64;
    return dist + makeSpiral + waves;
}
template<typename I>
unsigned char RD(I i,I j) noexcept {
    return (_kk[0]+_kk[1])/2 - BL(2*i, 2*j);
}
template<typename I>
unsigned char GR(I i,I j) noexcept {
    return BL(j,i)+128;
}
}
EXTERN_C DLLEXPORT int spiral_plot(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    auto tensor=MArgument_getMTensor(Args[0]);
    auto data=libData->MTensor_getIntegerData(tensor);
    std::copy(data, data+3, spiral::_kk);
    auto width=data[0];
    auto height=data[1];
    auto imageFuns=libData->imageLibraryFunctions;
    MImage image_out;
    imageFuns->MImage_new2D(width,height,3,MImage_Type_Bit8,MImage_CS_RGB,True,&image_out);
    raw_t_ubit8 *out=imageFuns->MImage_getByteData(image_out);
    tmp_plot<true>(spiral::RD<mint>,spiral::GR<mint>,spiral::BL<mint>, out,(mint)0, height, width);
    MArgument_setMImage(Res, image_out);
    return LIBRARY_NO_ERROR;
}
EXTERN_C DLLEXPORT int swirly_plot(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    mint width=MArgument_getInteger(Args[0]);
    mint height=MArgument_getInteger(Args[1]);
    auto imageFuns=libData->imageLibraryFunctions;
    MImage image_out;
    imageFuns->MImage_new2D(width,height,3,MImage_Type_Bit8,MImage_CS_RGB,True,&image_out);
    raw_t_ubit8 *out=imageFuns->MImage_getByteData(image_out);
    tmp_plot<true>(swirly::RD<mint>, swirly::GR<mint>, swirly::BL<mint>, out, (mint)0, height, width);
    MArgument_setMImage(Res, image_out);
    return LIBRARY_NO_ERROR;
}
EXTERN_C DLLEXPORT int lyapunov_plot(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    auto tensor=MArgument_getMTensor(Args[0]);
    auto data=libData->MTensor_getIntegerData(tensor);
    std::copy(data, data+4, lyapunov::_k);
    auto width=data[4];
    auto height=data[5];
    auto imageFuns=libData->imageLibraryFunctions;
    MImage image_out;
    imageFuns->MImage_new2D(width,height,3,MImage_Type_Bit8,MImage_CS_RGB,True,&image_out);
    raw_t_ubit8 *out=imageFuns->MImage_getByteData(image_out);
    tmp_plot<true>(lyapunov::GR_BL<0,mint>, lyapunov::GR_BL<1,mint>,lyapunov::GR_BL<2,mint>, out,(mint)0, height, width);
    MArgument_setMImage(Res, image_out);
    return LIBRARY_NO_ERROR;
}
