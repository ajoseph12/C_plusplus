//
//  player.cpp
//  learncpp
//
//  Created by Allwyn Joseph on 01/06/2022.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

//#include "globals.cpp"

#include "player.hpp"


/**
 * Updates player score and ace count
 *
 * @param deck a class  holding information of cards in the deck
 */
int Player::drawCard(Deck& deck)
{
    // Deal a card from the deck and update player score
    int cardValue { deck.dealCard().value() };
    m_score += cardValue;
    
    // Update ace count if `cardValue` == 11
    if (cardValue == 11)
        m_aceCount += 1;
    
    // Check if player score is greater than 21, if so decrease score by
    // 10 and ace_count by 1
    if (m_score > 21 and m_aceCount > 0)
    {
        m_aceCount -= 1;
        m_score -= 10;
    }
        
    return cardValue;
}

bool Player::isBust() const
{
    return (m_score > Global::blackJack);
}

int Player::score() const
{
    return m_score;
}
//
//int main()
//{
//    Deck deck{};
//
//    deck.shuffle();
//    deck.print();
//
//    Player player{};
//    Player dealer{};
//    
////    int playerCard { player.drawCard(deck) };
//    std::cout << "The player drew a card with value " << player.drawCard(deck) << " and now has score " << player.score() << '\n';
//    int dealerCard { dealer.drawCard(deck) };
//    std::cout << "The dealer drew a card with value " << dealerCard << " and now has score " << dealer.score() << '\n';
//
//    return 0;
//}
