//
//  quiz_question_3.cpp
//  src
//
//  Created by allwyn joseph on 2/18/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//
// Link to question : https://tinyurl.com/wo65oor

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
    
    return NULL;
}


int main()
{
    double val_1{}, val_2{}, ans{};
    char exp{};
    
    val_1 = enterValue();
    val_2 = enterValue();
    exp   = enterExp();
    ans   = getAnswer(val_1, val_2, exp);
    
    if (ans != NULL)
        cout << val_1 << " " << exp << " " << val_2 << " is " << ans <<endl;
    
    return 0;
    
}

