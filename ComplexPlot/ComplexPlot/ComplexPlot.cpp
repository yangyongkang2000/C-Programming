//
//  ComplexPlot.cpp
//  ComplexPlot
//
//  Created by 杨永康 on 2020/12/17.
//

#include<complex>
#include<array>
#include "WolframImageLibrary.h"
inline void ___(const std::complex<double> &z,raw_t_bit *out)
{
    using namespace std;
    using namespace std::complex_literals;
    complex<double> _z=(z-1.)*pow(z-1i,2.)*pow(z+1.,3.)/(z+1i);
    if(_z.real()>0)
    {
        out[_z.imag()>0?0:2]=1;
    }else{
        out[1]=1;
        out[_z.imag()>0?0:1]=1;
    }
}
namespace _Complex_Plot_
{
template<typename function_type>
inline void complex_plot(raw_t_bit *out, const double *point_data, const mint &width, const mint &height,const double &eps,const function_type &func)
{
    for (mint ii = 0; ii < height; ii++)
      for (mint jj = 0; jj < width; jj++)
          func({point_data[0]+jj*eps,point_data[1]-ii*eps}, out+3* (ii * width + jj));
}
}
EXTERN_C DLLEXPORT int complexplot(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    using namespace std;
    MTensor tensor=MArgument_getMTensor(Args[0]);
    double eps=MArgument_getReal(Args[1]);
    double *real_data=libData->MTensor_getRealData(tensor);
    mint width=(real_data[1]-real_data[0])/eps,height=(real_data[3]-real_data[2])/eps;
    auto imageFuns=libData->imageLibraryFunctions;
    MImage image_out;
    imageFuns->MImage_new2D(width,height,3,MImage_Type_Bit,MImage_CS_RGB,True,&image_out);
    raw_t_bit *out=imageFuns->MImage_getBitData(image_out);
    _Complex_Plot_::complex_plot(out, array<double,2>{real_data[0],real_data[3]}.data(),width, height, eps, ___);
    MArgument_setMImage(Res, image_out);
    return LIBRARY_NO_ERROR;
}


