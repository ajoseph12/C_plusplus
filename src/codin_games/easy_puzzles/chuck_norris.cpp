//
//  chuck_norris.cpp
//  codin_games
//
//  Created by allwyn joseph on 2/25/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//
// Source : https://www.codingame.com/training/easy/chuck-norris

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;


int main()
{
    string strInput, a;
    cout << "Enter a string : ";
    getline(cin, strInput);
    
    // Convert binary representation to a string
    // to be able to loop over
    for (int i = 0; i < strInput.size(); ++i)
    {
        a += bitset<7>(strInput[i]).to_string();
    }
    
    // Initializations
    int i{0};
    int j{0};
    char pointer_hold{};
    
    // Begin first pointer
    while (i < a.size())
    {
        // Ouput 00 if pointer at 0 and output
        // 0 if pointer at 1
        pointer_hold = a[i];
        if (pointer_hold == '0') cout << "00 0";
        if (pointer_hold == '1') cout << "0 0";
        
        j = i;
        
        // Begin second pointer
        while (j < a.size())
        {
            j++;
            // Output 0s if pointers i and j point
            // to the same value
            if (a[j] == pointer_hold) cout << "0";
            // if j has arrived to the end of the
            // sting, break it
            else if (j == a.size()){
                cout<<""<<endl;
                break;
            }
            // Else add space and continue loop
            else {
                cout << " ";
                break;
            }
        }
        i = j;
    }
}

// Most UpVoted Solution @vamPierchen
//int main()
//{
//    string MESSAGE;
//    cout << "Enter string : ";
//    getline(cin, MESSAGE);
//
//    bool pbit = 0x40;
//    cout <<pbit <<endl;
//    cout << (pbit ? "0 " : "00 ");
//    for (auto c: MESSAGE)
//    {
//        for (unsigned char bm = 0x40; bm != 0; bm /= 2)
//        {
//            bool bit = (c & bm);
//            cout << ((bit == pbit) ? "0"
//                     : (pbit = bit) ? " 0 0"
//                     : " 00 0");
//        }
//    }
//    cout << endl;
//    return 0;
//}
