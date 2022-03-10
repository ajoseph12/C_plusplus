//
//  11_x_quiz_question_3b.cpp
//  learncpp
//
//  Created by allwyn joseph on 3/10/22.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

#include <iostream>
#include <sstream> // for std::stringstream
#include <string>

int binarySearch(const int* array, int target, int min, int max)
{
    static int median{};
    
    // Recursion stop condirion
    if (min > max)
        return -1;
    
    median = (min + max) / 2;
    
    if (array[median] == target)
        return median;
    
    else if (array[median] > target)
        return binarySearch(array, target, min, median - 1);
    
    else
        return binarySearch(array, target, median + 1, max);
}

int main()
{
    constexpr int array[]{ 3, 6, 8, 12, 14, 17, 20, 21, 26, 32, 36, 37, 42, 44, 48 };
    int arr_size{ sizeof(array)/sizeof(array[0])};
    
    // We're going to test a bunch of values to see if they produce the expected results
    constexpr int numTestValues{ 9 };
    // Here are the test values
    constexpr int testValues[numTestValues]{ 0, 3, 12, 13, 22, 26, 43, 44, 49 };
    // And here are the expected results for each value
    int expectedValues[numTestValues]{ -1, 0, 3, -1, -1, 8, -1, 13, -1 };
    
    // Loop through all of the test values
    for (int count{ 0 }; count < numTestValues; ++count)
    {
        // See if our test value is in the array
        int index{ binarySearch(array, testValues[count], 0, arr_size - 1) };
        // If it matches our expected value, then great!
        if (index == expectedValues[count])
            std::cout << "test value " << testValues[count] << " passed!\n";
        else // otherwise, our binarySearch() function must be broken
            std::cout << "test value " << testValues[count] << " failed.  There's something wrong with your code!\n";
    }
    
    return 0;
}
