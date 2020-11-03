//
//  P_6_x_quiz_question_3.cpp
//  learncpp
//
//  Created by allwyn joseph on 9/10/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>

void swap(int &a, int &b)
{
    int temp{};

    temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a{4};
    int b{2};
    
    swap(a, b);
    
    
    std::cout << "Value of a : " << a << std::endl;
    std::cout << "Value of b : " << b << std::endl;
    
    return 0;
}
