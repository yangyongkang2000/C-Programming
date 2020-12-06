//
//  main.cpp
//  theoretical_plate_diagram
//
//  Created by 杨永康 on 2020/12/6.
//

#include <iostream>
#include<vector>
#include<array>
#include"theoretical_plate_diagram.hpp"

int main(int argc, const char * argv[]) {
    using namespace std;
    auto result=chemistry::TPD<vector<double>, vector<array<double,2>> >({2.46,0.06,0.94,0.44,1.38,2});
    for(auto &v:result)
    {
        for(auto &c:v)
        {
            cout<<c<<" ";
        }
        cout<<endl;
    }
    return 0;
}
