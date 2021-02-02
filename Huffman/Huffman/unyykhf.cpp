//
//  unyykhf.cpp
//  Huffman
//
//  Created by 杨永康 on 2021/2/1.
//

#include <iostream>
#include <algorithm>
#include<vector>
#include<array>
#include<limits>
#include<utility>
#include<cstdio>
#include<filesystem>
#include<bitset>
#include<cassert>
#include<cstring>
#include<execution>
#include<numeric>
#include<type_traits>
#include"buffer_file_zip_unzip.hpp"
int main(int argc, const char * argv[]) {
     namespace fs=std::filesystem;
    using namespace Huffman;
    std::string file_name;
    file_name.reserve(1024);
    if(argc>3||argc<2) {
        std::cout<<"yykhf:error: no input files"<<std::endl;
        return 1;
    }
    if(!fs::is_regular_file(fs::status(argv[1]))) {
        printf("yykhf:error: no such file or directory: '%s'\n",argv[1]);
        return 1;
    }
    fs::path p(argv[1]);
    if(p.extension().string()!=".yykhf"){
        printf("yykhf:error: Wrong file extension\n");
        return 1;
    }
    if(argc==2) {
        const std::string s=p.string();
        file_name.assign(s.begin(),s.end()-6);
    }
    else file_name.assign(argv[2],strlen(argv[2]));
    buffer_file_unzip<4000000, std::vector, unsigned char, uint64_t>(argv[1],file_name.c_str());
    std::cout<<file_name<<" "<<"has been generated"<<std::endl;
    return 0;
}
