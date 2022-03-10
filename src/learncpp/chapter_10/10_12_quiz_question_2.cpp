//
//  10_12_quiz_question_2.cpp
//  learncpp
//
//  Created by allwyn joseph on 3/4/21.
//  Copyright © 2021 allwyn joseph. All rights reserved.
//

#include <iostream>

int decompose(int x)
{
    // Assuming x is positive
    
    if (x == 0)
        return 0;
    return (x % 10) + decompose(x / 10);
}

int main()
{
    std::cout << decompose(93427) << std::endl;
}
