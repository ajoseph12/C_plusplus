//
//  Point3d.hpp
//  learncpp
//
//  Created by allwyn joseph on 4/26/22.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

#ifndef Point3d_hpp
#define Point3d_hpp

#include <iostream>

class Vector3d;

class Point3d
{
private:
    double m_x{};
    double m_y{};
    double m_z{};
    
public:
    Point3d(double x = 0.0, double y = 0.0, double z = 0.0);
    
    void print() const;
    
    void moveByVector(const Vector3d& v);
};



#endif /* Point3d_hpp */
