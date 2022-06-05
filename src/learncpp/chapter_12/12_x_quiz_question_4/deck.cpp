//
//  deck.cpp
//  learncpp
//
//  Created by Allwyn Joseph on 19/05/2022.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//


#include "deck.hpp"
#include "card.hpp"

#include <iostream>
#include <random>


Deck::Deck()
{
    for(int s{0}; s < static_cast<int>(Card::Suit::max_suits); s++)
    {
        for(int r{0}; r < static_cast<int>(Card::Rank::max_rank); r++)
        {
            m_deck[(s*Global::cardInASuit) + r] = {static_cast<Card::Rank>(r), static_cast<Card::Suit>(s)};
        }
    }
}

void Deck::print()
{
    for(int i{0}; i < Global::cardsInADeck; i++)
    {
        m_deck[i].print(); std::cout << "\t";
    }
    std::cout << "\n\n";
}

void Deck::shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_deck, m_deck + Global::cardsInADeck, g);
}

const Card &Deck::dealCard()
{
    int cardIndex{ m_cardIndex };
    
    if (++cardIndex >= Global::cardsInADeck)
    {
        m_cardIndex = 0;
        Deck::shuffle();
    }
    return m_deck[ m_cardIndex++ ];
}

int Deck::getIndex()
{
    return m_cardIndex;
}
