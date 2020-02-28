//
//  trails.cpp
//  src
//
//  Created by allwyn joseph on 2/19/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include "trails.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>

//using namespace std;
//
//bool approximatelyEqual(double a, double b, double epsilon)
//{
//    cout <<(max(abs(a), abs(b)) * epsilon) <<endl;
//    cout << abs(a - b)  <<endl;
//    return (abs(a - b)  <= (max(abs(a), abs(b)) * epsilon));
//}
//
//int main()
//{
//    // a is really close to 1.0, but has rounding errors, so it's slightly smaller than 1.0
//    double a{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 };
//
////    cout << abs(a - 1.0) - 0.0;
//
//    cout << approximatelyEqual(a, 1.0, 1e-8) << endl;
//    cout << approximatelyEqual(a-1.0, 0.0, 1e-8) << endl;
//}
void printA()
{
    std::cout << "A\n";
}

int main()
{
    printA();
    std::cout << '\n';
    
    return 0;
}
