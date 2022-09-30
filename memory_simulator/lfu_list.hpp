//
//  lfu_list.hpp
//  memory_simulator
//
//  Created by 杨永康 on 2022/9/27.
//

#ifndef lfu_list_h
#define lfu_list_h
template<int32_t _N>
class lfu_list_alloc {
    struct Node {
        int32_t val;
        int32_t prev;
        int32_t next;
    };
    std::vector<Node> data;
    int32_t remain=-1;
    friend class lfu_list;
public:
    static constexpr int32_t N=_N;
    lfu_list_alloc() {data.resize(N);}
    
};
class lfu_list {
    int32_t head=-1;
    int32_t tail=-1;
public:
    bool empty() const noexcept {
        return head<0;
    }
    template<typename InputIt,typename Alloc>
    void assign(InputIt beg,Alloc & ac) noexcept {
        head=0;
        tail=Alloc::N-1;
        for(int32_t i=0;i<Alloc::N;i++)
        {
            ac.data[i].val=*beg++;
            ac.data[i].prev=i-1;
            ac.data[i].next=i+1;
        }
    }
    template<typename Alloc>
    auto back(Alloc &ac)noexcept {
        return ac.data[tail].val;
    }
    template<typename Alloc>
    auto pop_back(Alloc &ac) noexcept
    {
        ac.remain=tail;
        if(head==tail)
            head=-1;
        else
            tail=ac.data[tail].prev;
    }
    template<typename Alloc>
    auto push_front(int32_t val,Alloc &ac) noexcept{
        if(empty())
            tail=ac.remain;
        else ac.data[head].prev=ac.remain;
        ac.data[ac.remain].val=val;
        ac.data[ac.remain].next=head;
        head=ac.remain;
    }
    auto begin() noexcept {
        return head;
    }
    template<typename Alloc>
    void erase(int32_t i,Alloc &ac) noexcept
    {
        ac.remain=i;
        if(i==tail) return pop_back(ac);
        if(i==head) head=ac.data[head].next;
        else {
            auto l=ac.data[i].prev;
            auto r=ac.data[i].next;
            ac.data[l].next=r;
            ac.data[r].prev=l;
        }
    }
};


#endif /* lfu_list_h */
