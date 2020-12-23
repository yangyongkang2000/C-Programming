//
//  main.cpp
//  FindAllGraphPath
//
//  Created by 杨永康 on 2020/12/21.
//

#include <iostream>
#include<vector>
#include<array>
#include<bitset>
#include<unordered_set>
#include<unordered_map>
#include"Tuples.hpp"
#include"FindAllGraphPath.hpp"
int main(int argc, const char * argv[]) {
    using namespace std;
    array<array<char,8>,8> matrix {0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, \
        0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, \
        1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0};
    const array<array<char,8>,8> number {0, 0, 0, 3, 4, 0, 0, 0, 0, 0, 1, 0, 0, 5, 0, 0, 0, 1, 0, 2, 0, 0, 6, \
        0, 3, 0, 2, 0, 0, 0, 0, 7, 4, 0, 0, 0, 0, 8, 0, 11, 0, 5, 0, 0, 8, 0, \
        9, 0, 0, 0, 6, 0, 0, 9, 0, 10, 0, 0, 0, 7, 11, 0, 10, 0};
    vector<unsigned long> uns;
    unordered_map<char,int> result {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8,
        0}, {9, 0}, {10, 0}, {11, 0},{12,0}};
    Graph::FindAllGraphPath(matrix, 0, 6, vector<char>{0}, uns, [&](auto & v,auto &s){v.push_back(s);}, [&number](auto &_,auto &__){bitset<12> ___;
        for(size_t i=0;i<__.size()-1;i++) ___.set(number[__[i]][__[i+1]]);
        _.push_back(___.to_ulong());
    }, [](auto & v,auto &s){v.pop_back();});
    combination::Tuples(2, 12, bitset<12>{}, result,[](auto &_,auto &__,auto &___){
        if(__) _.set(___-1);
    }, [&uns,&result](auto &_,auto &__){
        unsigned long ul=__.to_ulong();
        for(auto &___:uns)
            if((ul&___)==___)
            {
                _[__.count()]++;
                return;
            }
    });
    for(auto &[_,__]:result)
        cout<<(int)_<<","<<(int)__<<endl;
    return 0;
}
