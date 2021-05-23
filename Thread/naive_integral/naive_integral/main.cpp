//
//  main.cpp
//  naive_integral
//
//  Created by 杨永康 on 2021/4/24.
//

#include <iostream>
#include <iomanip>
#include<cmath>
#include<chrono>
#include"naive_integral.hpp"
#include"define_integral.hpp"
#include"simpson.hpp"
constexpr double precise_answer_1=0.527038332448776;
constexpr double precise_answer_2= 2.0749548496372165;
constexpr double tol=1e-10;
template<typename real>
inline constexpr real f(const real x)
{
    return std::log(std::cos(x) + std::sin(x)) * ((x - std::sin(x) + std::cosh(x)) / (x + std::cos(x) - std::sinh(x)));
}
template<typename real>
inline constexpr real g(const real x)
{
    return std::sin(x*x);
}
template<typename T,typename G,typename F>
inline constexpr auto test_time(G g,F f,std::pair<std::pair<T, T>, T> const &p,std::pair<T, T> const &q)
{
    using namespace std::chrono;
    auto t0=high_resolution_clock::now();
    auto answer=g(f,p);
    auto t1=high_resolution_clock::now();
    std::cout<<"time/s:"<<duration_cast<milliseconds>(t1-t0).count()<<"ms\n";
}
int main(int argc, const char * argv[]) {
    // insert code here...
    test_time<double>(demo::definite_integral<double,decltype(f<double>)>, f<double>, {{0.,1.},1e-10}, {precise_answer_2,tol});
    return 0;
}
