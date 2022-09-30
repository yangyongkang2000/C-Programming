//
//  memory_generate.hpp
//  memory_simulator
//
//  Created by 杨永康 on 2022/9/29.
//

#ifndef memory_generate_h
#define memory_generate_h



template<uint32_t N>
class test_memory {
    using R=std::discrete_distribution<int32_t> ;
    using R1=std::uniform_int_distribution<int32_t>;
    std::random_device rd {};
    std::mt19937 gen{rd()};
    R d{5,5,85,5};
    R1 d1{0,0x3ffff};
    uint32_t i=0;
    uint32_t j=0;
public :
    bool empty() noexcept {
        return i==N;
    }
    int32_t get() noexcept {
        ++i;
        return d(gen)*0x40000+d1(gen);
    }
    void add() noexcept {j++;}
    auto result() noexcept {return j;}
    void reset() noexcept {i=0;}
};
#endif /* memory_generate_h */
