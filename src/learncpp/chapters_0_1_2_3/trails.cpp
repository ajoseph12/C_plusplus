//
//  trails.cpp
//  src
//
//  Created by allwyn joseph on 2/19/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//


#include <iostream>

//int main()
//{
//    int outer {1};
//    while (outer < 6)
//    {
//        int inner {5};
//        while (inner)
//        {
//            if (inner  <= outer)
//                std::cout << inner << " ";
//            else
//                std::cout << "  ";
//                
//            --inner;
//        }
//        std::cout << "\n";
//        ++outer;
//    }
//}


int main()
{
    int outer {1};
    do
    {
        int inner {5};
        do
        {
            if (inner  <= outer)
                std::cout << inner << " ";
            else
                std::cout << "  ";
            
            --inner;
        }
        while (inner);
        std::cout << "\n";
        ++outer;
    }
    while(outer < 6);

}
//int main()
//{
//    constexpr std::uint_fast8_t isHungry{   1 << 0 };
//    constexpr std::uint_fast8_t isSad{      1 << 2 };
//    constexpr std::uint_fast8_t isMad{      1 << 3 };
//    constexpr std::uint_fast8_t isHappy{    1 << 4 };
//    constexpr std::uint_fast8_t isLaughing{ 1 << 5 };
//
//    std::uint_fast8_t me{};
//
//    me |= isHappy | isLaughing;
//    me &= ~isLaughing;
//
//    cout << "Am I happy? \t" << static_cast<bool>(me & isHappy) << "\n";
//    cout << "Am I laughing? \t" << static_cast<bool>(me & isLaughing) << "\n";
//}


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
