//
//  Vector3d.hpp
//  learncpp
//
//  Created by allwyn joseph on 4/26/22.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

#ifndef Vector3d_hpp
#define Vector3d_hpp

# include "Point3d.hpp"
# include <iostream>

class Vector3d
{
private:
    double m_x{};
    double m_y{};
    double m_z{};
    
public:
    Vector3d(double x = 0.0, double y = 0.0, double z = 0.0);
    
    void print() const;
    
    friend void Point3d::moveByVector(const Vector3d& v);
};


#endif /* Vector3d_hpp */
