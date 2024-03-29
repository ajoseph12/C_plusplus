//
//  trails_2.hpp
//  learncpp
//
//  Created by allwyn joseph on 4/1/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#ifndef trails_2_hpp
#define trails_2_hpp

# include "trails_1.hpp"

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


#endif /* trails_2_hpp */
