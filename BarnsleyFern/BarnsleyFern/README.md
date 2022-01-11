#  BarnsleyFern 介绍

## 关于BarnseleyFern介绍文档：
+ 参考[网页](https://en.wikipedia.org/w/index.php?title=Barnsley_fern&oldid=980949611)或者GitHub项目中的PDF文件。
## 实现方式
+ 利用WolframImageLibrary库,用Wolfram链接C++写成的动态库，你需要知道动态库的生成与链接。关于WolframImageLibrary的使用,参考之前写的[画图程序](https://github.com/yangyongkang2000/C-Programming/tree/master/ComplexPlot)和关于[WolframLibrary的使用介绍](https://github.com/yangyongkang2000/C-CPP_WolframLibrary_Example)，当然最主要的还是查看Wolfram帮助文档。
+ 我是在Mac下用Xcode IDE写的，当然源文件应该支持Windows，Linux下的编译环境。编译器所支持的C++标准-std=c++>=11. 
## 实现细节 
### C++
+ 先看头文件
```C++
#ifndef BarnsleyFern_
#define BarnsleyFern_
template<template<typename...>class C,typename T,typename D=double>
class ImageInfo{
public:
    ImageInfo(const T&w,const T&h, const C<D>&r);
    T width,height;
    /*
    就是图形的高宽，或者图片的分辨率(width*height)
    */
    C<D> range,delta;
    /*
    range为x,y坐标范围，delta为每个像素点之间的x,y差量。
    */
};

template<template<typename...>class C,typename T,typename D=double>
class BarnsleyFern:public ImageInfo<C,T,D>
{
public:
    using Y=ImageInfo<C,T,D>;
    BarnsleyFern( C<D>&&m, C<D>&& ps,const T&w,const T&h, const C<D>&r);
    C<D> matrix,position;
    template<typename data_type,typename Random,typename G,typename function_type>
    void Plot(data_type *data_out,Random &d, G&gen,const function_type &func,const uint64_t &iteration);
private:
    T row,col;
    template<typename Index>
    inline void _(const Index&i);
    inline void __();
};
#endif
```
+ 实现文件
>  函数的声明
```C++
EXTERN_C DLLEXPORT int BarnsleyFernPlot(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
```
> 参数列表Args的意义与获取列表中的参数

Args[0]:矩阵  
Args[1]:概率表  
Args[2]:起始点坐标  
Args[3]:x,y轴范围  
Args[4]:图片分辨率{width,height}  
Args[5]: 标记点RGB值。   
Args[6]: 所有点初始RGB值，不过只需要一个整数一并代表RGB（R=G=B)  
Args[7]:迭代次数  


列表中参数的获取C++代码  
```C++
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
```
> 对象初始化
```C++
BarnsleyFern<valarray, size_t> Obj({Real_Vec[0],static_cast<size_t>(length)},{Real_Vec[1],2},width,height,{Real_Vec[3],4});
```
> 图的构建与初始化  
```C++
  auto imageFuns=libData->imageLibraryFunctions;
    MImage image_out;
    imageFuns->MImage_new2D(width,height,3,MImage_Type_Bit8,MImage_CS_RGB,True,&image_out);
    raw_t_ubit8 *out=imageFuns->MImage_getByteData(image_out);
    fill_n(out, 3*width*height, init_color);
```
>随机数与生成函数  
```C++
 random_device rd;
    mt19937 gen(rd());
    discrete_distribution<int> d(Real_Vec[1],Real_Vec[1]+length1);
    auto func=[&](auto &data_out,auto &row,auto &col){copy(begin(color_RGB), end(color_RGB), data_out+3*(col*width+row));};
```
> 图的生成 
```C++
 Obj.Plot(out, d, gen,func, iteration);
```


### Wolfram
+ 导入链接库
```Mathematica
export[str_String :
   "/Users/yangyongkang/Library/Developer/Xcode/DerivedData/\
BarnsleyFern-azczmyhbrzlprfcxjphjblgvxfmr/Build/Products/Release/\
libBarnsleyFern.dylib", "BarnsleyFernPlot"] :=
 BarnsleyFernPlot =
  LibraryFunctionLoad[
   str, {{Real, 2}, {Real, 1}, {Real, 1}, {Real, 2}, {Integer,
     1}, {Integer, 1}, Integer, Integer},
   LibraryDataType[Image, "Byte"]];
```
+ 画图例子
```Mathematica
BarnsleyFernPlot[{{0., 0., 0, 0, 0.16, 0}, {0.85, 0.04, 0, -0.04,
   0.85, 1.6}, {0.2, -0.26, 0, 0.23, 0.22, 1.6}, {-0.15, 0.28, 0,
   0.26, 0.24, 0.44}}, {.07, 0.85, 0.01, 0.07}, {0,
  0}, {{-2.182, 2.6558}, {0, 10.1}}, {500, 500}, {34, 139,
  34}, 255, 10000000]
``` 
## 最后 
+ 更多信息参考项目文件  
+ 关于项目图片，我在Wolfram云上发布了三张。  
[图片1](https://www.wolframcloud.com/obj/92e26c04-85c4-4108-8ee2-078a503c5b43)  
[图片2](https://www.wolframcloud.com/obj/b13592f5-8c7f-4835-b40d-61ccbebb45d7)  
[图片3](https://www.wolframcloud.com/obj/167a87a4-ddee-41ff-8cf8-e2295d74b81a)
## 谢谢大家阅读！