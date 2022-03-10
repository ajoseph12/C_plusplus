//
//  P_6_x_quiz_question_2.cpp
//  learncpp
//
//  Created by allwyn joseph on 9/7/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


struct Student
{
    std::string prenom{};
    int grade{};
};
using vector_type = std::vector<Student>;


int getAndCheckInt(int number)
/**
 * Get and check validity of integer inputs by the user
 *
 * @return `number` if success else 0
 */
{
    cin >> number;
    
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "\tInvalid input please try again.";
        return 0;
    }
    else
    {
        cin.ignore(32767, '\n');
        return number;
    }
}


int getNumberOfStudents()
/**
 * Get user input for number of students
 *
 * @return `numberOfStudents`
 */
{
    while (true)
    {
        cout << "\nHow many student do you want to seek to enter into the database? ";
        
        int numberOfStudents{};
        
        numberOfStudents = getAndCheckInt(numberOfStudents);
        
        if (numberOfStudents)
            return numberOfStudents;
    }
}

int getStudentGrade()
/**
 * Get user input for grade of student
 *
 * @return `gradeOfStudent`
 */
{
    while (true)
    {
        cout << "\tPlease enter grade of student ";
        
        int gradeOfStudents{};
        
        gradeOfStudents = getAndCheckInt(gradeOfStudents);
        
        if (gradeOfStudents)
            return gradeOfStudents;
    }
}

string getStudentPrenom()
/**
 * Get user input for prenom of student
 *
 * @return `prenomOfStudents`
 */
{
    cout << "\tPlease enter name of student: ";
    string prenomOfStudent;
    getline(cin, prenomOfStudent);
    return prenomOfStudent;
}


void getStudentNameGrade(vector_type &student_db)
/**
 * Get user input for number of student
 *
 * @return `numberOfStudents`
 */
{
    int student_num {1};
    for (auto &student: student_db)
    {
        cout << "\nInformation concerning student " << student_num << '\n';
        student.prenom = getStudentPrenom();
        student.grade = getStudentGrade();
        ++student_num;
    }
}

bool great(Student a, Student b)
{
    return (a.grade > b.grade);
}

void printStudentNameGrade(vector_type student_db)
/**
 * Print student name and grade in descending order of grade.
 *
 * @param `student_db` vector of structs
 */
{
    std::sort(student_db.begin(), student_db.end(), great);
    
    for (auto student : student_db)
        cout << student.prenom << " got a grade of "<< student.grade << "\n";
    
}


int main()
{
    
    int numberOfStudents {getNumberOfStudents()};
    
    vector_type student_db(numberOfStudents);
    
    getStudentNameGrade(student_db);
    
    printStudentNameGrade(student_db);
    
    return 0;
}


