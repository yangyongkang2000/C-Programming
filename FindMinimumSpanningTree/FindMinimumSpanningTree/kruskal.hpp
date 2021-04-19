//
//  kruskal.hpp
//  FindMinimumSpanningTree
//
//  Created by 杨永康 on 2021/4/7.
//
// https://github.com/rdtaylorjr/Kruskals-Algorithm
// https://github.com/c650/kruskal
//
#ifndef kruskal_h
#define kruskal_h
#include"DisjSet.hpp"
#include "prim.hpp"
constexpr bool Kruskal=true;
constexpr bool Prim=false;
namespace graph_algorithm {
   template<bool Result,bool zero=false,template<typename...> class V,typename T,typename T1>
   inline  std::pair<V<UndirectedEdge<T, T1>>,T1> kruskal(V<UndirectedEdge<T,T1>> &graph,T num) noexcept
{
    constexpr T b=zero?0:1;
    std::pair<V<UndirectedEdge<T, T1>>,T1> result;
    result.second=0;
    if constexpr(Result)
       result.first.reserve(num);
    DisjSet<std::vector, T,Height_Union> S(num+1);
    std::sort(graph.begin(), graph.end());
    T edges_accepeted=0,index=0;
    while(edges_accepeted+b<num)
    {
        auto & e=graph[index++];
        auto  & u=e.edge.first;
        auto  & v=e.edge.second;
        auto  root1=S.template Find<true>(u);
        auto  root2=S.template Find<true>(v);
        if(root1!=root2)
        {
            S.RootUnion(root1, root2);
            if constexpr(Result)
                result.first.push_back(e);
            else  result.second+=e.weight;
            edges_accepeted++;
        }
    }
    return result;
}

template<bool Method,bool Result,template<typename ...> class L,bool heap=true,bool zero=false,template<typename...> class V,typename T,typename T1>
inline  std::pair<V<UndirectedEdge<T, T1>>,T1> find_minimum_spanning_tree(V<UndirectedEdge<T,T1>> &graph) noexcept
{
    if constexpr(Method)
    {
        auto q=std::max_element(graph.begin(), graph.end(), [](auto &l,auto &r){
            return std::max(l.edge.first, l.edge.second)<std::max(r.edge.first, r.edge.second);
        });
        return kruskal<Result,zero>(graph, std::max(q->edge.first,q->edge.second));
    }else {
        auto q=std::max_element(graph.begin(), graph.end(), [](auto &l,auto &r){
            return std::max(l.edge.first, l.edge.second)<std::max(r.edge.first, r.edge.second);
        });
        auto m=std::max(q->edge.first,q->edge.second)+1;
        auto n=q->edge.first;
        V<L<std::pair<T, T1>>> g(m);
        for(auto &_:graph)
        {
            g[_.edge.first].emplace_front(std::pair<T, T1>{_.edge.second,_.weight});
            g[_.edge.second].emplace_front(std::pair<T, T1>{_.edge.first,_.weight});
        }
        V<table_entry<T, T1>> table(m);
        table[n].d_v=0;
        return prim<heap,Result,zero>(g, table,n);
    }
}
}

#endif /* kruskal_h */
