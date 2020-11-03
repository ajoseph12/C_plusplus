//
//  P_6_9a_quiz_question_1.cpp
//  learncpp
//
//  Created by allwyn joseph on 5/18/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int getNumNames()
{
    cout <<"How many names you which to enter : ";
    int num{};
    cin >> num;
    
    return num;
}

void getNames(string* names, int length)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    for (int i{0}; i < length; ++i )
    {
        cout <<"Enter name " << i + 1 << ":";
        getline(cin, names[i] );
    }
}

void printNames(string* names, int length)
{
    cout << "\nHere is your sorted list:\n";
    
    for (int i{ 0 }; i < length; ++i)
        cout << "Name #" << i + 1 << ":" << names[i] << "\n";
}

int main()
{
    int length{ getNumNames() };
    
    auto *names{ new string[length]{}};

    getNames(names, length);
    std::sort(names, names + length);
    printNames(names, length);
    
    return 0;
}
