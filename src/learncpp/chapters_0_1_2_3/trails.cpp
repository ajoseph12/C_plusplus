//
//  trails.cpp
//  src
//
//  Created by allwyn joseph on 2/19/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//


#include <iostream>
#include <random> // for std::mt19937
#include <ctime> // for std::time
#include <iostream>

bool isLowerVowel(char c)
{
    switch (c)
    {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
    }
}

// returns the number of the test that failed, or 0 if all tests passed
int test()
{
    if (isLowerVowel('g') != true) return 1;
    if (isLowerVowel('q') != false) return 2;
    
    return 0;
}

int main()
{
    test();
    return 0;
}
