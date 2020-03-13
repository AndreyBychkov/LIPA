//
// Created by а on 13.03.2020.
//

#ifndef LIPA_OPTIMIZATION_HPP
#define LIPA_OPTIMIZATION_HPP

#include <iostream>
#include "armadillo"

using namespace arma;

vec affine_scaling_lp(const mat &A, const vec &b, const vec &c, const vec &x_0, const double_t gamma);


double_t compute_alpha(const double_t gamma, const vec &v_k, const vec &h_v);
double_t mean_absolute_error(const vec &v1, const vec &v2);


#endif //LIPA_OPTIMIZATION_HPP
