//
//  main.cpp
//  integer_vector_to_file
//
//  Created by 杨永康 on 2021/3/20.
//
#include"WolframLibrary.h"
#include"read_write_vector_file.hpp"
EXTERN_C DLLEXPORT int read(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) noexcept
{
    constexpr size_t N=800000;
    constexpr size_t M=10;
    auto file_in=MArgument_getUTF8String(Args[0]);
    const mint  size[1]={static_cast<mint>(std::filesystem::file_size(std::filesystem::path(file_in))/M)};
    MTensor tensor;
    libData->MTensor_new(MType_Integer,1,size,&tensor);
    mint * result=libData->MTensor_getIntegerData(tensor);
    file_to_vector<N, M>(file_in,result);
    MArgument_setMTensor(Res, tensor);
    return LIBRARY_NO_ERROR;
}
EXTERN_C DLLEXPORT int write(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) noexcept
{
    auto tensor=MArgument_getMTensor(Args[0]);
    auto list=libData->MTensor_getIntegerData(tensor);
    auto size=libData->MTensor_getDimensions(tensor);
    auto file_out=MArgument_getUTF8String(Args[1]);
   vector_to_file< 800000, 10>(list,static_cast<size_t>(size[0]), file_out);
    MArgument_setUTF8String(Res, file_out);
    return LIBRARY_NO_ERROR;
}
