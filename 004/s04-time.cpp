#include "Time.h"
#include <iostream>
#include <string>

Time::Time(int h, int m, int s) 
{
    this -> h = h;
    this -> m = m;
    this -> s = s;

    if(this -> h < 0) this -> h = 0;
    else this -> h = this -> h % 24;

    if(this -> m < 0) this -> m = 0;
    else this -> m = this -> m % 60;

    if(this -> s < 0) this -> s = 0;
    else this -> s = this -> s % 60;
}

void Time::nextHour()
{
    h++;

    if(h == 24) h = 0;
}

void Time::nextMinute()
{
    m++;
    if(m == 60) m = 0;
}

void Time::nextSecond()
{
    s++;
    if(s == 60) s = 0;
}

std::string ldZero(int num)
{
    if(num < 10) {
        return "0" + std::to_string(num);
    } else {
        return std::to_string(num);
    }
}

std::string Time::toString() const
{
    return ldZero(h) + ":" + ldZero(m) + ":" + ldZero(s);
}

std::string toString(TimeOfDay timeOfDay)
{
    switch(timeOfDay) 
    {
        case TimeOfDay::morning:
            return "morning";
            break;

        case TimeOfDay::day:
            return "day";
            break;
            
        case TimeOfDay::evening:
            return "evening";
            break;
            
        case TimeOfDay::night:
            return "night";
            break;
        
        default:
            return "err";
            break;
    }
}

TimeOfDay Time::timeOfDay() const
{
    if(h < 7) return TimeOfDay::night;
    else if(h < 10) return TimeOfDay::morning;
    else if(h < 17) return TimeOfDay::day;
    else if(h < 22) return TimeOfDay::evening;
    else if(h < 24) return TimeOfDay::night;
    else return TimeOfDay::day;
}

Time Time::operator+(Time const& time) const
{
    Time _time;
    _time.h = h + time.h;
    _time.m = m + time.m;
    _time.s = s + time.s;

    if(_time.h < 0) _time.h = 0;
    else _time.h = _time.h % 24;

    if(_time.m < 0) _time.m = 0;
    else _time.m = _time.m % 60;

    if(_time.s < 0) _time.s = 0;
    else _time.s = _time.s % 60;

    return _time;
}

Time Time::operator-(Time const& time) const
{
    Time _time;
    _time.h = h - time.h;
    _time.m = m - time.m;
    _time.s = s - time.s;

    if(_time.h < 0) _time.h = 0;
    else _time.h = _time.h % 24;

    if(_time.m < 0) _time.m = 0;
    else _time.m = _time.m % 60;

    if(_time.s < 0) _time.s = 0;
    else _time.s = _time.s % 60;

    return _time;
}

bool Time::operator<(Time const& time) const
{
    if(h != time.h) return h < time.h;
    else if(m != time.m) return m < time.m;
    else if(s != time.s) return s < time.s;
    else return false;
}

bool Time::operator>(Time const& time) const
{
    if(h != time.h) return h > time.h;
    else if(m != time.m) return m > time.m;
    else if(s != time.s) return s > time.s;
    else return false;
}

bool Time::operator==(Time const& time) const
{
    return h == time.h && m == time.m && s == time.s;
}

bool Time::operator!=(Time const& time) const
{
    return h != time.h && m != time.m && s != time.s;
}

uint64_t Time::countSeconds() const 
{
    return h * 3600 + m * 60 + s;
}

uint64_t Time::countMinutes() const
{
    int min = h * 60 + m;
    if(s != 0) min++;
    return min;
}

Time Time::timeToMidnight() const
{
    Time _time = *this;
    if(s > 0) _time.nextMinute();
    if(m > 0) _time.nextHour();

    return Time(24, 60, 60) - _time;
}

int main(int argc, char *argv[])
{
    Time time = Time(23, 59, 59);

    std::cout << time.toString() << "\n";
    time.nextHour();
    std::cout << time.toString() << "\n";
    time.nextMinute();
    std::cout << time.toString() << "\n";
    time.nextSecond();
    std::cout << time.toString() << "\n\n";

    time = Time(-1, 0, 0);

    for(int i = 0; i<24; i++) {
        time.nextHour();
        std::cout << time.toString() << ": " << toString(time.timeOfDay()) << "\n";
    }
    std::cout << "\n";

    time = Time(0, 0, 0);
    Time timeA = Time(10, 20, 30);
    Time timeB = Time(5, 10, 15);

    std::cout << time.toString() << "\n";
    time = timeA + timeB;
    std::cout << time.toString() << "\n";
    time = timeA - timeB;
    std::cout << time.toString() << "\n";

    std::cout << std::to_string(timeA > timeB) << "\n";
    std::cout << std::to_string(timeA < timeB) << "\n";
    std::cout << std::to_string(timeA == timeB) << "\n";
    std::cout << std::to_string(timeA != timeB) << "\n\n";

    time = Time(1, 1, 10);
    std::cout << std::to_string(time.countSeconds()) << "\n";
    std::cout << std::to_string(time.countMinutes()) << "\n";

    time = Time(1, 1, 1);
    std::cout << time.timeToMidnight().toString() << "\n";
    

    return 0;
}
