# SimpleM

A lightweight, header-only, expression-template matrix library written in modern C++20.

## Design goals

- Zero-overhead expression templates (Eigen-style)
- Fixed-size stack-allocated matrices (great for small / medium sizes)
- Clean, readable operator syntax
- Foundation for a future LAPACK-like set of dense linear-algebra routines

## Current status

### Working
- Fixed-size `Matrix<T, Rows, Cols>`
- Comma initializer
- Element-wise `+` `-` `*` `/`
- Scalar ↔ Matrix multiplication
- Matrix-matrix multiplication
- Transpose
- Nested expressions

### Planned
- LU / Cholesky / QR factorizations
- Linear solvers
- Eigenvalue & SVD routines
- Dynamic-size matrices
- More comprehensive test suite

## Quick example

```cpp
#include "SimpleMath/SimpleM.hpp"
using namespace SimpleM;

int main() {
    Matrix<float, 2, 2> A;
    A << 1, 2,
         3, 4;

    Matrix<float, 2, 1> b;
    b << 5,
         6;

    auto result = (A * b) + (2.0f * b);   // expression template, no temporary matrices
    // ...
}