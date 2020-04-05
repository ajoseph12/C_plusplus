//
//  L_5_5_quiz_question_2.cpp
//  learncpp
//
//  Created by allwyn joseph on 4/2/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>

int main()
{
    char caps = 'A';
    char small = 'a';
    
    while (caps <= 'Z')
    {
        std::cout << caps << " : " << static_cast<int>(caps) << " | "
        << small << " : " << static_cast<int>(small) << std::endl;
        
        ++caps;
        ++small;
    }
    
    return 0;
}
