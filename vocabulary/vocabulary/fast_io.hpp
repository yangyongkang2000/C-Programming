#ifndef fast_io_h
#define fast_io_h
template<std::size_t N,template<typename ...> class V=std::vector,typename S=std::string>
inline V<S> fast_fgetline(const char *filename) noexcept
{
    V<S> result;
    auto file=fopen(filename, "rb");
    std::array<char, N> mem{};
    auto beg=mem.data();
    std::size_t offset=0;
    while(true)
    {
        auto len=N-offset;
        auto n=fread(beg+offset, sizeof(char),len, file);
        auto end=beg+offset+n;
        auto first=beg;
        while (true) {
            auto last=(char*)memchr(first, '\n', end-first);
            if(last!=NULL)
            {
                if(last>first)
                result.emplace_back(first,last);
                first=last+1;
            }else{
                std::copy(first, end, beg);
                offset=end-first;
                if(offset==N) return {};
                break;
            }
        }
        if(n<len)
        {
            if(offset)
                result.emplace_back(beg,beg+offset);
            break;
        }
    }
    return result;
}
template<std::size_t N,template<typename ...> class V=std::vector,typename S=std::string>
inline V<std::pair<S,S>>  fast_get_dict(const char *filename) noexcept
{
    auto tmp(fast_fgetline<N,V,S>(filename));
    if (tmp.size()<2)
        return {};
    V<std::pair<S,S>> result;
    auto len=tmp.size()>>1;
    result.reserve(len+1);
    auto beg=tmp.begin();
    auto end=tmp.end();
    for(;beg!=end;beg+=2)
        result.emplace_back(std::move(*beg),std::move(*(beg+1)));
    return result;
}
#endif /* fast_io_h */

