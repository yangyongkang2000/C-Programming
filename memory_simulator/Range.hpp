//
//  Range.hpp
//  memory_simulator
//
//  Created by 杨永康 on 2022/9/23.
//

#ifndef Range_h
#define Range_h
template<typename T,T FROM, T TO>
class Range {
public:
    class iterator{
        T num = FROM;
    public:
        using value_type=T;
        using difference_type=T;
        using reference=T&;
        using pointer=T*;
        using iterator_category= std::random_access_iterator_tag;
        explicit iterator(T _num = 0) : num(_num) {};
        iterator& operator++() {++num; return *this;}
        iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
        reference operator*()  {return num;}
        iterator& operator+=(T n) {num+=n;return *this;}
        iterator& operator-=(T n) {num-=n;return *this;}
        friend iterator operator+(iterator lhs,T n) {lhs+=n;return lhs;}
        friend iterator operator-(iterator lhs,T n) {lhs-=n;return lhs;}
        friend difference_type operator-(iterator lhs,iterator rhs) {return lhs.num-rhs.num;}
        friend bool operator< (const iterator& l, const iterator& r){return l.num<r.num;}
        friend bool operator> (const iterator& lhs, const iterator& rhs){ return rhs < lhs; }
        friend bool operator<=(const iterator& lhs, const iterator& rhs){ return !(lhs > rhs); }
        friend bool operator>=(const iterator& lhs, const iterator& rhs){ return !(lhs < rhs); }
        friend bool operator==(const iterator& lhs, const iterator& rhs){ return lhs.num==rhs.num; }
        friend bool operator!=(const iterator& lhs, const iterator& rhs){ return !(lhs == rhs); }
    };
    iterator begin() {return iterator(FROM);}
    iterator end() {return iterator(TO);}
};

#endif /* Range_h */
