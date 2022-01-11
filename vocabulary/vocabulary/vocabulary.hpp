#ifndef vocabulary_h
#define vocabulary_h
inline int vocabulary(const std::filesystem::path &c_p) noexcept
{
    namespace fs = std::filesystem;
    using Type=std::pair<std::string,std::vector<std::string>>;
    using T=std::pair<std::string,std::string>;
    using C=std::vector<Type>;
    using X=std::vector<T>;
    using D=X::difference_type;
    using U=std::unordered_map<std::string, std::vector<std::string>>;
    auto t_p(fs::is_directory(c_p)?c_p:c_p.parent_path());
    fs::current_path(t_p);
    auto di{fs::directory_iterator(t_p)};
    auto dict_it=find_path(fs::begin(di), fs::end(di), ".yyk_dat");
    if(dict_it==fs::end(di)) {
        std::cout<<"Error:Dictionary isn't find\n";
        return 1;
    }
    fs::permissions(dict_it->path(),fs::perms::owner_read|fs::perms::group_read|fs::perms::others_read);
    auto dict(fast_get_dict<32*1024>(dict_it->path().string().c_str()));
    if (dict.empty())
    {
        printf("Error:Dictionary is empty\n");
        return 1;
    }
    auto f=find_path(fs::begin(di), fs::end(di), ".yyk_log");
    auto p(f==fs::end(di)?fs::path("history.yyk_log"):f->path());
    auto result(read(p.string()));
    X mem;
    U ump;
    printf("HELLO WELLCOME VOCABULARY\nVersion:2.7.5\nCopyright@2021 Yang Yongkang. All rights reserved.\n");
    while(true)
    {
        std::string tmp;
        std::string word;
        bool english=true;
        printf(">>> ");
        do{
            auto line(c_getline());
            tmp=word_string(line);
            if(tmp.empty())
            {
                auto ch(chinese_string(line));
                if(!ch.empty())
                {
                    tmp=std::move(ch[0]);
                    english=false;
                }
            }
        } while(tmp.empty());
        if('0'<=tmp[0]&&tmp[0]<='9')
        {
            int pos=std::atoi(tmp.c_str());
            if(pos>=0&&pos<static_cast<int>(mem.size()))
               word=mem[pos].first;
        }else
            word=tmp;
        if(word.front()=='['&&word.back()==']'&&word.size()>2)
        {
            auto cmd(word_string(word.substr(1,word.size()-2)));
            if (!cmd.empty())
            {
                if(yyk_strcasecmp(cmd.c_str(), "exit")==0)
                   return exit_io(ump, result, p);
                if(yyk_strcasecmp(cmd.c_str(), "test")==0)
                    test<10>(result);
                else {
                if(yyk_strcasecmp(cmd.c_str(), "new")==0)
                    output_new(ump);
                else system(cmd.c_str());
                }
            }
            continue;
        }
        auto a1(std::async(std::launch::async,[&](){
            auto it(std::lower_bound(result.begin(), result.end(), word,[](const auto &l,const auto &r){
                return yyk_strcasecmp(l.first.c_str(), r.c_str())<0;
       } ));
            auto u(std::upper_bound(result.begin(), result.end(), word, [](const auto &l,const auto &r){
                return yyk_strcasecmp(l.c_str(), r.first.c_str())<0;}));
            return std::make_pair(it, u);
        }));
        auto a2(std::async(std::launch::async, [&](){
                return std::lower_bound(dict.begin(), dict.end(), word,[](const auto &l,const auto &r){
                    return yyk_strcasecmp(l.first.c_str(), r.c_str())<0;
                });
        }));
        auto r1(a1.get());
        auto r2(a2.get());
        bool b=(r2!=dict.end()&&yyk_strcasecmp(word.c_str(), r2->first.c_str())==0);
        auto it=r1.first;
        auto u=r1.second;
        bool b1=b?(it!=result.end()&&yyk_strcasecmp(word.c_str(), it->first.c_str())==0):false;
        printf(b?(b1?"selsect:[1]search [2]add [3]remove [4]test [5]exit\nchoice:":"selsect:[1]search [2]add [4]test [5]exit\nchoice:"):"select:[1]search [4]test [5]exit\nchoice:");
        auto c_s(word_string(c_getline()));
        putchar('\n');
        char c=c_s.empty()?'\n':c_s[0];
        if(!b1)
            if((!b&&c=='2')||c=='3')
                continue;
        switch (c) {
            case '1':case '\n':
            {
                mem.clear();
                if(!b){
                    if(english){
                    auto it=r2;
                    auto d1=std::distance(dict.begin(), it);
                    d1=d1<5?d1:5;
                    auto d2=std::distance(it,dict.end());
                    d2=d2<5?d2:5;
                    std::vector<std::pair<T,D>> m;
                    for(auto beg=it-d1;beg!=it+d2;beg++)
                        m.emplace_back(std::pair<T,D>{*beg,beg<it?it-beg:beg-it});
                    std::sort(m.begin(), m.end(), [](auto &l,auto &r)
                              {
                        return l.second<r.second;
                    });
                        for(auto &l:m) mem.emplace_back(std::move(l.first));}
                    else {
                        auto vec(range_string_match<std::default_searcher>(dict.begin(),dict.end(), word));
                        std::move(vec.begin(),vec.end(),std::back_inserter(mem));
                    }
                    for(C::size_type i=0;i<mem.size();i++)
                    {
                        auto &[w,v]=mem[i];
                        printf("[%d]: %s ", static_cast<int>(i), w.c_str());
                        printf("%s\n\n",v.c_str());
                    }
                }else
                {
                    printf("[0]: %s %s\n\n",r2->first.c_str(),r2->second.c_str());
                    mem.emplace_back(*r2);
                }
                break;
            }
            case '2':
            {
                    std::vector<std::string> v_tmp;
                    printf(">>> ");
                do{
                    auto line(c_getline());
                    v_tmp=chinese_string(line);
                }while(v_tmp.empty());
                if(!b1)
                {
                    Type m{std::move(word),std::move(v_tmp)};
                    result.insert(u, m);
                    ump[m.first]=std::move(m.second);
                }
                else
                {
                    auto l1=it->second.size();
                    for_each(v_tmp.begin(),v_tmp.end(),[&](auto &l){
                        auto &v=it->second;
                        if(std::find(v.begin(), v.end(), l)==v.end()) v.emplace_back(l);
                    });
                    auto l2=it->second.size();
                    if(l1!=l2) ump[it->first]=it->second;
                }
                    save(result, p.string());
                break;
            }
            case '3':
            {
                    std::cout<<it->first<<" [0]\n";
                    auto &v=it->second;
                    for(C::size_type i=0;i<v.size();i++)
                        std::cout<<v[i]<<' '<<"["<<i+1<<"]\n";
                    putchar('\n');
                    printf(">>> ");
                    int pos=-1;
                    auto pos_s(word_string(c_getline()));
                   if('0'<=pos_s[0]&&pos_s[0]<='9')
                       pos=std::atoi(pos_s.c_str());
                    if(pos==0) {
                        ump.erase(it->first);
                        result.erase(it);
                    }
                    else {
                        if(0<pos&&pos<=static_cast<int>(v.size())) {
                            v.erase(v.begin()+pos-1);
                            ump[it->first]=it->second;
                            if(v.empty()) {
                                ump.erase(it->first);
                                result.erase(it);
                            }
                        }
                    }
                    save(result, p.string());
                break;
            }
            case '4':{
                  test<10>(result);
                break;
            }
            case '5':
            {
                return exit_io(ump, result, p);
            }
            default:
                break;
        }
    }
    return 0;
}
#endif /* vocabulary_h */
