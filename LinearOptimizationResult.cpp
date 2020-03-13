//
// Created by а on 13.03.2020.
//

#include "LinearOptimizationResult.hpp"

LinearOptimizationResult::LinearOptimizationResult(const vec result,
                                                   const std::vector<vec> intermediates,
                                                   const vec x_0,
                                                   const double_t gamma,
                                                   const size_t steps_num)
        : result(result), intermediates(intermediates), x_0(x_0), gamma(gamma), steps_num(steps_num) {

}
