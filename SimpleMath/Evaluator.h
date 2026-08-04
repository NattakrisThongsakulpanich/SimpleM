#pragma once
#include "Combinatorics.h"
#include "LinearAlgebra.h"

namespace SimpleM
{

    struct AddOp
    {
        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS)
        {
            return LHS + RHS;
        };
    };

    struct SubOp
    {
        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS)
        {
            return LHS - RHS;
        };
    };

    struct MulOp
    {
        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS)
        {
            return LHS * RHS;
        };
    };

}
