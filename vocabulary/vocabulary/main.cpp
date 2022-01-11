#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif
#include <iostream>
#include<string>
#include<cstdio>
#include<fstream>
#include<algorithm>
#include<random>
#include<vector>
#include <ctime>
#include<functional>
#include<array>
#include<cstring>
#include<future>
#include<iterator>
#include<unordered_map>
#include<filesystem>
#include<cassert>
#include<cstdlib>
#include<thread>
#include"yyk_string.hpp"
#include"fast_io.hpp"
#include"yyk_io.hpp"
#include"test.hpp"
#include"path.hpp"
#include"vocabulary.hpp"
int main(int argc, const char * argv[]) {
    namespace fs = std::filesystem;
#ifdef PATH_H
     return vocabulary(argc>=2?fs::path{argv[1]}:fs::path(PATH_H));
#else
    return vocabulary(argc>=2?fs::path{argv[1]}:fs::path{"."});
#endif
    
}
