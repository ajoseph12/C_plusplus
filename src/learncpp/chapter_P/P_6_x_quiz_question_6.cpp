//
//  P_6_x_quiz_question_6.cpp
//  learncpp
//
//  Created by allwyn joseph on 9/15/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//
#include <algorithm>
#include <iostream>
#include <random>
#include <array>


enum class Ranks
{
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE,
    TOTAL,
};

enum class Suits
{
    HEARTS,
    SPADES,
    DIAMONDS,
    CLUBS,
    TOTAL,
    
};

struct Card
{
    Ranks rank{};
    Suits suit{};
};

using deck_type = std::array<Card, 52>;


void printCard(const Card card)
{

    switch (card.rank) {
        case Ranks::TWO:
            std::cout << "2";
            break;
        case Ranks::THREE:
            std::cout << "3";
            break;
        case Ranks::FOUR:
            std::cout << "4";
            break;
        case Ranks::FIVE:
            std::cout << "5";
            break;
        case Ranks::SIX:
            std::cout << "6";
            break;
        case Ranks::SEVEN:
            std::cout << "7";
            break;
        case Ranks::EIGHT:
            std::cout << "8";
            break;
        case Ranks::NINE:
            std::cout << "9";
            break;
        case Ranks::TEN:
            std::cout << "T";
            break;
        case Ranks::JACK:
            std::cout << "J";
            break;
        case Ranks::QUEEN:
            std::cout << "Q";
            break;
        case Ranks::KING:
            std::cout << "K";
            break;
        case Ranks::ACE:
            std::cout << "A";
            break;
        default:
            break;
    }
    
    switch (card.suit)
    {
        case Suits::HEARTS:
            std::cout << "H";
            break;
        case Suits::SPADES:
            std::cout << "S";
            break;
        case Suits::DIAMONDS:
            std::cout << "D";
            break;
        case Suits::CLUBS:
            std::cout << "C";
            break;
            
        default:
            break;
    }
}

void createDeck(deck_type& deck)
{
    int diff{0};
    auto suits{ static_cast<int>(Suits::TOTAL) };
    auto ranks{ static_cast<int>(Ranks::TOTAL) };
    
    for (int s{0}; s < suits; s++)
    {
        diff = s*ranks;
        for (int r{0}; r < ranks; r++)
        {
            deck[diff +r].rank = static_cast<Ranks>(r);
            deck[diff +r].suit = static_cast<Suits>(s);
        }
    }
}

void printDeck(const deck_type deck)
{
    for (auto element : deck)
    {
        printCard(element);
        std::cout << "\t";
    }
}

void shuffleDeck(deck_type& deck)
{
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::shuffle(deck.begin(), deck.end(), mt);
}

void getCardValue(Card card)
{
    Ranks rank {card.rank};
    
    if (rank == Ranks::TEN or rank == Ranks::JACK or rank == Ranks::QUEEN or
        rank == Ranks::KING)
        std::cout <<" Card value = " << "10";
    else if (rank == Ranks::ACE)
        std::cout <<" Card value = " << "11";
    else
        std::cout <<" Card value = " << static_cast<int>(rank) + 2;
    
    std::cout << std::endl;
}



int main()
{

    deck_type deck;
    createDeck(deck);
    shuffleDeck(deck);
    printDeck(deck);
    
    return 0;
}
