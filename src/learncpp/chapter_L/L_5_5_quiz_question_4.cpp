//
//  L_5_5_quiz_question_4.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/2/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>

int main()
{
    int outer {1};
    while (outer < 6)
    {
        int inner {5};
        while (inner)
        {
            if (inner  <= outer)
                std::cout << inner << " ";
            else
                std::cout << "  ";
            
            --inner;
        }
        std::cout << "\n";
        ++outer;
    }
}
