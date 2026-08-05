#pragma once
#include "./Expression.h"
#include "./Operator.h"
#include "./Evaluator.h"
#include "LinearAlgebra.h"

namespace SimpleM
{

    template <typename T>
    struct Value : public EXPR<Value<T>>
    {
        Value(const T value) : data(value) {};
        const T data;
        inline auto operator [] (const unsigned int _) const
        {
            return data;
        }

        inline auto operator()(const unsigned int _0, const unsigned int _1) const 
        {
            return data;
        }

    }; 

    template <typename T>
    struct StoreType
    {
         using type = const T&;
    };

    template <typename T>
    struct StoreType< Value<T> >
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
        typename StoreType<Tl>::type lhs;
        typename StoreType<Tr>::type rhs;

        BinaryOp(const Tl& LHS, const Tr& RHS) : lhs(LHS), rhs(RHS) {};

        inline auto operator[](const unsigned int i) const 
        {
            return op::eval(lhs[i], rhs[i]);
        }

        inline auto operator()(const unsigned int r, const unsigned int c) const 
        {
            return op::eval(lhs(r,c), rhs(r,c));
        }

    };

    template <typename T, typename op>
    struct UnaryOp : public EXPR<
        UnaryOp<
            T,
            op
        >
    >
    {
        typename StoreType<T>::type value;

        UnaryOp(const T &VALUE) : value(VALUE) {};

        inline auto operator[](const unsigned int i) const 
        {
            return op::eval(value[i]);
        }

        inline auto operator()(const unsigned int r, const unsigned int c) const 
        {
            return op::eval(value(r,c));
        }

    };  

    template<typename L, typename R>
    auto operator+(
        const EXPR<L>& lhs, 
        const EXPR<R>& rhs
    )
    {
        return BinaryOp<
            L,
            R,
            AddOp
        >(lhs.self(), rhs.self());
    }

    template<typename L, typename R>
    auto operator-(
        const EXPR<L>& lhs,
        const EXPR<R>& rhs
    )
    {
        return BinaryOp<
            L,
            R,
            SubOp
        >(lhs.self(), rhs.self());
    }

    template<typename L, typename T>
    auto operator*(
        const EXPR<L>& lhs,
        const T& rhs
    )
    {
        return BinaryOp<
            L,
            Value<T>,
            MulOp
        >(lhs.self(), Value<T>(rhs));
    }

    template<typename T, unsigned int lhsR, unsigned int rhsC, unsigned int C_s>
    auto operator*(
        Matrix<T,lhsR,C_s> &lhs,
        Matrix<T,C_s,rhsC> &rhs
    )
    {
        return MatProduct<T, lhsR, rhsC, C_s>(lhs, rhs);    
    }

    template<typename L, typename T>
    auto operator*(
        const T &lhs,
        const EXPR<L> &rhs
    )
    {
        return BinaryOp<
            Value<T>,
            L,
            MulOp
        >(Value<T>(lhs), rhs.self());
    }

}
