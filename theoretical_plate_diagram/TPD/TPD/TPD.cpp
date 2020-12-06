//
//  TPD.cpp
//  TPD
//
//  Created by 杨永康 on 2020/12/6.
//

#include<vector>
#include<array>
#include"theoretical_plate_diagram.hpp"
#include<WolframLibrary.h>

EXTERN_C DLLEXPORT int TPD(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    using namespace std;
    vector<double> _cond;
    for(int i=0;i<Argc;i++)
    _cond.push_back(MArgument_getReal(Args[i]));
    auto result=chemistry::TPD<vector<double>, vector<array<double,2>>>(_cond);
    MTensor tensor;
    array<mint,2> dims {static_cast<mint>(result.size()),2};
    libData->MTensor_new(MType_Real,2,dims.data(),&tensor);
    double *list=libData->MTensor_getRealData(tensor);
    for(int i=0;i<result.size();i++)
    {
        list[2*i]=result[i][0];
        list[2*i+1]=result[i][1];
    }
    MArgument_setMTensor(Res,tensor);
    return LIBRARY_NO_ERROR;
}
