#pragma once

#include <type_traits>

#include "./Evaluator.h"
#include "./ExpressionTraits.h"
#include "./BinaryOp.h"
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
        using Expression = BinaryOp<Tl, Tr, Symbolic::ADD>;
        using Evaluator = Symbolic::ADD;
        static constexpr ExprFormat Format = ExprFormat::Scalar;
        static constexpr unsigned int rows = 0;
        static constexpr unsigned int cols = 0;
    };

    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::SUB, ExprFormat::Scalar, ExprFormat::Scalar>
    {
        using ValueType = typename EXPR_TRAITS<Tl>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Symbolic::SUB>;
        using Evaluator = Symbolic::ADD;
        static constexpr ExprFormat Format = ExprFormat::Scalar;
        static constexpr unsigned int rows = 0;
        static constexpr unsigned int cols = 0;
    };

    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::MUL, ExprFormat::Scalar, ExprFormat::Scalar>
    {
        using ValueType = typename EXPR_TRAITS<Tl>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Symbolic::MUL>;
        using Evaluator = Symbolic::MUL;
        static constexpr ExprFormat Format = ExprFormat::Scalar;
        static constexpr unsigned int rows = 0;
        static constexpr unsigned int cols = 0;
    };

    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::DIV, ExprFormat::Scalar, ExprFormat::Scalar>
    {
        using ValueType = typename EXPR_TRAITS<Tl>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Symbolic::DIV>;
        using Evaluator = Symbolic::DIV;
        static constexpr ExprFormat Format = ExprFormat::Scalar;
        static constexpr unsigned int rows = 0;
        static constexpr unsigned int cols = 0;
    };


    //comb: matrix +- matrix
    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::ADD, ExprFormat::Matrix, ExprFormat::Matrix>
    {
        using ValueType = typename EXPR_TRAITS<Tl>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Symbolic::ADD>;
        using Evaluator = Symbolic::ADD;
        static constexpr ExprFormat Format = ExprFormat::Matrix;
        static constexpr unsigned int rows = EXPR_TRAITS<Tl>::rows;
        static constexpr unsigned int cols = EXPR_TRAITS<Tr>::cols;
    };

    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::SUB, ExprFormat::Matrix, ExprFormat::Matrix>
    {
        using ValueType = typename EXPR_TRAITS<Tl>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Symbolic::SUB>;
        using Evaluator = Symbolic::SUB;
        static constexpr ExprFormat Format = ExprFormat::Matrix;
        static constexpr unsigned int rows = EXPR_TRAITS<Tl>::rows;
        static constexpr unsigned int cols = EXPR_TRAITS<Tl>::cols;
    };

    //comb: matrix * scalar (invert included)
    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::MUL, ExprFormat::Matrix, ExprFormat::Scalar>
    {
        using ValueType = typename EXPR_TRAITS<Tl>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Symbolic::MUL>;
        using Evaluator = Symbolic::MUL;
        static constexpr ExprFormat Format = ExprFormat::Matrix;
        static constexpr unsigned int rows = EXPR_TRAITS<Tl>::rows;
        static constexpr unsigned int cols = EXPR_TRAITS<Tl>::cols;
    };

    template <typename Tl, typename Tr>
    struct BinaryOpDispatcher<Tl,Tr, Symbolic::MUL, ExprFormat::Scalar, ExprFormat::Matrix>
    {
        using ValueType = typename EXPR_TRAITS<Tr>::ValueType;
        using Expression = BinaryOp<Tl, Tr, Symbolic::MUL>;
        using Evaluator = Symbolic::MUL;
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
        using Evaluator = void;
        static constexpr ExprFormat Format = ExprFormat::Matrix;
        static constexpr unsigned int rows = traitLeft::rows;
        static constexpr unsigned int cols = traitRight::cols;

    };


    //Currently use a hard code way to fix a BinOP +-*/ BinOp case
    // * need a change soon
    /*
    template <typename Tl, typename Tr, typename Op>
    struct EXPR_TRAITS<BinaryOp<Tl, Tr, Op>>
    {
        private:
        using LT = EXPR_TRAITS<Tl>;
        using RT = EXPR_TRAITS<Tr>;

        static constexpr bool leftIsMatrix  = (LT::Format == ExprFormat::Matrix);
        static constexpr bool rightIsMatrix = (RT::Format == ExprFormat::Matrix);

        public:
        using ValueType = std::conditional_t<
            leftIsMatrix,
            typename LT::ValueType,
            typename RT::ValueType
        >;

        static constexpr ExprFormat Format = (leftIsMatrix || rightIsMatrix) ? ExprFormat::Matrix : ExprFormat::Scalar;

        static constexpr unsigned int rows = leftIsMatrix ? LT::rows : RT::rows;
        static constexpr unsigned int cols = leftIsMatrix ? LT::cols : RT::cols;
    };
    */
    

    template <typename Tl, typename Tr, typename Sym>
    struct EXPR_TRAITS<BinaryOp<Tl, Tr, Sym>>
    {
        using ValueType = typename BinaryOpDispatcher<Tl, Tr, Sym>::ValueType ;
        static constexpr ExprFormat Format = BinaryOpDispatcher<Tl, Tr, Sym>::Format; 
        static constexpr unsigned int rows = BinaryOpDispatcher<Tl, Tr, Sym>::rows;
        static constexpr unsigned int cols = BinaryOpDispatcher<Tl, Tr, Sym>::cols;

    };
}
