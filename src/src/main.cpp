//
//  main.cpp
//  src
//
//  Created by allwyn joseph on 2/18/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>

using namespace std;

int main()
{
    string a = "1000011";
    
    int i{0};
    int j{0};
    char pointer_hold{};
    
    while (i < a.size())
    {
        pointer_hold = a[i];
        if (pointer_hold == '0') cout << "00 0";
        if (pointer_hold == '1') cout << "0 0";
        
        j = i;
        while (j < a.size())
        {
            j++;
            if (a[j] == pointer_hold) cout << "0";
            else {
                cout << " ";
                break;
            }
        }
        i = j;
    }
}
