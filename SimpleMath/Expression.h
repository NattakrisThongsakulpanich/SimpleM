#pragma once

namespace SimpleM
{
    
    enum class ExprFormat
    {
        UNDEFINED = 0,
        Matrix = 1,
        Scalar = 2
    };
    

    template <typename T>
    struct EXPR 
    {
        const T& self() const
        {
            return static_cast<const T&>(*this);
        }
    };

}
