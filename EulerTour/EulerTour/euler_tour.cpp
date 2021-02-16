//
//  euler_tour.cpp
//  EulerTour
//
//  Created by 杨永康 on 2021/2/14.
//
#include<stack>
#include<iostream>
#include<forward_list>
#include<algorithm>
#include<vector>
#include<list>
#include<forward_list>
#include<iterator>
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
int main()
{
    using namespace std;
    vector<size_t> v{12, 8, 1, 9, 6, 4, 11, 1, 5, 9, 7, 1, 8, 2, 4, 9, 1, 10, 2, 11, 5, \
        11, 3, 12, 3, 10, 7, 12, 2, 3, 1, 12, 7, 4, 9, 7, 10, 6, 10, 2, 4, \
        12, 3, 11};
    auto p(find_euler_tour_path<vector, list>(v.data(), v.size()/2));
    
}
