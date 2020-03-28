//
//  S_7_x_quiz_question_1.hpp
//  learncpp
//
//  Created by allwyn joseph on 3/28/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#ifndef S_7_x_quiz_question_1_hpp
#define S_7_x_quiz_question_1_hpp

#include <iostream>
#include <string>

using namespace std;

enum class MonsterBreed
{
    MONSTERBREED_OGRE,
    MONSTERBREED_DRAGON,
    MONSTERBREED_ORC,
    MONSTERBREED_GIANTSPIDER,
    MONSTERBREED_SLIME,
};

struct Monster
{
    MonsterBreed breed;
    string monsterName;
    int monsterHealth;
};

string compare(Monster monster)
{
    if (monster.breed == MonsterBreed::MONSTERBREED_OGRE)
        return "OGRE";
    else if (monster.breed == MonsterBreed::MONSTERBREED_DRAGON)
        return "DRAGON";
    else if (monster.breed == MonsterBreed::MONSTERBREED_ORC)
        return "ORC";
    else if (monster.breed == MonsterBreed::MONSTERBREED_GIANTSPIDER)
        return "GIANT SPIDER";
    else if (monster.breed == MonsterBreed::MONSTERBREED_SLIME)
        return "SLIME";
    return "???";
}

#endif /* S_7_x_quiz_question_1_hpp */
