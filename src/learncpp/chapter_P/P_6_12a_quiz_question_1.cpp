//
//  P_6_12a_quiz_question_1.cpp
//  learncpp
//
//  Created by allwyn joseph on 6/22/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>
#include <iterator>


std::string getUserInput()
{
    std::string userInput;
    std::cout << "Enter a name: ";
    std::getline(std::cin, userInput);
    return userInput;
}

int main()
{
    std::string userInput{ getUserInput() };
    std::string names[]{ "Alex", "Betty", "Caroline", "Dave", "Emily"
        "Fred", "Greg", "Holly" };
    
    for (auto name : names)
    {
        if (name == userInput)
        {
            std::cout << userInput << " was found. \n";
            return 0;
        }
        
    }
    std::cout << userInput << " was not found. \n";
    return 0;
}

// MORE READABLE
//int main()
//{
//    constexpr std::string_view names[]{ "Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly" };
//
//    std::cout << "Enter a name: ";
//    std::string username{};
//    std::cin >> username;
//
//    bool found{ false };
//
//    for (auto name : names)
//    {
//        if (name == username)
//        {
//            found = true;
//            break;
//        }
//    }
//
//    if (found)
//        std::cout << username << " was found.\n";
//    else
//        std::cout << username << " was not found.\n";
//
//    return 0;
//}
