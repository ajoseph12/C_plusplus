//
//  O_4_quiz_question_6.cpp
//  learncpp
//
//  Created by allwyn joseph on 3/8/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>

using namespace std;

void printBit(string binary)
{
    constexpr int bits {8};
    
    string  zeros;
    int binaryLen = bits - binary.size();
    
    for (int i; i < binaryLen; i++)
    {
        zeros += "0";
    }
    
    binary = zeros + binary;
    cout << binary <<endl;

    for (int j; j < bits; j++)
    {
        if (j == 4)
        {
            cout<<" ";
            cout<<binary[j];
        }
        else
            cout<<binary[j];
    }
    cout<<endl;
}

int main()
{
    constexpr int dividend { 2 };
    
    int userInput {};
    string store{};
    
    cout << "Enter a number between 0 and 255 : " ;
    cin >> userInput;
    
    while (userInput)
    {
        userInput /= dividend;
        (userInput%dividend)? store+= "1": store+= "0";
    }
    printBit(store);
}
