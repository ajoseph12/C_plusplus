//
//  P_6_x_quiz_question_7.cpp
//  learncpp
//
//  Created by allwyn joseph on 9/29/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//


#include "P_6_x_quiz_question_7.hpp"

#include <iostream>
#include <array>
#include <random>
#include <algorithm>


using namespace std;


enum class BlackJackResult
{
    player_won,
    dealer_won,
    tie
};

/**
 * Prints card's rank and suit.
 *
 * @param card a struct containing card rank and suit
 */
void printCard(const Card &card)
{
    char rank{getCardRank(card.rank)};
    char suit{getCardSuit(card.suit)};
    cout << rank << suit << "\n";
}

/**
 * Prints all the rank and suit of all the cards of the deck.
 *
 * @param deck a struct containing card rank and suit
 */
void printDeck(const Card deck[], int size = 52)
{
    for(int i{0}; i < size; i++)
        printCard(deck[i]);
}

/**
 * Shuffles cards in the deck
 *
 * @param deck a struct containing card rank and suit
 */
void shuffleDeck(Card deck[], int size = 52)
{
    random_device rd;
    mt19937 g(rd());
    shuffle(deck, deck + size, g);
}

/**
 * Displays player's and dealer's total card value
 *
 * @param playerValue an int indicating player's card value
 * @param dealerValue an int indicating dealer's card value
 */
void printDealerAndPlayerValue(int playerValue, int dealerValue)
{
    cout << "\n\n[INFO] - Player's total card value = " << playerValue;
    cout << "\n[INFO] - Dealer's total card value = " << dealerValue;
}

/**
 * Returns the result of the game played
 *
 * @param deck an array of structs, with each struct containing a card rank and
 *      card suit objects
 */
BlackJackResult playBlackJack(Card deck[])
{
    // Player plays until bust or satisfcation
    cout << "\n\n[INFO] - It's the player's chance to play first.";
    int playerValue{ play(deck) };
    
    // Check if player's total card value exceeds blackjack
    if (playerValue > blackJack)
    {
        printDealerAndPlayerValue(playerValue, 0);
        return BlackJackResult::dealer_won;
    }
    
    // Dealer plays until at least 17 or bust
    cout << "\n\n[INFO] - The dealer will now play until 17 or bust.";
    int dealerValue{ play(deck, true) };
    
    printDealerAndPlayerValue(playerValue, dealerValue);
    
    // If delar's card value is greater than 21 or player's card value greater
    // the dealer's, player wins (cause player's card value < 21)
    if (dealerValue > blackJack or playerValue > dealerValue)
        return BlackJackResult::player_won;
    // If dealers's value is greater than player's value, dealer wins
    else if (playerValue < dealerValue )
        return BlackJackResult::dealer_won;
    // Else both dealer and player has the same value and the game is a tie
    else
        return BlackJackResult::tie;
}

int main()
{    
    cout << "\n[INFO] - Beginning a game of BlackJack";
    // Create and shuffle deck of cards
    auto deck{ createDeck() };
    cout << "\n[INFO] - Shuffling deck ..";
    shuffleDeck(deck);
    
    // Play BlackJack and get result. True if player won, false if player lost
    BlackJackResult result{ playBlackJack(deck) };
    
    if (result == BlackJackResult::player_won)
        cout << "\n[INFO] - Player won !" << "\n";
    else if (result == BlackJackResult::dealer_won)
        cout << "\n[INFO] - Dealer won !" << "\n";
    else if (result == BlackJackResult::tie)
        cout << "\n[INFO] - The game is a tie !" << "\n";
    
    return 0;
}
