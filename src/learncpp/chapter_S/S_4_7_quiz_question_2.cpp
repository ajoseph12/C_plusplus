//
//  S_4_7_quiz_question_2.cpp
//  learncpp
//
//  Created by allwyn joseph on 3/28/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>

using namespace std;

struct Fraction
{
    int numerator;
    int denominator;
};

Fraction assignValues()
{
    Fraction temp;
    cout << " Please input a numerator \t \t : ";
    cin >> temp.numerator;
    cout << " Please input a denominator \t : ";
    cin >> temp.denominator;
    
    return temp;
}

void multiply (Fraction fraction_1, Fraction fraction_2)
{
    int mult_numerator { fraction_1.numerator * fraction_2.numerator };
    int mult_denominator { fraction_1.denominator * fraction_2.denominator };
    
    cout << " Result : " << static_cast<double>(mult_numerator) / (mult_denominator) << "\n";
    
}

int main()
{
    Fraction fraction_1 { assignValues() };
    Fraction fraction_2 { assignValues() };
    
    multiply(fraction_1, fraction_2);
    
    return 0;
}
