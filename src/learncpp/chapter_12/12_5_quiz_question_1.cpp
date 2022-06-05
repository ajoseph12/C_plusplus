//
//  12_5_quiz_question_1.cpp
//  learncpp
//
//  Created by allwyn joseph on 3/25/22.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

#include <iostream>
#include <string>

class Ball
{
private:
    std::string m_color {};
    double m_radius {};
    
public:
    // Constructor that's called if no values are passed,
    // only color is passed or both clor and radius is passed
    Ball(std::string color = "black", double radius = 10.0)
    {
        m_color = color;
        m_radius = radius;
    }
    
    // Constructor that's called only if radius is passed
    Ball(double radius)
    {
        m_color = "back";
        m_radius = radius;
    }
    
    void print()
    {
        std::cout << "colour: " << m_color << ", radius: " << m_radius <<"\n";
    }
};

int main()
{
    Ball def{};
    def.print();
    
    Ball blue{ "blue" };
    blue.print();
    
    Ball twenty{ 20.0 };
    twenty.print();
    
    Ball blueTwenty{ "blue", 20.0 };
    blueTwenty.print();
    
    return 0;
}
