//
//  P_6_8a_quiz_question_2.cpp
//  learncpp
//
//  Created by allwyn joseph on 5/14/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>


int* find(int *begin, int *end, int value)
{
    for (int* ptr{begin};  ptr < end; ++ptr)
    {
        if (*ptr == 20)
            return ptr;
    }
    return end;
}

int main()
{
    int arr[]{ 2, 5, 4, 10, 8, 20, 16, 40 };
    
    // Search for the first element with value 20.
    int* found{ find(std::begin(arr), std::end(arr), 20) };
    
    // If an element with value 20 was found, print it.
    if (found != std::end(arr))
    {
        std::cout << *found << '\n';
    }
    
    return 0;
}
