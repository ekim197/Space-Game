#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <iostream>

class Date{
    time_t date;

    // Private functions
    time_t slashDashToTime(const char* timeChar);
    time_t monthToTime(const char* timeChar);
    int monthToInt(const char* monthName);

public:
    // Constructors and Destructor
    Date();
    Date(const Date& objTime) = default;
    Date(time_t objTime);  // Date in time_t format
    Date(const char* objTime);
    ~Date(){}

    // Getters
    time_t getDate(){ return date; }
    struct tm* getDateTM(){ return localtime(&date); }

    // Operator Overloads
    friend std::ostream& operator << (std::ostream& out, Date& obj);
};

#endif // DATE_H
