
#include "MathEquation.h"
#include <cstdlib>
#include <ctime>


MathEquation::MathEquation(){}

MathEquation::~MathEquation(){}

void MathEquation::getEquation(int level)
{
    srand(time(nullptr));
    int trueOrFalse = rand();
    trueOrFalse = trueOrFalse % 2;
    if (trueOrFalse) this->key_ = 'Y';
    else this->key_ = 'N';
    int maxBound;
    if (level == 1) maxBound = 5;
    if (level == 2) maxBound = 10;
    if (level == 3) maxBound = 20;
    int diff;
    int const maxDiff = 5;
    diff = rand()%(maxDiff) + 1;
    int plusOrMinus = rand()%(2);
    if (plusOrMinus) plusOrMinus = 1;
    else plusOrMinus = -1;
    diff *= plusOrMinus;
    this->first_number_ = rand()%(maxBound) + 1;
    this->second_number_ = rand()%(maxBound) + 1;
    if (trueOrFalse){
        diff = 0;
        this->third_number_ = this->first_number_ + this->second_number_;
    }
    else{
        this->third_number_ = this->first_number_ + this->second_number_ + diff;
        if (this->third_number_ < 0) this->third_number_ = -this->third_number_;
        if (this->third_number_ == this->first_number_ + this->second_number_) this->third_number_ += 3;
    }
}