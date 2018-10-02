////
//// Created by hagitba on 1/23/18.
////

#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <chrono>
#include "Complex.h"
#include "Matrix.hpp"
#include <eigen3/Eigen/Dense>


//std::stack<clock_t> tictoc_stack;
std::stack<std::chrono::time_point<std::chrono::system_clock >> tictoc_stack;

/**
 * start checking time
 */
void tic()
{
    tictoc_stack.push(std::chrono::system_clock::now());
}

/**
 * finish checking
 * @param msg to print
 */
void toc(const std::string& msg)
{
    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
    std::cout << msg << elapsed_seconds.count() << "sec\n";
    tictoc_stack.pop();
}

/**
 * add 2 matrix
 * @param A first matrix
 * @param B second matrix
 * @return the result
 */
Eigen::MatrixXd doPlus(const Eigen::MatrixXd& A, const Eigen::MatrixXd& B)
{
    return (A + B);
}

/**
 * multiply 2 matrix
 * @param A first matrix
 * @param B second matrix
 * @return the result
 */
Eigen::MatrixXd doMult(const Eigen::MatrixXd& A, const Eigen::MatrixXd& B)
{
    return (A * B);
}

/**
 * main function calculte ant print the time that it's took to multiply and to adding 2 matrices by eigen library and
 * our implamentation
 * @param argc number of argument
 * @param argv size of the matrix
 * @return 0 if success
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "You need to enter two arguments" << std::endl;
        return -1;
    }

    Eigen::MatrixXd Matrix1, Matrix2;
    Matrix<int> Ra, Rm;

    std::size_t n = (size_t)std::stoi(argv[1]);
    unsigned int n0 = (unsigned int) n;
    std::cout << "size " << n << std::endl;

    Eigen::MatrixXd A = Eigen::MatrixXd::Random(n, n);
    Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);

    tic();
    Matrix1 = doPlus(A, A);
    toc("eigen add ");
    tic();
    Matrix2 = doMult(B, A);
    toc("eigen mult ");

    std::vector<int> matrix(n * n, 1);
    Matrix<int> m1(n0, n0, matrix);
    Matrix<int> m2(n0, n0, matrix);

    tic();
    Rm = m1 + m2;
    toc("matlib add ");
    tic();
    Ra = m1 * m2;
    toc("matlib mult ");

    return 0;
}