//
//  FindAllGraphPath.hpp
//  FindAllGraphPath
//
//  Created by 杨永康 on 2020/12/21.
//

#ifndef FindAllGraphPath_h
#define FindAllGraphPath_h
namespace  Graph{
template<typename AdjacentMatrix,typename T1,typename T2,typename func_type,typename _func_type,typename _func_type_>
void FindAllGraphPath(AdjacentMatrix &adjancent_matrix,size_t _s,const size_t &_e,T1 now_result,T2 &result,const func_type &_f,const _func_type &_g,const _func_type_ &_h)
{
    if(_s==_e)
        _g(result,now_result);
    else
        for(size_t index=0;index<adjancent_matrix.size();index++)
           if(adjancent_matrix[_s][index])
           {
               adjancent_matrix[index][_s]=adjancent_matrix[_s][index]=false;
               _f(now_result,index);
               FindAllGraphPath(adjancent_matrix,index,_e,now_result,result,_f,_g,_h);
               _h(now_result,index);
               adjancent_matrix[index][_s]=adjancent_matrix[_s][index]=true;
           }
}
}
#endif /* FindAllGraphPath_h */
