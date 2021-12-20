

#ifndef GAMESDL_MATHEQUATION_H
#define GAMESDL_MATHEQUATION_H

#include <cstring>
#include <string>
#include <sstream>

class MathEquation {
public:
    MathEquation();
    char key_;
    int firstNumber;
    int secondNumber;
    int thirdNumber;
    virtual ~MathEquation();
    const void GetEquation();
    void SetValue(int first, int second, int third){
        firstNumber = first;
        secondNumber = second;
        thirdNumber = third;
    } ;
};


#endif//GAMESDL_MATHEQUATION_H
