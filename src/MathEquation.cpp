
#include "../include/MathEquation.h"
#include <cstdlib>
#include <ctime>

MathEquation::MathEquation() {}

MathEquation::~MathEquation() {}


const void MathEquation::getEquation() {
    const int max_bound = 10;
    const int max_diff = 3;
    srand(time(nullptr));
    int true_or_false = rand();
    true_or_false = true_or_false % 2;
    if (true_or_false == 1) {
        this->key_ = 'Y';
    } else {
        this->key_ = 'N';
    }
    int diff;
    diff = rand() % (max_diff) + 1;
    int plus_or_minus = rand() % (2);
    if (plus_or_minus == 1) {
        plus_or_minus = 1;
    } else {
        plus_or_minus = -1;
    }
    diff *= plus_or_minus;
    this->firstNumber = rand() % (max_bound) + 1;
    this->secondNumber = rand() % (max_bound) + 1;
    if (true_or_false == 1) {
        this->thirdNumber = this->firstNumber + this->secondNumber;
    } else {
        this->thirdNumber = this->firstNumber + this->secondNumber + diff;
        if (this->thirdNumber < 0) {
            this->thirdNumber = -this->thirdNumber;
        } else if (this->thirdNumber == this->firstNumber + this->secondNumber) {
            this->thirdNumber += (rand() % max_diff);
        }
    }
}
