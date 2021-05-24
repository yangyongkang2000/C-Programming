# 用Wolfram语言探索C++17新标准之特殊函数
## 前言：
> 如果一个人精通C++,而且追求C++新标准,那C++17引入的特殊函数,你一定不能错过。如果你不画简单原子轨道图，那你一辈子都可能会错过。
## 运行环境
> 编译器:GCC,MSVC...(clang目前并不支持C++17特殊函数) 
> 
> 编译器必须支持C++17标准，并有特殊函数库。
> 
> 
> 其他语言支持:Wolfram Mathematica
## 简单介绍
> 程序非常简单,画二维的原子轨道密度图,所以轨道密度函数成为了关键。 
```C++
template<typename  T,typename T1>
inline T atomic_orbital_probability(T1 n,T1 l,T1 m,const T &x,const T &y)
{
T s=sqrt(x*x+y*y);
return exp(-2*s/n)*pow(s/n,2.0*l)*pow(std::assoc_legendre(l,m,y/s)*std::assoc_laguerre(n-l-1,1+2*l,2*s/n),2.0);
}
```

