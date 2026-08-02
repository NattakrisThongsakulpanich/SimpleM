#pragma once 
#include <cstdint>

namespace SimpleM
{
    constexpr uint64_t fac(const uint64_t z)
    {
        if (z == 1)
        {
            return 1;
        }
        else if (z == 0)
        {
            return 1;
        }
        else
        {
            return z * fac(z - 1);
        }
    }

}