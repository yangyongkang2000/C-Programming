//
//  main.cpp
//  kmeans
//
//  Created by 杨永康 on 2023/4/16.
//

#include <iostream>
#include"test2.hpp"
int main(int argc, const char * argv[]) {
    
    constexpr int N=9;
     constexpr int K=8;
     constexpr int Max=500;
     constexpr int L=17695;
     constexpr int M=1;
     auto [result,t]=kmeans_test_bin<N, K, Max, L, M, float>("./color17695.bin");
    for(int i=0;i<K;i++)
    {
        for(int j=0;j<N;j++)
            std::cout<<result[i][j]<<' ';
        std::cout<<'\n';
    }
    std::cout<<t/M<<"ms\n";
    return 0;
}
