//
//  10_9_quiz_question_1.hpp
//  learncpp
//
//  Created by allwyn joseph on 1/26/21.
//  Copyright © 2021 allwyn joseph. All rights reserved.
//

#ifndef _0_9_quiz_question_1_hpp
#define _0_9_quiz_question_1_hpp

#include <tuple>
#include <iostream>

// Type alias
using ArithmeticFunction = std::function<double(double, double)>;


std::tuple<double, double> get_UserInputs()
{
    // Get user number inputs
    
    double a{}, b{};
    std::cout << "Please enter 1st number : ";
    std::cin >> a ;
    std::cout << "Please enter 2nd number : ";
    std::cin >> b ;
    
    return {a, b};
}


char get_operation()
{
    // Get arithmetic operation the user wishes to execute on the numbers
    
    char op{};
    
    do
    {
        std::cout << "Please enter operation wished to be effectuated on the numbers : ";
        std::cin >> op;
        std::cin.clear();
        std::cin.ignore(32767, '\n');
    }
    while (op != '+' && op != '-' && op != '*' && op != '/');
    
    return op;
}


// Arithmetic operation callbacks
double add(double num1, double num2)
{
    return num1 + num2;
}

double subtract(double num1, double num2)
{
    return num1 - num2;
}

double multiply(double num1, double num2)
{
    return num1 * num2;
}

double divide(double num1, double num2)
{
    return num1 / num2;
}


ArithmeticFunction getArithmeticFunction(char op)
{
    // Get user arithmetic operation and return respective function
    
    switch (op)
    {
        default :
        case '+':
            return add;
        case '-':
            return subtract;
        case '*':
            return multiply;
        case '/':
            return divide;
        
    }
}

#endif /* _0_9_quiz_question_1_hpp */
