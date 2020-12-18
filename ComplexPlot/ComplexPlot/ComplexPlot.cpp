//
//  ComplexPlot.cpp
//  ComplexPlot
//
//  Created by 杨永康 on 2020/12/17.
//

#include<complex>
#include<array>
#include "WolframImageLibrary.h"
template<typename data_type>
inline void ___(const std::complex<double> &z,data_type *out)
{
    using namespace std;
    using namespace std::complex_literals;
    complex<double> _z=(z-1.)*pow(z-1i,2.)*pow(z+1.,3.)/(z+1i);
    if(abs(_z.real())<1e-322||abs(_z.imag())<1e-322)
        return;
    using T = array<unsigned char,3> ;
    auto func=[&out](const T &rgb){copy(rgb.begin(), rgb.end(), out);};
    if(_z.real()>0)
        func(_z.imag()>0?T{219,57,43}:T{30,68,124});
    else
        func(_z.imag()>0?T{241,229,57}:T{90,178,69});
}
namespace _Complex_Plot_
{
template<typename data_type,typename function_type>
inline void complex_plot(data_type *out, const double *point_data, const mint &width, const mint &height,const double &eps,const function_type &func)
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
    mint width=ceil((real_data[1]-real_data[0])/eps),height=ceil((real_data[3]-real_data[2])/eps);
    auto imageFuns=libData->imageLibraryFunctions;
    MImage image_out;
    imageFuns->MImage_new2D(width,height,3,MImage_Type_Bit8,MImage_CS_RGB,True,&image_out);
    raw_t_ubit8 *out=imageFuns->MImage_getByteData(image_out);
    _Complex_Plot_::complex_plot(out, array<double,2>{real_data[0],real_data[3]}.data(),width, height, eps, ___<raw_t_ubit8>);
    MArgument_setMImage(Res, image_out);
    return LIBRARY_NO_ERROR;
}


