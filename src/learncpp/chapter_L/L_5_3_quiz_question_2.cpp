//
//  L_5_3_quiz_question_2.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/1/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>

enum class Animal
{
    PIG,
    CHICKEN,
    GOAT,
    CAT,
    DOG,
    OSTRICH
};

std::string get_AnimalName(Animal animal)
{
    switch (animal)
    {
        case Animal::PIG:
            return " Pig ";
        case Animal::CHICKEN:
            return " Chicken ";
        case Animal::GOAT:
            return " Goat ";
        case Animal::CAT:
            return " Cat ";
        case Animal::DOG:
            return " Dog ";
        case Animal::OSTRICH:
            return " Ostrich ";
            
        default:
            std::cout << "get_AnimalName() : Unhandled case\n";
            break;
    }
}

void printNumberOfLegs(Animal animal)
{
    
    std::cout << "A" << get_AnimalName(animal) << "has";
    
    switch (animal)
    {
        case Animal::CHICKEN:
        case Animal::OSTRICH:
            std::cout << " 2 ";
            break;
            
        case Animal::PIG:
        case Animal::GOAT:
        case Animal::CAT:
        case Animal::DOG:
            std::cout << " 4 ";
            break;
            
        default:
            std::cout << "get_AnimalName() : Unhandled case\n";
            break;
    }
    std::cout << "legs\n";
}

int main()
{
    printNumberOfLegs(Animal::CAT);
    printNumberOfLegs(Animal::CHICKEN);
    return 0;
}
