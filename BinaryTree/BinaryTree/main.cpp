//
//  main.cpp
//  BinaryTree
//
//  Created by 杨永康 on 2021/3/25.
//

#include <iostream>
#include"BinaryTree.hpp"
#include"yyk_random.hpp"
int main(int argc, const char * argv[]) {
    // insert code here...
    yyk_random::uniform_int_distribution<> dis(0,999);
    yyk_BT::BinaryTree<long> bt;
    int p[1000]={};
    for(int i=0;i<10000;i++)
    {
        long j(dis());
        bt.insert(j);
        p[j]++;
    }
    for(int i=0;i<1000;i++)
    if(p[i]) {
        if(p[i]!=bt[i])
        {
            std::cout<<"it's error\n";
            exit(1);
        }
    }else {
        if(bt.find(i))
        {
            std::cout<<"it's error\n";
            exit(1);
        }
    }
    std::cout<<"it's true\n";
        
    
}
