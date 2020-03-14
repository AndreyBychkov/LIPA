//
// Created by а on 13.03.2020.
//

#include <fstream>
#include "LinearOptimizationResult.hpp"

using namespace std;

/// Wrapper over result of LinearOptimizationProblem
///
/// \param result - resulting point x
/// \param intermediates - intermediate points x_k
/// \param x_0 - initial point
/// \param gamma - step size coefficient. Must be 0 < gamma < 1.
/// \param steps_num - steps number of algorithm
LinearOptimizationResult::LinearOptimizationResult(const vec result,
                                                   const std::vector<vec> intermediates,
                                                   const vec x_0,
                                                   const double_t gamma,
                                                   const size_t steps_num)
        : result(result), intermediates(intermediates), x_0(x_0), gamma(gamma), steps_num(steps_num) {

}

/// Writes intermediate points to csv file. Intended for algorithm visualization.
void LinearOptimizationResult::intermediates_to_csv(string filename) {
    ofstream file;
    file.open(filename, ios::trunc);

    for (size_t i = 0; i != intermediates[0].size() - 1; ++i) {
        file << "x" << i << ",";
    }
    file << "x" << intermediates[0].size() - 1 << "\n";

    for (auto& inter: intermediates) {
        for (size_t i = 0; i != inter.size() - 1; ++i) {
            file << inter[i] << ",";
        }
        file << inter[inter.size() - 1] << "\n";
    }

    file.close();
}
