//
//  trails_2.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/1/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include "trails_2.hpp"

#include <iostream>

Vector3d::Vector3d(double x, double y, double z)
    : m_x{x}, m_y{y}, m_z{z}
{}

void Vector3d::print() const
{
    std::cout << "Vector(" << m_x << " , " << m_y << " , " << m_z << ")\n";
}
