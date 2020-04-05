//
//  L_5_5_quiz_question_3.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/2/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>

int main()
{
    int outer {5};
    while (outer)
    {
        int inner {outer};
        while (inner)
        {
            std::cout << inner << " ";
            --inner;
        }
        std::cout << "\n";
        --outer;
    }
}
