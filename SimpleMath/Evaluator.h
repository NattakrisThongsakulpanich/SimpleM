#pragma once 



namespace Symbolic
{
    //Standard Placeholder Symbolic 
    struct ADD 
    {
        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS, unsigned int index) 
        {
            return LHS[index] + RHS[index]; 
        }

        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS, unsigned int row, unsigned int col) 
        {
            return LHS(row, col) + RHS(row, col); 
        }


    };

    struct SUB 
    {
        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS, unsigned int index) 
        {
            return LHS[index] - RHS[index]; 
        }

        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS, unsigned int row, unsigned int col) 
        {
            return LHS(row, col) - RHS(row, col); 
        }


    };
    struct MUL 
    {
        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS, unsigned int index) 
        {
            return LHS[index] * RHS[index]; 
        }
        
        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS, unsigned int row, unsigned int col) 
        {
            return LHS(row, col) * RHS(row, col); 
        }

    };
    struct DIV 
    {
        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS, unsigned int index) 
        {
            return LHS[index] / RHS[index]; 
        }

        template <typename Tl, typename Tr>
        static inline auto eval(const Tl &LHS, const Tr &RHS, unsigned int row, unsigned int col) 
        {
            return LHS(row, col) / RHS(row, col); 
        }


    };
 
}


