//
//  L_5_x_quiz_question_2.hpp
//  learncpp
//
//  Created by allwyn joseph on 4/12/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#ifndef L_5_x_quiz_question_2_hpp
#define L_5_x_quiz_question_2_hpp

#include <iostream>
#include <string>
#include <random>
#include <ctime>

namespace prints
{
    void instructions()
    {
        std::cout << " Welcome to the game of Hi-Lo. The idea is I (your"
                     " machine) will pick a random number between 1 and 100"
                     " and you'll need to guess it within 7 tries. \n \n";
    }
    
    void result(int guessDifference)
    {
        if (guessDifference < 0)
            std::cout << "Your guess is too low \n";
        else if (guessDifference > 0)
            std::cout << "Your guess is too high \n";
    }
}

namespace myRandom
{
    std::mt19937 mersenne { static_cast<std::mt19937::result_type>\
                            (std::time(nullptr))};
}

namespace constants {
    
    constexpr int num_guesses { 8 };
    constexpr int min_range {1};
    constexpr int max_range {100};
}

// Verify user guess
bool checkGuess(int guessDifference)
{
    if (guessDifference == 0)
        return true;
    else
        return false;
}

// Get random number
int getRandomNumber(int min, int max)
{
    std::uniform_int_distribution<> number {min, max};
    
    return number(myRandom::mersenne);
}


#endif /* L_5_x_quiz_question_2_hpp */
