//
//  5_1_quiz_question_2.cpp
//  learncpp
//
//  Created by allwyn joseph on 2/20/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>

using namespace std;

int main()
{
    cout << "Enter an integer : ";
    int value {};
    cin >> value;
    
//    (value%2 == 0) ? cout << value << " is even \n": cout << value << " is odd \n";
    if (value%2 == 0)
        cout << value << " is even \n";
    else
        cout << value <<" is odd \n";
}
