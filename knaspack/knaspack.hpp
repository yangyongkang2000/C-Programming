//
//  knaspack.hpp
//  knaspack
//
//  Created by 杨永康 on 2023/3/3.
//

#ifndef knaspack_h
#define knaspack_h
#include<memory>
#include<utility>
#include<array>
#include<algorithm>
#include<bitset>
#include<numeric>
#include<stdio.h>
struct tree {
    int weight;
    int value;
    std::unique_ptr<tree> left;
    std::unique_ptr<tree> right;
    tree(int w,int v):weight(w),value(v) {}
}
;

template<int _N,int _W>
struct knapsack {
    static constexpr int N=_N;
    static constexpr int W=_W;
    using Array= std::array<std::pair<int, int>, N>;
    Array pack ;
    std::bitset<N> result {};
    int value=0;
    int weight=0;
}
;

template<int N>
struct dfs_pack {
    std::bitset<N> result;
    int weight=0;
    int value=0;
}
;


template<typename T,typename T1,typename T2>
void dfs_knaspack(T & knack,T1 pack,T2 &arr,int i,tree *root,int total_weight,int total_value) {
    constexpr int N=T::N;
    constexpr int W=T::W;
    if(i<N&&(pack.weight+knack.pack[i].first)<=W&&(pack.value+total_value-arr[i].second)>knack.value) {
        if(total_weight-arr[i].first+pack.weight<=W) {
            knack.value=pack.value+total_value-arr[i].second;
            knack.weight=total_weight-arr[i].first+pack.weight;
            for(int j=i;j<N;j++)
                knack.result.set(j);
            for(int j=i;j<N;j++)
            {
                root->left=std::unique_ptr<tree>(new tree(root->weight+knack.pack[j].first,root->value+knack.pack[j].second));
                root=root->left.get();
            }
        }else{
            pack.result.set(i);
            pack.weight+=knack.pack[i].first;
            pack.value+=knack.pack[i].second;
            if(pack.value>knack.value){
                knack.value=pack.value;
                knack.result=pack.result;
                knack.weight=pack.weight;
            }
            root->left=std::unique_ptr<tree>(new tree(root->weight+knack.pack[i].first,root->value+knack.pack[i].second));
            dfs_knaspack(knack, pack, arr, i+1, root->left.get(), total_weight, total_value);
            pack.result.reset(i);
            pack.weight-=knack.pack[i].first;
            pack.value-=knack.pack[i].second;
            root->right=std::unique_ptr<tree>(new tree(root->weight,root->value));
            dfs_knaspack(knack, pack, arr, i+1, root->right.get(), total_weight,total_value);
        }
    }
}

template<typename T>
auto solve_knaspack(T &knack) {
    dfs_pack<T::N> pack;
    tree root(0,0);
    std::array<std::pair<int, int>,T::N+1> arr{};
    std::sort(knack.pack.begin(),knack.pack.end());
    std::partial_sum(knack.pack.begin(),knack.pack.end(), arr.begin()+1, [](auto sum,auto &r){
        return std::pair<int, int>{sum.first+r.first,sum.second+r.second};
    });
    dfs_knaspack(knack, pack, arr, 0, &root,arr.back().first , arr.back().second);
    return root;
}


template<bool b>
void dfs_tree(tree *root,int i) {
    if(root) {
        if constexpr(b) {
            printf("{%d,{%d,%d}},",i,root->weight,root->value);
            dfs_tree<true>(root->left.get(), 2*i);
            dfs_tree<true>(root->right.get(), 2*i+1);
        }else{
            if(root->left)
                printf("{%d,%d},",i,2*i);
            if(root->right)
                printf("{%d,%d},",i,2*i+1);
            dfs_tree<false>(root->left.get(), 2*i);
            dfs_tree<false>(root->right.get(), 2*i+1);
        }
    }
}

#endif /* knaspack_h */
