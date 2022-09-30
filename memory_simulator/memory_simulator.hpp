//
//  memory_simulator.hpp
//  memory_simulator
//
//  Created by 杨永康 on 2022/8/8.
//

#ifndef memory_simulator_h
#define memory_simulator_h
#include<algorithm>
#include<random>
#include<vector>
#include<bitset>
#include<utility>
#include<cstdint>
#include<deque>
#include<unordered_map>
#include"LRU_list.hpp"
#include"Range.hpp"
#include"lfu_list.hpp"
namespace memory_simulator {
constexpr int32_t page_size=0x100000;
constexpr int32_t real_size=0x40000;
constexpr int32_t prime_size=0x16a0b;
class FIFO_model {
    std::bitset<2*page_size> page_table;
    std::deque<int32_t> l;
    template<typename Memory>
    friend void FIFO(FIFO_model &,Memory & ) noexcept;
    template<int N,typename Model>
    friend void init (Model &model) noexcept;
};
class LRU_model {
    lru_list<real_size> l;
    std::vector<int32_t> page_table;
    template<int N,typename Model>
    friend void init (Model &model) noexcept;
    template<typename Memory>
    friend void LRU(LRU_model &,Memory & ) noexcept;
public:
    LRU_model() {page_table.resize(page_size,-1);}
};
class LFU_model {
    lfu_list_alloc<real_size> ac;
    std::unordered_map<uint32_t, lfu_list> l;
    std::vector<std::pair<int32_t, uint32_t>> page_table;
    uint32_t minfreq=0;
    template<typename Memory>
    friend void LFU(LFU_model &,Memory & ) noexcept;
    template<int N,typename Model>
    friend void init (Model &model) noexcept;
public:
    LFU_model() {
        l.reserve(prime_size);
        page_table.resize(page_size,{-1,0});
    }
};
template<int N,typename Model>
void init (Model &model) noexcept{
    auto &p=model.page_table;
    auto &d=model.l;
    std::vector<int32_t> tmp(real_size);
    std::random_device rd{};
    std::default_random_engine gen{rd()};
    std::sample(Range<int32_t, 0,page_size>().begin(), Range<int32_t, 0,page_size>().end(), tmp.begin(), real_size, gen);
    if constexpr(N==1) {
        std::for_each_n(tmp.begin(), real_size, [&](auto i){p.set(2*i);});
        std::shuffle(tmp.begin(), tmp.end(), gen);
        d.assign(tmp.begin(),tmp.end());
    }
    if constexpr(N==2){
        for(int32_t i=0;i<real_size;i++)
            p[tmp[i]]=i+1;
        d.assign(tmp.begin());
    }
    if constexpr(N==3){
        for(int32_t i=0;i<real_size;i++)
            p[tmp[i]].first=i;
        d[0].assign(tmp.begin(),model.ac);
    }
}
template<typename Memory>
void FIFO(FIFO_model &f,Memory & m) noexcept
{
    auto & page_table=f.page_table;
    auto & d=f.l;
    while(!m.empty())
    {
        auto index=m.get();
        page_table.set(2*index+1);
        if(!page_table[2*index]) {
            m.add();
            for(auto i=d.front();page_table[2*i+1];i=d.front()){
                page_table[2*i+1]=false;
                d.pop_front();
                d.push_back(i);
            }
            page_table.reset(2*d.front());
            page_table.set(2*index);
            d.pop_front();
            d.push_back(index);
        }
    }
}
template<typename Memory>
void LRU(LRU_model &L,Memory & m) noexcept{
    auto& l=L.l;
    auto &page_table=L.page_table;
    while(!m.empty())
    {
        auto index=m.get();
        auto i=page_table[index];
        if(i!=-1)
            l.erase(i);
        else {
            m.add();
            page_table[l.back()]=-1;
            l.pop_back();
        }
        l.push_front(index);
        page_table[index]=l.begin();
    }
}
template<typename Memory>
void LFU(LFU_model &L,Memory & m) noexcept {
    auto &ac=L.ac;
    auto &page_table=L.page_table;
    auto &l=L.l;
    auto &min_freq=L.minfreq;
    while(!m.empty())
    {
        auto index=m.get();
        auto &i=page_table[index];
        if(i.first!=-1)
        {
            auto it=l.find(i.second);
            it->second.erase(i.first,ac);
            if(it->second.empty()) {
                l.erase(it);
                if(min_freq==i.second)
                    min_freq++;
            }
        }else{
            m.add();
            auto it=l.find(min_freq);
            while(it==l.end())
                it=l.find(++min_freq);
            page_table[it->second.back(ac)].first=-1;
            it->second.pop_back(ac);
            if(it->second.empty()) {
                l.erase(it);
                min_freq++;
            }
            min_freq=std::min(min_freq, i.second+1);
        }
        auto it=l.find(++i.second);
        if(it!=l.end()){
            it->second.push_front(index,ac);
            i.first=it->second.begin();
        }else{
            auto t=l.insert({i.second,lfu_list{}}).first;
            t->second.push_front(index,ac);
            i.first=t->second.begin();
        }
    }
}
}
#endif /* memory_simulator_h */
