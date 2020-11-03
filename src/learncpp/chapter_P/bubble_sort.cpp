//
//  bubble_sort.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/27/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>

int main()
{
    int array[] { 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    int array_length {(sizeof(array) / sizeof(array[0]))};
    int smallest_idx { 0 };
    
    while (array_length - 1)
    {
        bool no_swap {true};
        smallest_idx = 0;
        
        for (int i = 0; i < array_length-1; i++)
        {
            // If this is the case swap the index value and continue
            if (array[i] > array[i+1])
            {
                std::swap(array[i],  array[i+1]);
                no_swap = false;
            }
        }
        if (no_swap)
        {
            std::cout << "Early termination on iteration : "
            << (sizeof(array) / sizeof(array[0])) - array_length + 1
            << std::endl;
            break;
        }
        --array_length;
    }
    
    for (int i = 0; i < (sizeof(array) / sizeof(array[0]));  ++i)
    {
        std::cout << array[i];
    }
    std::cout << std::endl;
    return 0;
}
