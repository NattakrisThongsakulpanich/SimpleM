#pragma once

#include "../ExpressionTraits.h"

namespace Symbolic
{

    struct TRANSPOSE  
    {
        template <typename T>
        static inline auto eval(const T &V, unsigned int index) 
        {
            constexpr unsigned int rows = SimpleM::EXPR_TRAITS<T>::rows;
            return V(index % rows, index / rows); 
        }

        template <typename T>
        static inline auto eval(const T &V, unsigned int row, unsigned int col) 
        { 
            return V(row, col); 
        }


    };

}
