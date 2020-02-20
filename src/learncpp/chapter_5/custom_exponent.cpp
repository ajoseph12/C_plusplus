//
//  custom_exponent.cpp
//  learncpp
//
//  Created by allwyn joseph on 2/20/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//
// Link to source : https://tinyurl.com/sqe3os

#include <iostream>
#include <cstdint> // for std::int_fast64_t

using namespace std;

// note: exp must be positive
std::int_fast64_t powint(int base, int exp)
{
    std::int_fast64_t result{1};
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}

int main()
{
    cout << powint( 7, 12) <<endl;
    return 0;
}
