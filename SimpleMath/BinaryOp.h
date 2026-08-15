#pragma once

#include "./Expression.h"
#include "./Value.h"

namespace SimpleM
{

    template <typename T>
    struct BinaryOpStoreType
    {
         using type = const T&;
    };

    template <typename T>
    struct BinaryOpStoreType< Value<T> >
    {
        using type = Value<T>;
    };

    template <typename Tl, typename Tr, typename op>
    struct BinaryOp : public EXPR<
        BinaryOp<
            Tl,
            Tr,
            op
        >
    >
    {
        typename BinaryOpStoreType<Tl>::type lhs;
        typename BinaryOpStoreType<Tr>::type rhs;
        BinaryOp(const Tl& LHS, const Tr& RHS) : lhs(LHS), rhs(RHS) {};
        inline auto operator[](const unsigned int index) const 
        {
            return op::eval(lhs, rhs, index);
        }
        inline auto operator()(const unsigned int row, const unsigned int col) const 
        {
            return op::eval(lhs, rhs, row, col);
        }
    };
}
