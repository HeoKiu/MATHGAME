
#include "MathEquation.h"
#include <cstdlib>
#include <ctime>


MathEquation::MathEquation() {}

MathEquation::~MathEquation() {}

const void MathEquation::getEquation() {
    const int maxBound = 15;
    const int maxDiff = 5;
    srand(time(nullptr));
    int trueOrFalse = rand();
    trueOrFalse = trueOrFalse % 2;
    if (trueOrFalse) {
        this->key_ = 'Y';
    } else {
        this->key_ = 'N';
    }
    int diff;
    diff = rand() % (maxDiff) + 1;
    int plusOrMinus = rand() % (2);
    if (plusOrMinus) {
        plusOrMinus = 1;
    } else {
        plusOrMinus = -1;
    }
    diff *= plusOrMinus;
    this->firstNumber = rand() % (maxBound) + 1;
    this->secondNumber = rand() % (maxBound) + 1;
    if (trueOrFalse) {
        this->thirdNumber = this->firstNumber + this->secondNumber;
    } else {
        this->thirdNumber = this->firstNumber + this->secondNumber + diff;
        if (this->thirdNumber < 0) {
            this->thirdNumber = -this->thirdNumber;
        } else if (this->thirdNumber == this->firstNumber + this->secondNumber) {
            this->thirdNumber += 3;
        }
    }
}