//
//  10_12_quiz_question_3.cpp
//  learncpp
//
//  Created by allwyn joseph on 3/8/21.
//  Copyright © 2021 allwyn joseph. All rights reserved.
//

#include <iostream>

void print_binary(unsigned int x)
{
    
    if (x > 0)
        print_binary(x/2);
    
    std::cout << x % 2;
 
}

int main()
{
    int x{ 0 };
    std::cout << "Please enter number to be converted to binary : ";
    std::cin >> x;
    
    print_binary(static_cast<unsigned int>(x));
    std::cout<<std::endl;
    
    return 0;
}
