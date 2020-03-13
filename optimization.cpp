#include "optimization.hpp"

vec affine_scaling_lp(const mat &A, const vec &b, const vec &c, const vec &x_0, const double_t gamma) {
    vec x = x_0;
    vec x_next = vec(x_0.size());
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
        x_next = x + alpha * h_x;

        if (mean_absolute_error(x, x_next) < 0.001) {
            xs_not_close_enough = false;
        }
        x = x_next;
    }
    return x;
}

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