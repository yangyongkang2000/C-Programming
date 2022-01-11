#ifndef yyk_string_h
#define yyk_string_h
inline int yyk_strcasecmp(const char *s1,const char *s2) 
{
    const unsigned char *p1 = (const unsigned char *) s1;
      const unsigned char *p2 = (const unsigned char *) s2;
      int result;
      if (p1 == p2)
        return 0;
      while ((result = tolower (*p1) - tolower(*p2++)) == 0)
        if (*p1++ == '\0')
          break;
      return result;
}
template<template<typename...> class searcher,typename S>
inline bool string_match(const S &s1,const S &s2) noexcept
{
    auto beg=std::begin(s1);
    auto end=std::end(s1);
   auto it=std::search(beg, end, searcher(std::begin(s2),std::end(s2)));
    if(it==end||*(it-1)<0) return false;
    return true;
}
template<template<typename...> class searcher,typename InputIt,typename S>
inline auto range_string_match(InputIt beg,InputIt end,const S &s1) noexcept
{
    using T=typename std::iterator_traits<InputIt>::value_type;
    std::vector<T> result;
    for(auto it=beg;it!=end;it++)
        if(string_match<searcher>(it->second, s1))
            result.emplace_back(*it);
    return result;
}
#endif /* yyk_string_h */
