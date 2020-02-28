//
//  approximate_equality.cpp
//  learncpp
//
//  Created by allwyn joseph on 2/27/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <stdio.h>

bool approximatelyEqualRel(double a, double b, double absEpsilon, double relEpsilon)
{
    // This function is used to check equality of floating numbers
    
    // Check if the numbers are really close
    double diff { std::abs(a-b) };
    if (diff < absEpsilon)
        return true;
    
    // Else fall back to Knuth's algorithm
    return (diff <= (std::max(std::abs(a), std::abs(b))*relEpsilon)
}
