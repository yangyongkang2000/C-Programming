//
//  main.cpp
//  nearest_point
//
//  Created by 杨永康 on 2021/4/27.
//

#include <iostream>
#include<vector>
#include"naive_near_point.hpp"
int main(int argc, const char * argv[]) {
    // insert code here...
    std::vector<std::pair<double, double>> v {{0,0},{2,3},{2,2},{0,0.21},{2.9,3}};
    auto p=naive_near_point(v.begin(), v.end());
    std::cout << "Hello, World!\n";
    return 0;
}
