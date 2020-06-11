#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <cstring>
#include "Score.h"
#include "Date.h"

// Constructors and Destructor
Score::Score(){
    memset(name, '\0', sizeof(name));
    score = 0;
    date = Date();
}

Score::Score(char* objName, int objScore){
    strcpy(name, objName);
    score = objScore;
    date = Date();
}

Score::Score(char* objName, int objScore, char* objDate){
    strcpy(name, objName);
    score = objScore;
    date = Date(objDate);
}

Score::Score(char* objName, int objScore, time_t objDate){
	#define _CRT_SECURE_NO_WARNINGS
    strcpy(name, objName);
    score = objScore;
    date = Date(objDate);
}

// Operator Overloads
bool Score::operator < (const Score& objScore){
    if(score <= objScore.score) return true;
    return false;
}

std::ostream& operator << (std::ostream& out, Score& obj){
    Date date(obj.getDate());
    out << std::setfill('_') << std::setw(19) << std::left << obj.getName()
        << std::setfill('_') << std::setw(SizeOfScore) << std::left << obj.getScore()
        << date;
    return out;
}
