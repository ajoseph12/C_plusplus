//
//  thor.cpp
//  codin_games
//
//  Created by allwyn joseph on 2/28/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//
// Source : https://www.codingame.com/training/easy/power-of-thor-episode-1

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    int lightX; // the X position of the light of power
    int lightY; // the Y position of the light of power
    int initialTX; // Thor's starting X position
    int initialTY; // Thor's starting Y position
    cin >> lightX >> lightY >> initialTX >> initialTY; cin.ignore();
    
    // Dictionary up down and left right directions
    // Inspired from the most upvoted Solution
    initialTX = lightX - initialTX;
    initialTY = lightY - initialTY;
    
    // game loop
    while (1) {
        // cerr << "1st Debug messages..." <<lightX << initialTX << endl;
        
        int remainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        cin >> remainingTurns; cin.ignore();
        
        // Get directions
        if (initialTY > 0)
        {
            cout << "S";
            initialTY--;
            
        }
        if (initialTY < 0)
        {
            cout << "N";
            initialTY++;
        }
        
        if (initialTX > 0)
        {
            cout << "E";
            initialTX--;
        }
        if (initialTX < 0)
        {
            cout << "W";
            initialTX++;
        }
        
        cout << endl;
        
        
        // A single line providing the move to be made: N NE E SE S SW W or NW
        
        // cerr << "2nd Debug messages..." <<diffX << diffY << endl;
        
        
    }
}

// Most UpVoted Solution @ma
//int main()
//{
//    int lightX; // the X position of the light of power
//    int lightY; // the Y position of the light of power
//    int initialTX; // Thor's starting X position
//    int initialTY; // Thor's starting Y position
//    cin >> lightX >> lightY >> initialTX >> initialTY; cin.ignore();
//    
//    int dx = lightX - initialTX;
//    int dy = lightY - initialTY;
//    
//    // game loop
//    while (1) {
//        int remainingTurns;
//        cin >> remainingTurns; cin.ignore();
//        
//        // Write an action using cout. DON'T FORGET THE "<< endl"
//        // To debug: cerr << "Debug messages..." << endl;
//        if (dy > 0) {
//            cout << "S";
//            dy--;
//        }
//        if (dy < 0) {
//            cout << "N";
//            dy++;
//        }
//        
//        if (dx > 0) {
//            cout << "E";
//            dx--;
//        }
//        if (dx < 0) {
//            cout << "W";
//            dx++;
//        }
//        
//        cout << endl; // A single line providing the move to be made: N NE E SE S SW W or NW
//    }
//}
