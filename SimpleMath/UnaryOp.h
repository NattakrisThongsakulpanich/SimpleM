#pragma once 

#include "./Expression.h"
#include "./Value.h"

namespace SimpleM
{

    template <typename T>
    struct UnaryOpStoreType
    {
         using type = const T&;
    };

    template <typename T>
    struct UnaryOpStoreType< Value<T> >
    {
        using type = Value<T>;
    };

    template <typename T, typename op>
    struct UnaryOp : public EXPR<
        UnaryOp<
            T,
            op
        >
    >
    {

        typename UnaryOpStoreType<T>::type value;
        UnaryOp(const T &VALUE) : value(VALUE) {};

        inline auto operator[](const unsigned int index) const 
        {
            return op::eval(value, index);
        }
        inline auto operator()(const unsigned int row, const unsigned int col) const 
        {
            return op::eval(value, row, col);
        }

    };
}
