//
//  10_12_quiz_question_1.cpp
//  learncpp
//
//  Created by allwyn joseph on 3/4/21.
//  Copyright © 2021 allwyn joseph. All rights reserved.
//

#include <iostream>

int factorial(int x)
{
    if (x < 0)
        return 0;
    else if (x == 1 or x == 0)
        return 1;
    else
        return x * factorial(x-1);
}

int main()
{
    for(int x{ 1 }; x < 8; x++)
        std::cout << factorial(x) <<"\t";
    
    return 0;
}
