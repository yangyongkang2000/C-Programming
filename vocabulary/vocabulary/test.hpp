#ifndef test_h
#define test_h
template<unsigned int N,typename T>
inline void test(const T &r) noexcept
{
    T out;
    auto d=N<r.size()?N:r.size();
    std::random_device rd;
    std::mt19937 g(rd());
    std::sample(r.begin(), r.end(), std::back_inserter(out),
                    d,g);
    std::shuffle(out.begin(),out.end(),g);
    typename T::difference_type num(0);
    for(auto & p:out)
    {
        auto &w=p.first;
        auto &v=p.second;
        std::vector<std::string> ch;
        printf("Question:%s ",w.c_str());
        do {
            auto tmp(c_getline());
            ch=chinese_string(tmp);
        }while(ch.empty());
        auto cn=std::count_if(ch.begin(), ch.end(), [&](auto &s){
            return std::find(v.begin(), v.end(), s)!=v.end();
        });
        printf("Answer:%s ",w.c_str());
        for(auto &i:v)
            printf("%s ",i.c_str());
        auto rate=100*cn/v.size();
        std::cout << "\nCorrect Rate:" << rate << "%\n\n";
        num+=rate;
    }
    std::cout<<"Grade:"<<(num?num/out.size():num)<<"\n\n";
}
#endif /* test_h */
