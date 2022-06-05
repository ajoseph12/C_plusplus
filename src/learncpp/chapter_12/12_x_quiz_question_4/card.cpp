//
//  card.cpp
//  learncpp
//
//  Created by Allwyn Joseph on 17/05/2022.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

#include "card.hpp"

void Card::print() const
{
    switch(m_rank)
    {
        case rank_two:      std::cout << '2';   break;
        case rank_three:    std::cout << '3';   break;
        case rank_four:     std::cout << '4';   break;
        case rank_five:     std::cout << '5';   break;
        case rank_six:      std::cout << '6';   break;
        case rank_seven:    std::cout << '7';   break;
        case rank_eight:    std::cout << '8';   break;
        case rank_nine:     std::cout << '9';   break;
        case rank_ten:      std::cout << 'T';   break;
        case rank_jack:     std::cout << 'J';   break;
        case rank_queen:    std::cout << 'Q';   break;
        case rank_king:     std::cout << 'K';   break;  
        case rank_ace:      std::cout << 'A';   break;
        default:            std::cout << '?';   break;
    }
    
    switch (m_suit)
    {
        case suit_clubs:    std::cout << 'C';   break;
        case suit_diamonds: std::cout << 'D';   break;
        case suit_hearts:   std::cout << 'H';   break;
        case suit_spades:   std::cout << 'S';   break;
        default:            std::cout << '?';   break;
    }
}


int Card::value() const
{
    switch(m_rank)
    {
        case rank_two:     return 2;
        case rank_three:   return 3;
        case rank_four:    return 4;
        case rank_five:    return 5;
        case rank_six:     return 6;
        case rank_seven:   return 7;
        case rank_eight:   return 8;
        case rank_nine:    return 9;
        case rank_ten:
        case rank_jack:
        case rank_queen:
        case rank_king:    return 10;
        case rank_ace:     return 11;
        default:
            assert(false && "should never happen");
            return '0';
    }
    
}
