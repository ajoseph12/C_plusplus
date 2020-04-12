//
//  L_5_x_quiz_question_2.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/12/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include "L_5_x_quiz_question_2.hpp"


// Get user guess
int getUserGuess(int guessNumber)
{
    while (true)
    {
        std::cout << " Guess #" << guessNumber << " :\t";
        int guess;
        std::cin >> guess;
    
        if (std::cin.fail())
        {
            std::cin.clear(); // return back to normal state
            std::cin.ignore(32767, '\n'); // remove any extraneous inputs
            std::cout << " Invalid input entered, please try again .. \n";
        }
        else
        {
            std::cin.ignore(327767, '\n');
            return guess;
        }
    }
}


// Check if user wants to play again
bool getRePlay()
{
    char input;
    
    do
    {
        std::cout << " Would you like to play again (y/n)? ";
        std::cin >> input;
        
    }while (input != 'y' && input != 'n');
    
    return (input == 'y');
}

bool playGame(int random_number)
{
    for (int i {1}; i <= constants::num_guesses; ++i)
    {
        // Get user input guess
        int userGuess { getUserGuess( i ) };
        
        // Check if user guess equals random number
        bool result { checkGuess(userGuess - random_number) };
        
        // If user guessed right he/she wins and exit else continue
        if (result)
            return true;
        else if (!result)
            prints::result(userGuess - random_number);
    }
    return false;
}


int main()
{

    prints::instructions();
    
    do
    {
        int random_number {getRandomNumber(constants::min_range, \
                                           constants::max_range)};
        bool won { playGame(random_number) };

        if (won)
            std::cout << "Correct! You win! \n";
        else if (!won)
            std::cout << "Sorry, you lose.  The correct number was " \
            << random_number <<" .\n";

    }while(getRePlay()); // check if useer want to play again
    
    std::cout << "Thank you for playing. \n";
    return 0;
}


