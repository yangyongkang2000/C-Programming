//
//  BarnsleyFern.cpp
//  BarnsleyFern
//
//  Created by 杨永康 on 2021/1/17.
//

#include <random>
#include<valarray>
#include<algorithm>
#include<vector>
#include "WolframImageLibrary.h"
#include "BarnsleyFern.hpp"
EXTERN_C DLLEXPORT int BarnsleyFernPlot(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    using namespace std;
    vector<MTensor> Tensor_Vec;
    vector<double*> Real_Vec;
    Real_Vec.reserve(4);
    Tensor_Vec.reserve(6);
    for(auto i=0;i<=5;i++) Tensor_Vec.push_back(MArgument_getMTensor(Args[i]));
    auto init_color=static_cast<raw_t_ubit8>(MArgument_getInteger(Args[6]));
    auto iteration=MArgument_getInteger(Args[7]);
    for(auto i=0;i<=3;i++) Real_Vec.push_back(libData->MTensor_getRealData(Tensor_Vec[i]));
    auto WH=libData->MTensor_getIntegerData(Tensor_Vec[4]);
    valarray<mint> color_RGB{(libData->MTensor_getIntegerData(Tensor_Vec[5])),3};
    auto width=WH[0],height=WH[1];
    auto length=libData->MTensor_getFlattenedLength(Tensor_Vec[0]),length1=libData->MTensor_getFlattenedLength(Tensor_Vec[1]);
    BarnsleyFern<valarray, size_t> Obj({Real_Vec[0],static_cast<size_t>(length)},{Real_Vec[1],2},width,height,{Real_Vec[3],4});
    auto imageFuns=libData->imageLibraryFunctions;
    MImage image_out;
    imageFuns->MImage_new2D(width,height,3,MImage_Type_Bit8,MImage_CS_RGB,True,&image_out);
    raw_t_ubit8 *out=imageFuns->MImage_getByteData(image_out);
    fill_n(out, 3*width*height, init_color);
    random_device rd;
    mt19937 gen(rd());
    discrete_distribution<int> d(Real_Vec[1],Real_Vec[1]+length1);
    auto func=[&](auto &data_out,auto &row,auto &col){copy(begin(color_RGB), end(color_RGB), data_out+3*(col*width+row));};
    Obj.Plot(out, d, gen,func, iteration);
   MArgument_setMImage(Res, image_out);
    return LIBRARY_NO_ERROR;
}

