//
// Created by а on 13.03.2020.
//

#ifndef LIPA_LINEAROPTIMIZATIONPROBLEM_HPP
#define LIPA_LINEAROPTIMIZATIONPROBLEM_HPP

#include <iostream>
#include <vector>
#include "armadillo"
#include "LinearOptimizationResult.hpp"

using namespace arma;

class LinearOptimizationProblem {
public:
    LinearOptimizationProblem(const mat &A, const vec &b, const vec &c);
    LinearOptimizationResult maximize(const vec &x_0, const double_t gamma, double_t min_error, const std::string &method);


private:
    const mat &A;
    const vec &b;
    const vec &c;

    vec maximize_iter(const vec &x, double_t gamma, std::string method);
    vec affine_scaling(const vec &x, double_t gamma);

    static double_t affine_compute_alpha(const double_t gamma, const vec &v_k, const vec &h_v);
    static double_t mean_absolute_error(const vec &v1, const vec &v2);
};





#endif //LIPA_LINEAROPTIMIZATIONPROBLEM_HPP
