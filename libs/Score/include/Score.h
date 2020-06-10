#ifndef SCORE_H
#define SCORE_H

#include "Date.h"

const int SizeOfName = 16;
const int SizeOfDate = 13;
const int SizeOfScore = 10;

class Score{
    char name[16];
    int score;
    Date date;

public:
    // Constructors and Destructors
    Score();
    Score(char* objName, int objScore);
    Score(char* objName, int objScore, char* objDate);
    Score(char* objName, int objScore, time_t objDate);
    ~Score(){}

    // Getters
    char* getName(){ return name; }
    int getScore(){ return score; }
    Date getDate(){ return date; }

    // Operator Overloads
    bool operator < (const Score& scoreObj);
    friend std::ostream& operator << (std::ostream& out, Score& obj);
};

#endif // SCORE_H
