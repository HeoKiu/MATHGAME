

#ifndef GAMESDL_MATHEQUATION_H
#define GAMESDL_MATHEQUATION_H

#include <cstring>

class MathEquation {
public:
    MathEquation();
    char key_;
    int first_number_;
    int second_number_;
    int third_number_;
    virtual ~MathEquation();
    void getEquation(int level);
};


#endif//GAMESDL_MATHEQUATION_H
