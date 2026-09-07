#pragma once 

#include "../Expression.h"

namespace SimpleM
{

    template <typename Tl, typename Tr, typename T, unsigned int lhsR, unsigned int rhsC, unsigned int C_s >
    struct MatProduct : EXPR<MatProduct<Tl,Tr,T,lhsR,rhsC,C_s>> 
    {

        const Tl &lhs;
        const Tr &rhs;

        MatProduct(const Tl &LHS, const Tr &RHS) : lhs(LHS), rhs(RHS) {};

        constexpr static unsigned int productRows = lhsR;
        constexpr static unsigned int productCols = rhsC;

        const inline auto operator[](const unsigned int i) const
        {
            const unsigned int row = i / productCols;
            const unsigned int col = i % productCols;

            T sum = 0; 
            
            #pragma omp simd
            for(unsigned int k = 0; k < C_s ; ++k)
            {
                sum += lhs(row,k) * rhs(k,col);
            }
            return sum;
        }

        const inline auto operator()(const unsigned int row, const unsigned int col) const 
        {
            T sum = 0; 

            for(unsigned int k = 0; k < C_s ; ++k)
            {
                sum += lhs(row,k) * rhs(k,col);
            }
            return sum;

        }
 
    };


}
