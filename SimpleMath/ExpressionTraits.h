#pragma once

#include "./Value.h"
#include "./LinearAlgebra/Matrix.h"
#include "./BinaryOp.h"
#include "Expression.h"
#include "LinearAlgebra/MatrixProduct.h"

namespace SimpleM
{ 

    template <typename T>
    struct EXPR_TRAITS
    {
        using ValueType = void; 
        static constexpr ExprFormat Format = ExprFormat::UNDEFINED; 
        static constexpr unsigned int rows = 0;
        static constexpr unsigned int cols = 0;
    }; 

    template <typename T>
    struct EXPR_TRAITS<Value<T>>
    {
        using ValueType = T;
        static constexpr ExprFormat Format = ExprFormat::Scalar; 
        static constexpr unsigned int rows = 0;
        static constexpr unsigned int cols = 0;
    };  

    template <typename T, unsigned int row, unsigned int col>
    struct EXPR_TRAITS<Matrix<T, row, col>>
    {
        using ValueType = T;
        static constexpr ExprFormat Format = ExprFormat::Matrix; 
        static constexpr unsigned int rows = row;
        static constexpr unsigned int cols = col;
    };
 
    template <typename Tl, typename Tr, typename T, unsigned int lhsR, unsigned int rhsC, unsigned int C_s>
    struct EXPR_TRAITS<MatProduct<Tl,Tr,T,lhsR,rhsC,C_s>>
    {
        using ValueType = T;
        static constexpr ExprFormat Format = ExprFormat::Matrix; 
        static constexpr unsigned int rows = lhsR;
        static constexpr unsigned int cols = rhsC;
    };
        
}
