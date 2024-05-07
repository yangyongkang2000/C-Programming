
#include <iostream>
#include"test1.hpp"
int main(int argc, const char * argv[]) {
    // insert code here...
    constexpr int N=2;
    constexpr int K=12;
    constexpr int Max=100;
    constexpr int L=100000;
    constexpr int M=1;
    auto [result,t]=kmeans_test<N, K, Max, L, M, double>("./data.txt");
    for(int i=0;i<K;i++)
    {
        for(int j=0;j<N;j++)
            std::cout<<result[i][j]<<' ';
        std::cout<<'\n';
    }
    std::cout<<t/M<<"ms\n";
    return 0;
}

