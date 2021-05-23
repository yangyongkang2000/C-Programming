#include <iostream>
#include<vector>
#include<chrono>
#include "kruskal.hpp"
#include"yyk_random.hpp"
constexpr int N=8000;
constexpr int M=N*(N-1)/2;
int main() {
   using namespace  graph_algorithm;
   using namespace std::chrono;
    yyk_random::initialize_seed(time(NULL));
   yyk_random::uniform_int_distribution<int> dis(0,1000);
    std::vector<UndirectedEdge<int, int>> v;
    v.reserve(M);
    for(int i=1;i<=N;i++)
        for(int j=i+1;j<=N;j++)
            v.emplace_back(UndirectedEdge<int, int>{{i,j},dis()});
        auto t0=high_resolution_clock::now();
    find_minimum_spanning_tree<false,false,std::vector,false,false>(v);
    auto t1=high_resolution_clock::now();
    std::cout<<"time:"<<duration_cast<milliseconds>(t1-t0).count()<<"ms\n";
}
