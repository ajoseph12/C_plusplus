//
//  trails.cpp
//  src
//
//  Created by allwyn joseph on 2/19/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <bitset>
#include <iostream>

using namespace std;

std::bitset<4> rotl ( std::bitset<4> bits)
{
//    if (bits.test(3))
//    {
//        bits <<= 1;
//        bits.set(0);
//    }
//    else
//        bits <<= 1;
//    return bits;
    
//    std::bitset<4> rbits{bits};
//    rbits >>= 3;
//    bits <<=1;
//
//    return rbits | bits;
    
    return (bits << 1) | (bits >> 3);
}



int main()
{
    std::bitset<4> bits1{0b0001};
    std::cout << rotl(bits1) << "\n";
    
    std::bitset<4> bits2{0b1000};
    std::cout << rotl(bits2) << "\n";
    
}

//int main()
//{
//    std::bitset<8> bits { 0b0000'0101 };
//    bits.set(3);
//    bits.flip(4);
//    bits.reset(4);
//
//    std::cout << "All bits : " << bits;
//
//}

//#include "trails.hpp"
//#include <algorithm>
//#include <iostream>
//#include <cmath>

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
//void printA()
//{
//    std::cout << "A\n";
//}
//
//int main()
//{
//    printA();
//    std::cout << '\n';
//
//    return 0;
//}
