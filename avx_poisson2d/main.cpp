//
//  main.cpp
//  avx_poisson2d
//
//  Created by 杨永康 on 2022/10/9.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <limits>
#include "avx_poisson2d.hpp"
void print_benchmark_result(const std::string &name, const double time)
{
    std::cout << "Cpp," << name << ',' << std::setprecision(6) << time << std::endl;
}

int main()
{
    constexpr int NRUNS = 20;
    double tmin = std::numeric_limits<double>::max();
    int iter;
    for (int i = 0; i < 5; ++i)
    {
        auto t1 = std::chrono::system_clock::now();
        for (int j = 0; j < NRUNS; ++j)
            poisson2d(iter);
        auto t2 = std::chrono::system_clock::now();
        std::chrono::duration<double> duration = t2 - t1;
        if (duration.count() < tmin)
            tmin = duration.count();
    }
    print_benchmark_result("poisson2d", tmin / NRUNS);
    return 0;
}


