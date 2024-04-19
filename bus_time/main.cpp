//
//  main.cpp
//  calc_time
//
//  Created by 杨永康 on 2024/3/13.
//

#include <iostream>
#include<tuple>
#include<string>
#include<algorithm>
#include<vector>
#include<fstream>
#include<cstdio>
#include<ctime>
#include<filesystem>
auto trans_hms(int h,int m,int s) {
    std::string str{};
    if(h!=0)
        str+=std::to_string(h)+"h";
    if(m!=0)
        str+=std::to_string(m)+"m";
    if(s!=0)
        str+=std::to_string(s)+"s";
    return str;
}

template<typename V>
void read_file(const char *_,V &v) {
    std::ifstream is(_);
    int h,m,s;
    while(is>>h>>m>>s) {
    v.emplace_back(h,m,s);
    }
    std::sort(v.begin(),v.end());
    v.erase(std::unique(v.begin(),v.end()),v.end());
}

class bus_time {
    std::vector<std::tuple<int, int,int>> hm1;
    std::vector<std::tuple<int,int,int>> hm2;
    std::vector<std::tuple<int,int,int>> hm3;
    std::vector<std::tuple<int,int,int>> hm4;
    template<typename InputIt>
    void print(InputIt beg,InputIt end,int len,int d,bool b) {
        if(beg!=end) {
            for(int i=0;i<len&&beg!=end;i++) {
                auto [h, m, n] = *beg++;
                auto tmp = 3600 * h + 60 * m - d;
                std::printf("Next (%d) Bus:%d:%d\nBus Service/Route:%d/%d\n", i+1,h, m, n, b ? 1 : 2);
                std::cout << "Waiting Time:" << trans_hms(tmp / 3600, (tmp % 3600) / 60, (tmp % 3600) % 60) << "\n\n";
            }
        }else{
            std::cout<<"The last bus has been missed\n";
        }
    }

public:
    bus_time(const char * _1,const char * _2,const char * _3,const char * _4) {
        read_file(_1,hm1);
        read_file(_2,hm2);
        read_file(_3,hm3);
        read_file(_4,hm4);
    }
    void wait_next_bus(bool b=true,int next_count=1,bool b1=true) {
        auto now=std::time(nullptr);
        auto lt=std::localtime(&now);
        int  d=3600*lt->tm_hour+60*lt->tm_min+lt->tm_sec;
        auto week=lt->tm_wday;
        auto b2=(1<=week&&week<=5);
        auto &hm= b1 == b2 ? (b ? hm1 : hm2) : (b ? hm3 : hm4);
        auto it=std::find_if(hm.begin(), hm.end(), [=](auto p){
            auto [h,m,n]=p;
            return 1<=week&&week<=5?d<=(3600*h+60*m):(d<=(3600*h+60*m))&&(n==1);
        });
        print(it,hm.end(),next_count,d,b);
    }
};

int main(int argc,char **argv) {
    auto p=std::filesystem::path(__FILE__).parent_path();
    std::cout<<p<<"\n";
    bus_time b((p/"data1.txt").c_str(),(p/"data2.txt").c_str(),(p/"data3.txt").c_str(),(p/"data4.txt").c_str());
    if(argc<3) {
        b.wait_next_bus(true);
    }else{
        auto l1=std::stof(argv[1]);
        auto l2=std::stof(argv[2]);
        printf("Distance:%.2fkm\n",std::max(l1, l2));
        b.wait_next_bus(l1<l2,argc<4?1:std::stoi(argv[3]), argc < 5 || std::stoi(argv[4]) != 0);
    }
    return 0;
}
