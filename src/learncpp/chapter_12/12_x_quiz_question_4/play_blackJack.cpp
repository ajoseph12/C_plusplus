//
//  play_blackJack.cpp
//  learncpp
//
//  Created by Allwyn Joseph on 03/06/2022.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

#include "globals.cpp"
#include "card.cpp"
#include "deck.cpp"
#include "player.cpp"
#include "play_blackJack.hpp"

#include <iostream>


BlackJackResult playBlackJack(Player &player, Player &dealer, Deck deck)
{
    // Player plays until bust or satisfcation
    std::cout << "\n\n[INFO] - It's the player's chance to play first.";
    int playerValue{ play(deck, player) };
    
    // Check if player's total card value exceeds blackjack
    if (playerValue > Global::blackJack)
    {
        printDealerAndPlayerValue(playerValue, 0);
        return BlackJackResult::dealer_won;
    }
    
    // Dealer plays until at least 17 or bust
    std::cout << "\n\n[INFO] - The dealer will now play until 17 or bust.";
    int dealerValue{ play(deck, dealer, true) };
    
    printDealerAndPlayerValue(playerValue, dealerValue);
    
    // If delar's card value is greater than 21 or player's card value greater
    // the dealer's, player wins (cause player's card value < 21)
    if (dealerValue > Global::blackJack or playerValue > dealerValue)
        return BlackJackResult::player_won;
    // If dealers's value is greater than player's value, dealer wins
    else if (playerValue < dealerValue )
        return BlackJackResult::dealer_won;
    // Else both dealer and player has the same value and the game is a tie
    else
        return BlackJackResult::tie;
}


void decideWinner(BlackJackResult result)
{
    if (result == BlackJackResult::player_won)
        std::cout << "\n[INFO] - Player won !" << "\n";
    else if (result == BlackJackResult::dealer_won)
        std::cout << "\n[INFO] - Dealer won !" << "\n";
    else if (result == BlackJackResult::tie)
        std::cout << "\n[INFO] - The game is a tie !" << "\n";
}

int main()
{
    // Create deck of cards and shuffle
    Deck deck{};
    deck.shuffle();
    
    // Create player and dealer objects
    Player player{};
    Player dealer{};
    
    // Launch a game of blackjack and get resutl
    BlackJackResult result = playBlackJack(player, dealer, deck);
    
    // Decide the winner of the game
    decideWinner(result);
    return 0;
}
