# 斐波那契数列测试电脑速度性能
## 前言
> 最近闲来无事，用C++手写了一下斐波那契数列第N项的算法。然后用来测试电脑性能。 
## 介绍
### 算法方面
#### 斐波那契数列的第N项计算方法有两种实现方式。 
+ 第一种
> 矩阵幂乘法计算第N项，大数乘法和加法方面用10^n进制计算,简单实现。但是你会发现你尝试这么写，不一定比我快.(用来测速度)
+ 第二种 
> 内存优化算法 (用来测内存)  


### 测试介绍 
> 第一种用来测速度，第二种用来测内存。都是测第100万项斐波那契数列。当然可以测更大项。
  
### 如何测试
+ 吐槽
>YH买了新电脑，MBP19,i9 8核处理器 32GB内存，他就是第一个吃螃蟹的人。 
+ 适用环境 
> 系统：跨平台   
> 编译器:g++,clang++...  
> C++标准: -std=c++14 以上 
+ 测试步骤  

从github上下载本文件到电脑上，终端下进入到测试目录(Speed&Memory_Test)。在终端上先输入
```shell
make
```
测试性能输入 
```shell
make SpeedTest
``` 
测试内存输入 
```shell
make MemoryTest
```
记得测试完后输入
```shell
make clean
```
## 测试结果:
同样平台应该比MiloYip写的[代码](https://www.zhihu.com/question/292320341/answer/482517156) 跑的快。
## 写在最后 
YH是第一个测试的人，祝他好运。