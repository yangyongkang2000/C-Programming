//
//  LRU_list.hpp
//  memory_simulator
//
//  Created by 杨永康 on 2022/9/24.
//

#ifndef LRU_list_h
#define LRU_list_h
#include <tuple>
template<int32_t N>
class lru_list {
    struct Node {
        int32_t val;
        int32_t prev;
        int32_t next;
    };
    std::vector<Node> data;
    int32_t remain=-1;
public:
    lru_list(){data.resize(N+2);};
    template<typename InputIt>
    void assign(InputIt beg) noexcept
    {
        data[0].next=1;
        for(int32_t i=1;i<=N;i++)
        {
            data[i].val=*beg++;
            data[i].prev=i-1;
            data[i].next=i+1;
        }
        data[N+1].prev=N;
    }
    void erase(int32_t i) noexcept
    {
        remain=i;
        auto l=data[i].prev;
        auto r=data[i].next;
        data[l].next=r;
        data[r].prev=l;
    }
    int32_t back() noexcept{
        return data[data.back().prev].val;
    }
    void pop_back() noexcept{
        erase(data.back().prev);
    }
    void push_front(int32_t val) noexcept {
        auto t=data[0].next;
        data[0].next=remain;
        data[remain].val=val;
        data[remain].prev=0;
        data[remain].next=t;
        data[t].prev=remain;
    }
    int32_t begin() noexcept {
        return data[0].next;
    }
};

#endif /* LRU_list_h */
