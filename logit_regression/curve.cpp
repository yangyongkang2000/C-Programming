//
//  curve.cpp
//  logit_regression
//
//  Created by 杨永康 on 2023/4/29.
//

#include <cstdio>
#include<future>
#include<string>
#include"test_iris.hpp"

int main(int argc, const char * argv[]) {
    std::string file_name("./iris.txt");
    auto data(read_iris_data<5, 150, float>(file_name));
    auto data1(data);
    auto data2(data);
    constexpr int N1=100;
    constexpr int N2=100;
    constexpr int N3=100;
    auto f0=std::async(std::launch::async, [&]{ OvR<1, 3,N1,true>(data,std::string("./gd.txt"));});
    auto f1=std::async(std::launch::async,[&]{ OvR<2, 3,N2,true>(data1,std::string("./sgd.txt"));});
    auto f2=std::async(std::launch::async, [&]{ OvR<3, 3,N3,true>(data2,std::string("./adam.txt"));});
    f0.get();
    f1.get();
    f2.get();
    return 0;
}
