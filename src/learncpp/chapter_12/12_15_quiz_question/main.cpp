//
//  main.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/26/22.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

#include "trails_1.hpp"
#include "trails_2.hpp"

#include <iostream>

int main()
{
    Point3d p{1.0, 2.0, 3.0};
    Vector3d v{2.0, 2.0, -3.0};
    
    p.print();
    p.moveByVector(v);
    p.print();
    
    return 0;
}
