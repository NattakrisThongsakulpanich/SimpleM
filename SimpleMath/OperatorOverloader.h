#pragma once

#include <type_traits>

#include "./Expression.h"
#include "./BinaryOp.h"
#include "./ExpressionTraits.h"
#include "./BinaryOpDispatcher.h"
#include "Evaluator.h"

namespace SimpleM
{

    template<typename L, typename R>
    inline auto operator+(
        const EXPR<L>& lhs,
        const EXPR<R>& rhs
    )
    {
        using Recipe = BinaryOpDispatcher<L, R, Symbolic::ADD>;

        return typename Recipe::Expression(
            lhs.self(),
            rhs.self()
        );
    }

    template<typename L, typename R>
    inline auto operator-(
        const EXPR<L>& lhs,
        const EXPR<R>& rhs
    )
    {
        using Recipe = BinaryOpDispatcher<L, R, Symbolic::SUB>;

        return typename Recipe::Expression(
            lhs.self(),
            rhs.self()
        );
    }

    template<typename L, typename R>
    inline auto operator*(
        const EXPR<L>& lhs,
        const EXPR<R>& rhs
    )
    {
        using Recipe = BinaryOpDispatcher<L, R, Symbolic::MUL>;

        return typename Recipe::Expression(
            lhs.self(),
            rhs.self()
        );
    }

    template<typename L, typename R>
    inline auto operator/(
        const EXPR<L>& lhs,
        const EXPR<R>& rhs
    )
    {
        using Recipe = BinaryOpDispatcher<L, R, Symbolic::DIV>;

        return typename Recipe::Expression(
            lhs.self(),
            rhs.self()
        );
    }

    template<typename L, typename T, typename std::enable_if_t<!std::is_class_v<T>, int> = 0>
    inline auto operator*(
        const EXPR<L>& lhs,
        const T& rhs
    )
    {
        using Recipe = BinaryOpDispatcher<L, Value<T>, Symbolic::MUL>; 

        return typename Recipe::Expression(lhs.self(), Value<T>(rhs));
    }
    
    template<typename R, typename T, typename std::enable_if_t<!std::is_class_v<T>, int> = 0> 
    inline auto operator*(
        const T& lhs,
        const EXPR<R>& rhs
    )
    {
        using Recipe = BinaryOpDispatcher<Value<T>, R, Symbolic::MUL>;

        return typename Recipe::Expression(Value<T>(lhs), rhs.self());
    } 

}
