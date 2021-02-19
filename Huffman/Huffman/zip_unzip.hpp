//
//  file_zip.hpp
//  Huffman
//
//  Created by 杨永康 on 2021/1/30.
//

#ifndef file_zip_h
#define file_zip_h
#include"Huffman.hpp"
namespace Huffman {
template<template<typename...> class C,typename T,typename T1>
inline void method_zip(const C<T> &v,C<T> &result,const std::array<std::tuple<T1,T>,MAX<T>+1> &table)
{
    constexpr int  N=std::is_same<T1, BT<T>>::value?BIT<T>-5:BIT<T>-3;
    constexpr int  N1=std::is_same<T1, BT<T>>::value?BIT<T>:BIT<T>-2;
    for(int i=0;i<=MAX<T>;i++)
      if(std::get<T>(table[i])!=0)
      {
          result.push_back(i);
          for(int j=0;j<=L<T,N>;j++)
          {
              std::bitset<BIT<T>> b;
              const auto &mid=static_cast<BT_<T,N1>>(std::get<T1>(table[i]));
              for(int k=0;k<BIT<T>;k++)
                 b.set(BIT<T>-1-k,mid[BT_Size<N1>-BIT<T>*j-k-1]);
              result.push_back(b.to_ulong());
          }
          result.push_back(std::get<T>(table[i]));
      }
    std::bitset<BIT<T>>ch;
    int t=BIT<T>-1;
    for(auto &_:v)
    {
        int l=static_cast<int>(std::get<T>(table[_]));
        const auto &b=static_cast<BT_<T, N1>>(std::get<T1>(table[_]));
        for(auto i=0;i<l;i++)
        {
            ch.set(t--,b[l-i-1]);
            if(t<0)
            {
                result.push_back(ch.to_ulong());
                ch=0;
                t=BIT<T>-1;
            }
        }
    }
    if(t!=BIT<T>-1) result.push_back(ch.to_ulong());
}
template<typename T1,template<typename...> class C,typename T>
inline C<T> zip(const C<T> &v)
{
    std::array<T1,MAX<T>+1> list{};
    std::array<std::tuple<BT<T>,T>,MAX<T>+1> table{};
    std::array<std::tuple<T1,T>,MAX<T>+1> table1{};
    for(auto &_:v) list[_]++;
    T1 _count=std::count_if(list.begin(), list.end(), [](T1 i){return i!=0;});
    assert(_count>0);
    assert(_count<=MAX<T>+1);
    auto tree_vector=std::move(create_tree<C, T, T1>(list));
    create_huffman_tree(tree_vector);
    dfs(tree_vector[0], table, BT<T>(), 0);
    delete_tree(tree_vector);
    bool b=std::get<T>(*std::max_element(table.begin(), table.end(), [](auto &_,auto &__){
        return std::get<T>(_)<std::get<T>(__);}))<=(L<T, 2>+1);
    C<T> result;
    T1 bit_count=std::inner_product(list.begin(), list.end(), table.begin(), 0, std::plus<>(), [](auto &_,auto &__)->T1{return _*static_cast<T1>(std::get<T>(__));});
    T1 size=b?(BIT<T>+2)*_count+3+(bit_count>>3):((BIT<T> << 2)+2)*_count+3+(bit_count>>3);
    result.reserve(size+10);
    if(_count==MAX<T>+1) _count=0;
    result.push_back(b);
    result.push_back(_count);
    result.push_back(bit_count%BIT<T>);
    if(b)
    {
        for(auto i=0;i<table.size();i++)
        {
            std::get<T1>(table1[i])=(std::get<BT<T>>(table[i])).to_ullong();
            std::get<T>(table1[i])=std::get<T>(table[i]);
        }
        method_zip(v, result,table1);
    }else{
        method_zip(v, result, table);
    }
    return result;
}
template<typename T1,typename T>
inline void create_tree_unzip(root<T, T1>* tree,const T &ch,const BT<T> &b,int deep)
{
    if(tree==nullptr) return;
    if(deep<0)
    {
        tree->b=true;
        tree->val=ch;
        return ;
    }
    if(b[deep])
    {
       if(tree->right==nullptr)
           tree->right=new root<T,T1>();
        create_tree_unzip(tree->right, ch, b, deep-1);
    }else{
        if(tree->left==nullptr)
            tree->left=new root<T,T1>();
         create_tree_unzip(tree->left, ch, b, deep-1);
    }
    return ;
}
template<typename T1,template<typename...> class C,typename T>
inline C<T> tree_unzip(const C<T> &v)
{
    C<T> result;
    result.reserve(v.size()<<1);
    std::array<std::tuple<BT<T>,T>, MAX<T>+1> table{};
    root<T, T1> *tree=new root<T,T1>();
    int size=v[1]==0?MAX<T>+1:v[1],t=v[2]==0?BIT<T>:v[2];
    const int r1=v[0]?7:31,r2=v[0]?10:34,r3=v[0]?64:(MAX<T>+1);
    for(auto i=0;i<size;i++)
    {
        BT<T> ch;
        for(auto j=0;j<=r1;j++)
        {
            std::bitset<BIT<T>> mid(v[r2*i+j+4]);
            for(auto k=0;k<BIT<T>;k++)
            ch.set(r3-1-BIT<T>*j-k,mid[BIT<T>-1-k]);
        }
        std::get<BT<T>>(table[v[3+r2*i]])=ch;
        std::get<T>(table[v[3+r2*i]])=v[2+r2+r2*i];
        create_tree_unzip(tree, v[3+r2*i], ch,v[2+r2+r2*i]-1);
    }
    auto ch=tree;
    std::size_t ll=v.size()-1;
    for(std::size_t i=r2*size+3;i<ll;i++)
    {
        std::bitset<BIT<T>> b(v[i]);
        for(auto i=BIT<T>-1;i>=0;i--)
        {
            ch=b[i]?ch->right:ch->left;
            if(ch->b) {
                result.push_back(ch->val);
                ch=tree;
            }
        }
    }
    std::bitset<BIT<T>> b(v.back());
    for(auto i=0;i<t;i++)
    {
        ch=b[BIT<T>-1-i]?ch->right:ch->left;
        if(ch->b) {
            result.push_back(ch->val);
            ch=tree;
        }
    }
    delete_tree(tree);
    return result;
}
template<UL N,template<typename...> class C,typename T>
inline C<T> file_to_vector(const char *file_in_path)
{
    std::array<T,N> buffer;
    namespace fs = std::filesystem;
    fs::path p1(file_in_path);
    auto fileSize_in=fs::file_size(p1);
    assert(fileSize_in>0);
    C<T> result;
    result.reserve(fileSize_in+1);
    FILE *file_in=fopen(file_in_path, "rb");
    assert(std::is_trivially_copyable<decltype(buffer)>::value);
    while(true)
    {
        auto n = fread(buffer.data(), 1, N, file_in);
        result.insert(result.end(),buffer.begin(),buffer.begin()+n);
        if(n<N) break;
    }
    fclose(file_in);
    return result;
}
template<UL N,template<typename...> class C,typename T>
inline bool vector_to_file(const C<T> &v,const char* file_out_path)
{
    std::array<T,N> buffer;
    assert(std::is_trivially_copyable<decltype(buffer)>::value);
    FILE *file_out=fopen(file_out_path, "wb");
    if(v.size()<=N)
    {
        std::copy(v.begin(),v.end(),buffer.data());
        auto n=fwrite(buffer.data(), 1, v.size(), file_out);
        assert(n==v.size());
    }else {
        UL l=v.size()/N;
        for(UL i=0;i<l;i++)
        {
            std::copy(v.begin()+i*N, v.begin()+(i+1)*N, buffer.data());
            auto n=fwrite(buffer.data(), 1, N, file_out);
            assert(n==N);
        }
        std::copy(v.begin()+l*N, v.end(), buffer.data());
        UL ll=(v.end()-v.begin())-l*N;
        auto n=fwrite(buffer.data(), 1, ll, file_out);
        assert(ll==n);
    }
    fclose(file_out);
    return true;
}
}
#endif /* file_zip_h */
