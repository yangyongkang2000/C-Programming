//
//  prim.hpp
//  FindMinimumSpanningTree
//
//  Created by 杨永康 on 2021/4/6.
//

#ifndef prim_h
#define prim_h
#include<limits>
#include<utility>
#include<algorithm>
#include<queue>
#include<set>
#include<thread>
#include<numeric>
namespace graph_algorithm {
constexpr bool Grpah_Result=true;
constexpr bool Weight_Result=false;
  template<typename T,typename T1>
struct table_entry {
    bool known=false;
    T1 d_v=std::numeric_limits<T1>::max();
    T p_v=0;
};
template<typename T,typename T1>
struct UndirectedEdge {
    std::pair<T, T> edge;
    T1 weight;
};
/*template<typename T,typename T1,template<typename ...> class V>
class heap_compare {
    heap_compare(V<table_entry<T, T1>> &_table):table(_table) {};
    inline bool operator()(T i,T j)
    {
        return table[i].d_v>=table[j].d_v;
    }
private:
    V<table_entry<T, T1>> &table;
};*/

template<typename T,typename T1>
inline bool operator<(UndirectedEdge<T, T1> const &lhs,UndirectedEdge<T, T1> const &rhs) noexcept
{
    return lhs.weight<rhs.weight;
}
template<bool method,bool Result,bool parallel=false,bool zero=false,template<typename ...> class V,template<typename ...> class L,typename T,typename T1>
inline std::pair<V<UndirectedEdge<T, T1>>,T1> prim(V<L<std::pair<T, T1>>> const & graph,V<table_entry<T,T1>> & table,T start) noexcept
{
    constexpr T b=zero?0:1;
    if constexpr(method)
    {
        auto cmp=[](auto &l,auto &r) {return l.second>r.second;};
        std::priority_queue<std::pair<T, T1>,V<std::pair<T, T1>>,decltype(cmp)>heap(cmp);
        heap.emplace(std::pair<T, T1>{start,0});
        while (true) {
            if(heap.empty()) break;
            T v;
            do {
                v=heap.top().first;
                heap.pop();
                if(!table[v].known) break;
            }while(!heap.empty());
            if(table[v].known) break;
            table[v].known=true;
            for(auto & w:graph[v])
                if(!table[w.first].known)
                    if(w.second<table[w.first].d_v)
                    {
                        table[w.first].d_v=w.second;
                        table[w.first].p_v=v;
                        heap.emplace(std::pair<T, T1>{w.first,w.second});
                    }
        }
        /*std::vector<std::pair<T, T1>> heap;
        heap.reserve(graph.size());
        heap.emplace_back(std::pair<T, T1>{start,0});
        while(true)
        {
            if(heap.empty()) break;
            T v;
            do {
                v=heap.front().first;
                std::pop_heap(heap.begin(), heap.end(), cmp);
                heap.pop_back();
                if(!table[v].known) break;
            }while(!heap.empty());
            if(table[v].known) break;
            table[v].known=true;
            for(auto & w:graph[v])
                if(!table[w.first].known)
                    if(w.second<table[w.first].d_v)
                    {
                        table[w.first].d_v=w.second;
                        table[w.first].p_v=v;
                        heap.emplace_back(std::pair<T, T1>{w.first,w.second});
                        std::push_heap(heap.begin(), heap.end(), cmp);
                    }
        }*/
    }else {
        while(true)
        {
            auto it=std::min_element(table.begin()+b, table.end(), [](auto &l,auto &r){
                if(l.known)
                    return false;
                if(r.known)
                    return true;
                return l.d_v<r.d_v;
            });
            if(it->known) break;
            it->known=true;
            auto v=static_cast<T>(it-table.begin());
            for(auto & w:graph[v])
                if(!table[w.first].known)
                    if(w.second<table[w.first].d_v)
                    {
                        table[w.first].d_v=w.second;
                        table[w.first].p_v=v;
                    }
        }
    }
    std::pair<V<UndirectedEdge<T,T1>>,T1> _result;
    auto sum=[](T1 l,auto & t) {return l+t.d_v;};
    _result.second=std::accumulate(table.begin()+b, table.end(), T1{0},sum);
    if constexpr(Result)
    {
        auto &result=_result;
        result.reserve(table.size());
        for(T i=0;i+1<start;i++)
        result.emplace_back(UndirectedEdge<T,T1>{{i,table[i].p_v},table[i].d_v});
        for(T i=start+1;i<table.size();i++)
        result.emplace_back(UndirectedEdge<T,T1>{{i,table[i].p_v},table[i].d_v});
    }
    return _result;
}
}

#endif /* prim_h */
