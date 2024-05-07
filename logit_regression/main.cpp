//
//  main.cpp
//  logit_regression
//
//  Created by 杨永康 on 2023/4/26.
//


#include <cstdio>
#include<vector>
#include<fstream>
#include<cstring>
#include<array>
#include"test_iris.hpp"
int main(int argc, const char * argv[]) {
    std::string file_name("./iris.txt");
    auto data(read_iris_data<5, 150, float>(file_name));
    constexpr int N1=100;
    constexpr int N2=100;
    constexpr int N3=4000;
    auto result(OvR<1, 3,N1,false>(data,0));
    auto result1(OvR<2, 3,N2,false>(data,0));
    auto result2(OvR<3, 3,N3,false>(data,0));
    std::printf("method:gd iteration:%d,accuracy:%f,time:%lldms\n",N1,result.first,result.second);
    std::printf("method:sgd iteration:%d,accuracy:%f,time:%lldms\n",N2,result1.first,result1.second);
    std::printf("method:adam iteration:%d,accuracy:%f,time:%lldms\n",N3,result2.first,result2.second);
    return 0;
}
