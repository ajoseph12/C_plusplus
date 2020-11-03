//
//  P_6_x_quiz_question_7.hpp
//  learncpp
//
//  Created by allwyn joseph on 9/29/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#ifndef P_6_x_quiz_question_7_hpp
#define P_6_x_quiz_question_7_hpp

#include <iostream>
#include <random>
#include <array>


#endif /* P_6_x_quiz_question_7_hpp */

// Maximum score before losing.
constexpr int maximumScore{ 21 };

// Minimum score that the dealer has to have.
constexpr int minimumDealerScore{ 17 };


enum class Ranks
{
    // Enum object representing the
    // values of cards in a deck
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
    // Enum object representing 
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

struct Player
{
    int final_value{ 0 };
    std::string name;
    std::vector<int> cards;
    std::vector<int> values;
};

using player_type = std::vector<Player>;

using deck_type = std::array<Card, 52>;


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


void getCount(Player& player)
{
    /*
     Function to get player counts at the beginning of the game
    */
    
    int ace_value{ 1 };
    std::string msg{};
    
    // If `values` vector empty add an element to it. At the beginning
    // of the game the vector is empty.
    if (not player.values.size())
        player.values.push_back(static_cast<int>(0));
    
    for (int card : player.cards)
    {
        // The case where card count is less than 10.
        if (card <= static_cast<int>(Ranks::TEN))
        {
            // Increase value of all elements in `values` vector
            // by the card value that has just been hit.
            for (int& value : player.values)
            {
//                std::cout << "Before" << value << std::endl;
                value += card + 2;
//                std::cout << "After" << value << std::endl;
            }
            
        }
        
        // The case where an ACE is picked
        else if (card == static_cast<int>(Ranks::ACE))
        {
            std::vector<int> temp_values{ player.values };
            
            // Double the length of `values` vector by copying all elements
            // within it twice. Ex: [4,2] -> [4,2,4,2]
            for (int temp_value : temp_values)
                player.values.push_back(static_cast<int>(temp_value));
            
            // Add 1 to the first half of the `values` vector add 11 to the
            // second half
            for (int i{0}; i < player.values.size(); i++)
            {
                // Incrase the value of ace to 11 for the second half of the
                // vector
                if (i > (player.values.size())/2 - 1)
                   ace_value = 11;
                
                // Add value of ace to element of vector `values`
                player.values[i] += ace_value;
            }
        }
        
        // The case where JACK, QUEEN or KING is picked
        else
        {
            switch (card)
            {
                case static_cast<int>(Ranks::JACK):
                case static_cast<int>(Ranks::QUEEN):
                case static_cast<int>(Ranks::KING):
                    for (int& value : player.values)
                        value += 10;
                    break;
                // Basically should never happen
                default:
                    for (int value : player.values)
                        value += 1000000;
            }
        }
        
    }
    // Delete cards once the value is recorded
    player.cards.erase(player.cards.begin(), player.cards.end());

}

void h_P_Assign(Player& player)
{
    int selected_value{ 0 };
    
    for (int value : player.values)
    {
        if (value > selected_value and value < 22)
            selected_value = value;
        else if (not selected_value)
            selected_value = value;
    }
    
    player.final_value = selected_value;
}



bool check(Player player)
{

    if (player.values[0] > maximumScore)
        return 0;
    return 1;
}


void print_PlayerStats(std::vector<int> player_values)
{
    /*
     Function that prints total card value of players
     */
    
    // Display player / dealer stats
    for (int i{ 0 }; i < player_values.size(); i++)
        if (i)
            std::cout <<" or " << player_values[i];
        else if (not i)
            std::cout << player_values[i];
    std::cout << std::endl;
}


std::string getPlayerName(int count)
{
    std::string name{};
    std::cout << "Please enter name of Player " << count + 1 << ": ";
    std::cin >> name;
    
    return name;
}
