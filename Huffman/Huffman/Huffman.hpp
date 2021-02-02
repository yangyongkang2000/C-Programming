//
//  Huffman.hpp
//  Huffman
//
//  Created by 杨永康 on 2021/1/26.
//

#ifndef Huffman_h
#define Huffman_h
namespace Huffman {
using UL=unsigned long int;
using UC=unsigned char;
template<typename T,typename T1=int>
constexpr T1 BIT=sizeof(T)<<3;
template<typename T,typename T1=int>
constexpr T1 MAX=std::numeric_limits<T>::max();
template<typename T,int N,typename T1=int>
constexpr T1 L=MAX<T> >> N;
template<typename T>
using BT=std::bitset<MAX<T>+1>;
template<typename T,int N>
using BT_=std::bitset<1<<N>;
template<int N>
constexpr int BT_Size=1<<N;
template<typename T,typename T1>
struct root {
    T val;
    T1 weight;
    bool b;
    root<T,T1> *left,*right;
    root():b(false),left(nullptr),right(nullptr){};
    root(T v,T1 w):val(v),weight(w),b(true),left(nullptr),right(nullptr){};
    root(T1 w,root<T, T1>*l,root<T, T1>*r):weight(w),b(false),left(l),right(r){};
};
template<typename T,typename T1>
inline bool compar(root<T, T1>* lhs,root<T,T1> *rhs)
{
    return lhs->weight>rhs->weight;
}
template<template<typename...> class V,typename T,typename T1,typename Array>
inline V<root<T,T1>*> create_tree(const Array&array)
{
    V<root<T,T1>*> v;
    v.reserve(MAX<T>+1);
    for(T i=0;i<MAX<T>;i++)
    if(array[i]!=0)
    v.emplace_back(new root<T,T1>{i,array[i]});
    if(array[MAX<T>]!=0)  v.emplace_back(new root<T,T1>{MAX<T>,array[MAX<T>]});
    return v;
}
template<template<typename...> class V,typename T,typename T1>
inline void delete_tree(V<root<T,T1>*> &v)
{
    for(auto &_:v)
        delete_tree(_);
}
template<typename T,typename T1>
inline void delete_tree(root<T,T1>* tree)
{
    if(tree==nullptr)
        return;
    delete_tree(tree->left);
    delete_tree(tree->right);
    delete tree;
}
template<template<typename...> class  C,typename T,typename T1>
inline void create_huffman_tree(C<root<T,T1>*>& tree)
{
    assert(tree.size()>0);
    if(tree.size()==1)
    {
        auto it=tree[0];
        tree.pop_back();
        tree.push_back(new root<T,T1>{it->weight,it,nullptr});
        return;
    }
    std::make_heap(tree.begin(), tree.end(),compar<T,T1>);
    auto l=static_cast<int>(tree.size())-1;
    for(auto i=0;i<l;i++)
    {
        std::pop_heap(tree.begin(), tree.end(),compar<T,T1>);
        auto min_1=tree.back();
        tree.pop_back();
        std::pop_heap(tree.begin(), tree.end(),compar<T,T1>);
        auto min_2=tree.back();
        tree.pop_back();
        tree.emplace_back(new root<T,T1>{min_1->weight+min_2->weight,min_1,min_2});
        std::push_heap(tree.begin(), tree.end(), compar<T,T1>);
    }
}
template<typename T,typename T1,typename Table>
void dfs(Huffman::root<UC,T1> *tree,Table &table,T b,UC deepth)
{
    if(tree==nullptr)
        return;
    if(tree->b!=false)
    {
        std::get<T>(table[tree->val])=b;
        std::get<UC>(table[tree->val])=deepth;
    }
    dfs(tree->left, table,b<<1, deepth+1);
    dfs(tree->right, table,b<<1|static_cast<T>(0x1), deepth+1);
}
}
#endif /* Huffman_h */
