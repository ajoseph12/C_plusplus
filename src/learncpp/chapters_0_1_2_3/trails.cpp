//
//  trails.cpp
//  src
//
//  Created by allwyn joseph on 2/19/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include "trails.hpp"
#include <iostream>

using namespace std;

int main()
{
    int x{ 1 };
    int y{ 2 };
    
    std::cout << (++x, ++y); // increment x and y, evaluates to the right operand
    
    return 0;
}
