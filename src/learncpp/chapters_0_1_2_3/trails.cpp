//
//  trails.cpp
//  src
//
//  Created by allwyn joseph on 2/19/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <cstdint>
#include <iostream>

int main()
{
//    constexpr std::uint_fast8_t option_viewed{ 0x01 };
    std::bitset<8> bin1{ 0b1100'0101 };
//    constexpr std::uint_fast8_t option_favorited{ 0x04 };
//    constexpr std::uint_fast8_t option_shared{ 0x08 };
//    constexpr std::uint_fast8_t option_deleted{ 0x80 };
//
//    std::uint_fast8_t myArticleFlags{};
////    std::cout << "Enter a hex file : ";
////    std::cin >> std::hex >> myArticleFlags;
//    myArticleFlags != option_viewed;
//
//    std::cout << " Was the article deleted ? \t" << static_cast<bool>(myArticleFlags & option_deleted) <<std::endl;
//
//    if (myArticleFlags & option_favorited)
//        myArticleFlags &= ~option_favorited;
    std::cout << bin1 <<std::endl;
    std::cout << std::dec << bin1 << '\n'; 
    return 0;
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
