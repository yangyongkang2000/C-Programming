#ifndef yyk_io_h
#define yyk_io_h
template<typename InputIt,typename path>
inline auto find_path(InputIt beg,InputIt end,const path&p) noexcept
{
    return std::find_if(beg, end, [&](auto &entry){
        return entry.is_regular_file()&&entry.path().extension()==p;
    });
}
template<typename S=std::string>
inline S c_getline()
{
    S s;
    std::getline(std::cin,s);
    return s;
}
template<typename S=std::string,template<typename ...> class V=std::vector>
inline V<S> chinese_string(const S &s) noexcept
{
    V<S> result;
    S tmp;
    for(auto c:s){
        if(c<0)
            tmp.push_back(c);
        else{
            if(tmp.size())
            {
                result.push_back(tmp);
                tmp.clear();
            }
        }
    }
    if(tmp.size()) result.push_back(tmp);
    return result;
}
template<typename S=std::string>
inline S word_string(const S &s) noexcept
{
    S s1;
    for(auto c:s){
        if(c<0)
            break;
        if(c!=' '||(c==' '&&s1.size()!=0&&*s1.rbegin()!=' '))
              s1.push_back(c);
    }
    if(s1.size()&&*s1.rbegin()==' ') s1.pop_back();
    return s1;
}
template<template<typename...> class V=std::vector,typename  S=std::string>
inline V<std::pair<S,V<S>>> read(const S &file_name) noexcept
{
    std::ifstream is(file_name,std::ios::binary);
    V<std::pair<S,V<S>>> result;
    for(std::string line;std::getline(is, line);)
    {
        std::string line1;
        std::getline(is,line1);
        result.emplace_back(std::pair<S,V<S>>{std::move(line),std::move(chinese_string(line1))});
    }
    auto cmp=[](const auto &lhs,const auto &rhs){
        return yyk_strcasecmp(lhs.first.c_str(), rhs.first.c_str())<0;
    };
    if(!std::is_sorted(result.begin(), result.end(), cmp))
        std::sort(result.begin(), result.end(), cmp);
    return result;
}
template<typename T,typename S>
inline void save(const T &result,const S &file_name) noexcept
{
    std::ofstream os(file_name);
    for(auto &[w,v]:result)
    {
        os<<w<<'\n';
        for(auto &i:v)
            os<<i<<' ';
        os<<'\n';
    }
}
template<typename U>
inline void output_new(const U &ump) noexcept
{
       printf("New Words:\n");
       for(auto &[w,v]:ump)
       {
           printf("%s ",w.c_str());
           for(auto &str:v)
               printf("%s ",str.c_str());
           putchar('\n');
       }
       std::cout<<"Number of new words:"<<ump.size()<<"\n\n";
}
template<typename U,typename R,typename P>
inline int exit_io(const U &ump,const R &result,const P&p) noexcept
{
    namespace fs = std::filesystem;
    auto a1=std::async(std::launch::async,output_new<U>,ump);
    auto a2=std::async(std::launch::async,[&](){
        save(result,p);
    });
    a1.get();
    a2.get();
    return 0;
}
#endif /* yyk_io_h */
