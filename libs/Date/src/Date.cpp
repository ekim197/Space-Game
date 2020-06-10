#include "Date.h"
#include <cstring>
#include <cstdlib>

// Constructors and Destructor
Date::Date(){
    time(&date);
}

Date::Date(time_t timeArg){
    date = timeArg;
}

Date::Date(const char* timeChar){
    if(timeChar[2] == '/' || timeChar[2] == '-')    date = slashDashToTime(timeChar);
    else                                            date = monthToTime(timeChar);
}

// Private Functions
time_t Date::slashDashToTime(const char* timeChar){
    char* timeCopy;
    char* token;
    struct tm tmDate;

    timeCopy = new char [15];
    memset(timeCopy, '\0', 15);

    strcpy(timeCopy, timeChar);

    token = strtok(timeCopy, "-/");
    tmDate.tm_mon = atoi(token) - 1;
    token = strtok(NULL, "-/");
    tmDate.tm_mday = atoi(token);
    token = strtok(NULL, "-/");
    tmDate.tm_year = atoi(token) + 2000 - 1900;
    tmDate.tm_hour = 0;
    tmDate.tm_min = 0;
    tmDate.tm_sec = 0;
    tmDate.tm_isdst = -1;

    delete[] timeCopy;
    timeCopy = nullptr;

    return mktime(&tmDate);
}

time_t Date::monthToTime(const char* timeChar){
    char* timeCopy;
    char* token;
    struct tm tmDate;

    timeCopy = new char [15];
    token = new char [5];
    memset(timeCopy, '\0', 15);

    strcpy(timeCopy, timeChar);

    memset(token, '\0', 5);
    for(int i = 0; i < 2; i++) token[i] = timeCopy[i];
    tmDate.tm_mday = atoi(token);

    memset(token, '\0', 5);
    for(int i = 2; i < 5; i++) token[i-2] = timeCopy[i];
    tmDate.tm_mon = monthToInt(token);

    memset(token, '\0', 5);
    for(int i = 5; i < 7; i++) token[i-5] = timeCopy[i];
    tmDate.tm_year = atoi(token) + 2000 - 1900;
    tmDate.tm_hour = 0;
    tmDate.tm_min = 0;
    tmDate.tm_sec = 0;
    tmDate.tm_isdst = -1;

    delete[] timeCopy;
    timeCopy = nullptr;

    return mktime(&tmDate);
}

int Date::monthToInt(const char* monthName){
    if(strcmp(monthName, "Jan") == 0)      return 0;
    else if(strcmp(monthName, "Feb") == 0) return 1;
    else if(strcmp(monthName, "Mar") == 0) return 2;
    else if(strcmp(monthName, "Apr") == 0) return 3;
    else if(strcmp(monthName, "May") == 0) return 4;
    else if(strcmp(monthName, "Jun") == 0) return 5;
    else if(strcmp(monthName, "Jul") == 0) return 6;
    else if(strcmp(monthName, "Aug") == 0) return 7;
    else if(strcmp(monthName, "Sep") == 0) return 8;
    else if(strcmp(monthName, "Oct") == 0) return 9;
    else if(strcmp(monthName, "Nov") == 0) return 10;
    else                                   return 11;
}

// Operator Overload
std::ostream& operator << (std::ostream& out, Date& obj){
    if(obj.getDateTM()->tm_mon + 1 < 10) out << '0';
    out << obj.getDateTM()->tm_mon + 1 << '/';

    if(obj.getDateTM()->tm_mday < 10) out << '0';
    out << obj.getDateTM()->tm_mday << '/';

    if(obj.getDateTM()->tm_year - 100 < 10) out << '0';
    out << obj.getDateTM()->tm_year - 100 << "\n";

    return out;
}
