//
//  main.cpp
//  knaspack
//
//  Created by 杨永康 on 2023/3/3.
//

#include <iostream>

#include"knaspack.hpp"
int main() {
    // insert code here...
    constexpr int N=7;
    constexpr int W=150;
    knapsack<N, W> knack;
    knack.pack=std::to_array<std::pair<int, int>>({{35,10},{30,40},{60,30},{50,50},{40,35},{10,40},{25,30}});
    auto t=solve_knaspack(knack);
    printf("knaspack:");
    for(auto &[w,v]:knack.pack)
        printf("{%d %d} ",w,v);
    printf("\nmax_value:%d\n",knack.value);
    printf("weight:%d\nresult:",knack.weight);
    std::cout<<knack.result<<'\n';
    printf("{{");
    dfs_tree<false>(&t,1);
    printf("Nothing},");
    printf("{");
    dfs_tree<true>(&t,1);
    printf("Nothing}}\n");
    return 0;
}
