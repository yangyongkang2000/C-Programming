//
//  test2.hpp
//  kmeans
//
//  Created by 杨永康 on 2023/4/19.
//

#ifndef test2_h
#define test2_h
#include<chrono>
#include<array>
#include<fstream>
#include<vector>
#include"kmeans.hpp"
template<int N,int K,int Max,int L,int M,typename T>
inline auto kmeans_test_bin(const char *file_name) noexcept {
    std::array<std::array<T,N>,L> data;
    std::array<std::array<T,N>,K> result;
    std::ifstream is(file_name);
    is.seekg(8);
    is.read((char *)data.data(),sizeof data);
    std::vector<int> groups(L);
    auto t0=std::chrono::high_resolution_clock::now();
    for(int i=0;i<M;i++)
        result=kmeans<N, K, Max>(data.begin(), data.end(), groups.begin());
    auto t1=std::chrono::high_resolution_clock::now();
    return std::make_pair(result, std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count());
    
}

#endif /* test2_h */
