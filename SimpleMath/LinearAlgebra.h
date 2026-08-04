#pragma once
#include "./Expression.h"

namespace SimpleM
{
    template <typename T, unsigned int t_len, unsigned int t_stride>
    struct FlatView
    {
        const T* data;
        constexpr static unsigned int length = t_len;
        constexpr static unsigned int stride = t_stride; 
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
            return matStack[ (row - 1) * tCols + (col - 1) ]; 
        }

        inline const T& operator [] (const unsigned int index) const
        {
            return matStack[index];
        }

        inline const T& operator () (const unsigned int row, const unsigned int col) const
        {
            return matStack[ (row - 1) * tCols + (col - 1) ];
        } 

        FlatView<T, tCols, 0> getRowView(unsigned int row)
        {
            return FlatView<T, tCols, 0>{ &matStack[ (row-1) * tCols ] };
        }

        FlatView<T, tRows, tCols> getColView(unsigned int col)
        {
            return FlatView<T, tRows, tCols>{ &matStack[ col - 1 ] };
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

    //SimpleM will be using a Eager Evaluation for a Matrix * Matrix for a while
    // -> a Matrix * Matrix multiplication plan to be implement after trigs func finished 
    using namespace SimpleM;
    template <typename T, unsigned int C_s, unsigned int lhsR, unsigned int rhsC>
    inline auto operator * (
        const Matrix < T,lhsR,C_s > &lhs,
        const Matrix < T,C_s,rhsC > &rhs
    )
    { 

        Matrix<T, lhsR, rhsC> newMat = Matrix<T, lhsR, rhsC>();

        for(int r = 1; r <= lhsR; r++)
        {
            for(int c = 1; c <= rhsC; c++ )
            {

                T sum = 0;

                for(int lc = 1; lc <= C_s; lc++)
                {
                    sum += lhs(r, lc) * rhs(lc, c);
                }

                newMat(r, c) = sum;
            }
        }
            
        return newMat;
    };

}
