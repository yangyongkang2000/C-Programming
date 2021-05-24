#include<cmath>
#include<WolframImageLibrary.h>
#include<algorithm>
#include<valarray>
#include "atomic_orbital.h"
template<typename T=double,class I,typename D>
inline void atmoic_orbital(const mint *nlm,const mint *wh,const I&im,D out)
{
    std::valarray<T> result(wh[0]*wh[1]);
    for(auto i=0;i<im.height;i++)
        for(auto j=0;j<im.width;j++)
            result[i*im.width+j]=atomic_orbital_probability(nlm[0],nlm[1],nlm[2],im.x0+(j-1)*im.x_delta,im.y1+(i-1)*im.y_delta);
    const auto p=std::minmax_element(std::begin(result),std::end(result));
    const auto q=*p.second-*p.first;
    for(auto i=0;i<im.height;i++)
        for(auto j=0;j<im.width;j++)
            color_func(out+im.channels*(i*im.width+j), (result[i*im.width+j]-*p.first)/q);
}
EXTERN_C DLLEXPORT int atomic_orbital_density_plot(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    mint * nlm=libData->MTensor_getIntegerData(MArgument_getMTensor(Args[0]));
    double * range=libData->MTensor_getRealData(MArgument_getMTensor(Args[1]));
    mint * wh=libData->MTensor_getIntegerData(MArgument_getMTensor(Args[2]));
    ImageInfo<double,mint> im(range[0],range[1],range[2],range[3],wh[0],wh[1],3);
    auto imageFuns=libData->imageLibraryFunctions;
    MImage image_out;
    imageFuns->MImage_new2D(wh[0],wh[1],3,MImage_Type_Bit8,MImage_CS_RGB,True,&image_out);
    auto out=imageFuns->MImage_getByteData(image_out);
    atmoic_orbital(nlm,wh,im,out);
    MArgument_setMImage(Res, image_out);
    return LIBRARY_NO_ERROR;
}



