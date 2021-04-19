//
//  DisjSet.hpp
//  smallestStringWithSwaps
//
//  Created by 杨永康 on 2021/1/13.
//  Fixed by 杨永康 on 2021/4/8.

#ifndef DisjSet_h
#define DisjSet_h
constexpr int Normal_Union=0;
constexpr int Size_Union=1;
constexpr int Height_Union=2;
template<template<typename...> class Container,typename T,char Method>
class DisjSet {
public:
    template<typename _>
    DisjSet(_ size) noexcept {
        if constexpr(Method==Normal_Union|| Method==Height_Union)
            S.resize(size);
        else
            S.resize(size,-1);
    }
    /*void SetUnion(const T& x,const T&y,bool method=true)
    {
          T root1=Find(x,method);
          T root2=Find(y,method);
        if(root1!=root2)
           RootUnion(root1,root2);
    }*/
    template<bool method>
    inline constexpr void SetUnion(T const &x,T const &y) noexcept
    {
        T root1=Find<method>(x,method);
        T root2=Find<method>(y,method);
      if(root1!=root2)
         RootUnion(root1,root2);
    }
    inline constexpr void RootUnion(const T& root1,const T& root2) noexcept
    {
        /*switch (Method) {
            case Normal_Union:
                S[root2]=root1;
                break;
            case Size_Union:
                if(S[root1]>S[root2])
                {
                    S[root2]+=S[root1];
                    S[root1]=root2;
                }else{
                    S[root1]+=S[root2];
                    S[root2]=root1;
                }break;
            case Height_Union:
                if(S[root1]>S[root2])
                {
                    S[root1]=root2;
                }else{
                    if(S[root1]==S[root2])
                        S[root1]--;
                    S[root2]=root1;
                }break;
            default:break;
        }*/
        if constexpr(Method==Normal_Union)
            S[root2]=root1;
        if constexpr(Method==Size_Union)
        {
            if(S[root1]>S[root2])
            {
                S[root2]+=S[root1];
                S[root1]=root2;
            }else{
                S[root1]+=S[root2];
                S[root2]=root1;
            }
        }
        if constexpr(Method==Height_Union)
        {
            if(S[root1]>S[root2])
            {
                S[root1]=root2;
            }else{
                if(S[root1]==S[root2])
                    S[root1]--;
                S[root2]=root1;
            }
        }
    }
    /*T Find(const T&x,bool method=true)
    {
        if(S[x]<0)
            return x;
        else {
            if(Method!=Height_Union&&method)
                return S[x]=Find(S[x],method);
            return Find(S[x],method);
        }
    }*/
    template<bool method>
     inline constexpr T Find(T const & x) noexcept
    {
        if (S[x]<=0)
            return x;
        else {
            if constexpr(method)
                return S[x]=Find<method>(S[x]);
            return Find<method>(S[x]);
        }
    }
private:
    Container<T> S;
};

#endif /* DisjSet_h */
