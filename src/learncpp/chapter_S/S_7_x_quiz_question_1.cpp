//
//  S_7_x_quiz_question_1.cpp
//  learncpp
//
//  Created by allwyn joseph on 3/28/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include "S_7_x_quiz_question_1.hpp"
#include <iostream>

void printMonster (Monster monster)
{
    cout << "This " << compare(monster);
    cout << " is named "<< monster.monsterName;
    cout << " and has " << monster.monsterHealth << " health. \n";
}

int main()
{
    printMonster({MonsterBreed::MONSTERBREED_ORC, "Rudy", 10});
    printMonster({MonsterBreed::MONSTERBREED_SLIME, "Hardy", 1});
//    int a = MonsterBreed::MONSTERBREED_ORC
    return 0;
}

/*
 *
 *
 * 
 */
