//
//  card.hpp
//  learncpp
//
//  Created by Allwyn Joseph on 17/05/2022.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

#ifndef card_hpp
#define card_hpp

#include <iostream>

class Card
{
public:
    enum Rank
    {
        rank_two,
        rank_three,
        rank_four,
        rank_five,
        rank_six,
        rank_seven,
        rank_eight,
        rank_nine,
        rank_ten,
        rank_jack,
        rank_queen,
        rank_king,
        rank_ace,
        
        max_rank
    };
    enum Suit
    {
        suit_clubs,
        suit_diamonds,
        suit_hearts,
        suit_spades,
        
        max_suits
    };
    
private:
    Rank m_rank{};
    Suit m_suit{};

public:
    Card() = default;
    
    Card(Rank rank, Suit suit)
        : m_rank{ rank }, m_suit{ suit }
    {
    }
    
    void print() const;
    
    int value() const;

    
};


#endif /* card_hpp */
