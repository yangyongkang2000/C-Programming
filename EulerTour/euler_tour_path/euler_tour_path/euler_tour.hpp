//
//  euler_tour.hpp
//  EulerTour
//
//  Created by 杨永康 on 2021/2/14.
//

#ifndef euler_tour_h
#define euler_tour_h
namespace  euler_tour
{
template<bool b,template<typename ...> class V,template<typename ...> class L,typename  T>
void dfs(V<L<T>> &graph,T start, const T end,L<T> &m)
{
    if((start==end&&b)||graph[start].empty())
        return;
    T f=graph[start].front();
    graph[start].pop_front();
    m.push_back(f);
    graph[f].erase(std::find(graph[f].begin(), graph[f].end(), start));
    dfs<true>(graph,f,end,m);
}
template<template<typename ...> class V,template<typename ...> class L,typename  T>
inline L<T> euler_tour_path(V<L<T>>& graph,T start)
{
    std::forward_list<typename L<T>::const_iterator> s;
    L<T> result{start};
    s.push_front(result.cbegin());
    while (!s.empty()) {
        L<T> m;
        auto _it=s.front();
        s.pop_front();
        dfs<false>(graph,*_it,*_it,m);
        while(!s.empty()&&graph[*s.front()].empty())
            s.pop_front();
        for(auto it=m.cbegin();it!=m.cend();it++)
            if (!graph[*it].empty()) s.push_front(it);
        result.splice(std::next(_it),m);
    }
    return result;
}
template<template<typename ...> class V,template<typename ...> class L,typename  T>
inline std::pair<bool, V<T>> is_exist_euler_tour_path(const V<L<T>> &graph)
{
    V<T> result;
    result.reserve(2);
    for(T i=0;i<graph.size();i++)
    if(graph[i].size()&1){
          if(result.size()<2)
               result.push_back(i);
            else return {false,{}};
    }
    return result.size()!=1?std::pair<bool, V<T>>{true,result}:std::pair<bool, V<T>>{false,{}};
}
}
#endif /* euler_tour_h */
