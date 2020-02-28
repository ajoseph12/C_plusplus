//
//  ascii_art.cpp
//  codin_games
//
//  Created by allwyn joseph on 2/28/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//
// Source : https://www.codingame.com/training/easy/ascii-art

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore();
    string T;
    getline(cin, T);
    
    
    for (int i = 0; i < H; i++) {
        
        string ROW;
        string out;
        getline(cin, ROW);
        
        int temp_diff;
        string temp_str;
        
        for (int j = 0; j < T.size(); j++){
            
            temp_diff   =  toupper(T[j]) -  toupper('A');
            if (temp_diff < 0) temp_diff=26;
            temp_str.assign(ROW, temp_diff*L, L);
            out.append(temp_str);
        }
        cout <<out <<endl;
        
    }
    
}
// Most UpVoted Solution @Plopx
//int main()
//{
//    int L;
//    int H;
//    string T;
//    cin >> L; cin.ignore();
//    cin >> H; cin.ignore();
//    getline(cin, T);
//    for (int i = 0; i < H; i++) {
//        string ROW;
//        getline(cin, ROW);
//        
//        for (char c: T) {
//            int index = isalpha(c) ? toupper(c) - 'A' : 26;
//            cout << ROW.substr(L * index, L);
//        }
//        cout << endl;
//    }
//}
