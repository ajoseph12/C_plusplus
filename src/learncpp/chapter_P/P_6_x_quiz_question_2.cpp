//
//  P_6_x_quiz_question_2.cpp
//  learncpp
//
//  Created by allwyn joseph on 9/7/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//
#include <algorithm> // std::sort
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct student
{
    int grade{};
    string name{};
};


int get_UserInput()
{
    int num_of_students{0};
    
    do
    {
        cout << "Please enter the number of student you'll want to create records for : ";
        cin >> num_of_students;
        cin.ignore();
        
    }while(num_of_students <= 0);
    
    return num_of_students;
}

void print_struct(vector<student> data)
{
    for(auto student : data)
    {
        cout<< student.name << " got a grade of " << student.grade <<endl;
    }
}

int get_grade()
{
    int grade{0};
    
    cout << "Please enter student grade : ";
    cin >> grade;
    cin.ignore();
    
    return grade;
}

string get_name()
{
    string name;
    
    cout << "Please enter student name : ";
    getline(cin, name);
    
    return name;
}

bool grade_compare(const student a, const student b)
{

    return a.grade > b.grade;
    
}

int main()
{
    int num_studs{get_UserInput()};
    vector<student> data;
    
    for (int i{0}; i < num_studs; i++)
    {
        data.push_back(student());
        
        data[i].name = get_name();
        data[i].grade = get_grade();
    }
    
    std::sort(data.begin(), data.end(), grade_compare);
    print_struct(data);
    
    return 0;
}


