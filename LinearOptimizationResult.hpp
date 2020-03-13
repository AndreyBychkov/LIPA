//
// Created by а on 13.03.2020.
//

#ifndef LIPA_LINEAROPTIMIZATIONRESULT_HPP
#define LIPA_LINEAROPTIMIZATIONRESULT_HPP

#include <vector>
#include "armadillo"

using namespace arma;


class LinearOptimizationResult {
public:
    const vec result;
    const std::vector<vec> intermediates;
    const vec x_0;
    const double_t gamma;
    const size_t steps_num;
    LinearOptimizationResult(const vec result,
                             const std::vector<vec> intermediates,
                             const vec x_0,
                             const double_t gamma,
                             const size_t steps_num);
};


#endif //LIPA_LINEAROPTIMIZATIONRESULT_HPP
