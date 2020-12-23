//
//  Region_ComplexPlot.cpp
//  Region_ComplexPlot
//
//  Created by 杨永康 on 2020/12/19.
//

#include <complex>
#include<array>
#include<vector>
#include "WolframImageLibrary.h"
template<typename  data_type>
inline void ___(const std::complex<double> &z,data_type *out,const double * range_data,const unsigned char *rgb_data)
{
    using namespace std;
    using namespace std::complex_literals;
    auto func=[](const double &x,const double *range_data)->char
    {return x<range_data[0]?0:(x>range_data[1]?2:1);};
    complex<double> _z=(z-1.)*pow(z-1i,2.)*pow(z+1.,3.)/(z+1i);
    auto _func=[&rgb_data,&out](const auto &col,const auto &row)
    {copy(rgb_data+9*col+3*row, rgb_data+9*col+3*row+3, out);};
    _func(func(_z.real(),range_data),func(_z.imag(),range_data+2));
}
namespace _Complex_Plot_
{
template<typename data_type,typename function_type>
inline void complex_plot(data_type *out, const double *point_data, const mint &width, const mint &height,const double &eps,const function_type &func,const double * range_data,const unsigned char *rgb_data)
{
    for (mint ii = 0; ii < height; ii++)
      for (mint jj = 0; jj < width; jj++)
          func({point_data[0]+jj*eps,point_data[1]-ii*eps}, out+3* (ii * width + jj),range_data,rgb_data);
}
}
EXTERN_C DLLEXPORT int regioncomplexplot(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    using namespace std;
    MTensor tensor=MArgument_getMTensor(Args[0]),tensor1=MArgument_getMTensor(Args[2]),tensor3=MArgument_getMTensor(Args[3]);
    double eps=MArgument_getReal(Args[1]),*real_data=libData->MTensor_getRealData(tensor),*range_data=libData->MTensor_getRealData(tensor1);
    mint *rgb=libData->MTensor_getIntegerData(tensor3);
    vector<unsigned char> rgb_data(rgb,rgb+9);
    
    mint width=ceil((real_data[1]-real_data[0])/eps),height=ceil((real_data[3]-real_data[2])/eps);
       auto imageFuns=libData->imageLibraryFunctions;
       MImage image_out;
       imageFuns->MImage_new2D(width,height,3,MImage_Type_Bit8,MImage_CS_RGB,True,&image_out);
       raw_t_ubit8 *out=imageFuns->MImage_getByteData(image_out);
    _Complex_Plot_::complex_plot(out, array<double,2>{real_data[0],real_data[3]}.data(),width, height, eps, ___<raw_t_ubit8>,range_data,rgb_data.data());
    MArgument_setMImage(Res, image_out);
    return LIBRARY_NO_ERROR;
}
