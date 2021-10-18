#ifndef TIME_H
#define TIME_H

#include <string>

enum class TimeOfDay {morning, day, evening, night};

struct Time
{
  public:
    Time(int h = 0, int m = 0, int s = 0);

    int h;
    int m;
    int s;

    Time operator+(Time const&) const;
    Time operator-(Time const&) const;
    bool operator<(Time const&) const;
    bool operator>(Time const&) const;
    bool operator==(Time const&) const;
    bool operator!=(Time const&) const;

    uint64_t countSeconds() const;
    uint64_t countMinutes() const;
    Time timeToMidnight() const;


    void nextHour();
    void nextMinute();
    void nextSecond();

    TimeOfDay timeOfDay() const;

    std::string toString() const;
};

#endif