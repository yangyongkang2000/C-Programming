//
//  euler_tour_path.cpp
//  euler_tour_path
//
//  Created by 杨永康 on 2021/2/14.
//

#include<WolframLibrary.h>
#include<list>
#include<algorithm>
#include<vector>
#include<forward_list>
#include<array>
#include "euler_tour.hpp"
template<template<typename ...> class V,template<typename ...> class L,typename  T>
inline L<T> find_euler_tour_path(T *graph_data,const T dim)
{
    auto p=std::minmax_element(graph_data, graph_data+2*dim);
    V<L<T>> graph(*p.second+1);
    for(T i=0;i<dim;i++)
    {
        graph[graph_data[2*i]].push_front(graph_data[2*i+1]);
        graph[graph_data[2*i+1]].push_front(graph_data[2*i]);
    }
    auto q(euler_tour::is_exist_euler_tour_path(graph));
    if(!q.first) return {};
    if(q.second.empty()) return euler_tour::euler_tour_path(graph, *p.first);
    if(graph[q.second[0]].front()==q.second[1]||graph[q.second[1]].front()==q.second[0])
    {
        graph[q.second[0]].erase(std::find(graph[q.second[0]].begin(), graph[q.second[0]].end(), q.second[1]));
        graph[q.second[1]].erase(std::find(graph[q.second[1]].begin(), graph[q.second[1]].end(), q.second[0]));
        auto result(euler_tour::euler_tour_path(graph, q.second[0]));
        result.splice(result.end(),euler_tour::euler_tour_path(graph, q.second[1]));
        return result;
    }
    graph[q.second[0]].push_front(q.second[1]);
    graph[q.second[1]].push_front(q.second[0]);
    auto result(euler_tour::euler_tour_path(graph, q.second[0]));
    result.pop_front();
    return result;
}
EXTERN_C DLLEXPORT int euler_tour_path(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    auto tensor=MArgument_getMTensor(Args[0]);
    auto data=libData->MTensor_getIntegerData(tensor);
    auto dims=libData->MTensor_getDimensions(tensor);
    auto list(find_euler_tour_path<std::vector, std::list>(data, dims[0]));
    if(list.empty())
        return LIBRARY_FUNCTION_ERROR;
    MTensor result;
    libData->MTensor_new(MType_Integer,1,std::array<mint,1>{static_cast<long long>(list.size())}.data(),&result);
    auto p=libData->MTensor_getIntegerData(result);
    for(auto _:list)
        *p++=_;
    MArgument_setMTensor(Res, result);
    return LIBRARY_NO_ERROR;
}

