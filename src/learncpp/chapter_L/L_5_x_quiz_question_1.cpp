//
//  L_5_x_quiz_question_1.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/12/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include "L_5_x_quiz_question_1.hpp"

#include <iostream>

// Get initial height from the user and return it
double getInitialHeight()
{
    std::cout << "Enter height of tower in meters : ";
    double initialHeight {};
    std::cin >> initialHeight;
    
    return initialHeight;
}

int getSeconds()
{
    std::cout << "Enter the time (in seconds) the ball should be falling"
    " for : ";
    int seconds {};
    std::cin >> seconds;
    
    return seconds;
}

// Calculate and return height from the ground after "secondsPassed" seconds
double calculateHeight(double initialHeight, int secondsPassed)
{
    // Using fromula [ s = u * t + (a * t^2) / 2 ], here u(initial
    // velocity) = 0
    double distanceFallen {(myConstants::gravity * secondsPassed *
                            secondsPassed)};
    double currentHeight {initialHeight - distanceFallen};
    
    return currentHeight;
}

void printHeight(double height, int secondsPassed)
{
    if (height > 0.0)
        std::cout << "At " << secondsPassed << " seconds, the ball is at"
        " height \t: " << height << "\t meters \n";
    else
        std::cout <<  "At " << secondsPassed << " seconds, the ball is on"
        " the ground.\n";
}

void calculateAndPrintHeight(double initialHeight, int secondsPassed)
{
    double height {calculateHeight(initialHeight, secondsPassed)};
    printHeight(height, secondsPassed);
}

int main()
{
    const double initialHeight{getInitialHeight()};
    int seconds (getSeconds());
    
    for (int i=0; i <=  seconds; ++i)
    {
        calculateAndPrintHeight(initialHeight, i);
    }
    return 0;
}
