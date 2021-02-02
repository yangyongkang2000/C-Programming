//
//  CircleLight2D.cpp
//  CircleLight2D
//
//  Created by 杨永康 on 2021/1/25.
//

#include <iostream>
#include<random>
#include<algorithm>
#include<vector>
#include<memory>
#include<WolframImageLibrary.h>
#include "CircleLight2D.hpp"
EXTERN_C DLLEXPORT int CircleLight(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    using namespace CircleLight2D;
    MTensor tensor_0=MArgument_getMTensor(Args[0]);
    auto  data_0=libData->MTensor_getRealData(tensor_0);
    auto len_0=libData->MTensor_getFlattenedLength(tensor_0)>>2;
    _b=MArgument_getBoolean(Args[1]);
    auto range=libData->MTensor_getRealData(MArgument_getMTensor(Args[2]));
    auto wh=libData->MTensor_getIntegerData(MArgument_getMTensor(Args[3]));
    ImageInfo<double,mint> im(range[0],range[1],range[2],range[3],wh[0],wh[1]);
    auto condition=libData->MTensor_getRealData(MArgument_getMTensor(Args[4]));
    MAX_DISTANCE=condition[0];
    EPSILON=condition[1];
    auto condition_0=libData->MTensor_getIntegerData(MArgument_getMTensor(Args[5]));
    MAX_STEP=condition_0[0];
    n=condition_0[1];
    k=2*M_PI/n;
    std::vector<Circle2D<double>> v;
    v.reserve(len_0);
    for(auto i=0;i<len_0;i++)
     v.push_back({data_0[4*i+0],data_0[4*i+1],data_0[4*i+2],data_0[4*i+3]});
    auto imageFuns=libData->imageLibraryFunctions;
    MImage image_out;
    imageFuns->MImage_new2D(wh[0],wh[1],3,MImage_Type_Bit8,MImage_CS_RGB,True,&image_out);
    raw_t_ubit8 *out=imageFuns->MImage_getByteData(image_out);
    Circle_Light2D<3>(out,im,v);
    MArgument_setMImage(Res, image_out);
    return LIBRARY_NO_ERROR;
}
