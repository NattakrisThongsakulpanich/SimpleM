#pragma once

#include "../Expression.h"

namespace SimpleM
{

    template <typename T, unsigned int t_len, unsigned int t_stride>
    struct FlatView
    {
        const T* data;
        constexpr static unsigned int length = t_len;
        constexpr static unsigned int stride = t_stride;

        inline auto operator[](const unsigned int i)
        {
            return *(data + (i * t_stride));
        }
    };


    template <typename T, unsigned int tRows, unsigned int tCols>
    struct Matrix : public EXPR<Matrix<T,tRows,tCols>>  
    {
 
        T matStack[tRows * tCols] = {0};

        inline T& operator [] (const unsigned int index)
        {
            return matStack[index];
        }

        inline T& operator () (const unsigned int row, const unsigned int col)
        {
            return matStack[ row * tCols + col ]; 
        }

        inline const T& operator [] (const unsigned int index) const
        {
            return matStack[index];
        }

        inline const T& operator () (const unsigned int row, const unsigned int col) const
        {
            return matStack[ row * tCols + col ];
        } 

        FlatView<T, tCols, 1> getRowView(unsigned int row)
        {
            return FlatView<T, tCols, 1>{ &matStack[ row * tCols ] };
        }

        FlatView<T, tRows, tCols> getColView(unsigned int col)
        {
            return FlatView<T, tRows, tCols>{ &matStack[ col ] };
        }

        struct comma_chain
        {

            Matrix<T,tRows,tCols> &mat;
            unsigned int index;

            comma_chain operator , ( T val )
            {
                mat.matStack[index] = val;
                return comma_chain{ mat, index + 1 };
            }

        };

        comma_chain operator << ( T val )
        {
            matStack[0] = val;
            return comma_chain{ *this, 1 };
        }

        template <typename derived>
        void operator = (const EXPR<derived> &expr)
        {
            const derived &underlying = expr.self();
            for(unsigned int i =0;i < tRows * tCols; i++)
            {
                matStack[i] = underlying[i];
            }
        }

    };

}
