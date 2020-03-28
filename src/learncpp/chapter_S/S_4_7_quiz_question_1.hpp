//
//  S_4_7_quiz_question_1.hpp
//  learncpp
//
//  Created by allwyn joseph on 3/28/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#ifndef S_4_7_quiz_question_1_hpp
#define S_4_7_quiz_question_1_hpp

#include <iostream>

struct UserRevenue
{
    int numAds;
    float clickedAds;
    double adEarnings;
};

UserRevenue getInfo()
{
    UserRevenue temp;
    std::cout << " Please enter number of ads shown to readers \t \t : ";
    std::cin >> temp.numAds;
    std::cout << " Please enter percentage of ads clicked by reasers \t : ";
    std::cin >> temp.clickedAds;
    std::cout << " Please enter average earnings per ad click \t \t : ";
    std::cin >> temp.adEarnings;
    
    return temp;
}

void getEarnings(UserRevenue user)
{
    double earnings;

    earnings = user.numAds * (user.clickedAds/100) * user.adEarnings;
    std::cout << " Numer of ads shown to readers \t \t \t \t \t \t : "<<user.numAds <<std::endl;
    std::cout << " Percentage of ads clicked by user \t \t \t \t \t : "<<user.clickedAds <<std::endl;
    std::cout << " Average earnings per ad clicked \t \t \t \t \t : "<<user.adEarnings <<std::endl;
    std::cout << " Total earings for today \t \t \t \t \t \t \t : " << earnings <<std::endl;
    
}
#endif /* S_4_7_quiz_question_1_hpp */
