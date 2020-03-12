#include <iostream>
#include "Test.h"
#include "armadillo"
#include <vector>
using namespace arma;

double_t compute_alpha(const double_t gamma, const vec &v_k, const vec &h_v) {
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

double_t mean_absolute_error(const vec &v1, const vec &v2) {
    double_t mae = 0;
    for (size_t i = 0; i != v1.size(); ++i) {
        mae += fabs(v1[i] - v2[i]);
    }
    return mae;
}

vec affine_scaling(const mat &A, const vec &b, const vec &c, const vec &x_0, const double_t gamma) {
    vec x = x_0;
    vec x_next;
    bool xs_not_close_enough = true;
    while (xs_not_close_enough) {
        vec v_k = b - A * x;
        mat diag_v = diagmat(v_k);
        auto h_x = inv(A.t() * powmat(diag_v, -2) * A) * c;
        vec h_v = -A * h_x;

        auto zero_comp = (h_v >= zeros(h_v.size()));
        if (zero_comp.min() == 1) {
            exit(-1);
        }
        const double alpha = compute_alpha(gamma, v_k, h_v);
        x_next += alpha * h_x;

        if (mean_absolute_error(x, x_next) < 0.01) {
            xs_not_close_enough = false;
        }
        x = x_next;
    }
    return x;
}

// x - y < 0
// x > 0
// y > 0


int main() {
    mat A = mat(2, 2);
    A.at(0, 0) = 1;
    A.at(0, 1) = -1;
    A.at(1, 0) = -1;
    A.at(1, 1) = 0;

    vec b = zeros<vec>(2);
    vec c = zeros<vec>(2);
    vec x_0 = vec(2);
    x_0.at(0) = 0.1;
    x_0.at(1) = 0.1;
    double_t gamma = 0.5;

    vec res = affine_scaling(A, b, c, x_0, gamma);
    return 0;
}
