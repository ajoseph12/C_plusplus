//
//  L_5_3_quiz_question_1.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/1/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>

void calculate(double a, double b, char c)
{
    switch(c)
    {
        case '+':
            std::cout << a + b <<std::endl;
            break;
        case '-':
            std::cout << a - b <<std::endl;
            break;
        case '*':
            std::cout << a * b <<std::endl;
            break;
        case '/':
            std::cout << a / (b + 1e-16) <<std::endl;
            break;
        case '%':
            std::cout <<a / (b + 1e-16) <<std::endl;
            break;
        default:
            std::cout << "calculate() : Unhandled case \n";
    }
}

int main()
{
    double digit_1 {};
    double digit_2 {};
    char operation {};
    
    std::cout << "Please enter first digit : ";
    std::cin >> digit_1;
    
    std::cout << "Please enter second digit : ";
    std::cin >> digit_2;
    
    std::cout << "Please enter desired operation '+, -, *, /, or %' : ";
    std::cin >> operation;
    
    calculate(digit_1, digit_2, operation);
    return 0;
}
