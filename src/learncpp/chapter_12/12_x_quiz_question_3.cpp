//
//  12_x_quiz_question_3.cpp
//  learncpp
//
//  Created by Allwyn Joseph on 15/05/2022.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

#include <ctime> // for time()
#include <cstdlib> // for rand() and srand()
#include <iostream>

class Monster
{
public:
    enum class Type
    {
        Dragon,
        Globin,
        Ogre,
        Orc,
        Skeleton,
        Troll,
        Vampire,
        Zombie,
        max_moster_types
    };

private:
    Type m_type{};
    std::string m_name{};
    std::string m_roar{};
    int m_hitPoints{};

public:
    Monster(Type type, std::string name, std::string roar, int hitPoints)
    : m_type{ type }, m_name{ name }, m_roar{ roar }, m_hitPoints{ hitPoints }
    {}

    std::string getTypeString(Type monster)
    {
        switch (monster)
        {
        case Type::Dragon:
            return "Dragon";
        case Type::Globin:
            return "Globin";
        case Type::Ogre:
            return "Ogre";
        case Type::Orc:
            return "Orc";
        case Type::Skeleton:
            return "Skeleton";
        case Type::Troll:
            return "Troll";
        case Type::Vampire:
            return "Vampire";
        case Type::Zombie:
            return "Zombie";

        default:
            return "Undefined";
        }
    }

    void print()
    {
        std::cout << m_name << " the " << getTypeString(m_type) << " has "
            << m_hitPoints << " and says " << m_roar << "\n";
    }
    
};

class MonsterGenerator
{
public:
    static Monster generateMonster()
    {
        static std::string s_names[]{ "Blarg", "Moog", "Pksh", "Tyrn", "Mort", "Hans" };
        static std::string s_roars[]{ "*ROAR*", "*peep*", "*squeal*", "*whine*", "*hum*", "*burp*"};
        
        int randomIndex{ getRandomNumber(0, sizeof(s_names)/sizeof(s_names[0]) - 1)};
        int randomHitPoints{ getRandomNumber(0, 100)};
        auto randMonster{ static_cast<Monster::Type>(getRandomNumber(0, static_cast<int>(Monster::Type::max_moster_types) - 1)) };
        
        return {randMonster, s_names[randomIndex], s_roars[randomIndex], randomHitPoints};
    }
    
    static int getRandomNumber(int min, int max)
    {
        static constexpr double fraction{ 1.0 / (static_cast<double>(RAND_MAX) + 1.0) };
        return static_cast<int>(std::rand() * fraction * (max - min + 1) + min);
    };
};

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
    std::rand(); // If using Visual Studio, discard first random value

    Monster m{ MonsterGenerator::generateMonster() };
    m.print();

    return 0;
}
