//
//  play_blackJack.hpp
//  learncpp
//
//  Created by Allwyn Joseph on 03/06/2022.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

#ifndef play_blackJack_hpp
#define play_blackJack_hpp

#include <iostream>


enum class BlackJackResult
{
    player_won,
    dealer_won,
    tie
};


/**
 * Returns user's desire to hit or stay.
 */
char getUserResponse()
{
    char hit_or_stay;
    do
    {
        std::cout << "\n\t[UserInput] - Do you want to hit? (y/n): ";
        std::cin >> hit_or_stay;
        std::cin.ignore(32767, '\n');
    }
    while (hit_or_stay != 'y' && hit_or_stay != 'n');
    
    return hit_or_stay;
}


/**
 * Displays player's and dealer's total card value
 *
 * @param playerValue an int indicating player's card value
 * @param dealerValue an int indicating dealer's card value
 */
void printDealerAndPlayerValue(int playerValue, int dealerValue)
{
    std::cout << "\n\n[INFO] - Player's total card value = " << playerValue;
    std::cout << "\n[INFO] - Dealer's total card value = " << dealerValue;
}


void displayPlayerScore(int total, bool dealerIsPlaying = false)
{
    if (dealerIsPlaying)
        std::cout << "\n\t[INFO] - dealer's score: " << total;
    else
        std::cout << "\n\t[INFO] - player's score: " << total;
}


int play(Deck &deck, Player &player, bool dealerIsPlaying = false)
{
    
    int cardValue = player.drawCard(deck);
    displayPlayerScore(player.score(), dealerIsPlaying);
    
    bool keepPlaying{ 1 };
    
    // Run play until player/dealer has gone bust or decides to stop
    while (keepPlaying)
    {
        // If dealer is playing, keep hitting until bust or `maxDealerValue`
        if (dealerIsPlaying)
        {
            if (player.score() < Global::maxDealerValue)
            {
                int cardValue = player.drawCard(deck);
                displayPlayerScore(player.score(), dealerIsPlaying);
            }
            else
                keepPlaying = 0;
        }
        // iF player is playing, keep hitting until player decides to stay or
        // he/she has exceeded or equalled `blackJack`
        else
        {
            if (player.score() < Global::blackJack)
            {
                if (getUserResponse() == 'y')
                {
                    int cardValue = player.drawCard(deck);
                    displayPlayerScore(player.score(), dealerIsPlaying);
                }
                else
                    keepPlaying = 0;
            }
            else
                keepPlaying = 0;
        }
    }
    return player.score();
}

#endif /* play_blackJack_hpp */
