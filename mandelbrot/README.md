# 利用Apple平台的加速框架simd，使用C++17进行加速计算


## 关于Apple的加速框架 [Accelerate](url=https://developer.apple.com/documentation/accelerate?language=objc)


Apple Developer对它的介绍


>Make large-scale mathematical computations and image calculations, optimized for high performance and low energy consumption.

加速框架中有很多内容，其中包括了

+ [simd](url=https://developer.apple.com/documentation/accelerate/simd?language=objc)

> simd provides types and functions for small vector and matrix computations. The types include integer and floating-point vectors and matrices, and the functions provide basic arithmetic operations, element-wise mathematical operations, and geometric and linear algebra operations.
simd supports vectors containing up to 16 elements (for single-precision values) or 8 elements (for double-precision values), and matrices up to 4 x 4 elements in size. Other frameworks, such as vForce, allow you to work with larger vectors.

## 使用SIMD加速mandelbrot set计算

### 关于mandelbrot set
> https://en.wikipedia.org/wiki/Mandelbrot_set

### 传统计算mandelbrot set每个点迭代次数写法

```C++

....
for (count = 1; count < maxIters; ++count)
            {
                float x2 = x * x, y2 = y * y;
                float xy = (x+x)*y;
                x = x2 - y2 + cx;
                y = xy + cy;
                if (x2 + y2 >= 4)
                    break;
            }
...

```

### 使用SIMD加速计算

```C++
...
 for(int k=1;k<N;k++)
            {
                auto X2(X*X);
                auto Y2(Y*Y);
                auto R(X2+Y2);
                auto XY((X+X)*Y);
                X=X2-Y2+X0;
                Y=XY+Y0;
                auto mask=(R<4.0f);
                K+=mask&1;
                if(!simd_any(mask))
                    break;
            }
...
```

> 写法上，感受不到具体差异


### 着色方案

```C++
constexpr float m=float(1)/float(maxIters);
            auto t=m*float(count);
            *r++=2427.26f*t*t*t*(1-t);
            *g++=4096.0f*t*t*(1-t)*(1-t);
            *b++=2427.26f*t*(1-t)*(1-t)*(1-t);
```

### 将RGB数组生成PPM文件

+ 较快的实现
```C++
...
char *ptr=buffer;
        for(int i=0;i<M;i++)
        {
            ptr=std::to_chars(ptr, ptr+3, *r++).ptr;
            *ptr++=' ';
            ptr=std::to_chars(ptr, ptr+3, *g++).ptr;
            *ptr++=' ';
            ptr=std::to_chars(ptr, ptr+3, *b++).ptr;
            *ptr++='\n';
        }
        std::fwrite(buffer, sizeof(unsigned char), ptr-buffer, file);
...
```

+ 较慢的实现

```C++
auto file=std::fopen(file_name,"wb");
    fprintf(file, "P3\n%d %d\n%d\n", W, H, 255);
    for (int i = 0; i < W * H; i++)
        fprintf(file,"%d %d %d\n", *r++, *g++, *b++);
    fclose(file);
```

## 性能测试

### 配置要求
+ macOS系统
+ 支持C++17的Apple Clang编译器


### 程序参数设置
+ Width=1024
+ Height=1024
+ max_iteration=4096

## 测试配置

+  2.3 GHz 双核Intel Core i5 
+  8 GB 2133 MHz LPDDR3

## 测试结果

> mandelbrot:1145ms,rgb_ppm:213ms

> mandelbrot with simd:226ms,fast_rgb_ppm:26ms




## 仅当抛砖引玉，谢谢大家阅读。