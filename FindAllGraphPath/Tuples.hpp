//
//  Tuples.hpp
//  FindAllGraphPath
//
//  Created by 杨永康 on 2020/12/21.
//

#ifndef Tuples_h
#define Tuples_h
namespace combination  {
template<typename  T1,typename T2,typename func_type,typename _func_type>
void Tuples(size_t _m,size_t _n,T1 now_result,T2 &result,const func_type &_f,const _func_type &_g)
{
    if(_n==0)
        _g(result,now_result);
    else
        for(size_t _=0;_<_m;_++)
        {
            _f(now_result,_,_n);
            Tuples(_m, _n-1, now_result, result, _f, _g);
        }
}
}
#endif /* Tuples_h */
