//
//  10_15_quiz_question_1.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/8/21.
//  Copyright © 2021 allwyn joseph. All rights reserved.
//

#include <string>
#include <iostream>
#include <array>
#include <algorithm>

struct Student
{
    std::string name{};
    int points{};
};


int main()
{
    std::array<Student, 8> arr{
        { { "Albert", 3 },
            { "Ben", 5 },
            { "Christine", 2 },
            { "Dan", 8 }, // Dan has the most points (8).
            { "Enchilada", 4 },
            { "Francis", 1 },
            { "Greg", 3 },
            { "Hagrid", 5 } }
    };
    
    const auto best{
        std::max_element(arr.begin(),
                         arr.end(),
                         [](const auto a, const auto b){
                             return (a.points < b.points);
                         })
    };
    std::cout << best->name << " is the best student\n";
    return 0;
}

