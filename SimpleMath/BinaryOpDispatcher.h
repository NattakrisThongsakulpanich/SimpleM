#pragma once

#include "./Value.h"
#include "./Evaluator.h"
#include "./ExpressionTraits.h"
#include "./BinaryOp.h"
#include "./LinearAlgebra/Matrix.h"
#include "Expression.h"
#include "LinearAlgebra/MatrixProduct.h"

namespace SimpleM
{
    
    template <typename Tl, typename Tr, typename sym, ExprFormat Fl = EXPR_TRAITS<Tl>::Format, ExprFormat Fr = EXPR_TRAITS<Tr>::Format >
    struct BinaryOpDispatcher
    {
        using ValueType = void;
        using Expression = void;
        using Evaluator = void;
        static constexpr ExprFormat Format = ExprFormat::UNDEFINED;
        static constexpr unsigned int rows = 0;
        static constexpr unsigned int cols = 0;

    };

    //comb: Scalar +-*/scalar
    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::ADD, ExprFormat::Scalar, ExprFormat::Scalar>
    {
        using ValueType = typename EXPR_TRAITS<Tl>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Evaluator::ELM_ADD>;
        using Evaluator = Evaluator::ELM_ADD;
        static constexpr ExprFormat Format = ExprFormat::Scalar;
        static constexpr unsigned int rows = 0;
        static constexpr unsigned int cols = 0;
    };

    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::SUB, ExprFormat::Scalar, ExprFormat::Scalar>
    {
        using ValueType = typename EXPR_TRAITS<Tl>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Evaluator::ELM_SUB>;
        using Evaluator = Evaluator::ELM_SUB;
        static constexpr ExprFormat Format = ExprFormat::Scalar;
        static constexpr unsigned int rows = 0;
        static constexpr unsigned int cols = 0;
    };

    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::MUL, ExprFormat::Scalar, ExprFormat::Scalar>
    {
        using ValueType = typename EXPR_TRAITS<Tl>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Evaluator::ELM_MUL>;
        using Evaluator = Evaluator::ELM_MUL;
        static constexpr ExprFormat Format = ExprFormat::Scalar;
        static constexpr unsigned int rows = 0;
        static constexpr unsigned int cols = 0;
    };

    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::DIV, ExprFormat::Scalar, ExprFormat::Scalar>
    {
        using ValueType = typename EXPR_TRAITS<Tl>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Evaluator::ELM_DIV>;
        using Evaluator = Evaluator::ELM_DIV;
        static constexpr ExprFormat Format = ExprFormat::Scalar;
        static constexpr unsigned int rows = 0;
        static constexpr unsigned int cols = 0;
    };


    //comb: matrix +- matrix
    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::ADD, ExprFormat::Matrix, ExprFormat::Matrix>
    {
        using ValueType = typename EXPR_TRAITS<Tl>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Evaluator::ELM_ADD>;
        using Evaluator = Evaluator::ELM_ADD;
        static constexpr ExprFormat Format = ExprFormat::Matrix;
        static constexpr unsigned int rows = EXPR_TRAITS<Tl>::rows;
        static constexpr unsigned int cols = EXPR_TRAITS<Tr>::cols;
    };

    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::SUB, ExprFormat::Matrix, ExprFormat::Matrix>
    {
        using ValueType = typename EXPR_TRAITS<Tl>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Evaluator::ELM_SUB>;
        using Evaluator = Evaluator::ELM_SUB;
        static constexpr ExprFormat Format = ExprFormat::Matrix;
        static constexpr unsigned int rows = EXPR_TRAITS<Tl>::rows;
        static constexpr unsigned int cols = EXPR_TRAITS<Tl>::cols;
    };

    //comb: matrix * scalar (invert included)
    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::MUL, ExprFormat::Matrix, ExprFormat::Scalar>
    {
        using ValueType = typename EXPR_TRAITS<Tl>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Evaluator::ELM_MUL>;
        using Evaluator = Evaluator::ELM_MUL;
        static constexpr ExprFormat Format = ExprFormat::Matrix;
        static constexpr unsigned int rows = EXPR_TRAITS<Tl>::rows;
        static constexpr unsigned int cols = EXPR_TRAITS<Tl>::cols;
    };

    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::MUL, ExprFormat::Scalar, ExprFormat::Matrix>
    {
        using ValueType = typename EXPR_TRAITS<Tr>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Evaluator::ELM_MUL>;
        using Evaluator = Evaluator::ELM_MUL;
        static constexpr ExprFormat Format = ExprFormat::Matrix;
        static constexpr unsigned int rows = EXPR_TRAITS<Tr>::rows;
        static constexpr unsigned int cols = EXPR_TRAITS<Tr>::cols;
    };

    //comb matrix * matrix give a expression of MatProduct 
    // * Act as a virtual BinaryOp
    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::MUL, ExprFormat::Matrix, ExprFormat::Matrix>
    {
        protected:
            using traitLeft = EXPR_TRAITS<Tl>;
            using traitRight = EXPR_TRAITS<Tr>;

        public:
        using ValueType = typename EXPR_TRAITS<Tl>::ValueType;
        using Expression = MatProduct<Tl,Tr, ValueType, traitLeft::rows, traitRight::cols, traitRight::rows>;
        static constexpr ExprFormat Format = ExprFormat::Matrix;
        static constexpr unsigned int rows = traitLeft::rows;
        static constexpr unsigned int cols = traitRight::cols;

    };

    template <typename Tl, typename Tr, typename Sym>
    struct EXPR_TRAITS<BinaryOp<Tl, Tr, Sym>>
    {
        using ValueType = typename BinaryOpDispatcher<Tl, Tr, Sym>::ValueType ;
        static constexpr ExprFormat Format = BinaryOpDispatcher<Tl, Tr, Sym>::Format; 
        static constexpr unsigned int rows = BinaryOpDispatcher<Tl, Tr, Sym>::rows;
        static constexpr unsigned int cols = BinaryOpDispatcher<Tl, Tr, Sym>::cols;

    };

    

}
