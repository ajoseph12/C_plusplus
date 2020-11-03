//
//  P_6_x_quiz_question_1.cpp
//  learncpp
//  Created by allwyn joseph on 9/7/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//
# include <array>
# include <iostream>
# include <numeric>
# include <stdio.h>

using namespace std;

enum Game
{
    // Items of a player
    ARROWS,
    TORCHES,
    HEALTH_POTIONS,
};


int countTotalItems(array<int, 3> player)
{
    // Counts the total number of items the player has
    return accumulate(player.begin(), player.end(), 0);
}

int main()
{
    array<int, 3> player_1{10, 5, 2};
    
    int items{};
    items = countTotalItems(player_1);
    
    cout << "Number of items the player has = " << items <<endl;
    
    return 0;
}

