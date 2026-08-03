#pragma once
#include <iostream>
#include <chrono>

namespace Benchmark
{
    inline void sum( unsigned int iteration, double(*f)(unsigned int t) )
    {
        
        auto start = std::chrono::high_resolution_clock::now();

        volatile double result = 0;

        for(unsigned int i = 1; i <= iteration; i++)
        {
            result += f(i);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Time : " << duration.count() << " microseconds\n";
        std::cout << "T. Avg. per Call : " << ( duration.count() / static_cast<double>(iteration) ) * 1000 << " nanoseconds\n";
        std::cout << "Result : " << result << '\n';

    }
}
