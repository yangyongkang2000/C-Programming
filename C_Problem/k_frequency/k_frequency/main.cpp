//
//  main.cpp
//  k_frequency
//
//  Created by 杨永康 on 2021/5/24.
//

#include <iostream>
#include<string>
#include<vector>
#include<cstddef>
#include<algorithm>
#include<unordered_map>
void put_in(std::string const & s,std::unordered_map<std::string, uint64_t> &dict)
{
    auto f=s.begin();
    while(f!=s.end())
    {
        f=std::find_if(f, s.end(), [](auto const &c){return ('a'<=c&&c<='z')||('A'<=c&&c<='Z');});
        if(f!=s.end())
        {
        auto l= std::find_if(f+1, s.end(),[](auto const &c){return !('a'<=c&&c<='z')||('A'<=c&&c<='Z');});
            auto e=l==s.end()?s.end():l+1;
            auto m(s.substr(f-s.begin(),e-f));
            f=e;
            std::for_each(m.begin(), m.end(), [](auto &c) {if(c>='A') c-=('A'-'a');});
            if(dict.count(m))
                dict[m]++;
            else dict.insert({std::move(m),1});
        }
    }
}
template<typename OS>
void k_dict(OS &os,std::unordered_map<std::string, uint64_t> const & dict)
{
    std::vector<std::pair<std::string, int>> v;
    v.reserve(dict.size());
    std::for_each(dict.begin(), dict.end(), [](auto &p) {});
    std::nth_element(<#_RandomAccessIterator __first#>, <#_RandomAccessIterator __nth#>, <#_RandomAccessIterator __last#>, <#_Compare __comp#>)
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
