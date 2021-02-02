//
//  buffer_file_zip_unzip.hpp
//  Huffman
//
//  Created by 杨永康 on 2021/1/30.
//

#ifndef buffer_file_zip_unzip_h
#define buffer_file_zip_unzip_h
#include"zip_unzip.hpp"
#include"zip_unzip.hpp"
namespace Huffman {
template<UL N,template<typename...> class C,typename T,typename T1>
inline bool method_zip(const C<T> &v, std::array<T, N>&result,UL index,const std::array<std::tuple<T1,T>,MAX<T>+1> &table,const char*file_out_path)
{
    constexpr int  N2=std::is_same<T1, BT<T>>::value?BIT<T>-5:BIT<T>-3;
    constexpr int  N1=std::is_same<T1, BT<T>>::value?BIT<T>:BIT<T>-2;
    for(int i=0;i<=MAX<T>;i++)
      if(std::get<T>(table[i])!=0)
      {
          result[index++]=i;
          for(int j=0;j<=L<T,N2>;j++)
          {
              std::bitset<BIT<T>> b;
              const auto &mid=static_cast<BT_<T,N1>>(std::get<T1>(table[i]));
              for(int k=0;k<BIT<T>;k++)
                 b.set(BIT<T>-1-k,mid[BT_Size<N1>-BIT<T>*j-k-1]);
              result[index++]=b.to_ulong();
          }
          result[index++]=std::get<T>(table[i]);
      }
    std::bitset<BIT<T>>ch;
    int t=BIT<T>-1;
    FILE *file_out=fopen(file_out_path, "wb");
    for(auto &_:v)
    {
        int l=static_cast<int>(std::get<T>(table[_]));
        const auto &b=static_cast<BT_<T, N1>>(std::get<T1>(table[_]));
        for(auto i=0;i<l;i++)
        {
            ch.set(t--,b[l-i-1]);
            if(t<0)
            {
                result[index++]=ch.to_ulong();
                if(index==N)
                {
                    fwrite(result.data(), 1, N, file_out);
                    index=0;
                }
                ch=0;
                t=BIT<T>-1;
            }
        }
    }
    if(t!=BIT<T>-1) result[index++]=ch.to_ulong();
    UL size=fwrite(result.data(), 1, index, file_out);
    assert(size==index);
    fclose(file_out);
    return true;
}
template<UL N,template<typename...> class C,typename T,typename T1>
inline bool buffer_file_zip(const char *file_in_path,const char* file_out_path)
{
    assert(N>10000);
    C<T> v_in(std::move(file_to_vector<N, C, T>(file_in_path)));
    std::array<T1,MAX<T>+1> list{};
    std::array<std::tuple<BT<T>,T>,MAX<T>+1> table{};
    std::array<std::tuple<T1,T>,MAX<T>+1> table1{};
    for(auto &_:v_in) list[_]++;
    T1 _count=std::count_if(list.begin(), list.end(), [](T1 i){return i!=0;});
    assert(_count>0);
    assert(_count<=MAX<T>+1);
    auto tree_vector=std::move(create_tree<C, T, T1>(list));
    create_huffman_tree(tree_vector);
    dfs(tree_vector[0], table, BT<T>(), 0);
    delete_tree(tree_vector);
    bool b=std::get<T>(*std::max_element(table.begin(), table.end(), [](auto &_,auto &__){
        return std::get<T>(_)<std::get<T>(__);}))<=(L<T, 2>+1);
    T1 bit_count=std::transform_reduce(list.begin(), list.end(), table.begin(), 0, std::plus<>(), [](auto &_,auto &__)->T1{return _*static_cast<T1>(std::get<T>(__));});
    std::array<T,N> result;
    UL index=0;
    if(_count==MAX<T>+1) _count=0;
     result[index++]=b;
     result[index++]=_count;
     result[index++]=bit_count%BIT<T>;
    if(b)
    {
        for(auto i=0;i<table.size();i++)
        {
            std::get<T1>(table1[i])=(std::get<BT<T>>(table[i])).to_ullong();
            std::get<T>(table1[i])=std::get<T>(table[i]);
        }
       return method_zip<N>(v_in, result,index,table1,file_out_path);
    }
    return method_zip<N>(v_in, result,index,table,file_out_path);
}
template<UL N,template<typename...> class C,typename T,typename T1>
inline bool buffer_file_unzip(const char *file_in_path,const char* file_out_path)
{
    C<T> v(std::move(file_to_vector<N, C, T>(file_in_path)));
    std::array<T, N> result;
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
    UL   index=0;
    auto ch=tree;
    auto ll=static_cast<int>(v.size())-1;
    FILE *file_out=fopen(file_out_path, "wb");
    for(auto i=r2*size+3;i<ll;i++)
    {
        std::bitset<BIT<T>> b(v[i]);
        for(auto i=BIT<T>-1;i>=0;i--)
        {
            ch=b[i]?ch->right:ch->left;
            if(ch->b) {
                result[index++]=ch->val;
                if(index==N)
                {
                    fwrite(result.data(), 1, N, file_out);
                    index=0;
                }
                ch=tree;
            }
        }
    }
    std::bitset<BIT<T>> b(v.back());
    for(auto i=0;i<t;i++)
    {
        ch=b[BIT<T>-1-i]?ch->right:ch->left;
        if(ch->b) {
            result[index++]=ch->val;
            if(index==N)
            {
                fwrite(result.data(), 1, N, file_out);
                index=0;
            }
            ch=tree;
        }
    }
    delete_tree(tree);
    UL file_size=fwrite(result.data(), 1, index, file_out);
    assert(file_size==index);
    fclose(file_out);
    return true;
}
}

#endif /* buffer_file_zip_unzip_h */
