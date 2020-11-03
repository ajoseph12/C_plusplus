//
//  selection_sort.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/27/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>

int main()
{
    int array[] = { 4, 8, 2, 1, 9, 7, 6, 0, 5 };
    int array_length {(sizeof(array) / sizeof(array[0]))};
    int smallest_idx { 0 };
    
    // Begin by looping through all elemnts in the array
    // except the last one, as in theory towards the end of the
    // sort the last element will be sorted
    for (int i = 0; i < array_length-1; ++i)
    {
        // Assign the first element to be the smallest
        smallest_idx = i;
        
        // Loop through the remaining elements to see if
        // there exists smaller elements
        for (int j = i+1; j < array_length; ++j)
        {
            // If this is the case swap the index value and continue
            if (array[j] < array[smallest_idx])
                smallest_idx = j;
        }
        // Swap elements at indice i with element at
        // smallest indice and continue
        std::swap(array[i],  array[smallest_idx]);
    }
    for (int i = 0; i < (sizeof(array) / sizeof(array[0]));  ++i)
    {
        std::cout << array[i];
    }
    std::cout << std::endl;
    return 0;
}
