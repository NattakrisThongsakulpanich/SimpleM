#pragma once 



namespace Symbolic
{
    //Standard Placeholder Symbolic 
    struct ADD {};
    struct SUB {};
    struct MUL {};
    struct DIV {};
    struct TRANSPOSE {};
}

namespace Evaluator  
{
    //Evolved Symbolic
    // * Contains real evaluator.
    // * ELM stand for Element Wise ...
    struct ELM_ADD 
    {
        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS, unsigned int index) 
        {
            return LHS[index] + RHS[index]; 
        }
    };

    struct ELM_SUB
    {
        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS, unsigned int index) 
        {
            return LHS[index] - RHS[index]; 
        }
    };

    struct ELM_MUL 
    {
        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS, unsigned int index) 
        {
            return LHS[index] * RHS[index]; 
        }
    };

    struct ELM_DIV 
    {
        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS, unsigned int index) 
        {
            return LHS[index] / RHS[index]; 
        }
    };

}
