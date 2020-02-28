//
//  temperatures.cpp
//  codin_games
//
//  Created by allwyn joseph on 2/28/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//
// Source : https://www.codingame.com/training/easy/temperatures

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    int n; // the number of temperatures to analyse
    int close{5527};
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        int t; // a temperature expressed as an integer ranging from -273 to 5526
        cin >> t; cin.ignore();
        
        
        if (abs(t) < abs(close)) close = t;
        
        if (abs(t) ==  abs(close))
        {
            if (t > 0) close = t;
        }
        
    }
    if (close > 5526) close = 0;
    
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    
    cout << close << endl;
}

// Most UpVoted Solution @magaiti
//int main() {
//    istream_iterator<int> it(cin), eos;
//    cout << (++it == eos ? 0 : *min_element (it, eos, closer_to_zero)) << endl;
//}
