//
//  player.hpp
//  learncpp
//
//  Created by Allwyn Joseph on 01/06/2022.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include "deck.hpp"


class Player
{
private:
    int m_score{ 0 };
    int m_aceCount{ 0 };
    
public:
    Player() = default;
    int score() const;
    bool isBust() const;
    int drawCard(Deck& deck);
    
};
#endif /* player_hpp */
