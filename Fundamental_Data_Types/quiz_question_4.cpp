//
//  quiz_question_4.cpp
//  Intro_to_c++
//
//  Created by allwyn joseph on 2/14/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>

using namespace std;

double enterValue()
{
    cout << "Enter a double value : ";
    double value{};
    cin >> value;
    
    return value;
}

char enterExp()
{
    cout << "Enter one for the following : +, -, *, or / : ";
    char exp{};
    cin >> exp;
    
    return exp;
}

double getAnswer(double val_1, double val_2, char exp)
{
    
    if (exp == '*') return val_1*val_2;
    else if (exp == '+') return val_1+val_2;
    else if (exp == '-') return val_1-val_2;
    else if (exp == '/') return val_1/val_2;
    
    return 0;
}


int main()
{
    double val_1{}, val_2{}, ans{};
    char exp{};
    
    val_1 = enterValue();
    val_2 = enterValue();
    exp   = enterExp();
    ans   = getAnswer(val_1, val_2, exp);
    
    if (ans != 0)
        cout << val_1 << " " << exp << " " << val_2 << " is " << ans <<endl;
    
    return 0;
    
}
