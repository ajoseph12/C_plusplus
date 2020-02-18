//
//  quiz_question_4.cpp
//  learncpp
//
//  Created by allwyn joseph on 2/18/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "constants.hpp"

using namespace std;

double calcDist(int seconds);

int main()
{
    for (int i=0; i<6; i++)
    {
        cout << "At " << i << " seconds, the ball is at height: " << calcDist(i) << " meters \n";
    }
}

double calcDist(int seconds)
{
    double dist {};
    dist = (constants::g * pow(seconds, 2))/2;
    
    return  (100 - dist > 0) ? 100 - dist : 0;
}
