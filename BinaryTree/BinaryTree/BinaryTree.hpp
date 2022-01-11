//
//  BinaryTree.hpp
//  BinaryTree
//
//  Created by 杨永康 on 2021/3/25.
//

#ifndef BinaryTree_h
#define BinaryTree_h
#include<cstddef>
namespace yyk_BT {
template<typename elemType,typename T>
class BinaryTree;
template<typename valType,typename T>
class BTnode;
template<typename elemType,typename T=size_t>
class BinaryTree {
public:
    typedef elemType val_type;
    typedef  T   cnt_type;
    BinaryTree() :_root(nullptr) {}
    ~BinaryTree(){
        clear();
    }
    template<typename Input_It>
    BinaryTree(Input_It beg,Input_It end)
    {
        while(beg!=end)
            insert(*beg++);
    }
    BinaryTree(BinaryTree<elemType, T> const & rhs)
    {
        copy(_root, rhs.root);
    }
    BinaryTree(std::initializer_list<elemType> lst)
    {
        for(auto &_:lst)
            insert(_);
    }
  
    template<bool lazy=true>
    void remove_root() noexcept{
        if(!_root) return;
        if constexpr(lazy)
            if(--_root->_cnt)
                return;
        BTnode<elemType, T> *tmp=_root;
        if(_root->_rchild)
        {
            _root=_root->_rchild;
            if(tmp->_lchild)
            {
                BTnode<elemType, T> *lc=tmp->_lchild;
                BTnode<elemType, T> *newlc=_root->_rchild;
                if(!newlc)
                    _root->_rchild=newlc;
                else
                    BTnode<elemType, T>(lc,newlc);
            }
        }else _root=_root->_lchild;
        delete tmp;
    }
    template<bool lazy=true>
    void remove(elemType const & val) noexcept
    {
        if(_root)
        {
            if(_root->_val==val)
                remove_root<lazy>();
            else _root->remove_value<lazy>(val,_root);
        }
    }
    bool find(elemType const &val) noexcept
    {
        return _find(val)?true:false;
    }
    void insert(elemType const & elem) noexcept
    {
        if(!_root)
            _root=new BTnode<elemType, T>(elem);
        else
            _root->insert_value(elem);
    }
    template<typename Input_It>
    void insert(Input_It beg,Input_It end) noexcept
    {
        while(beg!=end)
            insert(*beg++);
    }
    T& operator[](elemType  &val) noexcept
    {
        return _find(val)->_cnt;
    }
    T const & operator[](elemType const &val) noexcept
    {
        return _find(val)->_cnt;
    }
    void clear() noexcept
    {
        if(_root)
        {
            clear(_root);
            _root=nullptr;
        }
    }
    bool empty() noexcept {
        return _root==nullptr;
    }
    BinaryTree<elemType, T> & operator=(BinaryTree<elemType, T> const &rhs) noexcept
    {
        if(this!=rhs)
        {
            clear();
            copy(_root, rhs._root);
        }
    }
    template<int N,typename Func>
    void  order(Func const & f)
    {
        BTnode<elemType,T>::template _order<N>(_root,f);
    }
private:
    BTnode<elemType,T> *_root;
    BTnode<elemType, T>* _find(elemType const & val) noexcept
    {
        if(val==_root->_val)
            return _root;
        if(val<_root->_val)
            return _root->_lchild->find(val);
        else return _root->_rchild->find(val);
    }
    static void clear(BTnode<elemType, T>*pt) noexcept
    {
        if(pt)
        {
            clear(pt->_lchild);
            clear(pt->_rchild);
            delete pt;
        }
    }
    static void copy(BTnode<elemType, T> *&tar,BTnode<elemType, T>*src) noexcept
    {
        if(src)
        {
            tar=new BTnode<elemType, T>(src->_val);
            if(src->_lchild) copy(tar->_lchild, src->_lchild);
            if(src->_rchild) copy(tar->_rchild, src->_rchild);
        }
    }
};
template<typename valType,typename T=size_t>
class BTnode {
    friend BinaryTree<valType,T>;
    BTnode(valType const & val): _val(val)
    {
        _cnt=1;
        _lchild=_rchild=nullptr;
    }
    valType _val;
    T _cnt;
    BTnode<valType,T> *_lchild;
    BTnode<valType,T> *_rchild;
    void insert_value(valType const & val) noexcept
    {
        if(_val==val)
        {
            _cnt++;
            return;
        }
        if(val<_val)
        {
            if(!_lchild)
                _lchild=new BTnode<valType,T>(val);
            else _lchild->insert_value(val);
        }else {
            if(!_rchild)
                _rchild=new BTnode<valType,T>(val);
            else _rchild->insert_value(val);
        }
    }
    static void lchild_leaf(BTnode<valType,T> *leaf,BTnode<valType,T> *subtree) noexcept
    {
        while(subtree->_lchild)
            subtree=subtree->_lchild;
        subtree->_lchild=leaf;
    }
    template<bool lazy=true>
    void remove_value(valType const & val,BTnode<valType, T> *& prev) noexcept
    {
        if(val<_val)
        {
            if(!_lchild)
                return;
            else _lchild->remove_value<lazy>(val,_lchild);
        } else if(val>_val)
        {
            if(!_rchild)
                return;
            else _rchild->remove_value<lazy>(val,_rchild);
        }
        else {
            if constexpr(lazy)
                if(--_cnt)
                    return;
            if(_rchild)
            {
                prev=_rchild;
                if(_lchild) {
                    if(!prev->_lchild)
                        prev->_lchild=_lchild;
                    else BTnode<valType, T> ::lchild_leaf(_lchild, prev->_lchild);
                }
            }
            else prev=_lchild;
            delete this;
        }
    }
    BTnode<valType, T> *find(valType const & val) noexcept
    {
        if(val==_val)
            return this;
        if(val<_val)
        {
            if(_lchild)
                return _lchild->find(val);
            else return nullptr;
        }
        else
        {
            if(_rchild)
                return _rchild->find(val);
            else return nullptr;
        }
    }
    template<int N,typename Func>
     static void _order(BTnode<valType,T> *bt,Func  const & f) noexcept
    {
           if(bt)
           {
               if constexpr(N==0) f(bt->_val);
               if(bt->_lchild) _order<N>(bt->_lchild,f);
               if constexpr(N==1) f(bt->_val);
               if(bt->_rchild) _order<N>(bt->_rchild,f);
               if constexpr(N==2) f(bt->_val);
           }
    }
};
}
#endif /* BinaryTree_h */
