#pragma once 
#include <cstdint>
#include "Combinatorics.h"

namespace SimpleM
{ 

    inline double pow(const double base, const unsigned int exp)
    {

        if (exp == 1) {return base;}
        if (exp == 0) {return 1.0f;}
        if (exp == 2) {return base * base;}
        if (exp == 3) {return base * base * base;}

        double result = 1;
        double current_base = base;
        uint64_t current_exp = exp; 
        while ( current_exp > 0)
        {
            if (current_exp & 1)
            {
                result *= current_base;
            }
            
            current_base *= current_base;
            current_exp >>= 1;
            
        }

        return result;

    }

    /*
     * old ln function
    inline double ln(const double a)
    {
        const double z = (a-1)/(a+1); 
        double sum = z;

        for(uint8_t i = 1; i<6; i++)
        {
            const uint8_t n = (2*i) + 1;
            sum += pow(z, n) / n;
        }

        return sum * 2;
    }
    */
    inline double ln(const double a)
    {
        const double z = (a-1)/(a+1);
        const double z_squared = pow(z,2); 
        double sum = 1.0f/13.0f;

        for (double i = 11; i >= 1; i-=2)
        {
            sum = sum*z_squared + 1.0f/i;
        }

        return sum * z * 2;

    }

    inline double log (const double base, const double a)
    {
        return ln(a)/ln(base);// need a faster algotithm soon. current: 2 * O(log n) complexity
    }

    inline double exp(const double a)
    {

        double sum = 1;
        double base = a;

        for(unsigned int i = 1; i<6; i++)
        {
            sum += base / fac(i);
            base *= base;
        }

        return sum;
    }

    inline double dpow(const double a, const double b) // loose a precision at 8 decimal places
    {
        return exp(b * ln(a));
    }

    
    inline double sqrt(const double a)
    {
        return exp(1.0f/2.0f * ln(a));    
    }
   
    inline double root(const double base, const double value)
    {
        return exp(1.0f/base * ln(value));    
    }

}
