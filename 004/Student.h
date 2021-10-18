#ifndef STUDENT_H
#define STUDENT_H

#include <string>

struct Student
{
  public:
    Student(std::string name, std::string surname, int indexNum, int semestr = 0, float averageGrade = 0);

    std::string name;
    std::string surname;
    int indexNum;
    int semestr;
    float averageGrade;

    std::string toString() const;
};

#endif