#pragma once

#include "../ExpressionTraits.h"

namespace Evaluator 
{
    struct ELM_ADD 
    {
        template <typename T>
        static inline auto eval(const T &V, unsigned int index) 
        {
            constexpr unsigned int rows = SimpleM::EXPR_TRAITS<T>::rows;
            return V(index % rows, index / rows); 
        }
    };

    //UnaryOpDispatcher is WIP

}
