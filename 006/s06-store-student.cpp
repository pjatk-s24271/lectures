#include "Student.h"
#include <iostream>
#include <string>
#include <fstream>

Student::Student(std::string name, std::string surname, int indexNum, int semestr, float averageGrade) 
{
    this -> name = name;
    this -> surname = surname;
    this -> indexNum = indexNum;
    this -> semestr = semestr;
    this -> averageGrade = averageGrade;
}

std::string Student::toString() const
{
    return "Name:" + name + 
    " Surname:" + surname + 
    " IndexNum:" + std::to_string(indexNum) + 
    " Semester:" + std::to_string(semestr) + 
    " averageGrade:" + std::to_string(averageGrade);
}

int main(int argc, char *argv[])
{
    Student student = Student("Jan", "Kowalski", 24271);

    std::ofstream outfile;
    outfile.open("s06-store-student_output.txt", std::ios::out | std::ios::trunc);

    outfile << student.name << " " << student.surname << "\n";
    outfile << std::to_string(student.indexNum) << "\n";
    outfile << std::to_string(student.semestr) << "\n";
    outfile << std::to_string(student.averageGrade) << "\n";

    outfile.close();
    
    return 0;
}
