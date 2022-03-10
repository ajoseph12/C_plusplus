//
//  trails_2.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/1/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

int g_x { 2 }; // non-constant globals have external linkage by default
extern constexpr int g_y { 3 }; // this extern gives g_y external linkage
