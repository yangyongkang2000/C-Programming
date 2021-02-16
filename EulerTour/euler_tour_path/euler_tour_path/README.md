#  欧拉回路与一笔画问题
## 前言 
> 欧拉回路与一笔画(欧拉环游)差不多有相同的解法，当一笔画不存在连通度为奇数的结点，就是欧拉回路问题，存在两个连通度为奇数的结点，只需要将这两个结点相连接，就变成了欧拉回路，本文用C++简单实现欧拉回路与一笔画问题，封装函数，在Wolfram语言条件下进行测试，开发Wolfram语言的欧拉回路内核函数，并与Wolfram内置函数进行比较。
## 介绍
> 本文不会提供对算法的介绍，而只是介绍一下链接函数。
```C++
EXTERN_C DLLEXPORT int euler_tour_path(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    auto tensor=MArgument_getMTensor(Args[0]);
    auto data=libData->MTensor_getIntegerData(tensor);
    auto dims=libData->MTensor_getDimensions(tensor);
    auto list(find_euler_tour_path<std::vector, std::list>(data, dims[0]));
    if(list.empty())
        return LIBRARY_FUNCTION_ERROR;
    MTensor result;
    libData->MTensor_new(MType_Integer,1,std::array<mint,1>{static_cast<long long>(list.size())}.data(),&result);
    auto p=libData->MTensor_getIntegerData(result);
    for(auto _:list)
        *p++=_;
    MArgument_setMTensor(Res, result);
    return LIBRARY_NO_ERROR;
}
```
>上面是链接函数的代码，接受一个参数
```C++
auto tensor=MArgument_getMTensor(Args[0]);
auto data=libData->MTensor_getIntegerData(tensor);
auto dims=libData->MTensor_getDimensions(tensor);
```
> 很容易看到接受到的参数为整数数组。
```C++
MTensor result;
    libData->MTensor_new(MType_Integer,1,std::array<mint,1>{static_cast<long long>(list.size())}.data(),&result);
    auto p=libData->MTensor_getIntegerData(result);
```
> 返回的结果是一维整数数组
