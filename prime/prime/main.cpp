//
//  main.cpp
//  prime
//
//  Created by 杨永康 on 2021/2/21.
//
#include <iostream>
#include<future>
#include<chrono>
#include<cmath>
#include<bitset>
#include"prime_filter.hpp"
/*int main(int argc, const char * argv[]) {
    using namespace std::chrono;
    auto time_0=high_resolution_clock::now();
    std::cout<<prime_filter::yyk_total<unsigned long long,202102180918,500000>()<<std::endl;
    auto time_1=high_resolution_clock::now();
    std::cout<<duration_cast<milliseconds>(time_1-time_0).count()<<"ms\n";
    return 0;
}*/
#include<numeric>
#include<thread>
#include<vector>
using namespace std;
using namespace chrono;
constexpr int segSizeRate=4;//系数可以根据CPU缓存大小做调整
auto getPrime(uint64_t upper)
{
    vector<uint32_t> primesList;
    vector<bool> isPrime;
    isPrime.resize(upper+1,true);//初始化bitset
    primesList.reserve(upper/log(upper)*1.2);//估计素数个数
    isPrime[0]=isPrime[1]=false;
    for (uint32_t i=2;i<=upper;++i)
    {
        if (isPrime[i])
            primesList.emplace_back(i);
        for (const auto &e:primesList)
        {
            if (e*i>upper) break;
            isPrime[e*i]=false;
            if (i%e==0) break;
        }
    }
    return primesList;
}
auto calPrimesTable(uint64_t beg,uint64_t end,const vector<uint32_t>& primesList)
{
    vector<bool> isPrime(end-=beg,true);
    if (primesList.size()>2)
        for (auto e=primesList.cbegin()+2;e!=primesList.cend();++e)
        {//不筛2和3
            auto iter=(beg%*e==0)?0:*e-beg%*e;
            if (iter+beg==*e&&iter<end)
            {
                isPrime[iter]=true;
                iter+=*e;
            }
            for (;iter<end;iter+=*e)
                isPrime[iter]=false;
        }
    return isPrime;
}
void calSeg(uint64_t beg,uint64_t end,int64_t& cnt,uint64_t upper,const vector<uint32_t>& primesList)
{
    auto rbeg=upper-end+1,rend=upper-beg+1,end2=end-1;
    const vector<bool> tableLeft=calPrimesTable(beg,end,primesList),
                       tableRight=calPrimesTable(rbeg,rend,primesList);
    auto iter=beg;
    if (beg<=2 && end >2 && tableRight[upper-2-rbeg]) ++cnt;//特判2
    if (beg<=3 && end >3 && tableRight[upper-3-rbeg]) ++cnt;  //特判3
    if (iter % 2 == 0) ++iter;
    if (iter % 6 == 3) iter += 2;
    switch (upper % 6)//利用素数的6n-1和6n+1性质快速枚举
    {
    case 0:
        if (iter % 6 == 1) goto flag;
        while (true)
        {
            if (iter >= end)
                return;
            cnt += tableLeft[iter-beg] && tableRight[end2 - iter];
            iter += 2;
        flag:
            if (iter >= end)
                return;
            cnt += tableLeft[iter-beg] && tableRight[end2 - iter];
            iter += 4;
        }
        return;
    case 2:
        if (iter % 6 == 5) iter += 2;
        while (iter < end)
        {
            cnt += tableLeft[iter-beg] && tableRight[end2 - iter];
            iter += 6;
        }
        return;
    case 4:
        if (iter % 6 == 1) iter += 4;
        while (iter < end)
        {
            cnt += tableLeft[iter-beg] && tableRight[end2 - iter];
            iter += 6;
        }
        return;
    default:
        return;
    }
}
void calPar(uint64_t beg,uint64_t end,int64_t&cnt,uint64_t upper,const vector<uint32_t>& primesList,uint64_t dis)
{
    auto segCount=(end-beg)/dis;
    for (uint64_t i = 0,iterEnd=beg; i < segCount; ++i,beg=iterEnd)
    {
        iterEnd = (i + 1 == segCount)? end : iterEnd + dis;
        calSeg(beg, iterEnd, cnt, upper, ref(primesList));
    }
}
auto cal(uint64_t upper)
{
    uint64_t count=0,sqrtUpper=ceil(sqrt(upper));
    const auto primesList=getPrime(sqrtUpper);
    vector<thread> threads;
    vector<int64_t> answers;
    auto threadCount = max(1u,thread::hardware_concurrency());
    answers.assign(threadCount,0);
    uint64_t mid = upper / 2 + 1, segDis = (mid - 2) /max<uint64_t>(sqrtUpper/segSizeRate,1), dis = (mid - 2)/threadCount;
    //segDis:分段筛中每段的长度，和cache有关,
    for (uint64_t i = 0,iterBegin=2,iterEnd=iterBegin; i < threadCount; ++i,iterBegin=iterEnd)
    {
        iterEnd = (i + 1 == threadCount)? mid : iterEnd + dis;
        threads.emplace_back(calPar, iterBegin, iterEnd, ref(answers[i]), upper, ref(primesList),segDis);
    }
    for (auto &&e:threads)
        e.join();
    return std::accumulate(answers.begin(),answers.end(),count);
}
int main(void)
{
    high_resolution_clock clk;
    auto timePoint1=clk.now();
    auto cnt=cal(202102180918);
    printf("used time: %.3fs\n",duration_cast<milliseconds>(clk.now()-timePoint1).count()/1e3);
    printf("answer: %llu\n",cnt);
    return 0;
}

