//
//  10_9_quiz_question_1.cpp
//  learncpp
//
//  Created by allwyn joseph on 1/26/21.
//  Copyright © 2021 allwyn joseph. All rights reserved.
//

#include "10_9_quiz_question_1.hpp"

#include <functional>


// Forward declarations
std::tuple<double, double> get_UserInputs();
char get_operation();
double add();
double subtract();
double multiply();
double divide();
ArithmeticFunction getArithmeticFunction();


    
int main()
{
    // Initializations
    double num1{}, num2{};
    std::function<double (double, double)> ptrFcn;
    
    // Get user inputs
    std::tie(num1, num2) = get_UserInputs();
    char op{ get_operation() };
    
    // Get operation function w.r.t user i/p
    ptrFcn = getArithmeticFunction(op);
    
    // Display result of operation
    std::cout << "The result is = " << ptrFcn(num1, num2) << std::endl;
    
    return 0;
}

