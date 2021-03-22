#  高性能(?)一维数组读写文件程序
## 前言
> 写一个将简单的一维数组写入文本和配套的从文本读入数组的程序，用C++开发，需要编译器支持C++17以上标准，因为我用到了 std::to_chars()函数还有filesystem库，当然可以不用它们。有些编译器不支持std::to_chars()对浮点数的支持。
## 读写说明
```C++
template<size_t N,size_t M,bool parallel=true,char Ch='\n',typename Input_It>
inline void vector_to_file(Input_It it,size_t len,char *file_out) noexcept
```
> 这是写函数,比如对一个数组{1,2,3} ,默认以 
``` 
1\0\0\0...\n
2\0\0\0...\n
3\0\0\0...\n
```
> \0的个数与M和要被读入的数有关


> 写函数
```C++
template<size_t N,size_t M,bool parallel=true,typename OutPut_It>
void file_to_vector(char *file_in,OutPut_It result) noexcept
```
> 配套的将文本写入数组
> 将
```C++
1\0\0\0...\n
2\0\0\0...\n
3\0\0\0...\n
```
> 转换为 {1,2,3}


## 性能测试
> 方便进行性能与正确性测试，写成动态库，与Wolfram语言交互使用。
> 更多交互例子可以看我的[GitHub](https://github.com/yangyongkang2000/C-CPP_WolframLibrary_Example)



```C++
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
```


## 测试结果
> 先导入动态库
```Mathematica
write = LibraryFunctionLoad[
  "/Users/yangyongkang/Library/Developer/Xcode/DerivedData/integer_\
vector_to_file-addrzseyucjvtgehtkwecfcdmaec/Build/Products/Release/\
libinteger_vector_to_file.dylib", "write", {{Integer, 1}, String}, 
  String];
read = LibraryFunctionLoad[
  "/Users/yangyongkang/Library/Developer/Xcode/DerivedData/integer_\
vector_to_file-addrzseyucjvtgehtkwecfcdmaec/Build/Products/Release/\
libinteger_vector_to_file.dylib", "read", {String}, {Integer, 1}]  
```



>本文测试完整代码
```Mathematica
Table[With[{t = RandomInteger[10^n, 10^n]}, {First@
    AbsoluteTiming@write[t, "/Users/yangyongkang/Desktop/a.txt"], 
   AbsoluteTiming@(read["/Users/yangyongkang/Desktop/a.txt"] == t), 
   FileSize["/Users/yangyongkang/Desktop/a.txt"]}], {n, 1, 6}]
```
>测试结果

![benchmark](https://github.com/yangyongkang2000/C-Programming/raw/master/integer_vector_to_file/source/benchmark.jpg)

