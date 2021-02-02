#  霍夫曼压缩算法C++实现
## 前言：
> 霍夫曼压缩算法是在1952年霍夫曼提出来的压缩文件方法，现在在任何一本数据结构或者算法书中都有它的介绍，虽然算法比较经典简单，方法比较暴力，但到现在不失为一种好的压缩算法，而且压缩速度根据写作者代码水平不同有速度层级，现在霍夫曼算法经常被拿来当作C++或者C大作业，因为代码量适中，只有两三百行，其实我用C++写的这个也差不多三百行，难度一般。考察语言知识还比较全面，涉及简单数据结构（数组，堆，哈希表，树）和一些简单方法（树的构建和遍历），位的操作，I/O操作等。
## 简单介绍
>  我用C++简单写了这个程序，我来简单分享一下我的方法。关于C++编程风格，我不受C++和C的分割，只为了尽量简单高效。我举几个例子来说明，先看看关于我对面向对象在本程序中的应用，很遗憾的告诉你很少，主要是泛型编程，唯一和面向对象沾一点边的是在huffman.hpp中，关于树，我用了结构体或者public的类来表示，看代码.     


```C++
template<typename T,typename T1>
struct root {
    T val;
    T1 weight;
    bool b;
    root<T,T1> *left,*right;
    root():b(false),left(nullptr),right(nullptr){};
    root(T v,T1 w):val(v),weight(w),b(true),left(nullptr),right(nullptr){};
    root(T1 w,root<T, T1>*l,root<T, T1>*r):weight(w),b(false),left(l),right(r){};
};
``` 
> 大部分主要是模版编程，几个例子，在huffman.hpp中 

```C++
using UL=unsigned long int;
using UC=unsigned char;
template<typename T,typename T1=int>
constexpr T1 BIT=sizeof(T)<<3;
template<typename T,typename T1=int>
constexpr T1 MAX=std::numeric_limits<T>::max();
template<typename T,int N,typename T1=int>
constexpr T1 L=MAX<T> >> N;
template<typename T>
using BT=std::bitset<MAX<T>+1>;
template<typename T,int N>
using BT_=std::bitset<1<<N>;
template<int N>
constexpr int BT_Size=1<<N;
 constexpr int  N=std::is_same<T1, BT<T>>::value?BIT<T>-5:BIT<T>-3;
    constexpr int  N1=std::is_same<T1, BT<T>>::value?BIT<T>:BIT<T>-2;
```
> 当然少不了我对STL的疯狂使用，甚至用了C++17的函数。
比如我对堆的构建和操作就用了算法库 
```C++
template<template<typename...> class  C,typename T,typename T1>
inline void create_huffman_tree(C<root<T,T1>*>& tree)
{
    assert(tree.size()>0);
    if(tree.size()==1)
    {
        auto it=tree[0];
        tree.pop_back();
        tree.push_back(new root<T,T1>{it->weight,it,nullptr});
        return;
    }
    std::make_heap(tree.begin(), tree.end(),compar<T,T1>);
    auto l=static_cast<int>(tree.size())-1;
    for(auto i=0;i<l;i++)
    {
        std::pop_heap(tree.begin(), tree.end(),compar<T,T1>);
        auto min_1=tree.back();
        tree.pop_back();
        std::pop_heap(tree.begin(), tree.end(),compar<T,T1>);
        auto min_2=tree.back();
        tree.pop_back();
        tree.emplace_back(new root<T,T1>{min_1->weight+min_2->weight,min_1,min_2});
        std::push_heap(tree.begin(), tree.end(), compar<T,T1>);
    }
}
```
```C++
T1 _count=std::count_if(list.begin(), list.end(), [](T1 i){return i!=0;});
bool b=std::get<T>(*std::max_element(table.begin(), table.end(), [](auto &_,auto &__){
        return std::get<T>(_)<std::get<T>(__);}))<=(L<T, 2>+1);
 T1 bit_count=std::transform_reduce(list.begin(), list.end(), table.begin(), 0, std::plus<>(), [](auto &_,auto &__)->T1{return _*static_cast<T1>(std::get<T>(__));});
 std::copy(v.begin()+l*N, v.end(), buffer.data());

```
> 当然我用了数据结构几乎都是C+=标准库提供的，而且我的不正确声明，导致有些数据结构声明很复杂。
```C++
 std::array<T1,MAX<T>+1> list{};
    std::array<std::tuple<BT<T>,T>,MAX<T>+1> table{};
    std::array<std::tuple<T1,T>,MAX<T>+1> table1{};
``` 
> 可以说C++好的没学到，坏的我学到了，所以代码几乎没有可读性，难免想到了MMA。 


## 测试
> 程序第一重要的是正确性，尤其是对文件的处理，丝毫毛虎不得。我很难证明这个程序没有bug,当然我希望没有，我写了一个简单分布的测试程序，只能验证一方面，希望各位阅读文章的读者测试找出我的bug，不胜感激。我写的测试程序代码 
```C++
int main()
{
    using namespace std;
    using namespace Huffman;
    vector<unsigned char> v;
    v.reserve(100000000);
    std::random_device rd;
    std::mt19937 gen(rd());
    uniform_int_distribution<> dis(1,100000000),dis1(0,255);
    while(true){
        auto l=dis(gen);
        for(auto i=0;i<l;i++)
        v.push_back(dis1(gen));
        auto p(tree_unzip<uint64_t>(zip<uint64_t>(v)));
        assert(p==v);
        v.clear();
    }
}
```
> 我分别提供了对zip,unzip的两种类型API，一种不涉及IO操作，一种涉及IO操作，供大家推广和在程序中使用。 
```C++
template<typename T1,template<typename...> class C,typename T>
inline C<T> zip(const C<T> &v)
template<typename T1,template<typename...> class C,typename T>
inline C<T> tree_unzip(const C<T> &v)
template<UL N,template<typename...> class C,typename T,typename T1>
inline bool buffer_file_zip(const char *file_in_path,const char* file_out_path)
template<UL N,template<typename...> class C,typename T,typename T1>
inline bool buffer_file_unzip(const char *file_in_path,const char* file_out_path)
```
## 编译
> 环境支持: 
+ 编译器: GCC,CLANG... 
+ 系统:Linux,Windows,MacOSX 
+ C++支持标准:C++17以上
> 编译:
+ 终端上在当前文件夹输入 
```
make
```
> 就会生成执行文件。 

> 如果想清除生成文件，输入 
```
make clean
```
## 如何运行
> 比如解压一个名叫a.txt的文件，有两种方式 
+ 第一种输入
```
./yykhf a.txt
```
>会自动压缩a.txt为a.txt.yykhf到当前目录下。

+ 第二种输入 
``` 
./yykhf a.txt ../../b.txt
```
> 会自动压缩a.txt为到指定文件目录下的b.txt.yykhf

> 同理解压命令 unyykhf 也有两种方法 
+ 1
``` 
./unyykhf a.txt.yykhf
```
> 会解压a.txt.yykhf 为a.txt.
+ 2
```
./unyykhf a.txt.yykhf ../../b.txt
```
> 解读留给读者。

## 关于性能
> 这是重点，我花里胡哨用C++写了一堆，效率如何，我想说很快，不比你C写的慢，有多快也不至于，但可能比一些国产垃圾付费压缩文件快，验证留给读者。