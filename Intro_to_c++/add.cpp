//
//  add.cpp
//  Intro_to_c++
//
//  Created by allwyn joseph on 4/9/19.
//  Copyright © 2019 allwyn joseph. All rights reserved.
//

/*# include <iostream>

int getInteger()
{
    std::cout << "Please enter an integer";
    int x{0};
    std::cin >> x;
    return x;
}

# include "add.hpp"

int add(int x, int y)
{
    return x+y;
}
*/

# include <iostream>

int readNumber()
{
    int num{0};
    std::cout << "Please input a number : ";
    std::cin >> num;

    return num;
}

void writeAnswer(int num1, int num2)
{
    std::cout << "The sum of the two input digits : " << num1 + num2 << "\n";

}
//int add(int x, int y)
//{
//    return x+y;
//}
//
//void doSomething()
//{
//#ifdef PRINT
//    std::cout << "Printing!";
//#endif
//#ifndef PRINT
//    std::cout << "Not printing!";
//#endif
//}
