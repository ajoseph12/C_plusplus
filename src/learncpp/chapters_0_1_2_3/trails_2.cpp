//
//  trails_2.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/1/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//


#include <iostream>

void doSomething()
{
#ifdef PRINT
    std::cout << "Printing!";
#endif
#ifndef PRINT
    std::cout << "Not printing!";
#endif
}
