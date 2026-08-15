#pragma once

#include "./Expression.h"

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

}
