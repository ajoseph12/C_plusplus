//
//  P_6_x_quiz_question_7.cpp
//  learncpp
//
//  Created by allwyn joseph on 9/29/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

//TO-DO
// Make this common
//hit(players[i].cards, deck, 1);
//
//// Update player card set values
//getCount(players[i]);
//
//displayStats(players[i], dealer_hit);
// - When cards were deleted it works !!!
// - Find winner
// - Add checks for name input, num of players input


#include "P_6_x_quiz_question_7.hpp"

#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <array>


int getNumOfPlayers()
{
    int num_players{0};
    std::cout << "Please enter number of players : ";
    std::cin >> num_players;
    std::cin.ignore(32767, '\n');

    return num_players;
}


void displayStats(Player& player, char& response)
{
    
    // Check if player / dealer has gone busr
    if (not check(player))
    {
        std::cout << "\t You have gone BUST!!! \n";
        response = 'n';
    }
    else
    {
        std::vector<int> temp_values;
        
        // Loop through value list and keep only those values less than
        // or equal to 21
        for (int value : player.values)
            if (value <= maximumScore)
                temp_values.push_back(value);
        
        // Display player / dealer stats
        std::cout <<"\t Your new card count(s) is/are : " ;
        print_PlayerStats(temp_values);
    }
}


void hit(std::vector<int>& cards, deck_type& deck, int times)
{
    /*
     Function to hit player / dealer on command
    */
    static int track{0};
    
    // if one has reached the end of the set
    // of cards shuffle and re-initialize
    if (track == 51)
    {
        shuffleDeck(deck);
        track = 0;
    }

    // Initialize players with cards
    for (int i{0}; i < times; i++)
    {
        cards.push_back(static_cast<int>(deck[track].rank));
        track++;
    }
    
    // Display value of the card hit
    for(int card : cards)
    {
        if (card < 8)
            std::cout << "\t Card value hit : " << card + 2 << std::endl;
        else if (card < 12)
            std::cout << "\t Card value hit : 10 " << std::endl;
        else
            std::cout << "\t Card value hit : 1 or 11" << std::endl;
    }
}


void fillPlayerInfo(player_type& players, deck_type& deck)
{
    /*
     Function to initialized the game by filling in the player and
     dealer info
    */
    
    int counter {0};
    for (auto& player : players)
    {
        if (counter != players.size() - 1)
        {
            player.name = getPlayerName(counter);
            hit(player.cards, deck, 2);
        }
        else
        {
            std::cout << "Initializing Dealer .. \n";
            player.name = "Dealer";
            hit(player.cards, deck, 1);
        }
        counter += 1;
    }
}


void hit_Participants(player_type& players, deck_type deck)
{
    /*
    Function to hit players/dealers and display necessary information
    */
    
    // Loop through participants, display info and hit if necessary
    for (auto i { 0 }; i < players.size() ; i++)
    {
        // Display player / dealer stats
        std::cout << "\n" << players[i].name << " it's your turn to hit or stay \n";
        std::cout << "\t Your current card count is/are : " ;
        print_PlayerStats(players[i].values);
        
        if (players[i].name != "Dealer")
        {
           
            // Get player reponse if he/she wants to hit or not
            char response;
            
            // Hit player until he/she wants to hit no-more
            do
            {
                std::cout << "\t Do you still want to hit ? (y/n) : ";
                std::cin >> response;
                std::cin.ignore(32767, '\n');
                
                if (response == 'y')
                {
                    hit(players[i].cards, deck, 1);
                    
                    // Update player card set values
                    getCount(players[i]);
                    
                    displayStats(players[i], response);
                }
                
            }
            while (response != 'n');
            
            // Get best value and assign to player struct
            h_P_Assign(players[i]);
            std::cout << "\t Your final value is : " << players[i].final_value << std::endl;
        }
        else
        {
            char dealer_hit;
            dealer_hit = 'y';
            
            do
            {
                hit(players[i].cards, deck, 1);
                
                // Update player card set values
                getCount(players[i]);
                
                displayStats(players[i], dealer_hit);
                
                h_P_Assign(players[i]);
            }
            while (players[i].final_value < minimumDealerScore and dealer_hit != 'n');
            
            
            std::cout << "\t Your final value is : " << players[i].final_value << std::endl;
        }
    }
}


void find_winners(player_type players)
{
    /*
     Funciton to display the winners, losers and Tie-ers (if that's even a word)
    */
    
    int dealer_value{ 0 };
    
    // Get dealer final card value
    for (auto player : players)
    {
        if (player.name == "Dealer" and player.final_value < 22)
                dealer_value = player.final_value;
    }
    
    // Get player final card value and compare with dealer's
    for (auto player : players)
    {
        int player_value{ 0 };
        
        if (player.name != "Dealer")
        {
            if (player.final_value < 22)
            {
                player_value = player.final_value ;
                
                if (player_value > dealer_value)
                    std::cout << player.name << ", winner, winner, chicken dinner! \n";
                else if (player_value == dealer_value)
                    std::cout << player.name << ", it's a Tie! \n";
                else if (player_value < dealer_value)
                    std::cout << player.name << ", Dealer has beat you ... \n";
            }
            else if(dealer_value != 0)
                std::cout << player.name << ", Dealer has beat you ... \n";
            
            else
                std::cout << player.name << ", it's a Tie! \n";
        }
    }
}

void playBlackjack(deck_type& deck)
{
    
    // Get number of players (+1 for dealer)
    // and define players object
    int num_players{getNumOfPlayers() + 1};
    player_type players(num_players);
    
    // Get and fill in player information
    // and display current stats.
    fillPlayerInfo(players, deck);

    // Update player/dealer current stata
    for (auto& player : players)
        getCount(player);
    
    // Begin hitting player and settle while
    // displaying scores during each hit
    hit_Participants(players, deck);
    
    // Winner winner chicken dinner
    find_winners(players);
}


int main()
{
    // Define and initialize
    // deck of cards
    deck_type deck;
    createDeck(deck);
    
    // Shuffle deck of cards
    shuffleDeck(deck);
    
    // Begin game of blackjack
    playBlackjack(deck);
    
    return 0;
}

