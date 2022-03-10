//
//  10_15_quiz_question_2.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/8/21.
//  Copyright © 2021 allwyn joseph. All rights reserved.
//

#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

auto greater{
    [](const auto a, const auto b)
    {
        return (a.averageTemperature < b.averageTemperature);
    }
};


struct Season
{
    std::string_view name{};
    double averageTemperature{};
};

int main()
{
    std::array<Season, 4> seasons{
        { { "Spring", 285.0 },
            { "Summer", 296.0 },
            { "Fall", 288.0 },
            { "Winter", 263.0 } }
    };
    
    std::sort(seasons.begin(), seasons.end(), greater);
    
    for (const auto& season : seasons)
    {
        std::cout << season.name << '\n';
    }
    
    return 0;
}
