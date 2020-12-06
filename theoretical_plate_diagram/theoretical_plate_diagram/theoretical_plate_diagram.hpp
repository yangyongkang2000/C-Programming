//
//  theoretical_plate_diagram.hpp
//  theoretical_plate_diagram
//
//  Created by 杨永康 on 2020/12/6.
//

#ifndef theoretical_plate_diagram_h
#define theoretical_plate_diagram_h
namespace  chemistry{
template<typename cond_type,typename result_type,typename T=double>
result_type TPD(const cond_type &_cond)
{
    T alpha=_cond[0],xW=_cond[1],xD=_cond[2],xF=_cond[3],q=_cond[4],R=_cond[5],k1=R/(R+1),b1=xD/(R+1),R1=(R+1)*(xF-xW)/(xD-xF)+(q-1)*(xD-xW)/(xD-xF),k2=(R1+1)/R1,b2=-xW/R1,xf=((R+1)*xF+(q-1)*xD)/(R+q),x,y;
    result_type result {{xD,xD},{xD/(alpha-(alpha-1)*xD),xD}};
    while((x=result[result.size()-2][0])>xW)
    {
        y=result[result.size()-2][1];
        x=y/(alpha-(alpha-1)*y);
        result.push_back({x,y=(x>xf?k1*x+b1:k2*x+b2)});
        result.push_back({y/(alpha-(alpha-1)*y),y});
    }
    result.pop_back();
    return result;
}
}

#endif /* theoretical_plate_diagram_h */
