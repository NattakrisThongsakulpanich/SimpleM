#include "../SimpleMath/SimpleM.h"
#include "../Benchmark/Benchmark.h"
#include <iostream>

void printSection(const char* name)
{
    std::cout << "--------------------------------------------------------------" << std::endl;
    std::cout << name << std::endl;
}

template <typename T, unsigned int rows, unsigned int cols>
void printMAT(const SimpleM::Matrix<T, rows, cols> &Mat, const char* name)
{
    printSection(name);
    unsigned int index = 0;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            std::cout << Mat.matStack[ index ] << ", ";
            index++;
        }
        std::cout << std::endl;
    }
}

// Global persistent instances to ensure work isn't fully optimized out
static SimpleM::Matrix<float, 4, 4> g_MatA;
static SimpleM::Matrix<float, 4, 4> g_MatB;
static SimpleM::Matrix<float, 4, 4> g_MatResult;

// --- Heavy Performance Test Workers ---

// Test 1: Baseline Math (Factorial)
static double FactorialBenchmark(unsigned int t) { return SimpleM::fac(5); }

// Test 2: Double Precision Transcendental Math
static double DpowBenchmark(unsigned int t) { return SimpleM::dpow(2.5, 3.5); }

// Test 3: Matrix Deep Expression Chains (Addition and Double Scalar Scaling)
static double MatrixExpressionChainBenchmark(unsigned int t)
{
    // Break the compound tree into separate steps that your operators support
    // (Matching the exact syntax that worked in your main function)

    g_MatResult = (g_MatA * 2) + (4 * g_MatB);    
    return g_MatResult.matStack[0]; 
}

// Test 4: Matrix Transposition Performance
static double MatrixTransposeBenchmark(unsigned int t)
{
    g_MatResult = Transpose(g_MatA);
    return g_MatResult.matStack[0];
}

// Test 5: Standard Matrix Multiplication (Dot Products)
static double MatrixMultiplicationBenchmark(unsigned int t)
{
    g_MatResult = g_MatA * g_MatB;
    return g_MatResult.matStack[0];
}

int main()
{   
    using namespace SimpleM;

    // --- Part 1: Correctness Verification (Kept intact) ---
    Matrix<float, 2, 4> mat;
    mat << 1,2,4,8,
           16, 32, 64, 128;
    printMAT(mat, "Matrix row by column comma-chain insertion"); 

    Matrix<float, 2, 4> mat2;
    mat2 << 2,2,2,2,
           2, 2, 2, 2;

    Matrix<float,4,2> matT;
    matT = Transpose(mat);
    printMAT(matT, "Matrix Transposition test");

    Matrix<float, 2, 4> intermediate;
    intermediate = mat+mat2;
    printMAT(intermediate, "Matrix-Matrix addition");

    intermediate = mat * 2 ;
    printMAT(intermediate, "Matrix-scalar multiplication (mat * n)");

    intermediate = 4 * mat;
    printMAT(intermediate, "Matrix-scalar multiplication (n * mat)");

    Matrix<float, 2, 2> rotationMat;
    rotationMat << 0, -1,
                   1, 0;
    Matrix<float, 2, 1> vertex = Matrix<float, 2, 1>();
    vertex << 2,
              3;

    Matrix<float, 2, 1> new_vertex = Matrix<float, 2, 1>();
    new_vertex = rotationMat * vertex;

    printMAT(vertex, "Matrix-Matrix multiplication (vertex BEFORE rotation)");
    printMAT(rotationMat, "Rotation Matrix");
    printMAT(new_vertex, "Matrix-Matrix multiplication (vertex AFTER rotation)"); 

    Matrix<float, 2,1> MatExpr_Test;
    MatExpr_Test = (rotationMat * vertex) + (2 * vertex); 

    printMAT(MatExpr_Test, "WHAT??");
    
    MatExpr_Test = (rotationMat * (rotationMat * vertex) );

    printMAT(MatExpr_Test, "HOW TF?");

    // --- Part 2: High-Load Performance & Statistics Comparison ---
    
    // Initialize global test data
    g_MatA << 1, 2, 3, 4,  5, 6, 7, 8,  9, 10, 11, 12,  13, 14, 15, 16;
    g_MatB << 16, 15, 14, 13,  12, 11, 10, 9,  8, 7, 6, 5,  4, 3, 2, 1;

    constexpr unsigned int ITERATIONS = 1000000; // 10^6 iterations

    printSection("[PERFORMANCE] Pure Math: Factorial(5)");
    Benchmark::sum(ITERATIONS, FactorialBenchmark);

    printSection("[PERFORMANCE] Pure Math: 2.5^3.5 (dpow)");
    Benchmark::sum(ITERATIONS, DpowBenchmark); 

    printSection("[PERFORMANCE] Linear Algebra: Matrix 4x4 Expression Chain ((A*2)+(3*B))");
    Benchmark::sum(ITERATIONS, MatrixExpressionChainBenchmark);

    printSection("[PERFORMANCE] Linear Algebra: Matrix 4x4 Transposition");
    Benchmark::sum(ITERATIONS, MatrixTransposeBenchmark);

    printSection("[PERFORMANCE] Linear Algebra: Matrix 4x4 Row-by-Column Multiplication");
    Benchmark::sum(ITERATIONS, MatrixMultiplicationBenchmark);

    return 0;
}

