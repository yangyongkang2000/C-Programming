//
//  main.cpp
//  FindMinimumSpanningTree
//
//  Created by 杨永康 on 2021/4/6.
//

/*#include <iostream>
#include<forward_list>
#include<vector>
#include"kruskal.hpp"
int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace graph_algorithm;
    std::vector<UndirectedEdge<int, int>> graph {{{1,4},1},{{1,2},2},{{1,3},4},{{3,4},2},{{3,6},5},{{6,4},8},{{6,7},1},{{7,5},6},{{4,7},4},{{6,4},8},{{4,5},7},{{2,5},10}};
    auto p(find_minimum_spanning_tree<Kruskal, std::forward_list>(graph));
    for(auto &_:p)
        std::cout<<"undirected_edge: "<<_.edge.first<<"->"<<_.edge.second<<" weight:       "<<_.weight<<'\n';
    auto q(find_minimum_spanning_tree<Kruskal, std::forward_list,false>(graph));
    for(auto &_:q)
        std::cout<<"undirected_edge: "<<_.edge.first<<"->"<<_.edge.second<<" weight:   "<<_.weight<<'\n';
    auto r(find_minimum_spanning_tree<Prim, std::forward_list,false>(graph));
    for(auto &_:r)
        std::cout<<"undirected_edge: "<<_.edge.first<<"->"<<_.edge.second<<" weight:"<<_.weight<<'\n';
    return 0;
}*/
#include <iostream>
#include<chrono>
#include<forward_list>
#include<ctime>
#include"yyk_random.hpp"
#include"kruskal.hpp"
using namespace graph_algorithm;
using namespace std::chrono;
yyk_random::uniform_int_distribution<int> dis(20,100);
constexpr int N=5000;
constexpr int _M=N*(N-1)/2;
std::vector<UndirectedEdge<int, int>> v;
namespace test {

struct Edge{
    int a, b, w;
    bool operator< (const Edge& e)const{
        return w < e.w;
    }
} edges[_M];

int p[N+1]={};
int find(int x){
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}
int cnt=0,res=0;
int main()
{
    
    /*for (int i = 0; i < m; i++){
        int a, b, w;
        std::cin >> a >> b >> w;
        edges[i] = {a, b, w};
    }*/
    int index=0;
    for(int i=1;i<=N;i++)
      for(int j=i+1;j<=N;j++)
    edges[index++]={i,j,dis()};
    /*edges[0]={1,N-1,dis()};
    for(int i=1;i<N-1;i++)
    edges[++index]={i,i+1,dis()};
    for(int i=1;i<N;i++)
    edges[++index]={N,i,dis()};*/
    v.reserve(_M);
    for(auto &_:edges)
        v.emplace_back(UndirectedEdge<int, int>{{_.a,_.b},_.w});
    for (int i = 0; i <= N; i++) p[i] = i;
    auto t0=high_resolution_clock::now();
    std::sort(edges, edges + _M);
    cnt=0;
    res=0;
    for (int i = 0; cnt<N-1; i++){
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        a = find(a); b = find(b);
        if (a != b){
            p[a] = b;
            cnt++;
            res += w;
        }
    }
    auto t1=high_resolution_clock::now();
    std::cout<<"kruskal_test_example(time):"<<duration_cast<milliseconds>(t1-t0).count()<<"ms   "<<
    "result:"<<res<<'\n';
    return 0;
}
}
namespace  yyk {
int main() {
auto t0=high_resolution_clock::now();
    auto q(find_minimum_spanning_tree<Kruskal, Weight_Result,std::forward_list>(v));
    auto t1=high_resolution_clock::now();
    std::cout<<"kruskal_yyk_example(time):"<<duration_cast<milliseconds>(t1-t0).count()<<"ms   "<<
    "result:"<<q.second<<'\n';
    return 0;
}
}
namespace prim {
int main() {
auto q=std::max_element(v.begin(), v.end(), [](auto &l,auto &r){
    return std::max(l.edge.first, l.edge.second)<std::max(r.edge.first, r.edge.second);
});
auto m=std::max(q->edge.first,q->edge.second)+1;
auto n=q->edge.first;
std::vector<std::vector<std::pair<int, int>>> g(m);
for(auto &_:v)
{
    g[_.edge.first].emplace_back(std::pair<int, int>{_.edge.second,_.weight});
    g[_.edge.second].emplace_back(std::pair<int, int>{_.edge.first,_.weight});
}
std::vector<table_entry<int, int>> table(m);
table[n].d_v=0;
auto t0=high_resolution_clock::now();
    auto p(graph_algorithm::prim<false, false,false>(g, table, n));
    auto t1=high_resolution_clock::now();
    std::cout<<"prim_yyk_example(time):"<<duration_cast<milliseconds>(t1-t0).count()<<"ms   "<<
    "result:"<<p.second<<'\n';
    return 0;
}
}
constexpr bool release=true;
int main()
{
    yyk_random::initialize_seed(time(NULL));
    if(release)
        std::cout<<"the release version:\n";
    else std::cout<<"the debug version:\n";
    test::main();
    yyk::main();
    prim::main();
}
