//
//  12_6_quiz_question_1.cpp
//  learncpp
//
//  Created by allwyn joseph on 3/28/22.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

#include <iostream>
#include <cstdint>

class RGBA
{
public:
    using ui = std::uint8_t;
    
private:
    ui m_red {};
    ui m_green {};
    ui m_blue {};
    ui m_alpha {};
    
public:
    RGBA(ui red=0,
         ui green=0,
         ui blue=0,
         ui alpha=255)
    : m_red{ red }, m_green{ green }, m_blue{ blue }, m_alpha{ alpha }
    {
    }
    
    void print()
    {
        std::cout << "r=" << static_cast<int>(m_red) << " "
        << "g=" << static_cast<int>(m_green) << " "
        << "b=" << static_cast<int>(m_blue) << " "
        << "a=" << static_cast<int>(m_alpha) << "\n";
    }
};


int main()
{
    RGBA teal{ 0, 127, 127 };
    teal.print();
    
    return 0;
}
