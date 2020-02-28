//
//  mars_lander.cpp
//  codin_games
//
//  Created by allwyn joseph on 2/28/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//
// Source : https://www.codingame.com/training/easy/mars-lander-episode-1

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    int surfaceN; // the number of points used to draw the surface of Mars.
    cin >> surfaceN; cin.ignore();
    for (int i = 0; i < surfaceN; i++) {
        int landX; // X coordinate of a surface point. (0 to 6999)
        int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> landX >> landY; cin.ignore();
    }
    
    // game loop
    while (1) {
        int X;
        int Y;
        int hSpeed; // the horizontal speed (in m/s), can be negative.
        int vSpeed; // the vertical speed (in m/s), can be negative.
        int fuel; // the quantity of remaining fuel in liters.
        int rotate; // the rotation angle in degrees (-90 to 90).
        int power; // the thrust power (0 to 4).
        cin >> X >> Y >> hSpeed >> vSpeed >> fuel >> rotate >> power; cin.ignore();
        
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        if (vSpeed > 0 && power > 0) power--;
        if (vSpeed < -40 && power < 4) power++;
        // 2 integers: rotate power. rotate is the desired rotation angle (should be 0 for level 1), power is the desired thrust power (0 to 4).
        cout << rotate << " " << power << endl;
    }
}
// Most UpVoted Solution @LeafarCoder
//int main()
//{
//    int surfaceN; // the number of points used to draw the surface of Mars.
//    cin >> surfaceN; cin.ignore();
//    for (int i = 0; i < surfaceN; i++) {
//        int landX; // X coordinate of a surface point. (0 to 6999)
//        int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
//        cin >> landX >> landY; cin.ignore();
//    }
//    
//    // game loop
//    while (1) {
//        int X;
//        int Y;
//        int hSpeed; // the horizontal speed (in m/s), can be negative.
//        int vSpeed; // the vertical speed (in m/s), can be negative.
//        int fuel; // the quantity of remaining fuel in liters.
//        int rotate; // the rotation angle in degrees (-90 to 90).
//        int power; // the thrust power (0 to 4).
//        cin >> X >> Y >> hSpeed >> vSpeed >> fuel >> rotate >> power; cin.ignore();
//        
//        // Write an action using cout. DON'T FORGET THE "<< endl"
//        // To debug: cerr << "Debug messages..." << endl;
//        
//        cout << "0 "<<(vSpeed>-40?(max(0,power-1)):min(4,power+1)) << endl; // rotate power. rotate is the desired rotation angle. power is the desired thrust power.
//    }
//}
