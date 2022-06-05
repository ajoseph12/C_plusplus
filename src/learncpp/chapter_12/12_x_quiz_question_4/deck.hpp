//
//  deck.hpp
//  learncpp
//
//  Created by Allwyn Joseph on 19/05/2022.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

#ifndef deck_hpp
#define deck_hpp

#include "globals.cpp"
#include "card.hpp"


class Deck
{
private:
    int m_cardIndex{ 0 };
    Card m_deck[ Global::cardsInADeck ];
    
public:
    Deck();
    void print();
    void shuffle();
    const Card &dealCard();
    int getIndex();

};


#endif /* deck_hpp */
