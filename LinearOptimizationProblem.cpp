#include "LinearOptimizationProblem.hpp"

/// Definition of Linear Omtimization Problem
///
/// @param A - condition matrix from Ax < b
/// @param b - condition vector from Ax < b
/// @param c - coefficients in target function c^T x
LinearOptimizationProblem::LinearOptimizationProblem(const mat &A, const vec &b, const vec &c) : A(A), b(b), c(c) {}

/// Solves defined problem
///
/// \param x_0 - initial point. Must be within borders defined in Ax < b
/// \param gamma - step size coefficient. Must be 0 < gamma < 1.
/// \param min_error - minimal Mean Absolute Error (MAE) value for mae(x_k, x_k+1) for which the algorithm stops
/// \param method - method of optimization. For now, only 'affine-scaling' is available.
/// \return result point with some utility information.
LinearOptimizationResult
LinearOptimizationProblem::maximize(const vec &x_0, const double_t gamma, double_t min_error, const std::string &method) {
    vec x = x_0;
    vec x_next = vec(x.size());
    std::vector<vec> intermediates = std::vector<vec>();
    size_t iter_counter = 0;
    bool xs_not_close_enough = true;
    while (xs_not_close_enough) {
        x_next = maximize_iter(x, gamma, method);
        intermediates.push_back(x_next);
        if (mean_absolute_error(x, x_next) < min_error) {
            xs_not_close_enough = false;
        }
        x = x_next;
        ++iter_counter;
    }
    return LinearOptimizationResult(x, intermediates, x_0, gamma, iter_counter);
}

vec LinearOptimizationProblem::maximize_iter(const vec &x, double_t gamma, std::string method) {
    if (method == "affine-scaling") {
        return affine_scaling(x, gamma);
    }
    exit(-1);
}

/// Algorithm I from https://doi.org/10.1007/BF01587095
vec LinearOptimizationProblem::affine_scaling(const vec &x, double_t gamma) {
    vec v_k = b - A * x;
    mat diag_v = diagmat(v_k);
    auto h_x = inv(A.t() * powmat(diag_v, -2) * A) * c;
    vec h_v = -A * h_x;

    auto zero_comp = (h_v >= zeros(h_v.size()));
    if (zero_comp.min() == 1) {
        exit(-1);
    }
    double_t alpha = affine_compute_alpha(gamma, v_k, h_v);
    return x + alpha * h_x;
}

double_t LinearOptimizationProblem::affine_compute_alpha(const double_t gamma, const vec &v_k, const vec &h_v) {
    double_t min_elem = std::numeric_limits<double_t>::max();
    for (size_t i = 0; i != v_k.size(); ++i) {
        if (h_v[i] < 0) {
            double_t div = -v_k[i] / h_v[i];
            if (div < min_elem)
                min_elem = div;
        }
    }
    return gamma * min_elem;
}

double_t LinearOptimizationProblem::mean_absolute_error(const vec &v1, const vec &v2) {
    double_t mae = 0;
    for (size_t i = 0; i != v1.size(); ++i) {
        mae += fabs(v1[i] - v2[i]);
    }
    return mae;
}
