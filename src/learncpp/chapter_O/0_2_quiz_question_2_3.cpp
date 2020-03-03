//
//  0_2_quiz_question_2_3.cpp
//  learncpp
//
//  Created by allwyn joseph on 3/3/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//


#include <bitset>
#include <iostream>


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
