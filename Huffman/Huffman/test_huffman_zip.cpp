//
//  test_huffman_zip.cpp
//  Huffman
//
//  Created by 杨永康 on 2021/2/2.
//

#include <iostream>
#include <algorithm>
#include<vector>
#include<array>
#include<limits>
#include<utility>
#include<cstdio>
#include<filesystem>
#include<bitset>
#include<cassert>
#include<cstring>
#include<execution>
#include<random>
#include<numeric>
#include<type_traits>
#include"buffer_file_zip_unzip.hpp"
int main()
{
    using namespace std;
    using namespace Huffman;
    vector<unsigned char> v;
    v.reserve(100000000);
    std::random_device rd;
    std::mt19937 gen(rd());
    uniform_int_distribution<> dis(1,100000000),dis1(0,255);
    while(true){
        auto l=dis(gen);
        for(auto i=0;i<l;i++)
        v.push_back(dis1(gen));
        auto p(tree_unzip<uint64_t>(zip<uint64_t>(v)));
        assert(p==v);
        v.clear();
    }
}
