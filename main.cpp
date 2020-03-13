#include <iostream>
#include "armadillo"
#include "LinearOptimizationProblem.hpp"

using namespace arma;

void default_main() {
    mat A = mat(3, 2);
    A.at(0, 0) = -3;
    A.at(0, 1) = 1;

    A.at(1, 0) = 1;
    A.at(1, 1) = 2;

    A.at(2, 0) = 0;
    A.at(2, 1) = -1;

    vec b = vec(3);
    b.at(0) = 6;
    b.at(1) = 4;
    b.at(2) = 3;

    vec c = vec(2);
    c.at(0) = 1;
    c.at(1) = -4;

    vec x_0 = vec(2);
    x_0.at(0) = 0.1;
    x_0.at(1) = 0.1;
    double_t gamma = 0.5;

    LinearOptimizationProblem linearOptimizationProblem = LinearOptimizationProblem(A, b, c);
    LinearOptimizationResult result = linearOptimizationProblem.maximize(x_0, gamma, 0.0001, "affine-scaling");
    result.result.print();
}

int main() {
    default_main();
    return 0;
}
