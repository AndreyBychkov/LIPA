//
// Created by а on 13.03.2020.
//

#include <fstream>
#include "LinearOptimizationResult.hpp"

using namespace std;

LinearOptimizationResult::LinearOptimizationResult(const vec result,
                                                   const std::vector<vec> intermediates,
                                                   const vec x_0,
                                                   const double_t gamma,
                                                   const size_t steps_num)
        : result(result), intermediates(intermediates), x_0(x_0), gamma(gamma), steps_num(steps_num) {

}

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
