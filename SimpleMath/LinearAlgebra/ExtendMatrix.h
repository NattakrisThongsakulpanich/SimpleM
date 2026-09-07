#pragma once

#include "../ExpressionTraits.h"

namespace Symbolic
{

    struct EXTMAT  
    {

        private:
        
        static inline auto (){};
    
        public:

        template <typename T>
        static inline auto eval(const T &V, unsigned int index) 
        {
            constexpr unsigned int rows = SimpleM::EXPR_TRAITS<T>::rows;
            constexpr unsigned int cols = SimpleM::EXPR_TRAITS<T>::cols; 
        }

        template <typename T>
        static inline auto eval(const T &V, unsigned int row, unsigned int col) 
        { 
            return V(row, col); 
        }


    };

}
