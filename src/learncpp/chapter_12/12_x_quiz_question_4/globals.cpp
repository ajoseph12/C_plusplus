//
//  globals.cpp
//  learncpp
//
//  Created by Allwyn Joseph on 19/05/2022.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

//#include <iostream>

#ifndef global_cpp
#define global_cpp

class Global
{
public:
    static const int cardsInADeck{ 52 };
    static const int cardInASuit{ 13 };
    static const int blackJack{ 21 };
    static const int maxDealerValue{ 17 };
    
    Global() =  default;
    
    static int getCardsInDeck()
    {
        return cardsInADeck;
    }
    
    static int getCardInASuit()
    {
        return cardInASuit;
    }
    
    static int getBlackJack()
    {
        return blackJack;
    }
    
    static int getMaxDealerValue()
    {
        return maxDealerValue;
    }
};
#endif /* deck_hpp */
