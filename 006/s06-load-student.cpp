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
    std::ifstream file("s06-store-student_output.txt");

    std::string line;
    
    getline(file, line);

    std::string name = line.substr(0, line.find(' '));
    std::string surname = line.substr(line.find(' ') + 1);

    std::string indexNum;
    getline(file, indexNum);

    std::string semestr;
    getline(file, semestr);

    std::string averageGrade;
    getline(file, averageGrade);

    Student student = Student(name, 
        surname,
        std::stoi(indexNum),
        std::stoi(semestr),
        std::stof(averageGrade));

    std::cout << student.toString();

    file.close();

    return 0;
}
