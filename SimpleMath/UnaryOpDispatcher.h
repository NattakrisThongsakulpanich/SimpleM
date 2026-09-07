#pragma once 

#include "./Expression.h"
#include "ExpressionTraits.h"
#include "./LinearAlgebra/Transpose.h"
#include "./UnaryOp.h"

namespace SimpleM
{
    template <typename T, typename sym, ExprFormat F = EXPR_TRAITS<T>::Format >
    struct UnaryOpDispatcher
    {
        using ValueType = void;
        using Expression = void;
        using Evaluator = void;
        static constexpr ExprFormat Format = ExprFormat::UNDEFINED;
        static constexpr unsigned int rows = 0;
        static constexpr unsigned int cols = 0; 
    };

    template <typename T>    
    struct UnaryOpDispatcher<T, Symbolic::TRANSPOSE, ExprFormat::Matrix>
    {
        using ValueType = typename EXPR_TRAITS<T>::ValueType;
        using Expression = UnaryOp<T, Symbolic::TRANSPOSE>;
        using Evaluator = Symbolic::TRANSPOSE;
        static constexpr ExprFormat Format = ExprFormat::Matrix;
        static constexpr unsigned int rows = EXPR_TRAITS<T>::rows;
        static constexpr unsigned int cols = EXPR_TRAITS<T>::cols;
    };

    template <typename T, typename sym>
    struct EXPR_TRAITS<UnaryOpDispatcher<T,sym>>
    {
        using ValueType = typename UnaryOpDispatcher<T,sym>::ValueType;
        static constexpr ExprFormat Format = UnaryOpDispatcher<T, sym>::Format; 
        static constexpr unsigned int rows = UnaryOpDispatcher<T, sym>::rows;
        static constexpr unsigned int cols = UnaryOpDispatcher<T, sym>::cols;
    };

}
