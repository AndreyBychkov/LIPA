//
// Created by а on 05.03.2020.
//

#ifndef LIPA_TEST_H
#define LIPA_TEST_H

#include <iostream>

class Test {
public:
    int a = 1;

    void hello() {
        std::cout << "Hello, I have an " << a << "!" << std::endl;
    }
};


#endif //LIPA_TEST_H
