#pragma once

namespace SimpleM
{

    template <typename T>
    struct EXPR 
    {
        const T& self() const
        {
            return static_cast<const T&>(*this);
        }
    };

}
