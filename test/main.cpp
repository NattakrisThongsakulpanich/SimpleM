#include "../SimpleMath/LinearAlgebra.h"
#include "../SimpleMath/Operator.h"
#include "../SimpleMath/Combinatorics.h"
#include "../SimpleMath/Exponents.h"
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

static double FactorialBenchmark(unsigned int t)
{
    return SimpleM::fac(5);
}

static double PowIntBenchmark(unsigned int)
{
    return SimpleM::pow(2.5, 16);
}

static double lnBenchmark(unsigned int)
{
    return SimpleM::ln(2.0);
}
static double dpowBenchmark(unsigned int)
{
    return SimpleM::dpow(2.5, 3.5);
}

int main()
{   

    //comma chain insertion test
    SimpleM::Matrix<float, 2, 4> mat = SimpleM::Matrix<float, 2, 4>();
    mat << 1,2,4,8,
           16, 32, 64, 128;
        
    printMAT(mat, "Matrix row by column comma-chain insertion"); 

    SimpleM::Matrix<float, 2, 4> mat2 = SimpleM::Matrix<float, 2, 4>();
    mat2 << 2,2,2,2,
           2, 2, 2, 2;

    SimpleM::Matrix<float, 2, 4> intermediate = SimpleM::Matrix<float, 2, 4>();

    intermediate = mat+mat2;

    printMAT(intermediate, "Matrix-Matrix addition");

    intermediate = mat * 2 ;

    printMAT(intermediate, "Matrix-scalar multiplication (mat * n)");

    intermediate = 4 * mat;

    printMAT(intermediate, "Matrix-scalar multiplication (n * mat)");

    SimpleM::Matrix<float, 2, 2> rotationMat = SimpleM::Matrix<float, 2, 2>();
    rotationMat << 0, -1,
                   1, 0;
    SimpleM::Matrix<float, 2, 1> vertex = SimpleM::Matrix<float, 2, 1>();
    vertex << 2,
              3;

    SimpleM::Matrix<float, 2, 1> new_vertex = SimpleM::Matrix<float, 2, 1>();

    new_vertex = rotationMat * vertex;

    printMAT(vertex, "Matrix-Matrix multiplication (vertex BEFORE rotation)");
    printMAT(rotationMat, "Rotation Matrix");
    printMAT(new_vertex, "Matrix-Matrix multiplication (vertex AFTER rotation)");

    printSection("sum of Factorial(5), iteration: 10^6");
    Benchmark::sum(1000000,FactorialBenchmark);

    printSection("sum of 2.5^16, iteration: 10^6");
    Benchmark::sum(1000000,PowIntBenchmark);

    printSection("sum of ln(2.0f), iteration: 10^6");
    Benchmark::sum(1000000,lnBenchmark); 

    printSection("sum of 2.5^3.5 (dpow) , iteration: 10^6");
    Benchmark::sum(1000000,dpowBenchmark); 

    return 0;
}
