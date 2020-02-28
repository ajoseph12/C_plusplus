//
//  the_descent.cpp
//  codin_games
//
//  Created by allwyn joseph on 2/28/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//
// Source : https://www.codingame.com/training/easy/the-descent

#include <stdio.h>

int main()
{
    
    // game loop
    while (1) {
        int max_MtIdx{0};
        int max_MtHt{0};
        for (int i = 0; i < 8; i++) {
            int mountainH; // represents the height of one mountain.
            cin >> mountainH; cin.ignore();
            
            
            if (mountainH > max_MtHt){
                max_MtHt = mountainH;
                max_MtIdx = i;
            }
        }
        
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        cerr << "max_MtIdx : " << max_MtIdx;
        cout << max_MtIdx << endl; // The index of the mountain to fire on.
    }
}

// Most UpVoted Solution @Caduchon
//int main()
//{
//    while(true)
//    {
//        unsigned short int max_i = 0;
//        unsigned short int max_h = 0;
//        for(unsigned short int i = 0; i < 8; ++i)
//        {
//            unsigned short int h;
//            std::cin >> h; std::cin.ignore();
//            if(h > max_h)
//            {
//                max_h = h;
//                max_i = i;
//            }
//        }
//        std::cout << max_i << std::endl;
//    }
//    
//    return 0;
//}
